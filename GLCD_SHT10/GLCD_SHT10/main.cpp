#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "glcd-font.h"
#include "sht/sht.h"
#include "sht/sht.c"
#include  <stdint-gcc.h>
// #include "I2C.h"
// #include  "DS1307.h"


// #include  "Include/Header/DS1307.h"
// #include "Include/Header/I2C.h"
#define BUF_SIZE 100
char StrBuff[BUF_SIZE];



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

//================================================
//DDDDDDDDDDDDDDDDDD DS1307 Registers Addresses SSSSSSSSSSSSSSSSSSSSSSS
#define DS1307_Address		0x68
#define DS1307_Read_addr		((DS1307_Address << 1) | 0x01)	//0xD1
#define DS1307_Write_addr		((DS1307_Address << 1) & 0xFE)	//0xD0
#define SECONDREG			0x00
#define MINUTEREG			0x01
#define HOURREG				0x02
#define DAYREG				0x03
#define DATEREG				0x04
#define MONTHREG			0x05
#define YEARREG				0x06
#define CONTROLREG			0x0E
#define STATUSREG			0x0F
#define _24_hour_format		0
#define _12_hour_format		1
#define AM					0
#define PM					1
//VVVVVVVVVVVVVVVVVVVVVVVVVV Variables RRRRRRRRRRRRRRRRRRRRRRRRR
unsigned int Year ;
unsigned char Mount ;
unsigned char Day ;
unsigned char DayOfWeek ;
unsigned char Hour ;
unsigned char Minute ;
unsigned char Second ;
unsigned char am_pm ;
unsigned char hr_format;
int ys,ms,ds;
//FFFFFFFFFFFFFFFFFFFFFFFFF Functions FFFFFFFFFFFFFFFFFFFFFFFFFFF
void DS1307_Init(void);
unsigned char BCD_To_Decimal(unsigned char d);
unsigned char Decimal_To_BCD(unsigned char d);
unsigned char DS1307_Read(unsigned char Address);
void DS1307_Write(unsigned char Address, unsigned char _value);
void DS1307_GetTime(unsigned char* hourP, unsigned char* minutP, unsigned char* secP, unsigned char* ampmP, unsigned char hour_format);
void DS1307_GetDate(unsigned char* dayP, unsigned char* dateP, unsigned char* montP, unsigned int* yearP);
void DS1307_SetTime(unsigned char hSet, unsigned char mSet, unsigned char sSet, unsigned char am_pm_state, unsigned char hour_format);
void DS1307_SetDate(unsigned char daySet, unsigned char dateSet, unsigned char monthSet, unsigned int yearSet);
void init_timer(void);
//===========================================
#define GLCD_DATA_PORT PORTB
#define GLCD_CTRL_PORT PORTA
#define GLCD_DPORT_DIR DDRB
#define GLCD_CPORT_DIR DDRA

#define RS  PA0
#define RW  PA1
#define E   PA2
#define RST PA3
#define CS1 PA4
#define CS2 PA6

typedef unsigned char byte;
#define E_DELAY 3

void glcd_cmd(unsigned char cmd);
void glcd_dta(unsigned char dta);
void glcd_PageSelect(char pge);//
void glcd_writeChar(char *chr);//char *chr
void glcd_SetCursor(uint8_t x, uint8_t y);
void glcd_writeStr(char x,char y,char pge,char *str);//
/*void glcd_writeStrFarsi(char x,char y,char pge,char *str);//*/
void glcd_writeImg(char *pxl);
void glcd_int(void);

void glcd_clear(void);
int m2s(int ym,int mm,int dm,int *ys,int *ms,int *ds);

