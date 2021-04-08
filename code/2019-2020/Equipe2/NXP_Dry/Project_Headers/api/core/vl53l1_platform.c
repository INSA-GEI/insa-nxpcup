
/*
* Copyright (c) 2017, STMicroelectronics - All Rights Reserved
*
* This file is part of VL53L1 Core and is dual licensed,
* either 'STMicroelectronics
* Proprietary license'
* or 'BSD 3-clause "New" or "Revised" License' , at your option.
*
********************************************************************************
*
* 'STMicroelectronics Proprietary license'
*
********************************************************************************
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms at www.st.com/sla0081
*
* STMicroelectronics confidential
* Reproduction and Communication of this document is strictly prohibited unless
* specifically authorized in writing by STMicroelectronics.
*
*
********************************************************************************
*
* Alternatively, VL53L1 Core may be distributed under the terms of
* 'BSD 3-clause "New" or "Revised" License', in which case the following
* provisions apply instead of the ones mentioned above :
*
********************************************************************************
*
* License terms: BSD 3-clause "New" or "Revised" License.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors
* may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*
********************************************************************************
*
*/


#include "vl53l1_platform.h"
#include "vl53l1_platform_log.h"

#include "vl53l1_api.h"
#include "C:\Users\maier\OneDrive\Documents\INSA\4A\PIR NXP CUP\Projet\insa-nxpcup\code\2019-2020\Equipe2\drivers\Debug.h"
// #include "stm32xxx_hal.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


// #define I2C_TIME_OUT_BASE   10
// #define I2C_TIME_OUT_BYTE   1

#define SLAVE_ADDRESS 0x52

// #ifdef VL53L1_LOG_ENABLE
// #define trace_print(level, ...) VL53L1_trace_print_module_function(VL53L1_TRACE_MODULE_PLATFORM, level, VL53L1_TRACE_FUNCTION_NONE, ##__VA_ARGS__)
// #define trace_i2c(...) VL53L1_trace_print_module_function(VL53L1_TRACE_MODULE_NONE, VL53L1_TRACE_LEVEL_NONE, VL53L1_TRACE_FUNCTION_I2C, ##__VA_ARGS__)
// #endif

// #ifndef HAL_I2C_MODULE_ENABLED
// #warning "HAL I2C module must be enable "
// #endif

//extern I2C_HandleTypeDef hi2c1;
//#define VL53L0X_pI2cHandle    (&hi2c1)

/* when not customized by application define dummy one */
// #ifndef VL53L1_GetI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
// #   define VL53L1_GetI2cBus(...) (void)0
// #endif

// #ifndef VL53L1_PutI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
// #   define VL53L1_PutI2cBus(...) (void)0
// #endif

// uint8_t _I2CBuffer[256];


/* 	VL53L1_DEV = structure explanations
 
	VL53L1_DevData_t   Data;

	uint8_t   I2cDevAddr;	= address on 7 MSB (0x52)  	
	uint8_t   comms_type;	
	uint16_t  comms_speed_khz;
	uint32_t  new_data_ready_poll_duration_ms;
	I2C_HandleTypeDef *I2cHandle;	
*/

uint32_t current_tick = 0;

/*!
 * Tick Count interrupt initialisation
 * Initialisation on rising edge detection interrupt on SCL
 */
void Tick_Interrupt_Init(void){
	PORTB_PCR0 |= PORT_PCR_ISF_MASK; 	//detect interrupt active
	PORTB_PCR0 |= PORT_PCR_IRQC(0x9); 	//activate in rising edge detection
	
	NVIC_ICPR |= 1 << PORTB_PCR0;		//clear pending register
	NVIC_ISER |= 1 << PORTB_PCR0;		//enable interrupt register
	
}

/*!
 * Tick Count interrupt handler
 * 
 */

void Tick_Interrupt_Handler(void) {
	PORTB_PCR0 |= PORT_PCR_ISF_MASK; //Clear the bit flag of interrupt
	current_tick++;
	uart_writeNb(current_tick);
}

/*!
 * I2C Wait
 * Wait until the I2C interrupt is pending
 */

