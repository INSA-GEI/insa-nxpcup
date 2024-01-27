/*
 * vl53l4cd_class.cpp
 *
 *  Created on: 24 janv. 2024
 *      Author: antoi
 */

#include "vl53l4cd_class.h"

lpi2c_master_handle_t g_m_handle;

volatile bool completionFlag = false;
volatile bool nakFlag        = false;




VL53L4CD::VL53L4CD(LPI2C_Type * lidar_i2c, GPIO_Type * xshut, uint32_t xshut_pin_mask, uint16_t addr)
{
	this->lidar_i2c = lidar_i2c;
	this->xshut = xshut;
	this->xshut_pin_mask = xshut_pin_mask;
	this->addr = addr;

	this->sensor_id = 0;


	this->CreateHandle();
	this->Off();
}
/**
 * @brief Effectue une mesure avec le capteur LIDAR.
 * Attend la disponibilité des nouvelles données et récupère le résultat.
 * Lance une exception en cas d'échec de la mesure.
 */
void VL53L4CD::Measure(void)
{
  uint8_t NewDataReady = 0;
  uint8_t status;

  do {
    status = this->CheckForDataReady(&NewDataReady);
  } while (!NewDataReady);

  if ((!status) && (NewDataReady != 0)) {
    this->ClearInterrupt();
    this->GetResult(&(this->results));
  }
}

/**
 * @brief Récupère la distance mesurée par le capteur LIDAR.
 * Ajuste la valeur pour assurer qu'elle est dans une plage valide.
 * @return La distance mesurée en millimètres.
 */
uint16_t VL53L4CD::getDistance(void)
{
  return this->results.distance_mm;
}
VL53L4CD_Error VL53L4CD::CheckSensor(void)
{
	VL53L4CD_Error result = this->GetSensorId(&(this->sensor_id));
	/* Check if there is a VL53L4CD sensor connected */
	if(result || (this->sensor_id != DEFAULT_VL53L4CD_ID))
	{
		printf("VL53L4CD not detected at requested address\n");
		return VL53L4CD_ERROR_XTALK_FAILED;
	}
	printf("VL53L4CD detected at requested address\n");
	return VL53L4CD_ERROR_NONE;
}
VL53L4CD_Error VL53L4CD::Init(void)
{
	this->Off();
	this->On();
	this->CheckSensor();
	VL53L4CD_Error result = this->SensorInit();
	if(result)
	{
		printf("VL53L4CD ULD Loading failed\n");
		return(result);
	}

	printf("VL53L4CD ULD ready !\n");
	return(result);
}


VL53L4CD_Error VL53L4CD::GetSWVersion(
  VL53L4CD_Version_t *p_Version)
{
  VL53L4CD_Error Status = VL53L4CD_ERROR_NONE;

  p_Version->major = VL53L4CD_IMPLEMENTATION_VER_MAJOR;
  p_Version->minor = VL53L4CD_IMPLEMENTATION_VER_MINOR;
  p_Version->build = VL53L4CD_IMPLEMENTATION_VER_BUILD;
  p_Version->revision = VL53L4CD_IMPLEMENTATION_VER_REVISION;
  return Status;
}

VL53L4CD_Error VL53L4CD::SetI2CAddress(
  uint8_t new_address)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrByte(VL53L4CD_I2C_SLAVE_DEVICE_ADDRESS,
                            (uint8_t)(new_address >> (uint8_t)1));

  this->addr = new_address;
  return status;
}

VL53L4CD_Error VL53L4CD::GetSensorId(
  uint16_t *p_id)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->RdWord(VL53L4CD_IDENTIFICATION_MODEL_ID, p_id);
  return status;
}

