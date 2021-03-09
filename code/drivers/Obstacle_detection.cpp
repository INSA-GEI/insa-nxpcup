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

/*One sensor is defined as:
 *  typedef struct {
 *	VL53L1_DevData_t   	Data;
 *	uint8_t   			I2cDevAddr;
 *	uint8_t   			comms_type;
 *	uint16_t  			comms_speed_khz;
 *	uint32_t  			new_data_ready_poll_duration_ms;
 *	I2C_HandleTypeDef*	I2cHandle;
 *  } VL53L1_Dev_t;
 *	
 *	typedef struct {
 *	   uint32_t 		dummy;
 *	} I2C_HandleTypeDef;
 * */
//Right sensor
VL53L1_Dev_t	devR;
VL53L1_DEV		DevR = &devR;
//Left sensor
VL53L1_Dev_t	devL;
VL53L1_DEV		DevL = &devL;

#define I2C_ADDR 0x52

/*Variable declaration*/
int status = 0;

void Obstacle::setup(VL53L1_DEV Dev, uint8_t DeviceAddress){
	
	//I2C clock init
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK | SIM_SCGC4_I2C1_MASK;
	
	/****** RIGHT SENSOR ******/
	/* Port initialization */
	I2C_init_port_right();
	/* Module initialization (as master) */
	I2C_init_master_right();

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
	status = VL53L1_SetDeviceAddress(Dev, DeviceAddress);
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
	I2C1_F |= (1<<5); //12MHz clk is divided by 160 : I2C clk is 75kHz (ICR=0x20)
	// Write: Control Register 1 to enable the I2C module and interrupts
	I2C1_C1 |= (1<<7); //Enable I2C module operation IICEN
	I2C1_C1 |= (1<<6); //Enable I2C interrupt requests IICIE
	I2C1_FLT |= (1<<5); //Enable the I2C Bus Stop Interrupt Enable STOPIE
	I2C1_FLT |= (1<<6); //Clear the I2C bus stop detect flag STOPF
	I2C1_S |= (1<<1); //Clear the interrupt flag IICIF
	// Initialize RAM variables (IICEN = 1 and IICIE = 1) for transmit data
	// Initialize RAM variables used to achieve the routine shown in the following figure
	// Write: Control Register 1 to enable TX
	I2C1_C1 |= (1<<4);
	// Write: Control Register 1 to enable MST (master mode)
	I2C1_C1 |= (1<<5);
	// Write: Data register with the address of the target slave (the LSB of this byte
	// determines whether the communication is master receive or transmit)
	I2C1_D = I2C_ADDR;
}

void I2C_init_master_left(void){
	// Write: Frequency Divider register to set the I2C baud rate
	I2C0_F |= (1<<5); //12MHz clk is divided by 160 : I2C clk is 75kHz (ICR=0x20)
	// Write: Control Register 1 to enable the I2C module and interrupts
	I2C0_C1 |= (1<<7); //Enable I2C module operation IICEN
	I2C0_C1 |= (1<<6); //Enable I2C interrupt requests IICIE
	I2C0_FLT |= (1<<5); //Enable the I2C Bus Stop Interrupt Enable STOPIE
	I2C0_FLT |= (1<<6); //Clear the I2C bus stop detect flag STOPF
	I2C0_S |= (1<<1); //Clear the interrupt flag IICIF
	// Initialize RAM variables (IICEN = 1 and IICIE = 1) for transmit data
	// Initialize RAM variables used to achieve the routine shown in the following figure
	// Write: Control Register 1 to enable TX
	I2C0_C1 |= (1<<4);
	// Write: Control Register 1 to enable MST (master mode)
	I2C0_C1 |= (1<<5);
	// Write: Data register with the address of the target slave (the LSB of this byte
	// determines whether the communication is master receive or transmit)
	I2C0_D = I2C_ADDR;
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