/*
char SYMS3_BMP[1024] = {
	255,255,255, 63,255,255,255,255, 63,255,255,127,191,191,191,191,
	255,255,127,191,191,127,127,255,255,255,255,191,  7,187,187,251,
	191,191,191,127,255,255,255, 63,191,191,191,191,127,191,191,191,
	191,127,255, 59,255,255,  3,255,255, 59,255,255,255,255,191,191,
	191,127,255,255,127,127,191,255,255,255,255,255,127,191,191,191,
	191, 63,255,255,255,127,191,255, 63,191,191,191,191,127,191,191,
	191,191,127,255,  3,191,191,191,127,255,255,255,127,191,191,191,
	127,255,255,255,  3,255,255,127,191,191,191,191,255,255,255,255,
	255,255,255,240,239,239,239,239,224,255,255,246,237,237,243,255,
	255,240,237,237,237,237,244,253,255,255,255,255,224,255,255,243,
	237,238,238,224,255,255,255,224,255,255,255,255,224,255,255,255,
	255,224,255,224,255,255,224,255,255,224,255,255,255,243,237,238,
	238,224,255,255,224,255,255,255,255,255,255,255,246,237,237,243,
	255,126, 57,199,249,254,255,255,224,255,255,255,255,224,255,255,
	255,255,224,255,224,239,239,239,247,248,255,255,240,239,239,239,
	247,248,255,255,224,255,255,246,237,237,243,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,191, 31,
	15, 15,159,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255, 15,  7,  7, 15,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255, 31, 95,223,223,223,223,223,223,223,223,223,223,223,223,223,
	223,223,223,223,223, 95, 31,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255, 63, 31,143,207,199,  7,  3,  3,  1,  1,  3,
	6,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,207,  7,  3,
	3,  3,  7,199,255,255,255,255,255,255,255,255,255,255,255,255,
	255,  0,255,254,253,251,119, 47,159,191,191,191,191,191,191,159,
	47,119,251,253,254,255,  0,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,224,224,255,255,  3,  0,  0,  0,  0, 56,254,
	252,248,249,241,243,227,231,231,255,255,255,255,255,255,255,255,
	255,255,255,127, 63, 63, 31, 15, 15,  7,  7,  3,  0,  0,  0,  0,
	1,  3,  7,  7, 15, 15, 31, 63, 63,127,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,127,255,  0,  0,
	0, 63, 63, 63, 63, 63, 63, 63, 63,255,255,255,255,255,255,255,
	255,224,231,227,233,236,238,239,239,239,239,239,239,239,239,239,
	239,238,236,233,227,231,224,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255, 63,  7,  0,128,224,248,252,248,224,  0,
	1,  7, 63,255,255,255,255,255,255,255,255,255,143,135,131,193,
	193,192,224,224,224,240,240,240,248,248,248,252,  0,  0,  0,  0,
	252,252,248,248,248,240,240,240,224,224,224,192,193,193,131,135,
	143,255,255,255,255,255,127, 15,  3,227,249,248,252,255,224,224,
	224,230,230,230,230,230,230,230,230,231,231,  7,  7, 15,127,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,239,225,224,248,254,255,255,255,255,255,255,255,
	248,224,224,227,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,127,127, 63, 31,  0,  0,128,  0,
	15, 31, 63,127,127,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,252,224,193,  7, 15, 63,127,127,255,255,
	255,255,255,255,255,255,255,127, 63, 31, 15,143,248,192,  0,  3,
	31,159,159,143,207,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,252,252,254,254,255,255,255,255,
	255,254,254,252,252,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,254,254,254,252,252,252,
	249,249,249,249,248,248,252,252,252,254,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
	255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
};*/
int i = 0, n = 0,motor_ = 22,roz_ = 22;//,temp = 22,hum = 22
float temp = 22,hum = 22,temp_,hum_;
// typedef
// struct _port_{
// 	uint16_t _0:1;
// 	uint16_t _1:1;
// 	uint16_t _2:1;
// 	uint16_t _3:1;
// 	uint16_t _4:1;
// 	uint16_t _5:1;
// 	uint16_t _6:1;
// 	uint16_t _7:1;
// }port;
//  
unsigned int d = 100;

void wait(unsigned int del) {
	for(del*=2; del; del--);
}
/*
ISR(INT0_vect)//<<<<<-----------------------------------------------------------
{
// 		PORTB.3 = 0; PC4
// 		wait(d);
// 		PORTB.3 = 1;???? 
//  portc->_4 = 0;
	PORTC &= ~(1<<PC4);
	wait(d);
	//_delay_us(9500);
	PORTC |= (1<<PC4);
/ *	_delay_ms(1000);* /
}*/ 
 
