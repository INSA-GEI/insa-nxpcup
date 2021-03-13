/*
 * Obstacle_detection.cpp
 *
 *  Created on: Feb 3, 2021
 *      Author: Carole Meyer
 *      
 *  NOTE FOR THE NEXT NXP CUP TEAM:    
 *  The sensor is controlled with the API given by ST, called VL53L1x API. 
 *  Check the documentation on the Git 'documentation' section.
 */

#include "Obstacle_detection.h"
#include <MKL25Z4.h>

// By default, this example blocks while waiting for sensor data to be ready.
// Comment out this line to poll for data ready in a non-blocking way instead.
// Interrupt mode is not implemented but is implementable.
//#define USE_BLOCKING_LOOP

/* Timing budget set through VL53L1_SetMeasurementTimingBudgetMicroSeconds()
* 20 ms is the minimum timing budget and can be used only in Short distance mode.
* 33 ms is the minimum timing budget which can work for all distance modes
* */
#define MEASUREMENT_BUDGET_MS 30

/* Interval between measurements, set through VL53L1_SetInterMeasurementPeriodMilliSeconds()
* According to the API user manual "the minimum inter-measurement period must be longer than the
* timing budget + 4 ms." 
* */
#define INTER_MEASUREMENT_PERIOD_MS 55

/* Predefined I2C address
 * */
#define I2C_ADDR 0x52

/*Variable declaration*/
int status = 0;

/*void Obstacle::Obstacle() {
	devR.Data=;
	devR.I2cDevAddr=0;
	devR.comms_type=0;
	devR.comms_speed_khz=0;
	devR.new_data_ready_poll_duration_ms=0;
	devR.I2cHandle=NULL;
}*/

void Obstacle::setup(VL53L1_DEV Dev){
	
	I2C_clock_init();
	
	/****** RIGHT SENSOR ******/
	/* Port initialization */
	I2C_init_port_right();
	/* Module initialization (as master) */
	I2C_init_master_right();

	uart_write("I2C init done.\n\r",16);
	
	/****** LEFT SENSOR ******/
	/* Port initialization */
	//I2C_init_port_left();
	/* Module initialization (as master) */
	//I2C_init_master_left();
	
	/*** Before initializing the sensor: Performs device software reset ***/
	VL53L1_software_reset(Dev);
	
	/*** System initialization ***/
	status = VL53L1_WaitDeviceBooted(Dev); 	//Wait for device booted
	//As two devices are used: SetDeviceAddress must be called to differentiate them with device address
	status = VL53L1_SetDeviceAddress(Dev, I2C_ADDR);
	status = VL53L1_DataInit(Dev);			//One time device initialization
	status = VL53L1_StaticInit(Dev);		//Basic device init with default settings
	
	/*** Optional functions call ***/
	/* If not working: try using VL53L1_SetPresetMode() and check API config */
	//Distance mode short has max detection distance of 135cm (same in the dark or under ambient light)
	status = VL53L1_SetDistanceMode(Dev, VL53L1_DISTANCEMODE_SHORT);
	//Timing budget is the maximum time allowed to run a full ranging sequence
	status = VL53L1_SetMeasurementTimingBudgetMicroSeconds(Dev, MEASUREMENT_BUDGET_MS * 1000);
	//Interval between measurements
	status = VL53L1_SetInterMeasurementPeriodMilliSeconds(Dev, INTER_MEASUREMENT_PERIOD_MS);
	
	/*** Start Measurement ***/
	status = VL53L1_StartMeasurement(Dev);
	
	if(status){
		uart_write("VL53L1_StartMeasurement failed\n\r",32);
	}
}

void Obstacle::init(void){
	
	uint8_t status = 0;
	
	I2C_clock_init();
	
	/****** RIGHT SENSOR ******/
	/* Port initialization */
	I2C_init_port_right();
	/* Module initialization (as master) */
	I2C_init_master_right();

	uart_write("I2C init done.\n\r",16);
	
	//uart_writeNb((int) I2C1_byte_read(0xFFFFFFFF, &status));
	
	if(status){
		uart_write("VL53L1_StartMeasurement failed\n\r",32);
	}
}

