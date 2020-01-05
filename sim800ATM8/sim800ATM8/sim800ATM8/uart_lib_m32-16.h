//******************************************************************************
//! Copyright (c) 2007 Atmel.
//******************************************************************************
#ifndef _UART_LIB_M32_16_H
#define _UART_LIB_M32_16_H

//#define REDUCED_UART_LIB

	int i;
	//_____ I N C L U D E S ________________________________________________________
	#include <stdarg.h>
	#include <avr/pgmspace.h>
	//_____ D E F I N I T I O N S __________________________________________________
	#define DATA_BUF_LEN               10
	
	#define Uart_send_byte(ch)         ( UDR = ch)
	#define Uart_get_byte()            ( UDR )
	
	#define Uart_enable()              ( UCSRB |=  ((1<<RXEN) | (1<<TXEN)) )
	#define Uart_disable()             ( UCSRB &= ~((1<<RXEN) | (1<<TXEN)) )
	
	#define Uart_rx_ready()            ((UCSRA & (1<<RXC)) >> RXC )
	#define Uart_tx_ready()			   (((UCSRA &   1<<UDRE)) >> UDRE )
	// ---------- Pre-definitions for "Uart_hw_init(config)" macro.
	#define CONF_9BIT_NOPAR_1STOP      ( (0<<UPM0) | (0<<USBS) | (7<<(UCSZ0-1)) )
	#define CONF_9BIT_NOPAR_2STOP      ( (0<<UPM0) | (1<<USBS) | (7<<(UCSZ0-1)) )
	#define CONF_9BIT_EVENPAR_1STOP    ( (2<<UPM0) | (0<<USBS) | (7<<(UCSZ0-1)) )
	#define CONF_9BIT_EVENPAR_2STOP    ( (2<<UPM0) | (1<<USBS) | (7<<(UCSZ0-1)) )
	#define CONF_9BIT_ODDPAR_1STOP     ( (3<<UPM0) | (0<<USBS) | (7<<(UCSZ0-1)) )
	#define CONF_9BIT_ODDPAR_2STOP     ( (3<<UPM0) | (1<<USBS) | (7<<(UCSZ0-1)) )

	#define CONF_8BIT_NOPAR_1STOP      ( (0<<UPM0) | (0<<USBS) | (3<<(UCSZ0-1)) )
	#define CONF_8BIT_NOPAR_2STOP      ( (0<<UPM0) | (1<<USBS) | (3<<(UCSZ0-1)) )
	#define CONF_8BIT_EVENPAR_1STOP    ( (2<<UPM0) | (0<<USBS) | (3<<(UCSZ0-1)) )
	#define CONF_8BIT_EVENPAR_2STOP    ( (2<<UPM0) | (1<<USBS) | (3<<(UCSZ0-1)) )
	#define CONF_8BIT_ODDPAR_1STOP     ( (3<<UPM0) | (0<<USBS) | (3<<(UCSZ0-1)) )
	#define CONF_8BIT_ODDPAR_2STOP     ( (3<<UPM0) | (1<<USBS) | (3<<(UCSZ0-1)) )

	#define CONF_7BIT_NOPAR_1STOP      ( (0<<UPM0) | (0<<USBS) | (2<<(UCSZ0-1)) )
	#define CONF_7BIT_NOPAR_2STOP      ( (0<<UPM0) | (1<<USBS) | (2<<(UCSZ0-1)) )
	#define CONF_7BIT_EVENPAR_1STOP    ( (2<<UPM0) | (0<<USBS) | (2<<(UCSZ0-1)) )
	#define CONF_7BIT_EVENPAR_2STOP    ( (2<<UPM0) | (1<<USBS) | (2<<(UCSZ0-1)) )
	#define CONF_7BIT_ODDPAR_1STOP     ( (3<<UPM0) | (0<<USBS) | (2<<(UCSZ0-1)) )
	#define CONF_7BIT_ODDPAR_2STOP     ( (3<<UPM0) | (1<<USBS) | (2<<(UCSZ0-1)) )

	#define CONF_6BIT_NOPAR_1STOP      ( (0<<UPM0) | (0<<USBS) | (1<<(UCSZ0-1)) )
	#define CONF_6BIT_NOPAR_2STOP      ( (0<<UPM0) | (1<<USBS) | (1<<(UCSZ0-1)) )
	#define CONF_6BIT_EVENPAR_1STOP    ( (2<<UPM0) | (0<<USBS) | (1<<(UCSZ0-1)) )
	#define CONF_6BIT_EVENPAR_2STOP    ( (2<<UPM0) | (1<<USBS) | (1<<(UCSZ0-1)) )
	#define CONF_6BIT_ODDPAR_1STOP     ( (3<<UPM0) | (0<<USBS) | (1<<(UCSZ0-1)) )
	#define CONF_6BIT_ODDPAR_2STOP     ( (3<<UPM0) | (1<<USBS) | (1<<(UCSZ0-1)) )

	#define CONF_5BIT_NOPAR_1STOP      ( (0<<UPM0) | (0<<USBS) | (0<<(UCSZ0-1)) )
	#define CONF_5BIT_NOPAR_2STOP      ( (0<<UPM0) | (1<<USBS) | (0<<(UCSZ0-1)) )
	#define CONF_5BIT_EVENPAR_1STOP    ( (2<<UPM0) | (0<<USBS) | (0<<(UCSZ0-1)) )
	#define CONF_5BIT_EVENPAR_2STOP    ( (2<<UPM0) | (1<<USBS) | (0<<(UCSZ0-1)) )
	#define CONF_5BIT_ODDPAR_1STOP     ( (3<<UPM0) | (0<<USBS) | (0<<(UCSZ0-1)) )
	#define CONF_5BIT_ODDPAR_2STOP     ( (3<<UPM0) | (1<<USBS) | (0<<(UCSZ0-1)) )

	#define Uart_hw_init(config)       { UCSRA |=  (1<<UDRE);         \
		UCSRB &= (~(1<<UCSZ2)); UCSRB |= config & (1<<UCSZ2);     \
		UCSRC  = config & ((3<<UPM0) | (1<<USBS));                \
	UCSRC |= ((config & (3<<(UCSZ0-1))) << UCSZ0);            }
	//_____ F U N C T I O N S ______________________________________________________
	unsigned char uart_getchar (void);
	void uart_putchar (unsigned char ch);
	static void uart_init(unsigned char mode);
	unsigned char uart_mini_printf(char *format, ...);
	void uart_put_string (char *data_string, char enter);
	unsigned char uart_getstring (char *buffer_data, int len_buffer);
	//------------------------------------------------------------------------------
	//uart_init
	//------------------------------------------------------------------------------
	static void uart_init(unsigned char mode)
	{
		Uart_hw_init(mode);
		Uart_enable();
		
		#define BAUD 9600
		#include <util/setbaud.h>
		UBRRH = UBRRH_VALUE;
		UBRRL = UBRRL_VALUE;
		#if USE_2X
		UCSRA |= (1 << U2X);
		#else
		UCSRA &= ~(1 << U2X);
		#endif
	}

	//------------------------------------------------------------------------------
	//uart_putchar (Send a character on the UART peripheral.)
	//------------------------------------------------------------------------------
	void uart_putchar (unsigned char ch)
	{
		while(!Uart_tx_ready());
		Uart_send_byte(ch);
	}

	//------------------------------------------------------------------------------
	//uart_getchar (Get a character from the UART peripheral.)
	//return read (received) character on the UART
	//------------------------------------------------------------------------------
	unsigned char uart_getchar (void)
	{
		U8 ch,t=0;

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

	//------------------------------------------------------------------------------
	//uart_getstring (Get a string from the UART peripheral.)
	//save recived data in to *buffer_data.
	//------------------------------------------------------------------------------
	unsigned char uart_getstring (char *buffer_data, int len_buffer)
	{
		U8 z;
		
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

	//------------------------------------------------------------------------------
	//uart_put_string
	//Put a data-string on TX UART. The data-string is send up to null
	//------------------------------------------------------------------------------
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

	//------------------------------------------------------------------------------
	//uart_mini_printf
	//
	// Minimal "PRINTF" with variable argument list. Write several variables
	// formatted by a format string to a file descriptor.
	// Example:
	// { u8_toto = 0xAA;
	//   uart_mini_printf ("toto = %04d (0x%012X)\r\n", u8_toto, u8_toto);
	//   /*   Expected:     toto = 0170 (0x0000000000AA)   &  Cr+Lf       */ }
	//
	// warning "uart_init()" must be performed before
	//
	// param argument list
	//
	//     The format string is interpreted like this:
	//        ,---------------,---------------------------------------------------,
	//        | Any character | Output as is                                      |
	//        |---------------+---------------------------------------------------|
	//        |     %c:       | interpret argument as character                   |
	//        |     %s:       | interpret argument as pointer to string           |
	//        |     %d:       | interpret argument as decimal (signed) S16        |
	//        |     %ld:      | interpret argument as decimal (signed) S32        |
	//        |     %u:       | interpret argument as decimal (unsigned) U16      |
	//        |     %lu:      | interpret argument as decimal (unsigned) U32      |
	//        |     %x:       | interpret argument as hex U16 (lower case chars)  |
	//        |     %lx:      | interpret argument as hex U32 (lower case chars)  |
	//        |     %X:       | interpret argument as hex U16 (upper case chars)  |
	//        |     %lX:      | interpret argument as hex U32 (upper case chars)  |
	//        |     %%:       | print a percent ('%') character                   |
	//        '---------------'---------------------------------------------------'
	//
	//     Field width (in decimal) always starts with "0" and its maximum is
	//     given by "DATA_BUF_LEN" defined in "uart_lib.h".
	//        ,----------------------,-----------,--------------,-----------------,
	//        |       Variable       | Writting  |  Printing    |    Comment      |
	//        |----------------------+-----------+--------------|-----------------|
	//        |                      |   %x      | aa           |        -        |
	//        |  u8_xx = 0xAA        |   %04d    | 0170         |        -        |
	//        |                      |   %012X   | 0000000000AA |        -        |
	//        |----------------------+-----------+--------------|-----------------|
	//        | u16_xx = -5678       |   %010d   | -0000005678  |        -        |
	//        |----------------------+-----------+--------------|-----------------|
	//        | u32_xx = -4100000000 |   %011lu  | 00194967296  |        -        |
	//        |----------------------+-----------+--------------|-----------------|
	//        |          -           |   %8x     | 8x           | Writting error! |
	//        |----------------------+-----------+--------------|-----------------|
	//        |          -           |   %0s     | 0s           | Writting error! |
	//        '----------------------'-----------'--------------'-----------------'
	//
	// Return: 0 = O.K.
	//
	//------------------------------------------------------------------------------
	#ifndef REDUCED_UART_LIB
	unsigned char uart_mini_printf(char *format, ...)
	{
		va_list arg_ptr;
		U8      *p,*sval;
		U8      u8_temp, n_sign, data_idx, min_size;
		U8      data_buf[DATA_BUF_LEN];
		S8      long_flag, alt_p_c;
		S8      s8_val;
		S16     s16_val;
		S32     s32_val;
		U16     u16_val;
		U32     u32_val;

		long_flag = FALSE;
		alt_p_c = FALSE;
		min_size = DATA_BUF_LEN-1;

		va_start(arg_ptr, format);   // make arg_ptr point to the first unnamed arg
		for (p = (U8 *) format; *p; p++)
		{
			if ((*p == '%') || (alt_p_c == TRUE))
			{
				p++;
			}
			else
			{
				uart_putchar(*p);
				alt_p_c = FALSE;
				long_flag = FALSE;
				continue;   // "switch (*p)" section skipped
			}
			switch (*p)
			{
				case 'c':
				if (long_flag == TRUE)      // ERROR: 'l' before any 'c'
				{
					uart_putchar('l');
					uart_putchar('c');
				}
				else
				{
					s8_val = (S8)(va_arg(arg_ptr, int));    // s8_val = (S8)(va_arg(arg_ptr, S16));
					uart_putchar((U8)(s8_val));
				}
				// Clean up
				min_size = DATA_BUF_LEN-1;
				alt_p_c = FALSE;
				long_flag = FALSE;
				break; // case 'c'
				
				case 's':
				if (long_flag == TRUE)      // ERROR: 'l' before any 's'
				{
					uart_putchar('l');
					uart_putchar('s');
				}
				else
				{
					for (sval = va_arg(arg_ptr, U8 *); *sval; sval++)
					{
						uart_putchar(*sval);
					}
				}
				// Clean up
				min_size = DATA_BUF_LEN-1;
				alt_p_c = FALSE;
				long_flag = FALSE;
				break;  // case 's'
				
				case 'l':  // It is not the number "ONE" but the lower case of "L" character
				if (long_flag == TRUE)      // ERROR: two consecutive 'l'
				{
					uart_putchar('l');
					alt_p_c = FALSE;
					long_flag = FALSE;
				}
				else
				{
					alt_p_c = TRUE;
					long_flag = TRUE;
				}
				p--;
				break;  // case 'l'
				
				case 'd':
				n_sign  = FALSE;
				for(data_idx = 0; data_idx < (DATA_BUF_LEN-1); data_idx++)
				{
					data_buf[data_idx] = '0';
				}
				data_buf[DATA_BUF_LEN-1] = 0;
				data_idx = DATA_BUF_LEN - 2;
				if (long_flag)  // 32-bit
				{
					s32_val = va_arg(arg_ptr, S32);
					if (s32_val < 0)
					{
						n_sign = TRUE;
						s32_val  = -s32_val;
					}
					while (1)
					{
						data_buf[data_idx] = s32_val % 10 + '0';
						s32_val /= 10;
						data_idx--;
						if (s32_val==0) break;
					}
				}
				else  // 16-bit
				{
					s16_val = (S16)(va_arg(arg_ptr, int)); // s16_val = va_arg(arg_ptr, S16);
					if (s16_val < 0)
					{
						n_sign = TRUE;
						s16_val  = -s16_val;
					}
					while (1)
					{
						data_buf[data_idx] = s16_val % 10 + '0';
						s16_val /= 10;
						data_idx--;
						if (s16_val==0) break;
					}
				}
				if (n_sign) { uart_putchar('-'); }
				data_idx++;
				if (min_size < data_idx)
				{
					data_idx = min_size;
				}
				uart_put_string ((char *)(data_buf + data_idx),0);
				// Clean up
				min_size = DATA_BUF_LEN-1;
				alt_p_c = FALSE;
				long_flag = FALSE;
				break;  // case 'd'
				
				case 'u':
				for(data_idx = 0; data_idx < (DATA_BUF_LEN-1); data_idx++)
				{
					data_buf[data_idx] = '0';
				}
				data_buf[DATA_BUF_LEN-1] = 0;
				data_idx = DATA_BUF_LEN - 2;
				if (long_flag)  // 32-bit
				{
					u32_val = va_arg(arg_ptr, U32);
					while (1)
					{
						data_buf[data_idx] = u32_val % 10 + '0';
						u32_val /= 10;
						data_idx--;
						if (u32_val==0) break;
					}
				}
				else  // 16-bit
				{
					u16_val = (U16)(va_arg(arg_ptr, int)); // u16_val = va_arg(arg_ptr, U16);
					while (1)
					{
						data_buf[data_idx] = u16_val % 10 + '0';
						data_idx--;
						u16_val /= 10;
						if (u16_val==0) break;
					}
				}
				data_idx++;
				if (min_size < data_idx)
				{
					data_idx = min_size;
				}
				uart_put_string ((char *)(data_buf + data_idx),0);
				// Clean up
				min_size = DATA_BUF_LEN-1;
				alt_p_c = FALSE;
				long_flag = FALSE;
				break;  // case 'u':
				
				case 'x':
				case 'X':
				for(data_idx = 0; data_idx < (DATA_BUF_LEN-1); data_idx++)
				{
					data_buf[data_idx] = '0';
				}
				data_buf[DATA_BUF_LEN-1] = 0;
				data_idx = DATA_BUF_LEN - 2;
				if (long_flag)  // 32-bit
				{
					u32_val = va_arg(arg_ptr, U32);
					while (u32_val)
					{
						u8_temp = (U8)(u32_val & 0x0F);
						data_buf[data_idx] = (u8_temp < 10)? u8_temp+'0':u8_temp-10+(*p=='x'?'a':'A');
						u32_val >>= 4;
						data_idx--;
					}
				}
				else  // 16-bit
				{
					u16_val = (U16)(va_arg(arg_ptr, int)); // u16_val = va_arg(arg_ptr, U16);
					while (u16_val)
					{
						u8_temp = (U8)(u16_val & 0x0F);
						data_buf[data_idx] = (u8_temp < 10)? u8_temp+'0':u8_temp-10+(*p=='x'?'a':'A');
						u16_val >>= 4;
						data_idx--;
					}
				}
				data_idx++;
				if (min_size < data_idx)
				{
					data_idx = min_size;
				}
				uart_put_string ((char *)(data_buf + data_idx),0);
				// Clean up
				min_size = DATA_BUF_LEN-1;
				alt_p_c = FALSE;
				long_flag = FALSE;
				break;  // case 'x' & 'X'
				
				case '0':   // Max allowed "min_size" 2 decimal digit, truncated to DATA_BUF_LEN-1.
				min_size = DATA_BUF_LEN-1;
				if (long_flag == TRUE)      // ERROR: 'l' before '0'
				{
					uart_putchar('l');
					uart_putchar('0');
					// Clean up
					alt_p_c = FALSE;
					long_flag = FALSE;
					break;
				}
				u8_temp = *++p;
				if ((u8_temp >='0') && (u8_temp <='9'))
				{
					min_size = u8_temp & 0x0F;
					u8_temp = *++p;
					if ((u8_temp >='0') && (u8_temp <='9'))
					{
						min_size <<= 4;
						min_size |= (u8_temp & 0x0F);
						p++;
					}
					min_size = ((min_size & 0x0F) + ((min_size >> 4) *10));  // Decimal to hexa
					if (min_size > (DATA_BUF_LEN-1))
					{
						min_size = (DATA_BUF_LEN-1);
					}  // Truncation
					min_size = DATA_BUF_LEN-1 - min_size;  // "min_size" formatted as "data_ix"
				}
				else      // ERROR: any "char" after '0'
				{
					uart_putchar('0');
					uart_putchar(*p);
					// Clean up
					alt_p_c = FALSE;
					long_flag = FALSE;
					break;
				}
				p-=2;
				alt_p_c = TRUE;
				// Clean up
				long_flag = FALSE;
				break;  // case '0'
				
				default:
				if (long_flag == TRUE)
				{
					uart_putchar('l');
				}
				uart_putchar(*p);
				// Clean up
				min_size = DATA_BUF_LEN-1;
				alt_p_c = FALSE;
				long_flag = FALSE;
				break;  // default
				
			}   // switch (*p ...
			
		}   // for (p = ...
		
		va_end(arg_ptr);
		return 0;
	}
	#endif  // REDUCED_UART_LIB
#endif