ISR (TIMER1_COMPA_vect)
{
	
	static int x20 = 0;
	if (++x20 == 20)
	{
		 x20 = 0;

		if((PIND & (1<<PD4)) == 16) //If switch is pressed  if(PINC & (1<<PC3) == 1)
		{
			PORTC |= (1<<PC3); //buzzer
			PORTC |= (1<<PC2);
			i++;
			if (i==2) i = 4;
			if (i==8) i = 0;
		}
//============================================	
		else if((PIND & (1<<PD5)) == 32) //If switch is pressed  if(PINC & (1<<PC3) == 1)
		{
			PORTC |= (1<<PC3); //buzzer
			PORTC |= (1<<PC2);
			switch( i )
			{
				case 0:
				temp_ += 1;
				break;	
				
				case 1:
				hum_ += 1;
				break;							
				
				case 4:
					n++;
				break;				
				
				case 5:
				 temp += 0.1;
				break;
			
				case 6:
					hum += 0.1;
				break;	
				
				case 7:
				motor_ += 1;
				break;						
			}
		}
//====================================	
		else if((PIND & (1<<PD6)) == 64) //If switch is pressed  if(PINC & (1<<PC3) == 1)
		{
			PORTC |= (1<<PC3); //buzzer
			PORTC |= (1<<PC2);
		
			switch( i )
			{
				case 0:
					temp_ -= 1;
				break;	
				
				case 1:
					hum_ -= 1;
				break;							
								
				case 4:
					n--;
				break;
				
				case 5:
					temp -=0.1;
				break;
			
				case 6:
					hum -=0.1;
				break;
				
				case 7:
					motor_ -= 1;
				break;				
			}		
		
		}
		else
		{
		PORTC &= ~(1<<PC3); //buzzer
		PORTC &= ~(1<<PC2);
		}
//=======================================
		PORTD ^=(1<<PD7);
	}
}


