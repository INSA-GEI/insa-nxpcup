/*   	//Set PTE24 to mux 5 [I2C_SCL]
				PORTE_PCR25 = PORT_PCR_MUX(0x5); 
 * i2c.c
 *
 *  Created on: 14/04/2017
 *      Author: evandro
 */
#include "i2c.h"

/****************************************************************************************
*
*****************************************************************************************/
bool i2c_Init(I2C_MemMapPtr i2c, uint8_t alt, uint8_t mult, uint8_t icr)
{
	if(i2c == I2C0)
	{
		switch(alt)
		{
			case ALT0:
				SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;      //Turn on clock to E module
				PORTE_PCR24 = PORT_PCR_MUX(0x5);    	//Set PTE25 to mux 5 [I2C_SDA]
			break;

			case ALT1:
				SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;      //Turn on clock to E module
				PORTB_PCR0 = PORT_PCR_MUX(0x2);    		//Set PTB0 to mux 2 [I2C_SCL]
				PORTB_PCR1 = PORT_PCR_MUX(0x2);    		//Set PTB1 to mux 2 [I2C_SDA]
			break;

			case ALT2:
				SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;      //Turn on clock to E module
				PORTB_PCR2 = PORT_PCR_MUX(0x2);    		//Set PTB2 to mux 2 [I2C_SCL]
				PORTB_PCR3 = PORT_PCR_MUX(0x2);    		//Set PTB3 to mux 2 [I2C_SDA]
			break;

			case ALT3:
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Turn on clock to E module
				PORTC_PCR8 = PORT_PCR_MUX(0x2);    		//Set PTB2 to mux 2 [I2C_SCL]
				PORTC_PCR9 = PORT_PCR_MUX(0x2);    		//Set PTB3 to mux 2 [I2C_SDA]
			break;

			default:
				return false;
			break;
		}
		//
		SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
		//
		//I2C0_F = I2C_F_ICR(icr) | I2C_F_MULT(mult);
		// enable IIC
		//I2C0_C1 = I2C_C1_IICEN_MASK |	// I2C Enable
		//		  I2C_C1_MST_MASK   |   // Master Mode Select
		//		  I2C_C1_TX_MASK;		// Transmit Mode Select
		//return true;
	}
	else if (i2c == I2C1)
	{
		switch(alt)
		{
			case ALT0:
				SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;      //Turn on clock to E module
				PORTE_PCR0 = PORT_PCR_MUX(0x6);    		//Set PTE0 to mux 6 [I2C_SDA]
				PORTE_PCR1 = PORT_PCR_MUX(0x6);    		//Set PTE1 to mux 6 [I2C_SCL]
			break;

			case ALT1:
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;      //Turn on clock to A module
				PORTA_PCR3 = PORT_PCR_MUX(0x2);    		//Set PTA3 to mux 2 [I2C_SCL]
				PORTA_PCR4 = PORT_PCR_MUX(0x2);    		//Set PTA4 to mux 2 [I2C_SDA]
			break;

			case ALT2:
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Turn on clock to C module
				PORTC_PCR1 = PORT_PCR_MUX(0x2);    		//Set PTC1 to mux 2 [I2C_SCL]
				PORTC_PCR2 = PORT_PCR_MUX(0x2);    		//Set PTC2 to mux 2 [I2C_SDA]
			break;

			case ALT3:
				SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Turn on clock to E module
				PORTC_PCR10 = PORT_PCR_MUX(0x2);    	//Set PTC10 to mux 2 [I2C_SCL]
				PORTC_PCR11 = PORT_PCR_MUX(0x2);    	//Set PTC11 to mux 2 [I2C_SDA]
			break;

			default:
				return false;
			break;
		}
		//
		SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK;
		//
		//I2C1_F = I2C_F_ICR(icr) | I2C_F_MULT(mult);
		// enable IIC
		//I2C1_C1 = I2C_C1_IICEN_MASK |	// I2C Enable
		//		  I2C_C1_MST_MASK   |   // Master Mode Select
		//		  I2C_C1_TX_MASK;		// Transmit Mode Select
		//return true;
	}
	else
	{
		return false;
	}

	//I2C1_F
	//i2c->F = 0x14;//
	i2c->F = I2C_F_ICR(icr) | I2C_F_MULT(mult);
	// enable IIC
	/*i2c->C1 = I2C_C1_IICEN_MASK |	// I2C Enable
			  I2C_C1_MST_MASK   |   // Master Mode Select
			  I2C_C1_TX_MASK;		// Transmit Mode Select
	*/
	i2c->C1 = 0x80;
	return true;

}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_DisableAck(I2C_MemMapPtr i2c)
{
	i2c->C1 |= I2C_C1_TXAK_MASK;
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_EnableAck(I2C_MemMapPtr i2c)
{
	i2c->C1 &= ~I2C_C1_TXAK_MASK;
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_RepeatedStart(I2C_MemMapPtr i2c)
{
	i2c->C1 |= I2C_C1_RSTA_MASK;
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_EnterRxMode(I2C_MemMapPtr i2c)
{
	i2c->C1 &= ~I2C_C1_TX_MASK;
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_Start(I2C_MemMapPtr i2c)
{
	i2c->C1 |= I2C_C1_TX_MASK;
	i2c->C1 |= I2C_C1_MST_MASK;
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_Stop(I2C_MemMapPtr i2c)
{
	i2c->C1 &= ~I2C_C1_MST_MASK;
	i2c->C1 &= ~I2C_C1_TX_MASK;
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_Wait(I2C_MemMapPtr i2c)
{
	uint32_t i = 0;
	i = 1000000;

	while(((i2c->S & I2C_S_IICIF_MASK) == 0) && i)
	{
		i--;
	}
	i2c->S |= I2C_S_IICIF_MASK;
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_WriteByte(I2C_MemMapPtr i2c,uint8_t data)
{
	i2c->D = (uint8_t)data;
}
/****************************************************************************************
*
*****************************************************************************************/
uint8_t i2c_ReadByte(I2C_MemMapPtr i2c)
{
	return (uint8_t)( i2c->D );
}
/****************************************************************************************
*
*****************************************************************************************/
void i2c_WriteRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress, uint8_t data)
{
	//uint8_t res = 0;

	i2c_Start(i2c);
	i2c_WriteByte(i2c, ((SlaveAddress << 1) | I2C_WRITE));
	i2c_Wait(i2c);

	i2c_WriteByte(i2c,RegisterAddress);
	i2c_Wait(i2c);

	i2c_WriteByte(i2c,data);
	i2c_Wait(i2c);

	i2c_Stop(i2c);

	delay(50);

	/*
	i2c_RepeatedStart(i2c);

	i2c_WriteByte(i2c, ((SlaveAddress << 1) | I2C_READ));
	i2c_Wait(i2c);

	i2c_EnterRxMode(i2c);
	i2c_DisableAck(i2c);

	res = i2c_ReadByte(i2c);
	i2c_Wait(i2c);
	i2c_Stop(i2c);
	res = i2c_ReadByte(i2c);
	delay(50);
	return res;*/
}
/****************************************************************************************
*
*****************************************************************************************/
uint8_t i2c_ReadRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress)
{
	uint8_t res = 0;

	i2c_Start(i2c);
	i2c_WriteByte(i2c, ((SlaveAddress << 1) | I2C_WRITE));
	i2c_Wait(i2c);

	i2c_WriteByte(i2c,RegisterAddress);
	i2c_Wait(i2c);

	i2c_RepeatedStart(i2c);

	i2c_WriteByte(i2c, ((SlaveAddress << 1) | I2C_READ));
	i2c_Wait(i2c);

	i2c_EnterRxMode(i2c);
	i2c_DisableAck(i2c);

	res = i2c_ReadByte(i2c);
	i2c_Wait(i2c);
	i2c_Stop(i2c);
	res = i2c_ReadByte(i2c);
	delay(50);

	return res;
}
/****************************************************************************************
*
*****************************************************************************************/
uint8_t i2c_ReadMultRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress,uint8_t n_data, uint8_t *res)
{
	uint8_t i = 0;
	
	//TEST
	uint8_t* res_aux=res;
	//

	i2c_Start(i2c);
	i2c_WriteByte(i2c, ((SlaveAddress << 1) | I2C_WRITE));
	i2c_Wait(i2c);

	i2c_WriteByte(i2c,RegisterAddress);
	i2c_Wait(i2c);

	i2c_RepeatedStart(i2c);

	i2c_WriteByte(i2c, ((SlaveAddress << 1) | I2C_READ));
	i2c_Wait(i2c);

	i2c_EnterRxMode(i2c);
	i2c_EnableAck(i2c);

	i = i2c_ReadByte(i2c);
	i2c_Wait(i2c);

	for(i=0;i<(n_data-2);i++)
	{
		*res = i2c_ReadByte(i2c);
		res++;
		i2c_Wait(i2c);
	}

	i2c_DisableAck(i2c);

	*res = i2c_ReadByte(i2c);
	res++;
	i2c_Wait(i2c);

	i2c_Stop(i2c);

	*res = i2c_ReadByte(i2c);
	
	//TEST
	res=res_aux;
	//

	delay(50);
	
	return 0;
}

/****************************************************************************************
*
*****************************************************************************************/
void i2c_WriteMultRegister(I2C_MemMapPtr i2c,uint8_t SlaveAddress,uint8_t RegisterAddress, uint8_t n_data, uint8_t* pdata)
{
	uint8_t i = 0;

	i2c_Start(i2c);
	i2c_WriteByte(i2c, ((SlaveAddress << 1) | I2C_WRITE));
	i2c_Wait(i2c);

	i2c_WriteByte(i2c,RegisterAddress);
	i2c_Wait(i2c);

	for(i=0;i<n_data;i++)
	{
		i2c_WriteByte(i2c,*pdata);
		pdata++;
		i2c_Wait(i2c);
	}
	i2c_Stop(i2c);

	delay(50);
}
/****************************************************************************************
*
*****************************************************************************************/
void delay(uint32_t t)
{
	uint32_t cnt = 0;
	for(cnt=0; cnt<t; cnt++)
	{
		__asm("nop");
	};
}
/*****************************************************************************************/

