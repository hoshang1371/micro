/*
 * atmega8_dimer.cpp
 *
 * Created: 12/28/2019 6:58:56 PM
 * Author : hojjat
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int d = 100;
void wait(unsigned int del) {
	for(del*=2; del; del--);
}

ISR(INT0_vect)//<<<<<-----------------------------------------------------------
{
	// 		PORTB.3 = 0; PC4
	// 		wait(d);
	// 		PORTB.3 = 1;????
	//  portc->_4 = 0;
	PORTB &= ~(1<<PB3);
// 	wait(d);
 	_delay_us(9500);
	PORTB |= (1<<PB3);
	/*	_delay_ms(1000);*/
}

int main(void)
{
	PORTB = 0x00;
	DDRB = 0x08;
	PORTD = 0x00;
	DDRD = 0x00;
	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Rising Edge
	// INT1: Off
	GICR |= 0x40;
	MCUCR = 0x03;
	GIFR = 0x40;
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK = (0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<TOIE0);
	/*PORTB |= (1<<PB3);*/
	// Global enable interrupts
	sei();
    while (1) 
    {
		d++;
		if(d==300)d=100;
		 _delay_ms(60);
    }
}