int main(void)
{	
	
	DS1307_Init();	
	I2C_Init();
	_delay_ms(10);
	//init interupt
	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Rising Edge
	// INT1: Off
// 	GICR |= 0x40;
// 	MCUCR = 0x03;
// 	GIFR = 0x40;
/*
	GICR  |=(1<<INT0);
	MCUCR |=(1<<ISC01)|(1<<ISC00);
	GIFR  |=(1<<INTF0);
	
*/
	//==================================
	char Temperature1[9];	
	char Humidity1[9];
// 	char Temperature[9] = "22";
// 	char Humidity[9] = "22";
	char roz[9] = "21";
	char motor[9] = "21";
	

	char donogh[8]	 = {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00};
	char space[8]	 = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	char xhard[8]	 = {0x00,0x00,0x24,0x24,0x24,0x38,0x00,0x00};
	char xharm[8]	 = {0x20,0x20,0x20,0x20,0x30,0x48,0x48,0x30};	  
	char xhara[8]	 = {0x00,0x1E,0x20,0x20,0x20,0x20,0x20,0x20};
	char xharr[8]	 = {0x00,0x80,0x80,0x40,0x30,0x00,0x00,0x00};
	char xhart[8]	 = {0x20,0x20,0x3E,0x30,0x28,0x28,0x18,0x00};	
	char xharo[8]	 = {0x00,0xB0,0xA8,0x78,0x20,0x20,0x20,0x20};
	char xharb[8]	 = {0x20,0x20,0x20,0x20,0xA0,0x20,0x28,0x30};
	char xhartt[8]	 = {0x00,0x30,0x28,0x22,0x20,0x22,0x28,0x30};	
	char xharn[8]	 = {0x20,0x20,0x20,0x20,0x22,0x20,0x18,0x00};
	char xhare[8]	 = {0x00,0x40,0xA0,0xB0,0x28,0x28,0x20,0x20};
	char xhargh[8]	 = {0x00,0x40,0xA0,0xB0,0x28,0x2A,0x20,0x20};	
	char xharrr[8]	 = {0x00,0x80,0x80,0x40,0x30,0x20,0x20,0x20};	
	char xharh[8]	 = {0x00,0x00,0x30,0x28,0x28,0x30,0x00,0x00};	
	char xharhh[8]   = {0x00,0x18,0x14,0x14,0x18,0x20,0x20,0x20};	
	char xharh_[8]   = {0x20,0x20,0x20,0x30,0x28,0x3A,0x2C,0x18};	
	char xhard_[8]   = {0x00,0x00,0x24,0x24,0x24,0x38,0x20,0x20};	
	char xharch[8]   = {0x20,0x20,0x28,0x28,0x68,0xB0,0x60,0x20};
	char xhargh_[8]  = {0x20,0x20,0x20,0x20,0x30,0x2A,0x28,0x32};
	char xhart_[8]   = {0x20,0x20,0x20,0x22,0x20,0x22,0x28,0x30};
	char xharl[8]    = {0x20,0x20,0x20,0x20,0x1F,0x20,0x20,0x20};
	char xharn__[8]  = {0x00,0x00,0x60,0x80,0x88,0x80,0x60,0x00};	
	char xhark_[8]	 = {0x22,0x25,0x25,0x25,0x25,0x25,0x25,0x19};
	char xhar_k[8]	 = {0x30,0x28,0x2C,0x2A,0x20,0x3F,0x20,0x20};
	char xhar_b_[8]	 = {0x20,0x20,0x20,0x20,0xB0,0x20,0x20,0x20};
	char xharsh_[8]	 = {0x20,0x20,0x20,0x38,0x22,0x39,0x22,0x18};
	char xhar_t_[8]	 = {0x20,0x20,0x20,0x22,0x30,0x22,0x20,0x20};
	char felesh[8]   = {0x00,0x1C,0x1C,0x1C,0x7F,0x3E,0x1C,0x08};
														
	glcd_int();
	init_timer();
// 	
// 	port *portc;
// 	portc = (struct _port_ *) & PORTC;
// 	
// 	for (int i = 0; i < 5; i++) {
// 		LED_HIGH;
// 		_delay_ms(100);
// 		LED_LOW;
// 		_delay_ms(100);
// 	}
			
// 			glcd_SetCursor(0,0);
// 			glcd_writeChar(SYMS3_BMP);
// 			glcd_SetCursor(0,5);
// 			glcd_writeChar(space);
// 			glcd_SetCursor(0,10);
// 			glcd_writeChar(xharH);
// 			glcd_SetCursor(0,15);
// 			glcd_writeChar(xharO);
// 			glcd_SetCursor(0,21);
// 			glcd_writeChar(xharJ);
	/*DDRB |=(1<<PB2)|(1<<PB3)|(1<<PB5);*/
	DDRD |=(1<<PD7);
	DDRD &=~((1<<PD4)|(1<<PD5)|(1<<PD6));//|(1<<PD7)
	DDRC |=((1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6)|(1<<PC7));
	/*DDRB &=~(1<<PB4);*/
	//PORTB |= (1 << PINB4);
// 	DS1307_SetTime(16, 53, 00, 1, 0);
// 	DS1307_SetDate(1, 17, 12, 2019);
	//glcd_writeImg(SYMS3_BMP);
	_delay_ms (3000);
	glcd_clear();
	//d=50;
    while (1) 
    {	
		        d++;
		        if(d==300)d=100;
		        _delay_ms(60);
		DS1307_GetTime(&Hour, &Minute, &Second, &am_pm, hr_format);
		DS1307_GetDate(&DayOfWeek, &Day, &Mount, &Year);

		m2s(Year,Mount,Day,&ys,&ms,&ds);
		sht_data data;
		data = sht_sense();
		
 		dtostrf((double)data._humidity+hum_, 5, 3, Humidity1);
 		dtostrf((double)data._temperature+temp_, 5, 3, Temperature1);

		sprintf(StrBuff, "%02u:%02u:%02u", Hour, Minute, Second);
		glcd_writeStr(0, 2, 0,StrBuff);//
/*		sprintf(StrBuff, "%02u/%02u/%02u",  Year, Mount, Day);*/
		sprintf(StrBuff, "%02u/%02u/%02u",  ys-2000, ms, ds);
		glcd_writeStr(0, 2, 1,StrBuff);//
		glcd_writeStr(0, 0, 0,Temperature1);
		glcd_writeStr(0, 1, 0,Humidity1);
		
		dtostrf(hum, 3, 1, StrBuff);
		glcd_writeStr(0, 6, 0,StrBuff);//___________________________________________
		dtostrf(temp, 3, 1, StrBuff);		
		glcd_writeStr(0, 5, 0,StrBuff);//___________________________________________
		

		glcd_writeStr(0, 3, 0,roz);
		dtostrf(motor_, 3, 0, motor);
		glcd_writeStr(0, 7, 0,motor);		
// 		glcd_writeStr(0, 6, 0,Humidity);
// 		glcd_writeStr(0, 5, 0,Temperature);
		

		
		glcd_PageSelect(1);
		glcd_SetCursor(0, 56);
		glcd_writeChar(xhard);
		glcd_SetCursor(0, 48);
		glcd_writeChar(xharm);
		glcd_SetCursor(0, 40);
		glcd_writeChar(xhara);
 		glcd_SetCursor(0, 16);
 		glcd_writeChar(donogh);
		 
		glcd_SetCursor(1, 56);
		glcd_writeChar(xharr);
		glcd_SetCursor(1, 48);
		glcd_writeChar(xhart);
		glcd_SetCursor(1, 40);
		glcd_writeChar(xharo);
		glcd_SetCursor(1, 32);
		glcd_writeChar(xharb);
		glcd_SetCursor(1, 24);
		glcd_writeChar(xhartt);		
		glcd_SetCursor(1, 16);
		glcd_writeChar(donogh);
		
		glcd_SetCursor(5, 56);
		glcd_writeChar(xhard);
		glcd_SetCursor(5, 48);
		glcd_writeChar(xharm);
		glcd_SetCursor(5, 40);
		glcd_writeChar(xhara);
		glcd_SetCursor(5, 16);
		glcd_writeChar(donogh);
		
		
		glcd_SetCursor(6, 56);
		glcd_writeChar(xharr);
		glcd_SetCursor(6, 48);
		glcd_writeChar(xhart);
		glcd_SetCursor(6, 40);
		glcd_writeChar(xharo);
		glcd_SetCursor(6, 32);
		glcd_writeChar(xharb);
		glcd_SetCursor(6, 24);
		glcd_writeChar(xhartt);
		glcd_SetCursor(6, 16);
		glcd_writeChar(donogh);
			
			
		glcd_SetCursor(4, 56);
		glcd_writeChar(xharn);	
		glcd_SetCursor(4, 48);
		glcd_writeChar(xharo);
		glcd_SetCursor(4, 40);
		glcd_writeChar(xhare);		
		glcd_SetCursor(4, 16);
		glcd_writeChar(donogh);
		
		glcd_SetCursor(3, 56);
		glcd_writeChar(xharm);
		glcd_SetCursor(3, 48);
		glcd_writeChar(xhara);
		glcd_SetCursor(3, 40);
		glcd_writeChar(xharn);
		glcd_SetCursor(3, 32);
		glcd_writeChar(xhard_);
		glcd_SetCursor(3, 24);
		glcd_writeChar(xharh);
 		glcd_SetCursor(3, 16);
 		glcd_writeChar(xharb);
 		glcd_SetCursor(3, 8);
 		glcd_writeChar(xharhh);			 
		//glcd_PageSelect(0); 	
 		glcd_SetCursor(3, 0);
 		glcd_writeChar(xharh_);	//____________________________________
		 
		glcd_SetCursor(7, 56);
		glcd_writeChar(xharm);
		glcd_SetCursor(7, 48);
		glcd_writeChar(xharo);
		glcd_SetCursor(7, 40);
		glcd_writeChar(xhart_);
		glcd_SetCursor(7, 32);
		glcd_writeChar(xharo);
		glcd_SetCursor(7, 24);
		glcd_writeChar(xharr);
		glcd_SetCursor(7, 16);
		glcd_writeChar(donogh);
				 		
		glcd_PageSelect(0);
		
		if (i==0)
		{
			glcd_SetCursor(1, 56);
			glcd_writeChar(space);			
			glcd_SetCursor(5, 56);
			glcd_writeChar(space);
			glcd_SetCursor(6, 56);
			glcd_writeChar(space);
			glcd_SetCursor(7, 56);
			glcd_writeChar(space);
		}
		else if (i==1)
		{
			glcd_SetCursor(0, 56);
			glcd_writeChar(space);
			glcd_SetCursor(5, 56);
			glcd_writeChar(space);
			glcd_SetCursor(6, 56);
			glcd_writeChar(space);
			glcd_SetCursor(7, 56);
			glcd_writeChar(space);
		}
		else if (i==4)
		{
			glcd_SetCursor(0, 56);
			glcd_writeChar(space);			
			glcd_SetCursor(1, 56);
			glcd_writeChar(space);			
			glcd_SetCursor(5, 56);
			glcd_writeChar(space);
			glcd_SetCursor(6, 56);
			glcd_writeChar(space);
			glcd_SetCursor(7, 56);
			glcd_writeChar(space);
		}				
		else if (i==5)
		{
			glcd_SetCursor(0, 56);
			glcd_writeChar(space);
			glcd_SetCursor(1, 56);
			glcd_writeChar(space);			
			glcd_SetCursor(4, 56);
			glcd_writeChar(space);
			glcd_SetCursor(6, 56);
			glcd_writeChar(space);
			glcd_SetCursor(7, 56);
			glcd_writeChar(space);
		}
		else if (i==6)
		{
			glcd_SetCursor(0, 56);
			glcd_writeChar(space);
			glcd_SetCursor(1, 56);
			glcd_writeChar(space);			
			glcd_SetCursor(4, 56);
			glcd_writeChar(space);
			glcd_SetCursor(5, 56);
			glcd_writeChar(space);
			glcd_SetCursor(7, 56);
			glcd_writeChar(space);			
		}
		else if (i==7)
		{
			glcd_SetCursor(0, 56);
			glcd_writeChar(space);
			glcd_SetCursor(1, 56);
			glcd_writeChar(space);			
			glcd_SetCursor(4, 56);
			glcd_writeChar(space);
			glcd_SetCursor(5, 56);
			glcd_writeChar(space);
			glcd_SetCursor(6, 56);
			glcd_writeChar(space);
		}		
		
		glcd_SetCursor(i, 56);//=================================================
		glcd_writeChar(felesh);
		
		glcd_SetCursor(3, 56);
		glcd_writeChar(xharch);			
		glcd_SetCursor(3, 48);
		glcd_writeChar(xharrr);
		glcd_SetCursor(3, 40);
		glcd_writeChar(donogh);	
		
//-----------------------------------------------------------------------------------
		switch (n)
		{
			case 0:
				glcd_SetCursor(4, 48);
				glcd_writeChar(space);
				glcd_SetCursor(4, 40);
				glcd_writeChar(space);
				glcd_SetCursor(4, 32);
				glcd_writeChar(space);			
				glcd_SetCursor(4, 24);
				glcd_writeChar(xharm);
				glcd_SetCursor(4, 16);
				glcd_writeChar(xharrr);
				glcd_SetCursor(4, 8);
				glcd_writeChar(xhargh);
				glcd_SetCursor(4, 0);
				glcd_writeChar(space);				
			break;
			
			case 1:
				glcd_SetCursor(4, 48);
				glcd_writeChar(xharb);
				glcd_SetCursor(4, 40);
				glcd_writeChar(xharo);
				glcd_SetCursor(4, 32);
				glcd_writeChar(xhargh_);
				glcd_SetCursor(4, 24);
				glcd_writeChar(xharl);
				glcd_SetCursor(4, 16);
				glcd_writeChar(xharm);
				glcd_SetCursor(4, 8);
				glcd_writeChar(xharo);
				glcd_SetCursor(4, 0);
				glcd_writeChar(xharn__);
			break;
			
			case 2:
				glcd_SetCursor(4, 48);
				glcd_writeChar(space);
				glcd_SetCursor(4, 40);
				glcd_writeChar(space);
				glcd_SetCursor(4, 32);
				glcd_writeChar(space);
				glcd_SetCursor(4, 24);
				glcd_writeChar(xhark_);
				glcd_SetCursor(4, 16);
				glcd_writeChar(xhar_b_);
				glcd_SetCursor(4, 8);
				glcd_writeChar(xhar_k);
				glcd_SetCursor(4, 0);
				glcd_writeChar(space);
			break;	
					
			case 3:
				glcd_SetCursor(4, 48);
				glcd_writeChar(xharsh_);
				glcd_SetCursor(4, 40);
				glcd_writeChar(xhar_t_);
				glcd_SetCursor(4, 32);
				glcd_writeChar(xharrr);
				glcd_SetCursor(4, 24);
				glcd_writeChar(xharm);
				glcd_SetCursor(4, 16);
				glcd_writeChar(xharrr);
				glcd_SetCursor(4, 8);
				glcd_writeChar(xhargh);
				glcd_SetCursor(4, 0);
				glcd_writeChar(space);
			break;
			
			default:
				n = 0;		
			break;	
		}
				
			

		
		_delay_us(5);
 		/*PORTB ^=(1<<PB2);*/

// 		_delay_ms (3000);
 		//glcd_clear();
    }
}