VL53L1_RangingMeasurementData_t & Obstacle::getRange(VL53L1_DEV Dev){
	
	static VL53L1_RangingMeasurementData_t RangingData;
	uint8_t isReady;
	 
	status = VL53L1_GetMeasurementDataReady(Dev, &isReady);
	if (!status){
		if(isReady){
			RangingData = printRangingData(Dev);
		}
		VL53L1_ClearInterruptAndStartMeasurement(Dev);
	}
	else {
		uart_write("Error with VL53L1_GetMeasurementDataReady(..)\n\r",47);
	}
	
  return RangingData;
}

void I2C_init_port_right(void){
	PORTE_PCR0 = PORT_PCR_MUX(6);
	PORTE_PCR1 = PORT_PCR_MUX(6);
}

void I2C_init_port_left(void){
	PORTB_PCR0 = PORT_PCR_MUX(2);
	PORTB_PCR1 = PORT_PCR_MUX(2);
}

void I2C_init_master_right(void){
	// Write: Frequency Divider register to set the I2C baud rate
	I2C1_F &= ~I2C_F_MULT(1); //MULT bits (6-7) = 00 (multiplier factor=1)
	I2C1_F |= I2C_F_ICR(0x20); //12MHz clk is divided by 160 : I2C clk is 75kHz (ICR=0x20)
	// Write: Data register with the address of the target slave (the LSB of this byte
	// determines whether the communication is master receive or transmit)
	I2C1_D = I2C_ADDR;
	// Write: Control Register 1 to enable the I2C module and interrupts
	I2C1_C1 |= I2C_C1_IICEN_MASK; //Enable I2C module operation IICEN
	I2C1_C1 |= I2C_C1_IICIE_MASK; //Enable I2C interrupt requests IICIE
	I2C1_FLT |= I2C_FLT_STOPIE_MASK; //Enable the I2C Bus Stop Interrupt Enable STOPIE
	I2C1_FLT |= I2C_FLT_STOPF_MASK; //Clear the I2C bus stop detect flag STOPF
	I2C1_S |= I2C_S_IICIF_MASK; //Clear the interrupt flag IICIF
	// Initialize RAM variables (IICEN = 1 and IICIE = 1) for transmit data
	// Initialize RAM variables used to achieve the routine shown in the following figure
	// Write: Control Register 1 to enable TX
	I2C1_C1 |= I2C_C1_TX_MASK;
	// Write: Control Register 1 to enable MST (master mode)
	I2C1_C1 |= I2C_C1_MST_MASK;
}

void I2C_init_master_left(void){
	// Write: Frequency Divider register to set the I2C baud rate
	I2C0_F &= ~I2C_F_MULT(1); //MULT bits (6-7) = 00 (multiplier factor=1)
	I2C0_F |= I2C_F_ICR(0x20); //12MHz clk is divided by 160 : I2C clk is 75kHz (ICR=0x20)
	// Write: Data register with the address of the target slave (the LSB of this byte
	// determines whether the communication is master receive or transmit)
	I2C0_D = I2C_ADDR;
	// Write: Control Register 1 to enable the I2C module and interrupts
	I2C0_C1 |= I2C_C1_IICEN_MASK; //Enable I2C module operation IICEN
	I2C0_C1 |= I2C_C1_IICIE_MASK; //Enable I2C interrupt requests IICIE
	I2C0_FLT |= I2C_FLT_STOPIE_MASK; //Enable the I2C Bus Stop Interrupt Enable STOPIE
	I2C0_FLT |= I2C_FLT_STOPF_MASK; //Clear the I2C bus stop detect flag STOPF
	I2C0_S |= I2C_S_IICIF_MASK; //Clear the interrupt flag IICIF
	// Initialize RAM variables (IICEN = 1 and IICIE = 1) for transmit data
	// Initialize RAM variables used to achieve the routine shown in the following figure
	// Write: Control Register 1 to enable TX
	I2C0_C1 |= I2C_C1_TX_MASK;
	// Write: Control Register 1 to enable MST (master mode)
	I2C0_C1 |= I2C_C1_MST_MASK;
}