VL53L4CD_Error VL53L4CD::SensorInit()
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint8_t Addr, tmp;
  uint8_t continue_loop = 1;
  uint16_t i = 0;

  do {
    status |= this->RdByte(
                              VL53L4CD_FIRMWARE_SYSTEM_STATUS, &tmp);

    if (tmp == (uint8_t)0x3) { /* Sensor booted */
      continue_loop = (uint8_t)0;
    } else if (i < (uint16_t)1000) {  /* Wait for boot */
      i++;
    } else { /* Timeout 1000ms reached */
      continue_loop = (uint8_t)0;
      status |= (uint8_t)VL53L4CD_ERROR_TIMEOUT;
    }
    WaitMs(1);
  } while (continue_loop == (uint8_t)1);

  /* Load default configuration */
  for (Addr = (uint8_t)0x2D; Addr <= (uint8_t)0x87; Addr++) {
    status |= this->WrByte( Addr,
                              VL53L4CD_DEFAULT_CONFIGURATION[
                             Addr - (uint8_t)0x2D]);
  }

  /* Start VHV */
  status |= this->WrByte( VL53L4CD_SYSTEM_START, (uint8_t)0x40);
  i  = (uint8_t)0;
  continue_loop = (uint8_t)1;
  do {
    status |= this->CheckForDataReady(&tmp);
    if (tmp == (uint8_t)1) { /* Data ready */
      continue_loop = (uint8_t)0;
    } else if (i < (uint16_t)1000) {  /* Wait for answer */
      i++;
    } else { /* Timeout 1000ms reached */
      continue_loop = (uint8_t)0;
      status |= (uint8_t)VL53L4CD_ERROR_TIMEOUT;
    }
    WaitMs(1);
  } while (continue_loop == (uint8_t)1);

  status |= this->ClearInterrupt();
  status |= this->StopRanging();
  status |= this->WrByte(
                            VL53L4CD_VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND,
                            (uint8_t)0x09);
  status |= this->WrByte( 0x0B, (uint8_t)0);
  status |= this->WrWord( 0x0024, 0x500);

  status |= this->SetRangeTiming(50, 0);

  return status;
}

VL53L4CD_Error VL53L4CD::ClearInterrupt()
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrByte( VL53L4CD_SYSTEM_INTERRUPT_CLEAR, 0x01);
  return status;
}

VL53L4CD_Error VL53L4CD::StartRanging()
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint8_t data_ready, continue_loop = 1;
  uint16_t i = 0;
  uint32_t tmp;

  status |= this->RdDWord( VL53L4CD_INTERMEASUREMENT_MS, &tmp);

  /* Sensor runs in continuous mode */
  if (tmp == (uint32_t)0) {
    status |= this->WrByte( VL53L4CD_SYSTEM_START, 0x21);
  }
  /* Sensor runs in autonomous mode */
  else {
    status |= this->WrByte( VL53L4CD_SYSTEM_START, 0x40);
  }

  do {
    status |= this->CheckForDataReady(&data_ready);
    if (data_ready == (uint8_t)1) { /* Data ready */
      continue_loop = (uint8_t)0;
    } else if (i < (uint16_t)1000) {  /* Wait for answer */
      i++;
    } else { /* Timeout 1000ms reached */
      continue_loop = (uint8_t)0;
      status = (uint8_t)VL53L4CD_ERROR_TIMEOUT;
    }
    WaitMs(1);
  } while (continue_loop == (uint8_t)1);

  status |= this->ClearInterrupt();

  return status;
}

VL53L4CD_Error VL53L4CD::StopRanging()
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrByte( VL53L4CD_SYSTEM_START, 0x00);
  return status;
}

VL53L4CD_Error VL53L4CD::CheckForDataReady(
  uint8_t *p_is_data_ready)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint8_t temp;
  uint8_t int_pol;

  status |= this->RdByte( VL53L4CD_GPIO_HV_MUX_CTRL, &temp);
  temp = temp & (uint8_t)0x10;
  temp = temp >> 4;

  if (temp == (uint8_t)1) {
    int_pol = (uint8_t)0;
  } else {
    int_pol = (uint8_t)1;
  }

  status |= this->RdByte( VL53L4CD_GPIO_TIO_HV_STATUS, &temp);

  if ((temp & (uint8_t)1) == int_pol) {
    *p_is_data_ready = (uint8_t)1;
  } else {
    *p_is_data_ready = (uint8_t)0;
  }

  return status;
}