void glcd_cmd(unsigned char cmd)
{
	GLCD_DATA_PORT = cmd;
	GLCD_CTRL_PORT &= ~(1<<RS);
	GLCD_CTRL_PORT &= ~(1<<RW);
	GLCD_CTRL_PORT |= (1<<E);
	_delay_ms(1);
	GLCD_CTRL_PORT &= ~(1<<E);
}

void glcd_dta(unsigned char dta)
{
	GLCD_DATA_PORT = dta;
	GLCD_CTRL_PORT |= (1<<RS);
	GLCD_CTRL_PORT &= ~(1<<RW);
	GLCD_CTRL_PORT |= (1<<E);
	_delay_us(10);
	GLCD_CTRL_PORT &= ~(1<<E);
}
void glcd_PageSelect(char pge)
{
	switch(pge)
	{
		case 0:
			GLCD_CTRL_PORT &= ~(1<<CS2);			
			GLCD_CTRL_PORT |=  (1<<CS1);
			break;
			
		case 1:
			GLCD_CTRL_PORT &= ~(1<<CS1);
			GLCD_CTRL_PORT |=  (1<<CS2);
			break;
		
		case 2:
			GLCD_CTRL_PORT |= (1<<CS2);
			GLCD_CTRL_PORT |= (1<<CS1);	
			break;
			
		case 3:
			GLCD_CTRL_PORT &= ~(1<<CS2);
			GLCD_CTRL_PORT &= ~(1<<CS1);
			break;
			
		default:
			GLCD_CTRL_PORT &= ~(1<<CS2);
			GLCD_CTRL_PORT |= (1<<CS1);
			break;	
										
		
	}
}