VL53L1_RangingMeasurementData_t printRangingData(VL53L1_DEV Dev){
  static VL53L1_RangingMeasurementData_t RangingData;

  status = VL53L1_GetRangingMeasurementData(Dev, &RangingData);
  if(!status){
	  //printing Range Status
	  uart_write("RangeStatus (0=valid) : ",24);
	  uart_writeNb(RangingData.RangeStatus);
	  uart_write("\n\r",2);
	  //printing Range Value
	  uart_write("Ranging data (mm) : ",20);
	  uart_writeNb(RangingData.RangeMilliMeter);
	  uart_write("\n\r",2);
	  //printing Signal Rate
	  /*uart_write("Signal rate : ",14);
	  uart_writeNb((int)(RangingData.SignalRateRtnMegaCps/65536.0));
	  uart_write("\n\r",2);	  
	  //printing Ambient Rate
	  uart_write("Ambient rate : ",15);
	  uart_writeNb((int)(RangingData.AmbientRateRtnMegaCps/65536.0));
	  uart_write("\n\r",2);	 */
  }
  else{
	  uart_write("Error GetRangingMeasurementData(..)\n\r",37);
  }
  return RangingData;
}

static void I2C_delay_us(uint16_t usec_time)
{
    uint16_t outer_loop;
    uint16_t inner_loop;
     
    /* System clock is configured as 48Mhz in BSPInit.c module.
         With 48Mhz clock, the time per instruction comes to be
       1/48000000 = 0.02834usec.
       The get 1usec time, number of instructions to be executed
       becomes 1usec / 0.02834usec which comes out to be ~35.
       The generate delay equal to 'cnt' usec, using this function, the 
       input parameter 'cnt' must be multiplied with '35'.
       As this function uses for loop to generate delay, additional
       overhead comes into picture to execute this loop and the delay
       generated will always be more than specified 'cnt' parameter.
       However, this should be okay in this case, as delay does not
       need to be very accurate.
       The max possible delay is 32768usec with uint16_t type.
    */
     
    for (outer_loop=0u; outer_loop < (uint16_t)35; outer_loop++)
    {
        for (inner_loop=0u; inner_loop < usec_time; inner_loop++)
        {
            // do nothing
        }
    }
}

void I2C1_start(void){
	/* 	START condition on I2C for distance sensor:
		SCL: HIGH
		SDA: HIGH to LOW Transition
	* */
    I2C1_C1 |= I2C_C1_MST_MASK;  /* MST bit changed from 0 to 1 generates START condition */
    I2C_delay_us(5);
}

void I2C1_repeat_start(void){
    /* START condition on I2C EEPROM:
         SCL: HIGH
         SDA: HIGH to LOW Transition
    */
    I2C1_C1 |= I2C_C1_RSTA_MASK;  /* RSTA bit changed from 0 to 1 generates RESTART condition */
    I2C_delay_us(5);
}

void I2C1_stop(void){
    /* STOP condition on I2C for distance sensor:
         SCL: HIGH
         SDA: LOW to HIGH Transition
    */
    I2C1_C1 &= ~I2C_C1_MST_MASK;  /* MST bit changed from 1 to 0 generates STOP condition */
    I2C_delay_us(5);
}

void I2C0_start(void){
	/* 	START condition on I2C for distance sensor:
		SCL: HIGH
		SDA: HIGH to LOW Transition
	* */
    I2C0_C1 |= I2C_C1_MST_MASK;  /* MST bit changed from 0 to 1 generates START condition */
    I2C_delay_us(5);
}

void I2C0_repeat_start(void){
    /* START condition on I2C EEPROM:
         SCL: HIGH
         SDA: HIGH to LOW Transition
    */
    I2C0_C1 |= I2C_C1_RSTA_MASK;  /* RSTA bit changed from 0 to 1 generates RESTART condition */
    I2C_delay_us(5);
}

