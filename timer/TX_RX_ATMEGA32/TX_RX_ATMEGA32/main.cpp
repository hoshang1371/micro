/*
 * TX_RX_ATMEGA32.cpp
 *
 * Created: 9/18/2019 4:06:37 PM
 * Author : hojjat
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

volatile char Rec_Data;  

int main(void)
{
	DDRD |=(1<<PD7);
	
	 DDRD  = 0X02;                    /* PD0(RX)-I/P, PD1(TX)-O/P                         */
	 UCSRA = 0X00;                    /* Clears TXC & RXC Flag Bit                        */
	 UCSRB |= (1<<TXEN)|(1<<RXEN);                    /* Transmission & Reception Enable (TXEN=1, RXEN=1) */
	 UCSRC = 0X86;                    /* URSEL=1,UMSEL=0,UCSZ1=1,UCSZ0=0                  */
	 UBRRL = 103;                      /* Serial Baudrate=9600                             */
	 UDR   = 'A';                     /* Transmit a charcter                              */
	 while((UCSRA & 0X20)!=0X20);     /* UDRE Flag Bit Check                              */
		
    while (1) 
    {
		PORTD ^=(1<<PD7);
		
/*
		while((UCSRA & 0X80)!=0X80);    / * RXC is set when unread data is in receive buffer * /
		Rec_Data=UDR;*/                   /* Store the received character                     */
		UDR = 'H'; //  Rec_Data              /* Transmit the received character                  */
		while((UCSRA & 0X20)!=0X20);    /* Wait here till UDR is empty                      */
		UDR = 'o'; //  Rec_Data              /* Transmit the received character                  */
		while((UCSRA & 0X20)!=0X20);    /* Wait here till UDR is empty                      */
		UDR = 'j'; //  Rec_Data              /* Transmit the received character                  */
		while((UCSRA & 0X20)!=0X20);    /* Wait here till UDR is empty                      */
		UDR = 'j'; //  Rec_Data              /* Transmit the received character                  */
		while((UCSRA & 0X20)!=0X20);    /* Wait here till UDR is empty                      */
		UDR = 'a'; //  Rec_Data              /* Transmit the received character                  */
		while((UCSRA & 0X20)!=0X20);    /* Wait here till UDR is empty                      */
		UDR = 't'; //  Rec_Data              /* Transmit the received character                  */
		while((UCSRA & 0X20)!=0X20);    /* Wait here till UDR is empty                      */
		UDR = '\n';   //Rec_Data              /* Transmit the received character                  */
		while((UCSRA & 0X20)!=0X20);    /* Wait here till UDR is empty                      */
		_delay_ms (500);
    }
}