void glcd_SetCursor(uint8_t x, uint8_t y)
{
	glcd_cmd(0xb8+x);
	glcd_cmd(0x40+y);
}
void glcd_writeChar(char *chr)
{
	uint8_t i;
	//glcd_SetCursor(0,0);
	for (i=0;i<8;i++)
	{
		glcd_dta(*(chr+i));
	}
}
void glcd_writeStr(char x,char y,char pge,char *str)//
{
	int i = 0;
	int startfont = 0,endFont = 0;
	glcd_PageSelect(pge);
	glcd_SetCursor(y ,x );
	while(*str)
	{
		startfont  = (*str - 32)*5;
		/*startfont  = (*str)*8;*/
		endFont    = startfont + 5;
		for (i=startfont;i<endFont;i++)
		{
			glcd_dta(Sys5x7[i]);
			_delay_ms(3);
		}
		glcd_dta(0x00);
		str++;
	}
	
}
		// int h =56;//static
/*
void glcd_writeStrFarsi(char x,char y,char pge,char *str)//
{
	int i = 0;
	
	int startfont = 0,endFont = 0;
	glcd_PageSelect(pge);
	glcd_SetCursor(y ,h );
	while(*str)
	{
		startfont  = (*str - 127)*8;
		endFont    = startfont + 8;
		for (i=startfont;i<endFont;i++)
		{
			glcd_dta(SysFarsi5x7[i]);
			
			_delay_ms(3);
		}
		glcd_SetCursor(y ,h-2 );
		/ *glcd_dta(0x00);* /
		str++;
	}
	
}*/