void I2C0_stop(void){
    /* STOP condition on I2C for distance sensor:
         SCL: HIGH
         SDA: LOW to HIGH Transition
    */
    I2C0_C1 &= ~I2C_C1_MST_MASK;  /* MST bit changed from 1 to 0 generates STOP condition */
    I2C_delay_us(5);
}

void I2C_clock_init(void){
	//I2C clock init
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK | SIM_SCGC4_I2C1_MASK;
}

static uint8_t I2C0_data_read(void){
    uint8_t data = 0x0;
     
    /* Master reading from slave */
    I2C0_S |= I2C_S_SRW_MASK;     
     
    /* Master Transmit mode disabled (to receive data) */
    I2C0_C1 &= ~I2C_C1_TX_MASK;
     
    /* Initiate data read (As per MCU datasheet, reading the
       I2C0_D register initiates the data transfer to next byte.
    */
    data = I2C0_D;
     
    /* Wait for data to read from EEPROM */
    I2C_delay_us(100);
     
    /* Read data from I2C data register */
    data = I2C0_D;
     
    /* Send NACK to slave */
    I2C0_C1 |= I2C_C1_TXAK_MASK;
     
    /* This delay is must to complete sending NACK on slave */
    I2C_delay_us(5);
     
    return data;
}

static uint8_t I2C1_data_read(void){
    uint8_t data = 0x0;
     
    /* Master reading from slave */
    I2C1_S |= I2C_S_SRW_MASK;     
     
    /* Master Transmit mode disabled (to receive data) */
    I2C1_C1 &= ~I2C_C1_TX_MASK;
     
    /* Initiate data read (As per MCU datasheet, reading the
       I2C0_D register initiates the data transfer to next byte.
    */
    data = I2C1_D;
     
    /* Wait for data to read from EEPROM */
    I2C_delay_us(100);
     
    /* Read data from I2C data register */
    data = I2C1_D;
     
    /* Send NACK to slave */
    I2C1_C1 |= I2C_C1_TXAK_MASK;
     
    /* This delay is must to complete sending NACK on slave */
    I2C_delay_us(5);
     
    return data;
}

static uint8_t I2C0_data_send(uint8_t data){
    uint32_t timeout = 4000000UL;  /* ~100msec */
    uint8_t ret_val = 0;
     
    /* Master writing to slave */
    I2C0_S &= ~I2C_S_SRW_MASK;     
     
    /* Master Transmit mode enabled (to transmit data) */
    I2C0_C1 |= I2C_C1_TX_MASK;   
     
    /* Write to I2C0 Data register */
    I2C0_D = data;
     
    while (((I2C0_S & I2C_S_RXAK_MASK) == I2C_S_RXAK_MASK) & (timeout != 0))
    {
        /* wait until ACK is received from slave device or timeout occurs */
        timeout--;
    }
     
    if (timeout != 0){
        timeout = 4000000UL;
        while (((I2C0_S & I2C_S_TCF_MASK) == 0) & (timeout != 0)){
            /* wait until transmit is in progress or timeout occurs */
            timeout--;
        }
    }
     
    if (timeout != 0){
        /* Return 1 when data transmit is successful without timeout */
        ret_val = 1;
    }
     
    /* Delay before sending next byte */
    I2C_delay_us(100);
     
    return ret_val;
}

static uint8_t I2C1_data_send(uint8_t data){
    uint32_t timeout = 4000000UL;  /* ~100msec */
    uint8_t ret_val = 0;
     
    /* Master writing to slave */
    I2C1_S &= ~I2C_S_SRW_MASK;     
     
    /* Master Transmit mode enabled (to transmit data) */
    I2C1_C1 |= I2C_C1_TX_MASK;   
     
    /* Write to I2C0 Data register */
    I2C1_D = data;
     
    while (((I2C1_S & I2C_S_RXAK_MASK) == I2C_S_RXAK_MASK) & (timeout != 0))
    {
        /* wait until ACK is received from slave device or timeout occurs */
        timeout--;
    }
     
    if (timeout != 0){
        timeout = 4000000UL;
        while (((I2C1_S & I2C_S_TCF_MASK) == 0) & (timeout != 0)){
            /* wait until transmit is in progress or timeout occurs */
            timeout--;
        }
    }
     
    if (timeout != 0){
        /* Return 1 when data transmit is successful without timeout */
        ret_val = 1;
    }
     
    /* Delay before sending next byte */
    I2C_delay_us(100);
     
    return ret_val;
}