void _I2CWait(void) {
	while ( (I2C0_S & I2C_S_IICIF_MASK) ==1){
		//I2C0_S |= I2C_S_IICIF_MASK;
	}
}
/*!
 * I2C Initialisation
 * Set Baud Rate and turn on I2C0
 */

void _I2CInit(VL53L1_DEV * Dev){
	
	SIM_SCGC5|= SIM_SCGC5_PORTB_MASK; 	// port clock on
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK; 	//Turn on clock to I2C` module
		
	PORTB_PCR0 |= PORT_PCR_MUX(2);		// activate pins PTB0 PTB1	
	PORTB_PCR1 |= PORT_PCR_MUX(2);
	
	I2C0_C1 |= I2C_C1_IICEN_MASK;		// enable I2C module
	
	// set baud rate (400kHz) with ICR=5 and MUL=2
	I2C0_F |= I2C_F_MULT(2);
	I2C0_F |= I2C_F_ICR(5);
	

	Tick_Interrupt_Init(); // initialisation of tick count interrupt
	
}

/*!
 * Start I2C Transmission
 * @param Dev is the I2C device used
 * @param Mode sets MWSR and MRSW mode !! must define MWSR and MRSW in the .h
 */

void  _I2CStartTransmission(VL53L1_DEV Dev, unsigned char Mode) {
	
			
	I2C0_D = (Dev->I2cDevAddr) | Mode; // initiated data transfer and set I2C transmission in mode chosen (MWSR or MRSW)
	//Dev->comms_type = Mode;
	
	if (Mode == MWSR) { 	// mode Master Write and Slave Read
		I2C0_C1 |= I2C_C1_MST_MASK; 	// I2C master mode	
		I2C0_C1 = I2C_C1_TX_MASK; 		// start master transmission
	}
	
	if (Mode == MRSW) { // mode Master Read Slave Write
		I2C0_C1 &= (~I2C_C1_TX_MASK); // start master reading
	}
}


/*!
 * Master Write
 * @param Dev is the I2C device used
 * @param *pData is the pointer on the data to write
 */
int _I2CWrite(VL53L1_DEV Dev, uint8_t *pdata, uint32_t count) {
     int status = 0;
     
    _I2CStartTransmission(Dev, MWSR); //start transmission in write mode
    _I2CWait(); //wait until I2C interrupt pending = task finished 
    
     //I2C0_D = Dev->I2cDevAddr; //specifies address where write the data 
     //_I2CWait(); //wait until task is finished
     
     I2C0_D = *pdata; // send data
     _I2CWait(); 
     
     I2C0_C1 &= ~I2C_C1_MST_MASK; 	//stop master mode
     I2C0_C1 &= ~I2C_C1_TX_MASK; 	//stop master transmission
         
     return status;
}


/*!
 * Master Read
 * @param Dev is the I2C device used
 * @param *pData is the pointer on the data read
 */
int _I2CRead(VL53L1_DEV Dev, uint8_t *pdata, uint32_t count) {
    
	int status = 0;

    _I2CStartTransmission(Dev, MWSR); 	//start transmission in write mode to send the address
    _I2CWait(); 						//wait until I2C interrupt pending = task finished 
    
	 //I2C0_D = Dev->I2cDevAddr; //specifies address where read the data 
	 //_I2CWait(); //wait until task is finished
	 
    
	 I2C0_C1 |= I2C_C1_RSTA_MASK; 		// repeat start to indicate we are in master mode
	 _I2CStartTransmission(Dev, MRSW);	//start transmission in read mode
     _I2CWait();
     
     
     I2C0_C1 &= ~I2C_C1_TXAK_MASK; // ensure TXAK bit is 0 so that we can receive data
     
     *pdata = I2C0_D; // dummy read to drive the clock
     _I2CWait();
     
     I2C0_C1 &= ~I2C_C1_MST_MASK; 	//stop master mode
     I2C0_C1 &= ~I2C_C1_TX_MASK; 	//stop master transmission
     
     *pdata = I2C0_D; //read data
    
    return status;
 }
 


/*!
 * Master Multi Write
 * @param Dev is the I2C device used
 * @param index is the 2 bytes index
 * @param *pdata is the pointer on the data to write = tab of "count" elements
 * @param count is the number of bytes to write
 */