void glcd_writeImg(char *pxl)
{
				glcd_PageSelect(0);
				glcd_SetCursor(0 ,0 );
				for (int i=0;i<64;i++)		glcd_dta(*(pxl+i));
				glcd_PageSelect(1);
				glcd_SetCursor(0 ,0 );
				for (int i=64;i<128;i++)	glcd_dta(*(pxl+i));
				glcd_PageSelect(0);
				glcd_SetCursor(1 ,0 );
				for (int i=128;i<192;i++)	glcd_dta(*(pxl+i));
				glcd_PageSelect(1);
				glcd_SetCursor(1 ,0  );
				for (int i=192;i<256;i++)	glcd_dta(*(pxl+i));
				glcd_PageSelect(0);
				glcd_SetCursor(2 ,0  );
				for (int i=256;i<320;i++)	glcd_dta(*(pxl+i));		
				glcd_PageSelect(1);
				glcd_SetCursor(2 ,0 );
				for (int i=320;i<384;i++)	glcd_dta(*(pxl+i));	
				glcd_PageSelect(0);
				glcd_SetCursor(3 ,0 );
				for (int i=384;i<448;i++)	glcd_dta(*(pxl+i));	
				glcd_PageSelect(1);
				glcd_SetCursor(3 ,0 );
				for (int i=448;i<512;i++)	glcd_dta(*(pxl+i));		
				glcd_PageSelect(0);
				glcd_SetCursor(4 ,0 );
				for (int i=512;i<576;i++)	glcd_dta(*(pxl+i));	
				glcd_PageSelect(1);
				glcd_SetCursor(4 ,0 );
				for (int i=576;i<640;i++)	glcd_dta(*(pxl+i));	
				glcd_PageSelect(0);
				glcd_SetCursor(5 ,0 );
				for (int i=640;i<704;i++)	glcd_dta(*(pxl+i));																				
				glcd_PageSelect(1);
				glcd_SetCursor(5 ,0 );
				for (int i=704;i<768;i++)	glcd_dta(*(pxl+i));
				glcd_PageSelect(0);
				glcd_SetCursor(6 ,0 );
				for (int i=768;i<832;i++)	glcd_dta(*(pxl+i));
				glcd_PageSelect(1);
				glcd_SetCursor(6 ,0 );
				for (int i=832;i<896;i++)	glcd_dta(*(pxl+i));		
				glcd_PageSelect(0);
				glcd_SetCursor(7 ,0 );
				for (int i=896;i<960;i++)	glcd_dta(*(pxl+i));
				glcd_PageSelect(1);
				glcd_SetCursor(7 ,0 );
				for (int i=960;i<1024;i++)	glcd_dta(*(pxl+i));										
}
void glcd_int(void)
{
	GLCD_DPORT_DIR = 0xff;
	GLCD_CPORT_DIR = 0xff;
	
	GLCD_CTRL_PORT &= ~(1<<RST);
	_delay_ms(10);
	GLCD_CTRL_PORT |= (1<<RST);
	_delay_ms(1);
	glcd_PageSelect(2);
	_delay_ms(1);
	glcd_cmd(0x3f);
	glcd_cmd(0xc0);
	_delay_ms(1);
	glcd_PageSelect(3);
	_delay_ms(1);
	
}
void glcd_clear()
{
	for(int z=0;z<2;z++)
	{
			glcd_PageSelect(z);
			glcd_SetCursor(0 ,0 );
			for(int j=0;j<9;j++)
			{
				for(int i=0;i<65;i++)	glcd_dta(0x00);
				glcd_SetCursor(j ,0 );
			}
	}	
}
//==============================================================================================

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
//===========================================
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
//============================================================================================
int m2s(int ym,int mm,int dm,int *ys,int *ms,int *ds)
{
	unsigned long int ys1,ym1;
	int ym2,ys2,mm1,ms1,k,ms0;
	ym1=ym+2000;
	k=ym1%4;
	ym1--;
	ym1=ym1*365;
	if(mm==1){mm1=0;}
	if(mm==2){mm1=31;}
	if(mm==3){mm1=59;}
	if(mm==4){mm1=90;}
	if(mm==5){mm1=120;}
	if(mm==6){mm1=151;}
	if(mm==7){mm1=181;}
	if(mm==8){mm1=212;}
	if(mm==9){mm1=243;}
	if(mm==10){mm1=273;}
	if(mm==11){mm1=304;}
	if(mm==12){mm1=334;}
	if(k==0){mm1++;}
	ym1=ym1+mm1;
	ym1=ym1+dm;
	ym2=ym+2000;
	ym2--;
	ym2=ym2/4;
	ym1=ym1+ym2;
	ym1=ym1-226899;
	ys2=ym2-155;
	ys1=ym1-ys2;
	*ys=ys1/365;
	*ys=*ys-1299;
	ms1=ys1%365;
	ms0=1;
	if(ms1>31){ms0++;ms1=ms1-31;}
	if(ms1>31){ms0++;ms1=ms1-31;}
	if(ms1>31){ms0++;ms1=ms1-31;}
	if(ms1>31){ms0++;ms1=ms1-31;}
	if(ms1>31){ms0++;ms1=ms1-31;}
	if(ms1>31){ms0++;ms1=ms1-31;}
	if(ms1>30){ms0++;ms1=ms1-30;}
	if(ms1>30){ms0++;ms1=ms1-30;}
	if(ms1>30){ms0++;ms1=ms1-30;}
	if(ms1>30){ms0++;ms1=ms1-30;}
	if(ms1>30){ms0++;ms1=ms1-30;}
	*ds=ms1;
	*ms=ms0;
	return *ys;
	return *ms;
	return *ds;
}

void init_timer(void)
{
	//--------------------------------------------------------------------------
	//timer2
	_delay_ms(2000);
	//--------------------------------------------------------------------------
	//timer1
	// set up timer with prescaler = 8 and CTC mode
	TCCR1B |= (1 << WGM12)|(1 << CS11);//|(1 << CS10)
	
	// initialize counter
	TCNT1 = 0;
	
	// initialize compare value
	OCR1A = 19999;
	
	// enable compare interrupt
	TIMSK |= (1 << OCIE1A);
	//--------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	sei();									// Enable global interrupt
}
