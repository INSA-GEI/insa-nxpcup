/*
 * vl53l4cd_class.cpp
 *
 *  Created on: 21 mars 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#include <lidar/vl53l4cd_class.hpp>

#define DEFAULT_OFFSET 			-18

i2c_master_handle_t g_m_handle;

volatile bool completionFlag = false;
volatile bool nakFlag = false;


VL53L4CD::VL53L4CD(int num)
{
	this->num = num;
	if(this->num == 1)
	{
		this->lidar_i2c = LIDAR1_I2C;
	}
	else if(this->num == 2)
	{
		this->lidar_i2c = LIDAR2_I2C;
	}

	this->addr = DEFAULT_VL53L4CD_ADDRESS;
	this->sensor_id = DEFAULT_VL53L4CD_ID;
	this->CreateHandle();
}

VL53L4CD::~VL53L4CD(void)
{
	this->StopRanging();
}


uint16_t VL53L4CD::getDistance(void)
{
	uint8_t NewDataReady = 0;
	uint8_t status;

	this->StartRanging();
	do {
		status = this->CheckForDataReady(&NewDataReady);
	  } while (!NewDataReady);

	  if ((!status) && (NewDataReady != 0)) {
		this->GetResult(&(this->results));
		// (Mandatory) Clear HW interrupt to restart measurements
		this->ClearInterrupt();
	}

	return this->results.distance_mm;
}


VL53L4CD_Error VL53L4CD::CheckSensor(void)
{
	VL53L4CD_Error result = this->GetSensorId(&(this->sensor_id));
	/* Check if there is a VL53L4CD sensor connected */
	if(result || (this->sensor_id != DEFAULT_VL53L4CD_ID))
	{
		PRINTF("VL53L4CD not detected at requested address\n");
		return VL53L4CD_ERROR_XTALK_FAILED;
	}
	PRINTF("VL53L4CD detected at requested address\n");
	return VL53L4CD_ERROR_NONE;
}

VL53L4CD_Error VL53L4CD::Init(void)
{
	this->I2C_Init();
	this->CheckSensor();
	VL53L4CD_Error result = this->SensorInit();
	this->SetOffset(DEFAULT_OFFSET);
	if(result)
	{
		PRINTF("VL53L4CD ULD Loading failed\n");
		return(result);
	}
	PRINTF("VL53L4CD ULD ready !\n");
	return(result);
}

void VL53L4CD::I2C_Init(void)
{
	gpio_pin_config_t config_output_gpio = {kGPIO_DigitalOutput, 0};
    i2c_master_config_t i2cConfig;
    I2C_MasterGetDefaultConfig(&i2cConfig);
    i2cConfig.baudRate_Bps = 100000; // Set desired baud rate

	if(this->num == 1)
	{
		CLOCK_EnableClock(kCLOCK_PortE); // enable clock for PORTE
		PORT_SetPinMux(LIDAR1_PORT, LIDAR1_SCL_PIN, kPORT_MuxAlt6);
		PORT_SetPinMux(LIDAR1_PORT, LIDAR1_SDA_PIN, kPORT_MuxAlt6);
		GPIO_PinInit(LIDAR1_GPIO,LIDAR1_SCL_PIN,&config_output_gpio);
		GPIO_PinInit(LIDAR1_GPIO,LIDAR1_SDA_PIN,&config_output_gpio);
	    I2C_MasterInit(LIDAR1_I2C, &i2cConfig, CLOCK_GetFreq(I2C1_CLK_SRC));
	    I2C_Enable(LIDAR1_I2C,true);
	}
	else if(this->num == 2)
	{
		CLOCK_EnableClock(kCLOCK_PortB); // enable clock for PORTB
		PORT_SetPinMux(LIDAR2_PORT, LIDAR2_SCL_PIN, kPORT_MuxAlt2);
		PORT_SetPinMux(LIDAR2_PORT, LIDAR2_SDA_PIN, kPORT_MuxAlt2);
		GPIO_PinInit(LIDAR2_GPIO,LIDAR2_SCL_PIN,&config_output_gpio);
		GPIO_PinInit(LIDAR2_GPIO,LIDAR2_SDA_PIN,&config_output_gpio);
	    I2C_MasterInit(LIDAR2_I2C, &i2cConfig, CLOCK_GetFreq(I2C0_CLK_SRC));
	    I2C_Enable(LIDAR2_I2C,true);
	}

}

