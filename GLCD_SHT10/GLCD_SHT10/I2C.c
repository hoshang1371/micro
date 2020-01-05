/*********************************************************************************************************
* File                : I2C.c
* Hardware            : AVR
* Created by          :www.learn-electronic.com
*
*********************************************************************************************************/
#include "I2C.h"
#include  "DS1307.h"

//////////////////////////////// I2C_Init //////////////////////////////
void I2C_Init(void)
{
	TWSR = 0x00;
	//set SCL to 400kHz //TWBR = 0x0A;
	TWBR = 72;	//SCL Frequency = 1600000 / (16 + 2 x 65) = 100.997  kHz
	TWCR = (1<<TWEN);	//enable TWI
}
//////////////////////////////// I2C_Start //////////////////////////////
unsigned char I2C_Start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	// Wait for TWINT=1 in the TWCR Register
	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != START)
	return 0;
	else return 1;
}
//////////////////////////////// I2C_StartRep //////////////////////////////
unsigned char I2C_StartRep(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != START_REP)
	return 0;
	else return 1;
}
////////////////////////////////// I2C_Stop ////////////////////////////////
unsigned char I2C_Stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	return 1;
}
////////////////////////////////// I2C_Write ////////////////////////////////
unsigned char I2C_Write(unsigned char data)
{
	unsigned char d=data;
	TWDR = d;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != MT_DATA_ACK)
	return 0;
	else return 1;
}
////////////////////////////////// I2C_Read ////////////////////////////////
unsigned char I2C_Read(unsigned char* data)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	*data = TWDR;
	if ((TWSR & 0xF8) != MR_DATA_NACK)
	return 0;
	else return 1;
}