/*********************************************************************************************************
* File                : DS1307.c
* Hardware            : AVR
* Created by          :www.learn-electronic.com
*
*********************************************************************************************************/
#include "DS1307.h"
#include "I2C.h"
//////////////////////////////// BCD_To_Decimal //////////////////////////////
unsigned char BCD_To_Decimal(unsigned char d)
{
	return ((d & 0x0F) + (((d & 0xF0) >> 4) * 10));
}
//////////////////////////////// Decimal_To_BCD //////////////////////////////
unsigned char Decimal_To_BCD(unsigned char d)
{
	return (((d / 10) << 4) & 0xF0) | ((d % 10) & 0x0F);
}
//////////////////////////////// DS1307_Read //////////////////////////////
unsigned char DS1307_Read(unsigned char Address)
{
	unsigned char _value = 0;
	I2C_Start();
	I2C_Write(DS1307_Write_addr);
	I2C_Write(Address);
	I2C_Start();
	I2C_Write(DS1307_Read_addr);
	I2C_Read(&_value);
	I2C_Stop();
	return _value;
}
//////////////////////////////// DS1307_Write //////////////////////////////
void DS1307_Write(unsigned char Address, unsigned char _value)
{
	I2C_Start();
	I2C_Write(DS1307_Write_addr);
	I2C_Write(Address);
	I2C_Write(_value);
	I2C_Stop();
}
//////////////////////////////// DS1307_Init //////////////////////////////
void DS1307_Init(void)
{
	
	I2C_Init();
	_delay_ms(10);
	DS1307_Write(CONTROLREG, 0x05);
	DS1307_Write(STATUSREG, 0x00);
}
////////////////////////////// DS1307_GetTime ///////////////////////////////////////
void DS1307_GetTime(unsigned char* hourP, unsigned char* minutP, unsigned char* secP, unsigned char* ampmP, unsigned char hour_format)
{
	unsigned char tmp = 0;
	*secP = DS1307_Read(SECONDREG);
	*secP = BCD_To_Decimal(*secP);
	*minutP = DS1307_Read(MINUTEREG);
	*minutP = BCD_To_Decimal(*minutP);
	switch(hour_format)
	{
		case _12_hour_format:
		{
			tmp = DS1307_Read(HOURREG);
			tmp &= 0x20;
			*ampmP = (short)(tmp >> 5);
			*hourP = (0x1F & DS1307_Read(HOURREG));
			*hourP = BCD_To_Decimal(*hourP);
			break;
		}
		default:
		{
			*hourP = (0x3F & DS1307_Read(HOURREG));
			*hourP = BCD_To_Decimal(*hourP);
			break;
		}
	}
}
////////////////////////////// DS1307_GetDate ///////////////////////////////////////
void DS1307_GetDate(unsigned char* dayP, unsigned char* dateP, unsigned char* montP, unsigned int* yearP)
{
	*yearP = DS1307_Read(YEARREG);
	*yearP = BCD_To_Decimal(*yearP);
	*montP = DS1307_Read(MONTHREG);
	*yearP += ((*montP >> 7) * 100) + 2000;
	*montP = (0x1F & *montP);
	*montP = BCD_To_Decimal(*montP);
	*dateP = (0x3F & DS1307_Read(DATEREG));
	*dateP = BCD_To_Decimal(*dateP);
	*dayP = (0x07 & DS1307_Read(DAYREG));
	*dayP = BCD_To_Decimal(*dayP);
}
////////////////////////////// DS1307_SetTime ///////////////////////////////////////
void DS1307_SetTime(unsigned char hSet, unsigned char mSet, unsigned char sSet, unsigned char am_pm_state, unsigned char hour_format)
{
	unsigned char tmp = 0;
	DS1307_Write(SECONDREG, (Decimal_To_BCD(sSet)));
	DS1307_Write(MINUTEREG, (Decimal_To_BCD(mSet)));
	switch(hour_format)
	{
		case _12_hour_format:
		{
			switch(am_pm_state)
			{
				case 1:
				{
					tmp = 0x60;
					break;
				}
				default:
				{
					tmp = 0x40;
					break;
				}
			}
			DS1307_Write(HOURREG, ((tmp | (0x1F & (Decimal_To_BCD(hSet))))));
			break;
		}
		
		default:
		{
			DS1307_Write(HOURREG, (0x3F & (Decimal_To_BCD(hSet))));
			break;
		}
	}
	
}
////////////////////////////// DS1307_SetDate ///////////////////////////////////////
void DS1307_SetDate(unsigned char daySet, unsigned char dateSet, unsigned char monthSet, unsigned int yearSet)
{
	DS1307_Write(DAYREG, (Decimal_To_BCD(daySet)));
	DS1307_Write(DATEREG, (Decimal_To_BCD(dateSet)));
	DS1307_Write(MONTHREG, (Decimal_To_BCD(monthSet)));
	DS1307_Write(YEARREG, (Decimal_To_BCD(yearSet % 100)));
}