uint8_t I2C0_byte_read(uint32_t mem_loc, uint8_t *read_status){
    uint8_t data;
     
    *read_status = 1;
     
    /* Generate START condition */
    I2C0_start();
     
    /* Send sensor device address for Write operation */
    if (!I2C0_data_send(I2C_ADDR))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Send Higher Word of memory location to Write */
    if (!I2C0_data_send((uint16_t)((mem_loc & 0xFFFF0000) >> 16)))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Send Lower Word of memory location to Write */
    if (!I2C0_data_send((uint16_t)((mem_loc & 0x0000FFFF))))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Generate Re-Start condition */
    I2C0_repeat_start();
     
    /* Send sensor device address for Read operation */
    if (!I2C0_data_send(I2C_ADDR))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Read EEPROM to get data */
    data = I2C0_data_read();
     
    /* Generate STOP condition */
    I2C0_stop();
     
    return data;
}

uint8_t I2C1_byte_read(uint32_t mem_loc, uint8_t *read_status){
    uint8_t data;
     
    *read_status = 1;
     
    /* Generate START condition */
    I2C1_start();
     
    /* Send sensor device address for Write operation */
    if (!I2C1_data_send(I2C_ADDR))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Send Higher Word of memory location to Write */
    if (!I2C1_data_send((uint16_t)((mem_loc & 0xFFFF0000) >> 16)))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Send Lower Word of memory location to Write */
    if (!I2C1_data_send((uint16_t)((mem_loc & 0x0000FFFF))))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Generate Re-Start condition */
    I2C1_repeat_start();
     
    /* Send sensor device address for Read operation */
    if (!I2C1_data_send(I2C_ADDR))
    {
        /* Return if transmission is not successful */
        *read_status = 0;
        return 0;
    }
     
    /* Read EEPROM to get data */
    data = I2C1_data_read();
     
    /* Generate STOP condition */
    I2C1_stop();
     
    return data;
}

void I2C0_byte_write(uint32_t mem_loc, uint8_t byte, uint8_t *write_status){
    *write_status = 1;
     
    /* Generate START condition */
    I2C0_start();
     
    /* Send sensor device address for Write operation */
    if (!I2C0_data_send(I2C_ADDR))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Send Higher Word of memory location to Write */
    if (!I2C0_data_send((uint16_t)((mem_loc & 0xFFFF0000) >> 16)))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Send Lower Word of memory location to Write */
    if (!I2C0_data_send((uint16_t)((mem_loc & 0x0000FFFF))))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Send data to be written to sensor */
    if (!I2C0_data_send(byte))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Generate STOP condition */
    I2C0_stop();
     
    /* Wait to finish Write operation (~10msec) */
    I2C_delay_us(10000);
}

void I2C1_byte_write(uint32_t mem_loc, uint8_t byte, uint8_t *write_status){
    *write_status = 1;
     
    /* Generate START condition */
    I2C1_start();
     
    /* Send sensor device address for Write operation */
    if (!I2C1_data_send(I2C_ADDR))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Send Higher Word of memory location to Write */
    if (!I2C1_data_send((uint16_t)((mem_loc & 0xFFFF0000) >> 16)))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Send Lower Word of memory location to Write */
    if (!I2C1_data_send((uint16_t)((mem_loc & 0x0000FFFF))))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Send data to be written to sensor */
    if (!I2C1_data_send(byte))
    {
        /* Return if transmission is not successful */
        *write_status = 0;
        return;
    }
     
    /* Generate STOP condition */
    I2C1_stop();
     
    /* Wait to finish Write operation (~10msec) */
    I2C_delay_us(10000);
}