VL53L1_Error VL53L1_WriteMulti(VL53L1_DEV Dev, uint16_t index, uint8_t *pdata, uint32_t count) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    
    
    _I2CStartTransmission(Dev, MWSR);  	//master mode + Tx mode + send address 
    _I2CWait(); 						//wait until interrupt is pending = task finish
        
    I2C0_D = index << 8; 	// send 8 index MSB 
    _I2CWait();
    
    I2C0_D = index & 0xFF; 	// send 8 index LSB
    _I2CWait();
    
    uart_write("entree for", 12);
	for (unsigned int i=0; i<count; i++) { //for i in [0, count[ => send data[i] 
    	I2C0_D = pdata[i];
    	uart_writeNb(I2C0_D);
    	uart_writeNb(pdata[i]);
    	uart_write("_", 1);
    	_I2CWait();
    }
	uart_write("sortie for", 12);
	
	I2C0_C1 &= ~I2C_C1_MST_MASK; 	//stop master mode
	I2C0_C1 &= ~I2C_C1_TX_MASK; 	//stop master transmission
	
    return Status;
}


/*!
 * Master Multi Read
 * @param Dev is the I2C device used
 * @param index is the 2 bytes index
 * @param *pdata is the pointer on the data to read = tab of "count" elements
 * @param count is the number of bytes to read
 */

// the ranging_sensor_comms.dll will take care of the page selection
VL53L1_Error VL53L1_ReadMulti(VL53L1_DEV Dev, uint16_t index, uint8_t *pdata, uint32_t count) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    
    _I2CStartTransmission(Dev, MWSR);	//master mode + Tx mode + send write address
    _I2CWait(); 					//wait until interrupt is pending = task finish
            
	I2C0_D = index >> 8; 	// send 8 index MSB 
	_I2CWait();
	
	I2C0_D = index & 0xFF;	// send 8 index LSB
	_I2CWait();
	
	I2C0_C1 |= I2C_C1_RSTA_MASK; 		// repeat start to indicate we are in master mode
	_I2CStartTransmission(Dev, MRSW);	//start transmission in read mode
	_I2CWait();
	 
	 
	I2C0_C1 &= ~I2C_C1_TXAK_MASK; 	// ensure TXAK bit is 0 so that we can receive data
	 
	pdata[0] = I2C0_D; 			// dummy read to drive the clock
	_I2CWait();
	
	for (unsigned int i=0; i<(count-1) ; i++) { // for i in [0, count-1[ => receive data[i]
		pdata[i]=I2C0_D;
		_I2CWait();
	}
	
	I2C0_C1 |= I2C_C1_TXAK_MASK; 	// turn off ACK while we read the second last to read
	
    pdata[count-2] = I2C0_D; 		//receive data[count-2]
    
    I2C0_C1 &= ~I2C_C1_MST_MASK; 	//stop master mode
    I2C0_C1 &= ~I2C_C1_TX_MASK; 	//stop master transmission
    
    pdata[count-1] = I2C0_D; 		//receive data[count-1]
    
    return Status;
}


/*!
 * Master Write Byte
 * @param Dev is the I2C device used
 * @param index is the 2 bytes index
 * @param data is the data to write data = 1byte
 */
VL53L1_Error VL53L1_WrByte(VL53L1_DEV Dev, uint16_t index, uint8_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    Status = VL53L1_WriteMulti(Dev, index, &data, 1);
    return Status;
}

/*!
 * Master Write Word
 * @param Dev is the I2C device used
 * @param index is the 2 bytes index
 * @param data is the data to write data = 2 bytes
 */
VL53L1_Error VL53L1_WrWord(VL53L1_DEV Dev, uint16_t index, uint16_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    
    uint8_t byte_data = data >> 8; // send 8 data MSB
    Status = VL53L1_WrByte(Dev, index, byte_data);
    _I2CWait();
    
    byte_data = data & 0xFF; // send 8 data LSB
    Status = VL53L1_WrByte(Dev, index, byte_data);
    
    return Status;
}

/*VL53L1_Error VL53L1_WrDWord(VL53L1_DEV Dev, uint16_t index, uint32_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    return Status;
}*/

