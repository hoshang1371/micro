/*
 * sim800ATM8.cpp
 *
 * Created: 12/17/2019 5:04:01 PM
 * Author : hojjat
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>

# define USART_BAUDRATE 9600
# define BAUD_PRESCALE ((( F_CPU / ( USART_BAUDRATE * 16UL))) - 1)

# define on 1
# define off 0

#define FALSE   (0==1)
#define TRUE    (1==1)

#define DISABLE  0

#define Uart_send_byte(ch)         ( UDR = ch)
#define Uart_rx_ready()            ((UCSRA & (1<<RXC)) >> RXC )
#define Uart_tx_ready()			   (((UCSRA &   1<<UDRE)) >> UDRE )

#define BUFFER_LEN				180
#define TEX_RECIVE_LEN			100
#define MOBILE_NUMBER_LEN		53
#define COMPAR_LEN				50
#define DATA_LEN				250
#define CHARGE_LEN				15
#define MOBILE_BUFFER_LEN		14
#define TEX_SEND_LEN			80
#define SMS_QUEUE				8
#define CH_SMS_LEN				3
#define NAME_OPERATOR_LEN		10

#define Uart_get_byte()            ( UDR )

#define BUF_SIZE 100
char StrBuff[BUF_SIZE]="ATD09367262334;";//ATD

int i;

// char bufGsm[40] = {};
// char bufGsm1[60] = {};
// volatile unsigned char	 tx_gsm,Temp_gsm,numberRX = 0 ,the_data_has,addressBufGsm1, addressTemp = 0;

/*
struct{
	char buffer[BUFFER_LEN+1],unread,tex_recive[TEX_RECIVE_LEN+1],net_registration,sim_opator,name_operator[NAME_OPERATOR_LEN+1],chargere[CHARGE_LEN+1],tex_send[TEX_SEND_LEN+1];
	char compar[COMPAR_LEN+1],data[DATA_LEN+1],ch,ch_sms[CH_SMS_LEN],err_counter,recived_sms[SMS_QUEUE+1][2],mobile_number[MOBILE_NUMBER_LEN+1],mobile_buffer[MOBILE_BUFFER_LEN+1];
	char recive_sms,dell,rdy,re_send,flag,charj,flag_charj,flag_simname,net_state,ring,apply,signal_value,rdy_tout,hangup,answer,flag_unread;
	int index,stat,recived_sms_counter,number_of_charecter;
	volatile char recive;
}gsm;*/

void uart_putchar (unsigned char ch)
{
	while(!Uart_tx_ready());
	Uart_send_byte(ch);
}

void uart_put_string (char *data_string, char enter)
{
	while(*data_string) uart_putchar (*data_string++);
	if(enter)uart_putchar (13);
}

void uart_put_string_p (const char *data_string, char enter)
{
	while(pgm_read_byte(data_string)) uart_putchar (pgm_read_byte(data_string++));
	if(enter)uart_putchar (13);
}

unsigned char uart_getchar (void)
{
	uint8_t ch,t=0;

	while(!Uart_rx_ready())
	{
		if ((TIFR & (1 << TOV0)) > 0)
		{
			TIFR = (1<<TOV0);
			t++;
			if(t > 5){i++;return 0xFF;}
		}
	}
	ch = Uart_get_byte();
	return ch;
}

unsigned char uart_getstring (char *buffer_data, int len_buffer)
{
	uint8_t z;
		
	memset(buffer_data,0,len_buffer);
	i=0;
		
	TCNT0 =0;
	TCCR0 |= ((1<<CS00) | (1<<CS02)); //PS: 1024
		
	while(1)
	{
		z = uart_getchar();
		if ((z==0xFF) && (i != 0)){TCCR0=0;return i;}
		if (i<len_buffer/* && z!=13 && z!=10*/){buffer_data[i] = z;i++;}
	}
}

ISR(INT0_vect)
{
	
	uart_put_string (StrBuff, 1);
	PORTB |=(1<<PB0);
}

// ISR(INT1_vect)
// {
// }
/*
void wait_flage(void)
{
	static int cu=0;
	gsm.recive = DISABLE;
	while(gsm.recive==DISABLE){cu++;_delay_ms(10);if(cu>400){break;}}
	gsm.recive = DISABLE;
}*/

void serial_init(){
	UCSRB = (1 << RXEN ) | (1 << TXEN );
	UCSRC = (1 << URSEL ) | (1 << UCSZ0 ) | (1 << UCSZ1 );
	UBRRH = ( BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE ;
	UCSRB |= (1 << RXCIE );
	/*sei ();*/
}


// ISR ( USART_RXC_vect )
// {
// 
// }
// ISR ( USART_UDRE_vect )
// {
// 	
// }


int main(void)
{
	GICR|=(1<<INT0);//|(1<<INT1)
	
	MCUCR|=(1<<ISC01);//(1<<ISC00)|
	
	_delay_ms(400);
	
	serial_init();
	DDRB |=(1<<PB0);
	/*PORTB |=(1<<PB0);*/
	/*if (get_ok() == TRUE)*/ 
	//uart_put_string_p ("ATD09367262334;", 1);
	/*uart_put_string (StrBuff, 1);*/
// 	uart_put_string("ATD",0);
// 	uart_put_string(StrBuff,1);
// 	wait_flage();
	_delay_ms(400);
	//uart_put_string (StrBuff, 1);
	sei ();
    while (1) 
    {
		
		_delay_ms(500);
		/*PORTB ^=(1<<PB0);*/
    }
}