VL53L4CD_Error VL53L4CD::SetRangeTiming(
  uint32_t timing_budget_ms,
  uint32_t inter_measurement_ms)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint16_t clock_pll, osc_frequency, ms_byte;
  uint32_t macro_period_us = 0, timing_budget_us = 0, ls_byte, tmp;
  float inter_measurement_factor = (float)1.055;

  status |= this->RdWord( 0x0006, &osc_frequency);
  if (osc_frequency != (uint16_t)0) {
    timing_budget_us = timing_budget_ms * (uint32_t)1000;
    macro_period_us = (uint32_t)((uint32_t)2304 *
                                 ((uint32_t)0x40000000 / (uint32_t)osc_frequency)) >> 6;
  } else {
    status |= (uint8_t)VL53L4CD_ERROR_INVALID_ARGUMENT;
  }

  /* Timing budget check validity */
  if ((timing_budget_ms < (uint32_t)10)
      || (timing_budget_ms > (uint32_t)200) || (status != (uint8_t)0)) {
    status |= VL53L4CD_ERROR_INVALID_ARGUMENT;
  }
  /* Sensor runs in continuous mode */
  else if (inter_measurement_ms == (uint32_t)0) {
    status |= this->WrDWord( VL53L4CD_INTERMEASUREMENT_MS, 0);
    timing_budget_us -= (uint32_t)2500;
  }
  /* Sensor runs in autonomous low power mode */
  else if (inter_measurement_ms > timing_budget_ms) {
    status |= this->RdWord(
                              VL53L4CD_RESULT_OSC_CALIBRATE_VAL, &clock_pll);
    clock_pll = clock_pll & (uint16_t)0x3FF;
    inter_measurement_factor = inter_measurement_factor
                               * (float)inter_measurement_ms
                               * (float)clock_pll;
    status |= this->WrDWord( VL53L4CD_INTERMEASUREMENT_MS,
                               (uint32_t)inter_measurement_factor);

    timing_budget_us -= (uint32_t)4300;
    timing_budget_us /= (uint32_t)2;

  }
  /* Invalid case */
  else {
    status |= (uint8_t)VL53L4CD_ERROR_INVALID_ARGUMENT;
  }

  if (status != (uint8_t)VL53L4CD_ERROR_INVALID_ARGUMENT) {
    ms_byte = 0;
    timing_budget_us = timing_budget_us << 12;
    tmp = macro_period_us * (uint32_t)16;
    ls_byte = ((timing_budget_us + ((tmp >> 6) >> 1)) / (tmp >> 6))
              - (uint32_t)1;

    while ((ls_byte & 0xFFFFFF00U) > 0U) {
      ls_byte = ls_byte >> 1;
      ms_byte++;
    }
    ms_byte = (uint16_t)(ms_byte << 8)
              + (uint16_t)(ls_byte & (uint32_t)0xFF);
    status |= this->WrWord( VL53L4CD_RANGE_CONFIG_A, ms_byte);

    ms_byte = 0;
    tmp = macro_period_us * (uint32_t)12;
    ls_byte = ((timing_budget_us + ((tmp >> 6) >> 1)) / (tmp >> 6))
              - (uint32_t)1;

    while ((ls_byte & 0xFFFFFF00U) > 0U) {
      ls_byte = ls_byte >> 1;
      ms_byte++;
    }
    ms_byte = (uint16_t)(ms_byte << 8)
              + (uint16_t)(ls_byte & (uint32_t)0xFF);
    status |= this->WrWord( VL53L4CD_RANGE_CONFIG_B, ms_byte);
  }

  return status;
}

VL53L4CD_Error VL53L4CD::GetRangeTiming(
  uint32_t *p_timing_budget_ms,
  uint32_t *p_inter_measurement_ms)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint16_t osc_frequency = 1, range_config_macrop_high, clock_pll = 1;
  uint32_t tmp, ls_byte, ms_byte, macro_period_us;
  float clock_pll_factor = (float)1.065;

  /* Get InterMeasurement */
  status |= this->RdDWord( VL53L4CD_INTERMEASUREMENT_MS, &tmp);
  status |= this->RdWord(
                            VL53L4CD_RESULT_OSC_CALIBRATE_VAL, &clock_pll);
  clock_pll = clock_pll & (uint16_t)0x3FF;
  clock_pll_factor = clock_pll_factor * (float)clock_pll;
  clock_pll = (uint16_t)clock_pll_factor;
  *p_inter_measurement_ms = (uint16_t)(tmp / (uint32_t)clock_pll);

  /* Get TimingBudget */
  status |= this->RdWord( 0x0006, &osc_frequency);
  status |= this->RdWord( VL53L4CD_RANGE_CONFIG_A,
                            &range_config_macrop_high);

  macro_period_us = (uint32_t)((uint32_t)2304 * ((uint32_t)0x40000000
                                                 / (uint32_t)osc_frequency)) >> 6;
  ls_byte = (range_config_macrop_high & (uint32_t)0x00FF) << 4;
  ms_byte = (range_config_macrop_high & (uint32_t)0xFF00) >> 8;
  ms_byte = (uint32_t)0x04 - (ms_byte - (uint32_t)1) - (uint32_t)1;

  macro_period_us = macro_period_us * (uint32_t)16;
  *p_timing_budget_ms = (((ls_byte + (uint32_t)1) * (macro_period_us >> 6))
                         - ((macro_period_us >> 6) >> 1)) >> 12;

  if (ms_byte < (uint8_t)12) {
    *p_timing_budget_ms = (uint32_t)(*p_timing_budget_ms
                                     >> (uint8_t)ms_byte);
  }

  /* Mode continuous */
  if (tmp == (uint32_t)0) {
    *p_timing_budget_ms += (uint32_t)2500;
  }
  /* Mode autonomous */
  else {
    *p_timing_budget_ms *= (uint32_t)2;
    *p_timing_budget_ms += (uint32_t)4300;
  }

  *p_timing_budget_ms = *p_timing_budget_ms / (uint32_t)1000;

  return status;
}