/*VL53L1_Error VL53L1_UpdateByte(VL53L1_DEV Dev, uint16_t index, uint8_t AndData, uint8_t OrData) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    return Status;
}*/

/*!
 * Master Read Byte
 * @param Dev is the I2C device used
 * @param index is the 2 bytes index
 * @param *data is the pointer on the data to read = 1 byte
 */
VL53L1_Error VL53L1_RdByte(VL53L1_DEV Dev, uint16_t index, uint8_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    Status = VL53L1_ReadMulti(Dev, index, data, 1);
    return Status;
}

/*!
 * Master Read Word
 * @param Dev is the I2C device used
 * @param index is the 2 bytes index
 * @param *data is the pointer on the data to read = 2 bytes
 */
VL53L1_Error VL53L1_RdWord(VL53L1_DEV Dev, uint16_t index, uint16_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    
    uint8_t byte_data = (*data >> (uint16_t) 8); // send 8 data MSB
    
	Status = VL53L1_RdByte(Dev, index, &byte_data);
	_I2CWait();
	
	byte_data = (*data & (uint16_t)0xFF); // send 8 data LSB
	Status = VL53L1_RdByte(Dev, index, &byte_data);
        
    return Status;
}

/*VL53L1_Error VL53L1_RdDWord(VL53L1_DEV Dev, uint16_t index, uint32_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    return Status;
}*/

/*!
 * Get Tick Count
 * value of the absolute time --> t=0 is the initialisation of I2C
 * @param *ptick_count_ms is the pointer where write the absolute time in ms
 */
VL53L1_Error VL53L1_GetTickCount(uint32_t *ptick_count_ms){
	VL53L1_Error status  = VL53L1_ERROR_NONE;
	uint32_t period = 1/400; 				// I2C frequency = 400kHz
	*ptick_count_ms = period*current_tick;	// current_tick update each rising edge of SCL
	
	return status;
}

//#define trace_print(level, ...) 
//	_LOG_TRACE_PRINT(VL53L1_TRACE_MODULE_PLATFORM, 
//	level, VL53L1_TRACE_FUNCTION_NONE, ##__VA_ARGS__)

//#define trace_i2c(...) 
//	_LOG_TRACE_PRINT(VL53L1_TRACE_MODULE_NONE, 
//	VL53L1_TRACE_LEVEL_NONE, VL53L1_TRACE_FUNCTION_I2C, ##__VA_ARGS__)

/*VL53L1_Error VL53L1_GetTimerFrequency(int32_t *ptimer_freq_hz){
	VL53L1_Error status  = VL53L1_ERROR_NONE;
	return status;
}*/


/*!
 * Wait milliseconds
 * @param *pdev is a pointer on the device used
 * @param wait_ms is the time in millisecond we want to wait
 */
VL53L1_Error VL53L1_WaitMs(VL53L1_Dev_t *pdev, int32_t wait_ms){
	VL53L1_Error status  = VL53L1_ERROR_NONE;
	
	uint32_t start_time, current_time; 
	
	VL53L1_GetTickCount(&start_time); 				// take the current absolute time as a start time
	
	while (current_time < (start_time + wait_ms)) { // we wait until the current time equals to the start time + the wait time
		VL53L1_GetTickCount(&current_time);
	}	
	return status;
}

/*!
 * Wait microseconds
 * @param *pdev is a pointer on the device used
 * @param wait_us is the time in microseconds we want to wait
 */
VL53L1_Error VL53L1_WaitUs(VL53L1_Dev_t *pdev, int32_t wait_us){
	VL53L1_Error status  = VL53L1_ERROR_NONE;
	
	uint32_t start_time, current_time;
	VL53L1_GetTickCount(&start_time);
		
	while (current_time*1000 < (start_time*1000 + wait_us)) {
		VL53L1_GetTickCount(&current_time);
	}	
	return status;
}

VL53L1_Error VL53L1_WaitValueMaskEx(
	VL53L1_Dev_t *pdev,
	uint32_t      timeout_ms,
	uint16_t      index,
	uint8_t       value,
	uint8_t       mask,
	uint32_t      poll_delay_ms)
{
	VL53L1_Error status  = VL53L1_ERROR_NONE;
	return status;
}



