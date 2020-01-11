/*
 * atm8Timer.cpp
 *
 * Created: 9/12/2019 3:34:44 PM
 * Author : hojjat
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char  bcd_7seg[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char  code[4]={0,1,2,3};
unsigned char  second=0;
unsigned char  minute=0;
unsigned char  hour=0;
bool h = true, h1 = true;


void init_timer()
{
	//--------------------------------------------------------------------------
	//timer2
	_delay_ms(2000);
	ASSR |= (1<<AS2);						// Set timer2 to run asynchronous
	TCCR2 |= (1<<CS20) | (1<<CS22);			// Start timer2 with prescaler = 128 (TCNT2 = 255 takes 1 sec.)
	while(ASSR & (1<<TCN2UB));				// Wait until TC2 is updated
	TIMSK = (1<<TOIE2);						// Enable timer2 overflow interrupt
	//--------------------------------------------------------------------------
	//timer1
    // set up timer with prescaler = 64 and CTC mode
    TCCR1B |= (1 << WGM12)|(1 << CS11);//|(1 << CS10)
    
    // initialize counter
    TCNT1 = 0;
    
    // initialize compare value
    OCR1A = 156;
    
    // enable compare interrupt
    TIMSK |= (1 << OCIE1A);
	//--------------------------------------------------------------------------	
	sei();									// Enable global interrupt
}

ISR(TIMER2_OVF_vect)
{
	if (h == true)
	{
		if(++second == 60)
		{
			second=0;
			if(++minute == 60)
			{
				minute=0;
				if(++hour == 24) hour=0;
			}
	  }
	PORTC ^=(1<<PC0);
	}
}

ISR (TIMER1_COMPA_vect)
{
	static int select = 0, x20 ;//, b 
/*
	b = (1<<select);
	PORTB |= b;*/
	PORTB &= ~((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3));	
 switch (select)
 {
	 case 0:
		PORTD=bcd_7seg[minute%10];
	 break;
	 
	 case 1:
		PORTD=bcd_7seg[minute/10];
	 break;
	 
	 case 2:
		PORTD=bcd_7seg[hour%10];
	 break;
	 
	 case 3:
		PORTD=bcd_7seg[hour/10];
	 break;
 }
	PORTB = (1<<select);
	if (++select==4) select = 0;
	
	if (++x20 == 20)
	{
		x20 = 0;
		PORTC ^=(1<<PC1);
		//PORTC ^=(1<<PC2);
		if((PINC & (1<<PC3)) == 8) //If switch is pressed  if(PINC & (1<<PC3) == 1)
		{
			PORTC |= (1<<PC2); //Turns ON LED
			second=0;
			minute=0;
			hour=0;
		}
		else if((PINC & (1<<PC4)) == 16)
		{
			PORTC |= (1<<PC2); //Turns ON LED
			if (h1 == true)
			{
				h = false;
				h1 = false;
			}
			else if (h1 == false)
			{
				h = true;
				h1 = true;				
			}

		}
		else
		{
			 PORTC &= ~(1<<PC2); //Turns OFF LED
		}
	}

	
}

int main(void)
{
    DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3);
	DDRD |= (1<<PD0)|(1<<PD1)|(1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5)|(1<<PD6)|(1<<PD7);
	DDRC = (1<<PC0)|(1<<PC1)|(1<<PC2);
	//DDRC &= ~(1<<PC3);
	
	init_timer();
	
    while (1) 
    {
		_delay_ms (500);
    }
}