VL53L4CD_Error VL53L4CD::GetResult(
  VL53L4CD_ResultsData_t *p_result)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint16_t temp_16;
  uint8_t temp_8;
  uint8_t status_rtn[24] = { 255, 255, 255, 5, 2, 4, 1, 7, 3,
                             0, 255, 255, 9, 13, 255, 255, 255, 255, 10, 6,
                             255, 255, 11, 12
                           };

  status |= this->RdByte( VL53L4CD_RESULT_RANGE_STATUS,
                            &temp_8);
  temp_8 = temp_8 & (uint8_t)0x1F;
  if (temp_8 < (uint8_t)24) {
    temp_8 = status_rtn[temp_8];
  }
  p_result->range_status = temp_8;

  status |= this->RdWord( VL53L4CD_RESULT_SPAD_NB,
                            &temp_16);
  p_result->number_of_spad = temp_16 / (uint16_t) 256;

  status |= this->RdWord( VL53L4CD_RESULT_SIGNAL_RATE,
                            &temp_16);
  p_result->signal_rate_kcps = temp_16 * (uint16_t) 8;

  status |= this->RdWord( VL53L4CD_RESULT_AMBIENT_RATE,
                            &temp_16);
  p_result->ambient_rate_kcps = temp_16 * (uint16_t) 8;

  status |= this->RdWord( VL53L4CD_RESULT_SIGMA,
                            &temp_16);
  p_result->sigma_mm = temp_16 / (uint16_t) 4;

  status |= this->RdWord( VL53L4CD_RESULT_DISTANCE,
                            &temp_16);
  p_result->distance_mm = temp_16;

  p_result->signal_per_spad_kcps = p_result->signal_rate_kcps
                                   / p_result->number_of_spad;
  p_result->ambient_per_spad_kcps = p_result->ambient_rate_kcps
                                    / p_result->number_of_spad;

  return status;
}

VL53L4CD_Error VL53L4CD::SetOffset(
  int16_t OffsetValueInMm)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint16_t temp;

  temp = (uint16_t)((uint16_t)OffsetValueInMm * (uint16_t)4);

  status |= this->WrWord( VL53L4CD_RANGE_OFFSET_MM, temp);
  status |= this->WrWord( VL53L4CD_INNER_OFFSET_MM, (uint8_t)0x0);
  status |= this->WrWord( VL53L4CD_OUTER_OFFSET_MM, (uint8_t)0x0);
  return status;
}

VL53L4CD_Error  VL53L4CD::GetOffset(
  int16_t *p_offset)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint16_t temp;

  status |= this->RdWord( VL53L4CD_RANGE_OFFSET_MM, &temp);

  temp = temp << 3;
  temp = temp >> 5;
  *p_offset = (int16_t)(temp);

  if (*p_offset > 1024) {
    *p_offset = *p_offset - 2048;
  }

  return status;
}

VL53L4CD_Error VL53L4CD::SetXtalk(
  uint16_t XtalkValueKcps)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrWord(
                            VL53L4CD_XTALK_X_PLANE_GRADIENT_KCPS, 0x0000);
  status |= this->WrWord(
                            VL53L4CD_XTALK_Y_PLANE_GRADIENT_KCPS, 0x0000);
  status |= this->WrWord(
                            VL53L4CD_XTALK_PLANE_OFFSET_KCPS,
                            (XtalkValueKcps << 9) / (uint16_t)1000);

  return status;
}

