/*********************************************************************************************************
* File                : I2C.h
* Hardware            : AVR
* Created by          :www.learn-electronic.com
*
*********************************************************************************************************/

#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>
#include  <util/delay.h>
#include "I2C.h"
#include  "DS1307.h"

//IIIIIIIIIIIIIIIIIIII I2C Interface Conditions IIIIIIIIIIIIIIIIIIII
#define START       0x08
#define START_REP   0x10
#define MT_SLA_ACK  0x18
#define MT_DATA_ACK     0x28
#define MR_SLA_ACK      0x40
#define MR_DATA_NACK    0x58

void I2C_Init(void);
unsigned char I2C_Start(void);
unsigned char I2C_StartRep(void);
unsigned char I2C_Stop(void);
unsigned char I2C_Write(unsigned char data);
unsigned char I2C_Read(unsigned char* data);
// void I2C_Init(void)
// {
// 	TWSR = 0x00;
// 	//set SCL to 400kHz //TWBR = 0x0A;
// 	TWBR = 72;	//SCL Frequency = 1600000 / (16 + 2 x 65) = 100.997  kHz
// 	TWCR = (1<<TWEN);	//enable TWI
// }
#endif /* I2C_H_ */