VL53L4CD_Error VL53L4CD::SetI2CAddress(uint8_t new_address)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrByte(VL53L4CD_I2C_SLAVE_DEVICE_ADDRESS,(uint8_t)(new_address >> (uint8_t)1));

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
  uint8_t Addr, tmp = 0;
  uint8_t continue_loop = 1;
  uint16_t i = 0;

  do {
    status |= this->RdByte(VL53L4CD_FIRMWARE_SYSTEM_STATUS, &tmp);

    if (tmp == (uint8_t)0x3) { /* Sensor booted */
      continue_loop = (uint8_t)0;
    } else if (i < (uint16_t)1000) {  /* Wait for boot */
      i++;
    } else { /* Timeout 1000ms reached */
      continue_loop = (uint8_t)0;
      status |= (uint8_t)VL53L4CD_ERROR_TIMEOUT;
    }
  } while (continue_loop == (uint8_t)1);

  /* Load default configuration */
  for (Addr = (uint8_t)0x2D; Addr <= (uint8_t)0x87; Addr++)
  {
    status |= this->WrByte( Addr,VL53L4CD_DEFAULT_CONFIGURATION[Addr - (uint8_t)0x2D]);
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
  } while (continue_loop == (uint8_t)1);


  status |= this->StopRanging();
  status |= this->WrByte(VL53L4CD_VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND,(uint8_t)0x09);
  status |= this->WrByte( 0x0B, (uint8_t)0);
  status |= this->WrWord( 0x0024, 0x500);

  status |= this->SetRangeTiming(50, 0);

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
  } while (continue_loop == (uint8_t)1);

  // (Mandatory) Clear HW interrupt to restart measurements
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

VL53L4CD_Error VL53L4CD::GetResult(VL53L4CD_ResultsData_t *p_result)
{
  VL53L4CD_Error status = VL53L4CD_ERROR_NONE;
  uint16_t temp_16;
  uint8_t temp_8;
  uint8_t status_rtn[24] = { 255, 255, 255, 5, 2, 4, 1, 7, 3,
                             0, 255, 255, 9, 13, 255, 255, 255, 255, 10, 6,
                             255, 255, 11, 12 };

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


static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{

	/* Signal transfer success when received success status. */
	if (status == kStatus_Success)
	{
		completionFlag = true;
	}
	/* Signal transfer success when received success status. */
	if (status == kStatus_I2C_Nak)
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
	I2C_MasterTransferCreateHandle(this->lidar_i2c, &g_m_handle, i2c_master_callback, NULL);
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
	i2c_master_transfer_t masterXfer;
	status_t reVal = kStatus_Fail;
	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress   = (uint8_t)((this->addr >> 1) & 0x7F);
	masterXfer.direction      = (rw == 'r') ? kI2C_Read : kI2C_Write;
	masterXfer.subaddress     = RegisterAddress;
	masterXfer.subaddressSize = 2;
	masterXfer.data           = buff;
	masterXfer.dataSize       = size;
	masterXfer.flags          = (rw == 'r') ? kI2C_TransferNoStopFlag : kI2C_TransferDefaultFlag;


	reVal = I2C_MasterTransferNonBlocking(this->lidar_i2c, &g_m_handle, &masterXfer);
	if (reVal != kStatus_Success)
	{
		return 255;
	}
	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag))
	{
	}

	if(rw == 'r')
	{
		I2C_MasterStop(this->lidar_i2c);
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


VL53L4CD_Error VL53L4CD::ClearInterrupt()
{
	VL53L4CD_Error status = VL53L4CD_ERROR_NONE;

  status |= this->WrByte(VL53L4CD_SYSTEM_INTERRUPT_CLEAR, 0x01);
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