VL53L4CD_Error VL53L4CD::GetXtalk(
  uint16_t *p_xtalk_kcps)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->RdWord(
                            VL53L4CD_XTALK_PLANE_OFFSET_KCPS, p_xtalk_kcps);
  *p_xtalk_kcps = (uint16_t)(*p_xtalk_kcps * (uint16_t)1000) >> 9;

  return status;
}

VL53L4CD_Error VL53L4CD::SetDetectionThresholds(
  uint16_t distance_low_mm,
  uint16_t distance_high_mm,
  uint8_t window)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrByte( VL53L4CD_SYSTEM_INTERRUPT, window);
  status |= this->WrWord( VL53L4CD_THRESH_HIGH, distance_high_mm);
  status |= this->WrWord( VL53L4CD_THRESH_LOW, distance_low_mm);
  return status;
}

VL53L4CD_Error VL53L4CD::GetDetectionThresholds(
  uint16_t *p_distance_low_mm,
  uint16_t *p_distance_high_mm,
  uint8_t *p_window)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->RdWord( VL53L4CD_THRESH_HIGH, p_distance_high_mm);
  status |= this->RdWord( VL53L4CD_THRESH_LOW, p_distance_low_mm);
  status |= this->RdByte( VL53L4CD_SYSTEM_INTERRUPT, p_window);
  *p_window = (*p_window & (uint8_t)0x7);

  return status;
}

VL53L4CD_Error VL53L4CD::SetSignalThreshold(
  uint16_t signal_kcps)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrWord(
                            VL53L4CD_MIN_COUNT_RATE_RTN_LIMIT_MCPS, signal_kcps >> 3);
  return status;
}

VL53L4CD_Error VL53L4CD::GetSignalThreshold(
  uint16_t  *p_signal_kcps)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint16_t tmp = 0;

  status |= this->RdWord(
                            VL53L4CD_MIN_COUNT_RATE_RTN_LIMIT_MCPS, &tmp);
  *p_signal_kcps = tmp << 3;

  return status;
}

VL53L4CD_Error VL53L4CD::SetSigmaThreshold(
  uint16_t  sigma_mm)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  if (sigma_mm > (uint16_t)((uint16_t)0xFFFF >> 2)) {
    status |= (uint8_t)VL53L4CD_ERROR_INVALID_ARGUMENT;
  } else {
    status |= this->WrWord(
                              VL53L4CD_RANGE_CONFIG_SIGMA_THRESH, sigma_mm << 2);
  }

  return status;
}

VL53L4CD_Error VL53L4CD::GetSigmaThreshold(
  uint16_t  *p_sigma_mm)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status += this->RdWord(
                            VL53L4CD_RANGE_CONFIG_SIGMA_THRESH, p_sigma_mm);
  *p_sigma_mm = *p_sigma_mm >> 2;

  return status;
}

VL53L4CD_Error VL53L4CD::StartTemperatureUpdate()
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint8_t tmp = 0, continue_loop = 1;
  uint16_t i = 0;

  status |= this->WrByte(
                            VL53L4CD_VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND, (uint8_t)0x81);
  status |= this->WrByte( 0x0B, (uint8_t)0x92);
  status |= this->WrByte( VL53L4CD_SYSTEM_START, (uint8_t)0x40);

  do {
    status |= this->CheckForDataReady(&tmp);
    if (tmp == (uint8_t)1) { /* Data ready */
      continue_loop = (uint8_t)0;
    } else if (i < (uint16_t)1000) {  /* Wait for answer */
      i++;
    } else { /* Timeout 1000ms reached */
      continue_loop = (uint8_t)0;
      status = (uint8_t)VL53L4CD_ERROR_TIMEOUT;
    }
    WaitMs(1);
  } while (continue_loop == (uint8_t)1);

  status |= this->ClearInterrupt();
  status |= this->StopRanging();

  status += this->WrByte(
                            VL53L4CD_VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND, 0x09);
  status += this->WrByte( 0x0B, 0);
  return status;
}

void lpi2c_master_callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        completionFlag = true;
    }
    /* Signal transfer success when received success status. */
    if (status == kStatus_LPI2C_Nak)
    {
        nakFlag = true;
    }
}

void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < I2C_RELEASE_BUS_COUNT; i++)
    {
        __NOP();
    }
}
void VL53L4CD::CreateHandle(void)
{

	/*LPI2C_MasterEnable(this->lidar_i2c, true);*/
	LPI2C_MasterTransferCreateHandle(this->lidar_i2c, &g_m_handle, lpi2c_master_callback, NULL);
}



