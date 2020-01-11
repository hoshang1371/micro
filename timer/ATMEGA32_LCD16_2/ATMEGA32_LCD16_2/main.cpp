/*
 * ATMEGA32_LCD16_2.cpp
 *
 * Created: 9/19/2019 4:23:55 PM
 * Author : hojjat
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define RS 6
#define E  5

void send_a_command (unsigned char command);
void send_a_character(unsigned char character);

int main(void)
{
	DDRA = 0xFF;
	DDRD = 0xFF;
	_delay_ms(50);
	send_a_command(0x01);// sending all clear command
	send_a_command(0x38);// 16*2 line LCD
	send_a_command(0x0c);// screen and cursor OFF  0x0e  0x0c  
	//send_a_command(0x0f);
	

/*
	send_a_command(0x1c);//Shift complete data to right side
	send_a_command(0x1c);//Shift complete data to right side
	send_a_command(0x14);//Cursor position shifts to right
	send_a_command(0x10);//Cursor position Shifts to left
	send_a_command(0x80);//Move cursor to the beginning of second line */

	send_a_command(0x14);//Cursor position shifts to right
	send_a_command(0x14);//Cursor position shifts to right
		    
	send_a_character (0x48); // ASCII(American Standard Code for Information Interchange) code for 'H'
	send_a_character (0x65); // ASCII(American Standard Code for Information Interchange) code for 'e'
	send_a_character (0x6C); // ASCII(American Standard Code for Information Interchange) code for 'l'
	send_a_character (0x6C); // ASCII(American Standard Code for Information Interchange) code for 'l'
	send_a_character (0x6f); // ASCII(American Standard Code for Information Interchange) code for 'o'
    send_a_character (0x20); // ASCII(American Standard Code for Information Interchange) code for ' '
	send_a_character (0x57); // ASCII(American Standard Code for Information Interchange) code for 'w'
	send_a_character (0x6f); // ASCII(American Standard Code for Information Interchange) code for 'o'
	send_a_character (0x72); // ASCII(American Standard Code for Information Interchange) code for 'r'
	send_a_character (0x6C); // ASCII(American Standard Code for Information Interchange) code for 'l'
	send_a_character (0x64); // ASCII(American Standard Code for Information Interchange) code for 'd'
	send_a_character (0x21); // ASCII(American Standard Code for Information Interchange) code for '!'
	
	send_a_command(0xC0);//Move cursor to the beginning of second line 0x80
	
	send_a_command(0x14);//Cursor position shifts to right
	send_a_command(0x14);//Cursor position shifts to right
	
	send_a_character (0x48); // ASCII(American Standard Code for Information Interchange) code for 'H'
	send_a_character (0x6f); // ASCII(American Standard Code for Information Interchange) code for 'o'
	send_a_character (0x6A); // ASCII(American Standard Code for Information Interchange) code for 'j'
	send_a_character (0x6A); // ASCII(American Standard Code for Information Interchange) code for 'j'
	send_a_character (0x61); // ASCII(American Standard Code for Information Interchange) code for 'a'
	send_a_character (0x74); // ASCII(American Standard Code for Information Interchange) code for 't'
	
/*
	_delay_ms (1000);	
	send_a_command(0x01);// sending all clear command*/
	
	while (1) 
    {
		PORTD ^=(1<<PD7);
		_delay_ms (500);
    }
}

void send_a_command (unsigned char command)
{
	PORTA=command;
	PORTD&= ~(1<<RS);
	PORTD|= (1<<E);
	_delay_ms(50);
	PORTD&= ~(1<<E);
	PORTA =0;
}

void send_a_character (unsigned char character)
{
	PORTA=character;
	PORTD|= (1<<RS);
	PORTD|= (1<<E);
	_delay_ms(50);
	PORTD&= ~(1<<E);
	PORTA =0;
}

