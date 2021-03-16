/*
 * Sensor.cpp
 *
 *  Created on: Mar 16, 2021
 *      Author: carol
 */

#include "Sensor.h"
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



void Obstacle::init(void){

	I2C_clock_init();
	
	/****** RIGHT SENSOR ******/
	/* Port initialization */
	I2C_init_port_right();
	/* Module initialization (as master) */
	I2C_init_master_right();

	uart_write("I2C init done.\n\r",16);
	
}


void Obstacle::I2C_init_port_right(void){
	PORTE_PCR0 = PORT_PCR_MUX(6);
	PORTE_PCR1 = PORT_PCR_MUX(6);
}


void Obstacle::I2C_init_master_right(void){
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


void Obstacle::I2C_clock_init(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	//I2C clock init
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK | SIM_SCGC4_I2C1_MASK;
}

void Obstacle::I2C_delay_us(uint16_t usec_time)
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

uint8_t Obstacle::I2C1_data_send(uint8_t data){
    uint32_t timeout = 4000000UL;  /* ~100msec */
    uint8_t ret_val = 0;
     
    /* Master writing to slave */
    I2C1_S &= ~I2C_S_SRW_MASK;     
     
    /* Master Transmit mode enabled (to transmit data) */
    I2C1_C1 |= I2C_C1_TX_MASK;   
     
    /* Write to I2C1 Data register */
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

uint8_t Obstacle::I2C1_data_read(void){
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