void VL53L4CD::On(void)
{
	GPIO_PortSet(this->xshut, this->xshut_pin_mask) ;
	i2c_release_bus_delay();
}

    /**
     * @brief       PowerOff the sensor
     * @return      void
     */
void VL53L4CD::Off(void)
{
	GPIO_PortClear(this->xshut, this->xshut_pin_mask) ;
	i2c_release_bus_delay();
}

uint8_t VL53L4CD::RdDWord(uint16_t RegisterAdress, uint32_t *value)
{
	uint8_t status = 0;
	 uint8_t buffer[4] = {0, 0, 0, 0};

	  status = this->I2CSend(RegisterAdress, buffer, 4,'r');
	  if (!status) {
	    *value = ((uint32_t)buffer[0] << 24) + ((uint32_t)buffer[1] << 16) + ((uint32_t)buffer[2] << 8) + (uint32_t)buffer[3];
	  }
	  return status;
}

uint8_t VL53L4CD::RdWord(uint16_t RegisterAdress, uint16_t *value)
{
	uint8_t status = 0;
	  uint8_t buffer[2] = {0, 0};

	  status = this->I2CSend(RegisterAdress, buffer, 2,'r');
	  if (!status) {
	    *value = (buffer[0] << 8) + buffer[1];
	  }
	  return status;
}

uint8_t VL53L4CD::RdByte(uint16_t RegisterAdress, uint8_t *value)
{
	uint8_t status = 0;
		  uint8_t buffer[1] = {0};

		  status = this->I2CSend(RegisterAdress, buffer, 1,'r');
		  if (!status) {
		    *value = buffer[0];
		  }
	  return status;
}
uint8_t  VL53L4CD::I2CSend(uint16_t RegisterAddress, uint8_t *buff, uint32_t size, char rw)
{
	lpi2c_master_transfer_t masterXfer;
	status_t reVal = kStatus_Fail;
	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress   = (uint8_t)((this->addr >> 1) & 0x7F);
	masterXfer.direction      = (rw == 'r') ? kLPI2C_Read : kLPI2C_Write;
	masterXfer.subaddress     = RegisterAddress;
	masterXfer.subaddressSize = 2;
	masterXfer.data           = buff;
	masterXfer.dataSize       = size;
	masterXfer.flags          = (rw == 'r') ? kLPI2C_TransferNoStopFlag : kLPI2C_TransferDefaultFlag;

	/*  direction=write : start+device_write;cmdbuff;xBuff; */
	/*  direction=recive : start+device_write;cmdbuff;repeatStart+device_read;xBuff; */

	reVal = LPI2C_MasterTransferNonBlocking(this->lidar_i2c, &g_m_handle, &masterXfer);
	if (reVal != kStatus_Success)
	{
		return 255;
	}
	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag))
	{
	}

	nakFlag = false;

	if (completionFlag == true)
	{
		completionFlag = false;
		return 0;
	}
	else
	{
		return 255;
	}
}




uint8_t VL53L4CD::WrByte( uint16_t RegisterAdress, uint8_t value)
{
	uint8_t status = 0;
	status =this->I2CSend(RegisterAdress, &value, 1,'w');
	return status;
}

uint8_t VL53L4CD::WrWord(uint16_t RegisterAdress, uint16_t value)
{
	uint8_t status = 0;
	uint8_t buffer[2];
	buffer[0] = value >> 8;
	buffer[1] = value & 0x00FF;
	status = this->I2CSend(RegisterAdress, (uint8_t *)buffer, 2,'w');
	return status;
}

uint8_t VL53L4CD::WrDWord(uint16_t RegisterAdress, uint32_t value)
{
	uint8_t status = 0;
	uint8_t buffer[4];

	buffer[0] = (value >> 24) & 0xFF;
	buffer[1] = (value >> 16) & 0xFF;
	buffer[2] = (value >>  8) & 0xFF;
	buffer[3] = (value >>  0) & 0xFF;
	status = this->I2CSend(RegisterAdress, (uint8_t *)buffer, 4,'w');
	return status;
}

void VL53L4CD::WaitMs(uint32_t TimeMs)
{
	/* Il serait bien de mettre un vrai delay() */
	delayMillis(TimeMs);
}
