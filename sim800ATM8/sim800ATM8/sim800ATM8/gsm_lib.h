/************************************************************************/
/* GSM LIB                                                              */
/* Ver 1.8																*/
/* Abolfazl Shakeri                                                     */
/* Designer2013.blogsky.com                                             */
/* Designer2100@outlook.com                                             */
/************************************************************************/
#ifndef _GSM_UART_LIB_H
#define _GSM_UART_LIB_H

#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "compiler.h"
#include "uart_lib_m32-16.h"
#define SIM800_MODULE		2
#define SIM900_MODULE		1
/************************************************************************/
/* EDIT THIS DEFINE's                                                   */
/************************************************************************/
//#define DEBUGE_GSM					1

#define GSM_MODULE				SIM800_MODULE

#define GSM_ON_DDR				DDRD
#define GSM_ON_PORT				PORTD
#define GSM_ON_PIN				PORTD4

#define GSM_STATE_DDR			DDRD
#define GSM_STATE_PORT			PORTD
#define GSM_STATE_IN			PIND
#define GSM_STATE_PIN			PORTD3

#define GSM_UART_ISR			USART_RXC_vect

//#define LCD_PROGRESS			1
//#define LCD					1
//#define CLOCK					1
#define _WDT					1
/************************************************************************/
/* DONT EDIT THIS DEFINE's                                              */
/************************************************************************/
//---------------------------------------
#define SEND_SMS				1
#define OFF_GSM					2
#define GET_IMEI				3
#define GSM_MOD					4
#define UCS2_MOD				5
#define DEL_ALL					6
#define GET_CHARJ				7
#define SIM_NAME				8
#define NET_STATUS				9
#define GSM_RST					10
#define CHARJ_SIM				11
#define DELL_SMS				12
#define SIGNAL_Q				13
#define REQUEST_TA				14
#define HANG_UP					15
#define ANSWER_RING				16
#define CMICH					17
#define CMICL					18
#define CUSD_ON					19
#define CUSD_OFF				20
#define RST_GSM					21
#define RECIEVED_UNREAD			22
//--------------------------------------
#define SMS_MOD					UCS2_MOD
//--------------------------------------
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
//--------------------------------------
#define NET_REGISTRED			10
#define NET_NOT_REGISTRED		0
//--------------------------------------
#define IRANCELL				1
#define IR_MCI					2
#define NO_KNOW					4
#define NO_SIM					3
//---------------------------------------
#define APPLY_GSM				1
//---------------------------------------
#define GSM_DELET				1
#define GSM_PRE_DELET			2
#define GSM_GET_SMS				3
#define GSM_READ_SMS			4
#define GSM_READ_CHARJ			5
#define ERROR_MODULE			6
//--------------------------------------
#define ON_GSM_HIGH				(GSM_ON_PORT |=   1<<GSM_ON_PIN)
#define ON_GSM_LOW				(GSM_ON_PORT &= ~(1<<GSM_ON_PIN))
//---------------------------------------
#define STATUS					(GSM_STATE_IN & 1<<GSM_STATE_PIN)
//---------------------------------------

struct{
	char buffer[BUFFER_LEN+1],unread,tex_recive[TEX_RECIVE_LEN+1],net_registration,sim_operator,name_operator[NAME_OPERATOR_LEN+1],charge[CHARGE_LEN+1],tex_send[TEX_SEND_LEN+1];
	char compar[COMPAR_LEN+1],data[DATA_LEN+1],ch,ch_sms[CH_SMS_LEN],err_counter,recived_sms[SMS_QUEUE+1][2],mobile_number[MOBILE_NUMBER_LEN+1],mobile_buffer[MOBILE_BUFFER_LEN+1];
	char recive_sms,dell,rdy,re_send,flag,charj,flag_charj,flag_simname,net_state,ring,apply,signal_value,rdy_tout,hangup,answer,flag_unread;
	int index,stat,recived_sms_counter,number_of_charecter;
	volatile char recive;
}gsm;

char buffer_gsm[20];
char get_charj_code_irancell[10]="*141*1#";
char get_charj_code_ir_mci[10]="*140*11#";
int sms_number,sms_number_tout;
int counter;
int temp1_gsm,temp2_gsm,temp3_gsm;

void gsm_ready();
char a_to_i_gsm(char i);
char get_info(void);
char gsm_handl(void);
void wait_flage(void);
void detect_gsm(void);
void gsm_start(void);
void read_sms(void);
void read_charj(void);
void get_sms(int ch);
void send2gsm(char select);
void gsm_initializing(void);
char convert_to_char(char *buffer_in);
void gsm_send_sms(char *mobile,char *tex);
void select_unicode(char ch, char *buffer_out);
void chang_to_unicode(char *tex_in ,char *unicode_buffer);
//--------------------------------------
char get_ok(void)
{
	char con=0;
	repet_get_ok:
	uart_put_string("AT",1);
	wait_flage();
	if ((strstr_P(gsm.buffer,PSTR("OK"))) == 0){con++;if(con<2){_delay_ms(250);uart_put_string("ATE0",1);_delay_ms(300);goto repet_get_ok;}}else{return TRUE;}
	return FALSE;
}
//--------------------------------------
char gsm_handl(void)
{
	if (STATUS==0)
	{
		gsm.stat = DISABLE;
		return OFF_GSM;
	}
	else if(gsm.stat==DISABLE)
	{
		gsm.stat = ENABLE;
	}
	
	if (gsm.dell==ENABLE)
	{
		gsm.recive_sms = DISABLE;
		gsm.dell = DISABLE;
		send2gsm(GSM_MOD);
		send2gsm(DELL_SMS);
		_delay_ms(200);
	}
	
	if (gsm.hangup==ENABLE && gsm.rdy==ENABLE)
	{
		send2gsm(HANG_UP);
		gsm.hangup = DISABLE;
	}
	
	if (sms_number==0 && gsm.rdy==ENABLE)
	{
		for (int t=0; t<SMS_QUEUE; t++)
		{
			if (gsm.recived_sms[t][0]!=0)
			{
				sms_number=gsm.recived_sms[t][0];
				gsm.recived_sms[t][0]=0;
				break;
			}
		}
		if (sms_number>0)
		{
			gsm.rdy_tout=0;
			get_sms(sms_number);
			gsm.flag = GSM_GET_SMS;
		}
		else if(gsm.unread==ENABLE)
		{
			gsm.flag_unread = ENABLE;
			send2gsm(RECIEVED_UNREAD);
		}
	}
	
	if (gsm.answer==ENABLE && gsm.rdy==ENABLE)
	{
		send2gsm(ANSWER_RING);
		gsm.answer = DISABLE;
	}
	
	if (gsm.flag==GSM_READ_SMS)
	{
		read_sms();
		gsm.flag=DISABLE;
	}
	else if (gsm.flag==GSM_READ_CHARJ)
	{
		read_charj();
		gsm.flag = DISABLE;
	}
	
	if(gsm.apply==APPLY_GSM)
	{
		memset(gsm.tex_send,0,TEX_SEND_LEN);
		gsm.apply = DISABLE;
		return APPLY_GSM;
	}
	
	if (gsm.err_counter>3)
	{
		return ERROR_MODULE;
	}
	
	if (gsm.net_registration>599 && gsm.recive_sms==DISABLE)
	{
		gsm.net_registration = 0;
		send2gsm(NET_STATUS);
	}
	
	if (gsm.dell==GSM_PRE_DELET)
	{
		counter++;
		if (counter>800)
		{
			gsm.dell=ENABLE;
			counter = 0;
		}
		_delay_ms(10);
	}
	
	if (gsm.sim_operator==0)
	{
		//send2gsm(SIM_NAME);
	}
	
	return 0;
}
//--------------------------------------
char a_to_i_gsm(char i)
{
	if (i>47 && i<58)
	{
		return(i-48);
	}
	else
	{
		return 10;
	}
}
//--------------------------------------
void gsm_initializing(void)
{	
	#ifdef _WDT
	wdt_reset();
	#endif
	#ifdef DEBUGE_GSM 
	uart_put_string("GSM_UART INIT",1);
	#endif
	#ifdef DEBUGE_GSM 
	uart_put_string("AT",1);
	#endif
	uart_put_string_p(PSTR("AT"),1);
	wait_flage();
	_delay_ms(600);
	
	#ifdef _WDT
	wdt_reset();
	#endif
	#ifdef DEBUGE_GSM 
	uart_put_string("ATE0",1);
	#endif
	uart_put_string_p(PSTR("ATE0"),1);
	wait_flage();
	_delay_ms(600);
	
	#ifdef _WDT
	wdt_reset();
	#endif
	#ifdef DEBUGE_GSM 
	uart_put_string("AT+CMGF=1",1);
	#endif
	uart_put_string_p(PSTR("AT+CMGF=1"),1);
	wait_flage();
	_delay_ms(600);
	
	#ifdef _WDT
	wdt_reset();
	#endif
	#ifdef DEBUGE_GSM 
	uart_put_string("AT+CLIP=1",1);
	#endif
	uart_put_string_p(PSTR("AT+CLIP=1"),1);
	wait_flage();
	_delay_ms(600);
	
	#ifdef _WDT
	wdt_reset();
	#endif
	 #ifdef DEBUGE_GSM 
	 uart_put_string("AT+CMGDA=\"DEL ALL\"",1);
	 #endif
	uart_put_string_p(PSTR("AT+CMGDA=\"DEL ALL\""),1);
	wait_flage();
	_delay_ms(600);
	
	#ifdef _WDT
	wdt_reset();
	#endif
	#ifdef DEBUGE_GSM 
	uart_put_string("AT+CSMP=17,167,0,25",1);
	#endif
	uart_put_string_p(PSTR("AT+CSMP=17,167,0,25"),1);
	wait_flage();
	_delay_ms(600);
	#ifdef _WDT
	wdt_reset();
	#endif
	
	/*#ifdef _WDT
	wdt_reset();
	#endif
	#ifdef DEBUGE_GSM
	uart_put_string("AT+CUSD=1",1);
	#endif
	uart_put_string("AT+CUSD=1",1);
	wait_flage();
	_delay_ms(600);
	#ifdef _WDT
	wdt_reset();
	#endif*/
}
//--------------------------------------
void detect_gsm(void)
{
	static int cou=0;
	
	/*if (strstr(gsm.buffer,">")==0)
	{
		uart_putchar('<');
		uart_put_string(gsm.buffer,0);
		uart_putchar('>');
		uart_putchar(13);
	}*/
	
	if(strstr_P(gsm.buffer,PSTR("+CMTI:"))!=0)
	{
		gsm.err_counter = 0;
		for (cou=0; cou<16; cou++)
		{
			if (gsm.buffer[cou]==',' && a_to_i_gsm(gsm.buffer[cou+1])<10)
			{
				gsm.recived_sms[gsm.recived_sms_counter][0]=a_to_i_gsm(gsm.buffer[cou+1]);
				if (a_to_i_gsm(gsm.buffer[cou+2])<10)
				{
					gsm.recived_sms[gsm.recived_sms_counter][0]= ((gsm.recived_sms[gsm.recived_sms_counter][0]*10)+a_to_i_gsm(gsm.buffer[cou+2]));
				}
				#ifdef DEBUGE_GSM 
				 uart_put_string("RECIVE SMS",0);
				 uart_mini_printf(" %d\r\n",gsm.recived_sms[gsm.recived_sms_counter][0]);
				#endif
				gsm.recived_sms_counter++;if(gsm.recived_sms_counter>SMS_QUEUE){gsm.recived_sms_counter=0;}
				if(gsm.recive_sms==DISABLE)gsm.rdy = ENABLE;
			}
		}
		//return;
	}
	if (strstr_P(gsm.buffer,PSTR("+CMGR:"))!=0)
	{
		gsm.flag = GSM_READ_SMS;
		//#ifdef DEBUGE_GSM
		uart_put_string("flag=read_sms",1);
		//#endif
		return;
	}
	if(strstr_P(gsm.buffer,PSTR("+CMGL:"))!=0)
	{
		gsm.unread=DISABLE;
		gsm.flag_unread = DISABLE;
		gsm.err_counter = 0;
		for (cou=0; cou<16; cou++)
		{
			if (gsm.buffer[cou]==' ' && a_to_i_gsm(gsm.buffer[cou+1])<10)
			{
				gsm.recived_sms[gsm.recived_sms_counter][0]=a_to_i_gsm(gsm.buffer[cou+1]);
				if (a_to_i_gsm(gsm.buffer[cou+2])<10)
				{
					gsm.recived_sms[gsm.recived_sms_counter][0]= ((gsm.recived_sms[gsm.recived_sms_counter][0]*10)+a_to_i_gsm(gsm.buffer[cou+2]));
				}
				#ifdef DEBUGE_GSM
				uart_put_string("RECIVED SMS",0);
				uart_mini_printf(" %d\r\n",gsm.recived_sms[gsm.recived_sms_counter][0]);
				#endif
				gsm.recived_sms_counter++;if(gsm.recived_sms_counter>SMS_QUEUE){gsm.recived_sms_counter=0;}
				if(gsm.recive_sms==DISABLE)gsm.rdy = ENABLE;
			}
		}
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("+CMGS:"))!=0)
	{
		#ifdef DEBUGE_GSM
		uart_put_string("+CMGS:_D",1);
		#endif
		if(gsm.recive_sms==ENABLE){
			gsm.dell = ENABLE; 
			#ifdef DEBUGE_GSM 
			uart_put_string("dell=EN",1);
			#endif
		}
		else
		{
			gsm.rdy = ENABLE;
		}
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("ERROR"))!=0 && gsm.dell==GSM_PRE_DELET)
	{
		#ifdef DEBUGE_GSM
		uart_put_string("ERR1_D",1);
		#endif
		if(gsm.recive_sms==ENABLE){
			gsm.dell = ENABLE;
			#ifdef DEBUGE_GSM 
			uart_put_string("dell=EN(2)",1);
			#endif
		}
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("ERROR"))!=0 && gsm.rdy==DISABLE)
	{
		#ifdef DEBUGE_GSM 
		uart_put_string("rdy=EN",1);
		#endif
		gsm.err_counter++;
		if(gsm.re_send==ENABLE ){gsm.re_send=DISABLE;gsm.rdy = ENABLE;return;}
		if(gsm.re_send==DISABLE){gsm.re_send=ENABLE;}
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("+CUSD: 0"))!=0)
	{
		gsm.flag = GSM_READ_CHARJ;
		 #ifdef DEBUGE_GSM 
		 uart_put_string("flag=read_charj",1);
		 #endif
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("NO CARRIER"))!=0 && gsm.flag_charj==ENABLE)
	{
		gsm.flag_charj = DISABLE;
		gsm.charj = ENABLE;
		strcpy(gsm.charge,"NET WRONG ");
		#ifdef DEBUGE_GSM
		uart_put_string("charj=EN",1);
		#endif
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("+CUSD: 2"))!=0)
	{
		gsm.charj = ENABLE;
		strcpy(gsm.charge,"NET WRONG ");
		#ifdef DEBUGE_GSM 
		uart_put_string("charj=EN",1);
		#endif
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("+CREG"))!=0)
	{
		if (gsm.buffer[11]!='1' && gsm.buffer[11]!='5')
		{
			gsm.net_state = NET_NOT_REGISTRED;
			#ifdef DEBUGE_GSM
			uart_put_string("NET_NOT_REGISTRED",1);
			#endif
		}
		else
		{
			gsm.net_state = NET_REGISTRED;
			#ifdef DEBUGE_GSM
			uart_put_string("NET_REGISTRED",1);
			#endif
		}
		return;
	}
	if(strstr_P(gsm.buffer,PSTR("+CLIP:"))!=0)
	{
		gsm.number_of_charecter = strlen(gsm.buffer);
		memset(gsm.mobile_number,0,MOBILE_NUMBER_LEN);
		for (temp1_gsm=0; temp1_gsm<gsm.number_of_charecter; temp1_gsm++)
		{
			if (gsm.buffer[temp1_gsm]==34)
			{
				temp2_gsm=0;
				for (temp3_gsm=++temp1_gsm; temp3_gsm<gsm.number_of_charecter; temp3_gsm++)
				{
					if ((gsm.buffer[temp3_gsm]!=34)){gsm.mobile_number[temp2_gsm] = gsm.buffer[temp3_gsm];temp2_gsm++;}
					if ((gsm.buffer[temp3_gsm]==34)){goto re_dial;}
				}
			}
		}
		
		re_dial:
		temp2_gsm = strlen(gsm.mobile_number);
		gsm.mobile_number[0]='0';
		for (temp3_gsm=3; temp3_gsm<temp2_gsm; temp3_gsm++)
		{
			gsm.mobile_number[temp3_gsm-2] = gsm.mobile_number[temp3_gsm];
		}
		gsm.mobile_number[13]=0;
		gsm.mobile_number[12]=0;
		gsm.mobile_number[11]=0;
		
		if (strcmp(gsm.mobile_number,gsm.mobile_buffer)!=0)
		{
			strcpy(gsm.mobile_buffer,gsm.mobile_number);
			gsm.ring = 0;
		}
		gsm.ring++;
		return;
	}
	if ((strstr_P(gsm.buffer,PSTR("+CSQ:")))!=0)
	{
		memset(gsm.compar,0,COMPAR_LEN);
		temp2_gsm=0;
		gsm.number_of_charecter = strlen(gsm.buffer);
		for (temp1_gsm=6; temp1_gsm<gsm.number_of_charecter; temp1_gsm++)
		{
			if(gsm.buffer[temp1_gsm]==','){break;}
			if(a_to_i_gsm(gsm.buffer[temp1_gsm])<10){gsm.compar[temp2_gsm] = gsm.buffer[temp1_gsm];temp2_gsm++;}
		}
		gsm.signal_value = atoi(gsm.compar);
		
		return;
	}
	if (strstr_P(gsm.buffer,PSTR("SMS Ready"))!=0)
	{
		gsm.rdy = ENABLE;
		#ifdef DEBUGE_GSM
		uart_put_string("AT+CSMP=17,167,0,25",1);
		#endif
		_delay_ms(200);
		uart_put_string("AT+CSMP=17,167,0,25",1);
		wait_flage();
		return;
	}
	if ((strstr_P(gsm.buffer,PSTR("+CSPN:"))) != 0)
	{
		gsm.flag_simname = DISABLE;
		gsm.number_of_charecter = strlen(gsm.buffer);
		memset(gsm.compar,0,COMPAR_LEN);
		for (temp1_gsm=0; temp1_gsm<gsm.number_of_charecter; temp1_gsm++)
		{
			if (gsm.buffer[temp1_gsm]==34)
			{
				temp3_gsm=0;
				for (temp2_gsm=(temp1_gsm+1);temp2_gsm<gsm.number_of_charecter;temp2_gsm++)
				{
					if (gsm.buffer[temp2_gsm]!=34){gsm.compar[temp3_gsm]=gsm.buffer[temp2_gsm];temp3_gsm++;}
					if (gsm.buffer[temp2_gsm]==34){goto re_cspn;}
				}
			}
		}
		re_cspn:
		memset(gsm.name_operator,0,NAME_OPERATOR_LEN);
		#ifdef DEBUGE_GSM
		uart_put_string(gsm.compar,1);
		#endif
		if ((strcmp_P(gsm.compar,PSTR("IRANCELL")))==0)
		{
			gsm.sim_operator = IRANCELL;
			strcpy(gsm.name_operator,gsm.compar);
			#ifdef LCD
			LCDGotoXY(0,0);
			LCDstring((uint8_t *)"    IRANCELL    ",16);
			_delay_ms(700);
			#endif
			
		}
		else if ((strcmp_P(gsm.compar,PSTR("IR-MCI")))==0)
		{
			gsm.sim_operator = IR_MCI;
			strcpy(gsm.name_operator,gsm.compar);
			#ifdef LCD
			LCDGotoXY(0,0);
			LCDstring((uint8_t *)"     IR-MCI     ",16);
			_delay_ms(700);
			#endif
		}
		else
		{
			gsm.sim_operator = NO_KNOW;
			strcpy(gsm.name_operator,"NO KNOW");
			#ifdef LCD
			LCDGotoXY(0,0);
			LCDstring((uint8_t *)"    UNKNOWN   ",16);
			_delay_ms(700);
			#endif
		}
		//show_txt(gsm.name_operator,1,them,ALINE_CENTER,20,0,0);
	}
	if ((strstr_P(gsm.buffer,PSTR("ERROR"))) != 0 && gsm.flag_simname == ENABLE)
	{
		gsm.flag_simname = DISABLE;
		gsm.sim_operator = NO_SIM;
		strcpy(gsm.name_operator,"NO SIM");
		#ifdef LCD
		LCDGotoXY(0,0);
		LCDstring((uint8_t *)"     NO SIM     ",16);
		_delay_ms(1000);
		#endif
		//show_txt(gsm.name_operator,1,them,ALINE_CENTER,20,0,0);
	}
	if(gsm.flag_unread==ENABLE && (strstr_P(gsm.buffer,PSTR("OK")))!= 0)
	{
		gsm.unread=DISABLE;
		gsm.flag_unread=DISABLE;
	}
	if (gsm.flag==GSM_GET_SMS && (strstr_P(gsm.buffer,PSTR("OK")))!= 0)
	{
		sms_number = 0;
		gsm.flag = DISABLE;
	}
	#ifdef _WDT
		wdt_reset(); 
	#endif
}
//--------------------------------------
void wait_flage(void)
{
	static int cu=0;
	gsm.recive = DISABLE;
	while(gsm.recive==DISABLE){cu++;_delay_ms(10);if(cu>400){break;}}
	gsm.recive = DISABLE;
}
//--------------------------------------
void get_sms(int ch)
{
	gsm.recive_sms=ENABLE;
	memset(gsm.ch_sms,0,CH_SMS_LEN);
	sprintf(gsm.ch_sms,"%d",ch);//gsm.ch_sms = ch;
	
	#ifdef DEBUGE_GSM 
	uart_put_string("get_sms-",0);
	uart_put_string(gsm.ch_sms,ENABLE);
	#endif
	memset(gsm.data,0,DATA_LEN);
	memset(gsm.mobile_number,0,MOBILE_NUMBER_LEN);
	//memset(gsm.buffer,0,BUFFER_LEN);
	memset(gsm.tex_send,0,TEX_SEND_LEN);
	send2gsm(UCS2_MOD);
	wait_flage();/*_delay_ms(400);*/

	#ifdef _WDT
	wdt_reset();
	#endif
	gsm_ready();
	
	#ifdef _WDT
	wdt_reset();
	#endif
	_delay_ms(400);
	
	 #ifdef DEBUGE_GSM 
	 uart_put_string("AT+CMGR=",0);
	uart_put_string(gsm.ch_sms,0);
	#endif
	uart_put_string("AT+CMGR=",0);
	uart_put_string(gsm.ch_sms,ENABLE);
}
//--------------------------------------
void read_charj(void)
{
	 #ifdef DEBUGE_GSM 
	 uart_put_string("read_charj",1);
	 #endif
	 
	 /*#ifdef LCD
	 LCDGotoXY(0,1);
	 LCDstring((uint8_t*)gsm.buffer,16);
	 _delay_ms(600);
	#endif*/
	
	gsm.flag = DISABLE;
	memset(gsm.charge,0,CHARGE_LEN);
	int len = strlen(gsm.buffer);
	if (gsm.sim_operator==IRANCELL)
	{
		for (int i=8; i<len; i++)
		{
			if (gsm.buffer[i]==':' && gsm.buffer[i+1]==' ')
			{
				int v=0;
				for (int ii=i+2; ii<len; ii++)
				{
					if(gsm.buffer[ii]!=' '){gsm.charge[v] = gsm.buffer[ii];v++;}
					if(gsm.buffer[ii]==' ')break;
				}
				break;
			}
		}
	}
	else if (gsm.sim_operator==IR_MCI)
	{
		memset(gsm.compar,0,COMPAR_LEN);
		temp3_gsm = 0;
		for (temp1_gsm=12; temp1_gsm<95; temp1_gsm+=4)
		{
			buffer_gsm[0]=gsm.buffer[temp1_gsm];
			buffer_gsm[1]=gsm.buffer[temp1_gsm+1];
			buffer_gsm[2]=gsm.buffer[temp1_gsm+2];
			buffer_gsm[3]=gsm.buffer[temp1_gsm+3];
			gsm.compar[temp3_gsm] = convert_to_char(buffer_gsm);
			temp3_gsm++;
		}
		memset(gsm.tex_send,0,TEX_SEND_LEN);
		strcpy(gsm.tex_send,gsm.compar);
		 #ifdef DEBUGE_GSM 
		 uart_put_string(gsm.tex_send,1);
		 #endif
		
		memset(gsm.charge,0,CHARGE_LEN);
		int len = strlen(gsm.tex_send);
		for (int i=8; i<len; i++)
		{
			if (gsm.tex_send[i]=='�')
			{
				int v=0;
				for (int ii=i+1; ii<len; ii++)
				{
					if(gsm.tex_send[ii]!='�'){gsm.charge[v] = gsm.tex_send[ii];v++;}
					if(gsm.tex_send[ii]=='�')break;
				}
				break;
			}
		}
		 #ifdef DEBUGE_GSM 
		 uart_put_string(gsm.charge,1);
		 #endif
	}
	
	gsm.charj = ENABLE;
}
//--------------------------------------
void read_sms(void)
{
	int temp_read_sms=0,len=0,cou=0;
	cli();
	len=strlen(gsm.buffer);
	for (temp_read_sms=2; temp_read_sms<len; temp_read_sms++)
	{
		if(gsm.buffer[temp_read_sms]==0xd || gsm.buffer[temp_read_sms]==0xa){break;}
		if(temp_read_sms<DATA_LEN){gsm.data[temp_read_sms-2]=gsm.buffer[temp_read_sms];}
	}
	cou=0;
	for (temp_read_sms=temp_read_sms+2; temp_read_sms<len; temp_read_sms++)
	{
		if(gsm.buffer[temp_read_sms]==0xd || gsm.buffer[temp_read_sms]==0xa){break;}
		if(cou<TEX_SEND_LEN){gsm.tex_send[cou]=gsm.buffer[temp_read_sms];}
		cou++;
	}
	
 #ifdef DEBUGE_GSM 
	uart_put_string(gsm.tex_send,1);
	uart_put_string(gsm.data,1);
#endif

	memset(gsm.compar,0,COMPAR_LEN);
	temp3_gsm = 0;
	for (temp1_gsm=0; temp1_gsm<=(TEX_SEND_LEN-5); temp1_gsm+=4)
	{
		buffer_gsm[0]=gsm.tex_send[temp1_gsm];
		buffer_gsm[1]=gsm.tex_send[temp1_gsm+1];
		buffer_gsm[2]=gsm.tex_send[temp1_gsm+2];
		buffer_gsm[3]=gsm.tex_send[temp1_gsm+3];
		gsm.compar[temp3_gsm] = convert_to_char(buffer_gsm);
		temp3_gsm++;
	}
	memset(gsm.tex_recive,0,TEX_RECIVE_LEN); 
	strcpy(gsm.tex_recive,gsm.compar);
	sei();
	#ifdef _WDT
	wdt_reset();
	#endif
	
 #ifdef DEBUGE_GSM 
	uart_put_string(">>",0);
	uart_put_string(gsm.tex_recive,1);
#endif
	
	gsm.number_of_charecter = strlen(gsm.data);
	for (temp1_gsm=0;temp1_gsm<gsm.number_of_charecter;temp1_gsm++)
	{
		if (gsm.data[temp1_gsm]==',')
		{
			temp2_gsm=0;
			for (temp3_gsm=(temp1_gsm+2);temp3_gsm<gsm.number_of_charecter;temp3_gsm++)
			{
				if ((gsm.data[temp3_gsm]!=34)){gsm.mobile_number[temp2_gsm] = gsm.data[temp3_gsm];temp2_gsm++;}
				if ((gsm.data[temp3_gsm]==34)){goto resum;}
			}
		}
	}
	
resum:
	gsm.mobile_number[0]='+';
	temp2_gsm = 7;
	for (temp1_gsm=1; temp1_gsm<13; temp1_gsm++)
	{
		gsm.mobile_number[temp1_gsm] = gsm.mobile_number[temp2_gsm];
		temp2_gsm += 4;
	}
	temp1_gsm = strlen(gsm.mobile_number);
	for (temp2_gsm=13; temp2_gsm<temp1_gsm; temp2_gsm++)
	{
		gsm.mobile_number[temp2_gsm]=0;
	}
			
	temp2_gsm = strlen(gsm.mobile_number);
	gsm.mobile_number[0]='0';
	for (temp3_gsm=3; temp3_gsm<temp2_gsm; temp3_gsm++)
	{
		gsm.mobile_number[temp3_gsm-2] = gsm.mobile_number[temp3_gsm];
	}
	gsm.mobile_number[13]=0;
	gsm.mobile_number[12]=0;
	gsm.mobile_number[11]=0;
				
 #ifdef DEBUGE_GSM 
	uart_put_string(">>",0);
	uart_put_string(gsm.mobile_number,1);
#endif

#ifdef LCD
	LCDclr();
	LCDstring((uint8_t *)">:",12);
	LCDstring((uint8_t *)gsm.mobile_number,16);
#endif
		
	#ifdef _WDT
	wdt_reset();
	#endif
	gsm.apply = APPLY_GSM;
	gsm.dell = GSM_PRE_DELET;
	//return;

	/*_delay_ms(250);
	send2gsm(GSM_MOD);
	send2gsm(DELL_SMS);*/
}
//--------------------------------------
void select_unicode(char ch, char *buffer_out)
{
	switch(ch)
	{
		case	' ': strcpy_P(buffer_out,PSTR("00A0"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0622"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0627"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0628"));break;
		case	'�': strcpy_P(buffer_out,PSTR("067E"));break;
		case	'�': strcpy_P(buffer_out,PSTR("062A"));break;
		case	'�': strcpy_P(buffer_out,PSTR("062B"));break;
		case	'�': strcpy_P(buffer_out,PSTR("062C"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0686"));break;
		case	'�': strcpy_P(buffer_out,PSTR("062D"));break;
		case	'�': strcpy_P(buffer_out,PSTR("062E"));break;
		case	'�': strcpy_P(buffer_out,PSTR("062F"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0630"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0631"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0632"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0633"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0634"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0635"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0636"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0637"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0638"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0639"));break;
		case	'�': strcpy_P(buffer_out,PSTR("063A"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0641"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0642"));break;
		//case	'�': strcpy_P(buffer_out,PSTR("0643"));break;
		case	'�': strcpy_P(buffer_out,PSTR("06A9"));break;
		case	'�': strcpy_P(buffer_out,PSTR("06AF"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0644"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0645"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0646"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0647"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0648"));break;
		case	'�': strcpy_P(buffer_out,PSTR("06CC"));break;
		case	'?': strcpy_P(buffer_out,PSTR("064A"));break;
		case	'�': strcpy_P(buffer_out,PSTR("0698"));break;
		case	'0': strcpy_P(buffer_out,PSTR("0030"));break;
		case	'1': strcpy_P(buffer_out,PSTR("0031"));break;
		case	'2': strcpy_P(buffer_out,PSTR("0032"));break;
		case	'3': strcpy_P(buffer_out,PSTR("0033"));break;
		case	'4': strcpy_P(buffer_out,PSTR("0034"));break;
		case	'5': strcpy_P(buffer_out,PSTR("0035"));break;
		case	'6': strcpy_P(buffer_out,PSTR("0036"));break;
		case	'7': strcpy_P(buffer_out,PSTR("0037"));break;
		case	'8': strcpy_P(buffer_out,PSTR("0038"));break;
		case	'9': strcpy_P(buffer_out,PSTR("0039"));break;
		case	'A': strcpy_P(buffer_out,PSTR("0041"));break;
		case	'B': strcpy_P(buffer_out,PSTR("0042"));break;
		case	'C': strcpy_P(buffer_out,PSTR("0043"));break;
		case	'D': strcpy_P(buffer_out,PSTR("0044"));break;
		case	'E': strcpy_P(buffer_out,PSTR("0045"));break;
		case	'F': strcpy_P(buffer_out,PSTR("0046"));break;
		case	'G': strcpy_P(buffer_out,PSTR("0047"));break;
		case	'H': strcpy_P(buffer_out,PSTR("0048"));break;
		case	'I': strcpy_P(buffer_out,PSTR("0049"));break;
		case	'J': strcpy_P(buffer_out,PSTR("004A"));break;
		case	'K': strcpy_P(buffer_out,PSTR("004B"));break;
		case	'L': strcpy_P(buffer_out,PSTR("004C"));break;
		case	'M': strcpy_P(buffer_out,PSTR("004D"));break;
		case	'N': strcpy_P(buffer_out,PSTR("004E"));break;
		case	'O': strcpy_P(buffer_out,PSTR("004F"));break;
		case	'P': strcpy_P(buffer_out,PSTR("0050"));break;
		case	'Q': strcpy_P(buffer_out,PSTR("0051"));break;
		case	'R': strcpy_P(buffer_out,PSTR("0052"));break;
		case	'S': strcpy_P(buffer_out,PSTR("0053"));break;
		case	'T': strcpy_P(buffer_out,PSTR("0054"));break;
		case	'U': strcpy_P(buffer_out,PSTR("0055"));break;
		case	'V': strcpy_P(buffer_out,PSTR("0056"));break;
		case	'W': strcpy_P(buffer_out,PSTR("0057"));break;
		case	'X': strcpy_P(buffer_out,PSTR("0058"));break;
		case	'Y': strcpy_P(buffer_out,PSTR("0059"));break;
		case	'Z': strcpy_P(buffer_out,PSTR("005A"));break;
		case	'a': strcpy_P(buffer_out,PSTR("0061"));break;
		case	'b': strcpy_P(buffer_out,PSTR("0062"));break;
		case	'c': strcpy_P(buffer_out,PSTR("0063"));break;
		case	'd': strcpy_P(buffer_out,PSTR("0064"));break;
		case	'e': strcpy_P(buffer_out,PSTR("0065"));break;
		case	'f': strcpy_P(buffer_out,PSTR("0066"));break;
		case	'g': strcpy_P(buffer_out,PSTR("0067"));break;
		case	'h': strcpy_P(buffer_out,PSTR("0068"));break;
		case	'i': strcpy_P(buffer_out,PSTR("0069"));break;
		case	'j': strcpy_P(buffer_out,PSTR("006A"));break;
		case	'k': strcpy_P(buffer_out,PSTR("006B"));break;
		case	'l': strcpy_P(buffer_out,PSTR("006C"));break;
		case	'm': strcpy_P(buffer_out,PSTR("006D"));break;
		case	'n': strcpy_P(buffer_out,PSTR("006E"));break;
		case	'o': strcpy_P(buffer_out,PSTR("006F"));break;
		case	'p': strcpy_P(buffer_out,PSTR("0070"));break;
		case	'q': strcpy_P(buffer_out,PSTR("0071"));break;
		case	'r': strcpy_P(buffer_out,PSTR("0072"));break;
		case	's': strcpy_P(buffer_out,PSTR("0073"));break;
		case	't': strcpy_P(buffer_out,PSTR("0074"));break;
		case	'u': strcpy_P(buffer_out,PSTR("0075"));break;
		case	'v': strcpy_P(buffer_out,PSTR("0076"));break;
		case	'w': strcpy_P(buffer_out,PSTR("0077"));break;
		case	'x': strcpy_P(buffer_out,PSTR("0078"));break;
		case	'y': strcpy_P(buffer_out,PSTR("0079"));break;
		case	'z': strcpy_P(buffer_out,PSTR("007A"));break;
		case	'=': strcpy_P(buffer_out,PSTR("003D"));break;
		case	',': strcpy_P(buffer_out,PSTR("002C"));break;
		case	'(': strcpy_P(buffer_out,PSTR("0028"));break;
		case	')': strcpy_P(buffer_out,PSTR("0029"));break;
		case	':': strcpy_P(buffer_out,PSTR("003A"));break;
		case	';': strcpy_P(buffer_out,PSTR("003B"));break;
		case	'#': strcpy_P(buffer_out,PSTR("0023"));break;
		case	'*': strcpy_P(buffer_out,PSTR("002A"));break;
		case	'$': strcpy_P(buffer_out,PSTR("0024"));break;
		case	'+': strcpy_P(buffer_out,PSTR("002B"));break;
		case	'@': strcpy_P(buffer_out,PSTR("0040"));break;
		case	'.': strcpy_P(buffer_out,PSTR("002E"));break;
		case	'\'':strcpy_P(buffer_out,PSTR("0027"));break;
		case	'\"':strcpy_P(buffer_out,PSTR("0022"));break;
		case	'�': strcpy_P(buffer_out,PSTR("00B0"));break;
		case	'>': strcpy_P(buffer_out,PSTR("003E"));break;
		case	'<': strcpy_P(buffer_out,PSTR("003C"));break;
		case	'-': strcpy_P(buffer_out,PSTR("002D"));break;
		case	'_': strcpy_P(buffer_out,PSTR("005F"));break;
		case	'\\':strcpy_P(buffer_out,PSTR("000A"));break;	//NEW LINE
	}
}
//--------------------------------------
void chang_to_unicode(char *tex_in ,char *unicode_buffer)
{
	int i=0;
	gsm.number_of_charecter = strlen(tex_in);
	memset(gsm.compar,0,COMPAR_LEN);
	
	select_unicode(tex_in[0],gsm.compar);strcpy(unicode_buffer, gsm.compar);
	for (i=1; i<gsm.number_of_charecter; i++)
	{
		select_unicode(tex_in[i],gsm.compar);strcat(unicode_buffer,gsm.compar);
	}
}
//--------------------------------------
char convert_to_char(char *buffer_in)
{
	if(strcmp_P(buffer_in,PSTR("0030"))==0){return '0';}
	else	if(strcmp_P(buffer_in,PSTR("0040"))==0){return '@';}
	else	if(strcmp_P(buffer_in,PSTR("002E"))==0){return '.';}
	else	if(strcmp_P(buffer_in,PSTR("0031"))==0){return '1';}
	else	if(strcmp_P(buffer_in,PSTR("0032"))==0){return '2';}
	else	if(strcmp_P(buffer_in,PSTR("0033"))==0){return '3';}
	else	if(strcmp_P(buffer_in,PSTR("0034"))==0){return '4';}
	else	if(strcmp_P(buffer_in,PSTR("0035"))==0){return '5';}
	else	if(strcmp_P(buffer_in,PSTR("0036"))==0){return '6';}
	else	if(strcmp_P(buffer_in,PSTR("0037"))==0){return '7';}
	else	if(strcmp_P(buffer_in,PSTR("0038"))==0){return '8';}
	else	if(strcmp_P(buffer_in,PSTR("0039"))==0){return '9';}
	else	if(strcmp_P(buffer_in,PSTR("0041"))==0){return 'A';}
	else	if(strcmp_P(buffer_in,PSTR("0042"))==0){return 'B';}
	else	if(strcmp_P(buffer_in,PSTR("0043"))==0){return 'C';}
	else	if(strcmp_P(buffer_in,PSTR("0044"))==0){return 'D';}
	else	if(strcmp_P(buffer_in,PSTR("0045"))==0){return 'E';}
	else	if(strcmp_P(buffer_in,PSTR("0046"))==0){return 'F';}
	else	if(strcmp_P(buffer_in,PSTR("0047"))==0){return 'G';}
	else	if(strcmp_P(buffer_in,PSTR("0048"))==0){return 'H';}
	else	if(strcmp_P(buffer_in,PSTR("0049"))==0){return 'I';}
	else	if(strcmp_P(buffer_in,PSTR("004A"))==0){return 'J';}
	else	if(strcmp_P(buffer_in,PSTR("004B"))==0){return 'K';}
	else	if(strcmp_P(buffer_in,PSTR("004C"))==0){return 'L';}
	else	if(strcmp_P(buffer_in,PSTR("004D"))==0){return 'M';}
	else	if(strcmp_P(buffer_in,PSTR("004E"))==0){return 'N';}
	else	if(strcmp_P(buffer_in,PSTR("004F"))==0){return 'O';}
	else	if(strcmp_P(buffer_in,PSTR("0050"))==0){return 'P';}
	else	if(strcmp_P(buffer_in,PSTR("0051"))==0){return 'Q';}
	else	if(strcmp_P(buffer_in,PSTR("0052"))==0){return 'R';}
	else	if(strcmp_P(buffer_in,PSTR("0053"))==0){return 'S';}
	else	if(strcmp_P(buffer_in,PSTR("0054"))==0){return 'T';}
	else	if(strcmp_P(buffer_in,PSTR("0055"))==0){return 'U';}
	else	if(strcmp_P(buffer_in,PSTR("0056"))==0){return 'V';}
	else	if(strcmp_P(buffer_in,PSTR("0057"))==0){return 'W';}
	else	if(strcmp_P(buffer_in,PSTR("0058"))==0){return 'X';}
	else	if(strcmp_P(buffer_in,PSTR("0059"))==0){return 'Y';}
	else	if(strcmp_P(buffer_in,PSTR("005A"))==0){return 'Z';}
	else	if(strcmp_P(buffer_in,PSTR("0061"))==0){return 'a';}
	else	if(strcmp_P(buffer_in,PSTR("0062"))==0){return 'b';}
	else	if(strcmp_P(buffer_in,PSTR("0063"))==0){return 'c';}
	else	if(strcmp_P(buffer_in,PSTR("0064"))==0){return 'd';}
	else	if(strcmp_P(buffer_in,PSTR("0065"))==0){return 'e';}
	else	if(strcmp_P(buffer_in,PSTR("0066"))==0){return 'f';}
	else	if(strcmp_P(buffer_in,PSTR("0067"))==0){return 'g';}
	else	if(strcmp_P(buffer_in,PSTR("0068"))==0){return 'h';}
	else	if(strcmp_P(buffer_in,PSTR("0069"))==0){return 'i';}
	else	if(strcmp_P(buffer_in,PSTR("006A"))==0){return 'j';}
	else	if(strcmp_P(buffer_in,PSTR("006B"))==0){return 'k';}
	else	if(strcmp_P(buffer_in,PSTR("006C"))==0){return 'l';}
	else	if(strcmp_P(buffer_in,PSTR("006D"))==0){return 'm';}
	else	if(strcmp_P(buffer_in,PSTR("006E"))==0){return 'n';}
	else	if(strcmp_P(buffer_in,PSTR("006F"))==0){return 'o';}
	else	if(strcmp_P(buffer_in,PSTR("0070"))==0){return 'p';}
	else	if(strcmp_P(buffer_in,PSTR("0071"))==0){return 'q';}
	else	if(strcmp_P(buffer_in,PSTR("0072"))==0){return 'r';}
	else	if(strcmp_P(buffer_in,PSTR("0073"))==0){return 's';}
	else	if(strcmp_P(buffer_in,PSTR("0074"))==0){return 't';}
	else	if(strcmp_P(buffer_in,PSTR("0075"))==0){return 'u';}
	else	if(strcmp_P(buffer_in,PSTR("0076"))==0){return 'v';}
	else	if(strcmp_P(buffer_in,PSTR("0077"))==0){return 'w';}
	else	if(strcmp_P(buffer_in,PSTR("0078"))==0){return 'x';}
	else	if(strcmp_P(buffer_in,PSTR("0079"))==0){return 'y';}
	else	if(strcmp_P(buffer_in,PSTR("007A"))==0){return 'z';}
	else	if(strcmp_P(buffer_in,PSTR("003D"))==0){return '=';}
	else	if(strcmp_P(buffer_in,PSTR("002C"))==0){return ',';}
	else	if(strcmp_P(buffer_in,PSTR("0028"))==0){return '(';}
	else	if(strcmp_P(buffer_in,PSTR("0029"))==0){return ')';}
	else	if(strcmp_P(buffer_in,PSTR("003A"))==0){return ':';}
	else	if(strcmp_P(buffer_in,PSTR("003B"))==0){return ';';}
	else	if(strcmp_P(buffer_in,PSTR("0023"))==0){return '#';}
	else	if(strcmp_P(buffer_in,PSTR("002A"))==0){return '*';}
	else	if(strcmp_P(buffer_in,PSTR("002B"))==0){return '+';}
	else	if(strcmp_P(buffer_in,PSTR("002B"))==0){return '+';}
	else	if(strcmp_P(buffer_in,PSTR("0027"))==0){return '\'';}
	else	if(strcmp_P(buffer_in,PSTR("0022"))==0){return '\"';}
	else	if(strcmp_P(buffer_in,PSTR("002B"))==0){return '+';}
	else	if(strcmp_P(buffer_in,PSTR("00B0"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("00A0"))==0){return ' ';}
	else	if(strcmp_P(buffer_in,PSTR("0622"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0627"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0628"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("067E"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("062A"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("062B"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("062C"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0686"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("062D"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("062E"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("062F"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0630"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0631"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0632"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0633"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0634"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0635"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0636"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0637"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0638"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0639"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("063A"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0641"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0642"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0643"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("06A9"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("06AF"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0644"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0645"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0646"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0647"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0648"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0649"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("064A"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("06CC"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0698"))==0){return '�';}
	else	if(strcmp_P(buffer_in,PSTR("0660"))==0){return '0';}
	else	if(strcmp_P(buffer_in,PSTR("0661"))==0){return '1';}
	else	if(strcmp_P(buffer_in,PSTR("0662"))==0){return '2';}
	else	if(strcmp_P(buffer_in,PSTR("0663"))==0){return '3';}
	else	if(strcmp_P(buffer_in,PSTR("0664"))==0){return '4';}
	else	if(strcmp_P(buffer_in,PSTR("0665"))==0){return '5';}
	else	if(strcmp_P(buffer_in,PSTR("0666"))==0){return '6';}
	else	if(strcmp_P(buffer_in,PSTR("0667"))==0){return '7';}
	else	if(strcmp_P(buffer_in,PSTR("0668"))==0){return '8';}
	else	if(strcmp_P(buffer_in,PSTR("0669"))==0){return '9';}
	else	if(strcmp_P(buffer_in,PSTR("06F0"))==0){return '0';}
	else	if(strcmp_P(buffer_in,PSTR("06F1"))==0){return '1';}
	else	if(strcmp_P(buffer_in,PSTR("06F2"))==0){return '2';}
	else	if(strcmp_P(buffer_in,PSTR("06F3"))==0){return '3';}
	else	if(strcmp_P(buffer_in,PSTR("06F4"))==0){return '4';}
	else	if(strcmp_P(buffer_in,PSTR("06F5"))==0){return '5';}
	else	if(strcmp_P(buffer_in,PSTR("06F6"))==0){return '6';}
	else	if(strcmp_P(buffer_in,PSTR("06F7"))==0){return '7';}
	else	if(strcmp_P(buffer_in,PSTR("06F8"))==0){return '8';}
	else	if(strcmp_P(buffer_in,PSTR("06F9"))==0){return '9';}
	else	if(strcmp_P(buffer_in,PSTR("007C"))==0){return '|';}	// pass char  ____  xxxx|
	else	if(strcmp_P(buffer_in,PSTR("0024"))==0){return '$';}
	else	if(strcmp_P(buffer_in,PSTR("000A"))==0){return '\\';}
	else	if(strcmp_P(buffer_in,PSTR("003E"))==0){return '>';}
	else	if(strcmp_P(buffer_in,PSTR("003C"))==0){return '<';}
	else	if(strcmp_P(buffer_in,PSTR("002D"))==0){return '-';}
	else	if(strcmp_P(buffer_in,PSTR("005F"))==0){return '_';}
	return 0;
}
//--------------------------------------
void gsm_ready()
{
	static char count=0;
	#ifdef _WDT
	wdt_reset();
	#endif
	
	repet:
	#ifdef DEBUGE_GSM
	uart_put_string("AT",1);
	#endif
	uart_put_string("AT",1);
	wait_flage();
	if ((strstr_P(gsm.buffer,PSTR("OK"))) == 0){_delay_ms(300);count++;if(count<4){goto repet;}}
	
	#ifdef _WDT
	wdt_reset();
	#endif
	_delay_ms(400);
}
//--------------------------------------
void gsm_dialing(char *tex)
{
	gsm_ready();
	
	#ifdef DEBUGE_GSM
	uart_put_string("ATD",0);
	uart_put_string(tex,1);
	#endif
	uart_put_string("ATD",0);
	uart_put_string(tex,1);
	wait_flage();
	_delay_ms(400);
}
//--------------------------------------
void gsm_send_sms(char *mobile,char *tex)
{
	char count=0;
	#ifdef _WDT
	wdt_reset();
	#endif
	if (gsm.stat==ENABLE)
	{
		counter=0;
		gsm_ready();
		
		gsm.rdy = DISABLE;
		memset(gsm.tex_recive,0,TEX_RECIVE_LEN); 		//mobile number
		memset(gsm.data,0,DATA_LEN);
		#ifdef LCD
		LCDclr();
		LCDstring((uint8_t *)"Send To:",16);
		LCDGotoXY(0,1);
		LCDstring((uint8_t *)mobile,16);
		#endif
		chang_to_unicode(mobile,gsm.tex_recive);
		chang_to_unicode(tex,gsm.data);
		#ifdef DEBUGE_GSM
		uart_put_string(tex,1);
		#endif
		
		#ifdef _WDT
		wdt_reset();
		#endif
		#ifdef DEBUGE_GSM
		uart_put_string("AT+CSCS=\"UCS2\"",1);
		#endif
		uart_put_string("AT+CSCS=\"UCS2\"",1);
		_delay_ms(500);
		#ifdef _WDT
		wdt_reset();
		#endif
		#ifdef DEBUGE_GSM
		uart_put_string("AT+CMGS=\"",0);
		uart_put_string(gsm.tex_recive,0);
		uart_put_string("\"\r",0);
		#endif
		uart_put_string("AT+CMGS=\"",0);
		uart_put_string(gsm.tex_recive,0);
		uart_put_string("\"\r",0);
		#ifdef _WDT
		wdt_reset();
		#endif
		repet_:
		wait_flage();
		if ((strstr_P(gsm.buffer,PSTR(">"))) == 0){_delay_ms(300);count++;if(count<4){goto repet_;}}
		_delay_ms(300);
		#ifdef DEBUGE_GSM
		uart_put_string(gsm.data,1);
		#endif
		uart_put_string(gsm.data,1);
		uart_putchar(26);
		uart_putchar(13);
		#ifdef _WDT
		wdt_reset();
		#endif
		_delay_ms(200);
	}
}
//--------------------------------------
void send2gsm(char select)
{
	#ifdef _WDT
	wdt_reset();
	#endif
	if (gsm.stat==ENABLE)
	{	
		gsm_ready();
		
		#ifdef _WDT
		wdt_reset();
		#endif
		_delay_ms(400);
		
		switch(select)
		{
		case OFF_GSM:
			//re_off:
			 #ifdef DEBUGE_GSM 
			 uart_put_string("AT+CPOWD=1",1);
			 #endif
			uart_put_string("AT+CPOWD=1",1);
			wait_flage();
			//if(STATUS)goto re_off;
			break;
			
		case GET_IMEI:
			#ifdef DEBUGE_GSM 
			uart_put_string("AT+GSN",1);
			#endif
			uart_put_string("AT+GSN",1);
			wait_flage();
			break;
			
		case UCS2_MOD:
			#ifdef DEBUGE_GSM 
			uart_put_string("AT+CSCS=\"UCS2\"",1);
			#endif
			uart_put_string("AT+CSCS=\"UCS2\"",1);
			wait_flage();
			break;
			
		case GSM_MOD:
			#ifdef DEBUGE_GSM 
			uart_put_string("AT+CSCS=\"GSM\"",1);
			#endif
			uart_put_string("AT+CSCS=\"GSM\"",1);
			wait_flage();
			break;
			
		case DEL_ALL:
			 #ifdef DEBUGE_GSM 
			 uart_put_string("AT+CMGDA=\"DEL ALL\"",1);
			 #endif
			uart_put_string("AT+CMGDA=\"DEL ALL\"",1);
			sms_number=0;
			gsm.dell = DISABLE;
			wait_flage();
			break;
			
		case DELL_SMS:
			 #ifdef DEBUGE_GSM 
			 uart_put_string("AT+CMGD=",0);
			uart_put_string(gsm.ch_sms,ENABLE);
			#endif
			uart_put_string("AT+CMGD=",0);
			uart_put_string(gsm.ch_sms,ENABLE);
			sms_number=0;
			gsm.unread = ENABLE;
			gsm.dell = DISABLE;
			#ifdef DEBUGE_GSM
			uart_put_string("gsm_rdy=ENABLE",1);
			#endif
			gsm.rdy = ENABLE;
			break;
			
		case GET_CHARJ:
			#ifdef _WDT
			wdt_reset();
			#endif
			gsm.charj = DISABLE;
			if (gsm.sim_operator == IRANCELL)
			{
				 #ifdef DEBUGE_GSM 
				 uart_put_string("ATD",0);
				uart_put_string(get_charj_code_irancell,1);
				#endif
				uart_put_string("ATD",0);
				uart_put_string(get_charj_code_irancell,1);
			}
			else if (gsm.sim_operator == IR_MCI)
			{
				 #ifdef DEBUGE_GSM 
				 uart_put_string("ATD",0);
				uart_put_string(get_charj_code_ir_mci,1);
				#endif
				uart_put_string("ATD",0);
				uart_put_string(get_charj_code_ir_mci,1);
			}
			gsm.flag_charj = ENABLE;
			break;
			
		case  SIM_NAME:
			 #ifdef DEBUGE_GSM 
			 uart_put_string("AT+CSPN?",1);
			 #endif
			uart_put_string("AT+CSPN?",1);
			gsm.flag_simname = ENABLE;
			wait_flage();
			break;
			
		case NET_STATUS:
			#ifdef DEBUGE_GSM 
			uart_put_string("AT+CREG?",1);
			#endif
			uart_put_string("AT+CREG?",1);
			wait_flage();
			break;
			
		case GSM_RST:
			#ifdef DEBUGE_GSM 
			uart_put_string("AT+CFUN=1,1",1);
			#endif
			uart_put_string("AT+CFUN=1,1",1);
			wait_flage();
			break;
			
		case SIGNAL_Q:
			uart_put_string("AT+CSQ",1);
			wait_flage();
			break;
			
		case REQUEST_TA:
			uart_put_string("AT+GSN",1);
			wait_flage();
			break;
			
		case HANG_UP:
			uart_put_string("ATH",1);
			wait_flage();
			break;
			
		case ANSWER_RING:
			uart_put_string("ATA",1);
			break;
			
		case CMICH:
			uart_put_string("AT+CMIC=0,15",1);
			wait_flage();
			break;
		
		case CMICL:
			uart_put_string("AT+CMIC=0,10",1);
			wait_flage();
			break;
		
		case RECIEVED_UNREAD:
			#ifdef DEBUGE_GSM
			uart_put_string("AT+CMGL",1);
			#endif
			uart_put_string("AT+CMGL",1);
			break;
		
		case CUSD_ON:
			uart_put_string("AT+CUSD=1",1);
			wait_flage();
			break;
			
		case CUSD_OFF:
			uart_put_string("AT+CUSD=0",1);
			wait_flage();
			break;
		
		case RST_GSM:
			uart_put_string("ATZ",1);
			wait_flage();
			break;
		
		}
		
		#ifdef _WDT
		wdt_reset();
		#endif
	}
}
//--------------------------------------
void gsm_start(void)
{
	GSM_ON_PORT &= ~(1<<GSM_ON_PIN);
	GSM_ON_DDR |= 1<<GSM_ON_PIN;
	
	GSM_STATE_PORT &= ~(1<<GSM_STATE_PIN);
	GSM_STATE_DDR &= ~(1<<GSM_STATE_PIN);
	/************************************************************************/
	/* CONFIG UART                                                          */
	/************************************************************************/
	uart_init(CONF_8BIT_NOPAR_1STOP);
	UCSRB |= 1<<RXCIE;
	
	#ifdef _WDT
	wdt_reset();
	#endif
	if (STATUS == 0)
	{
		ON_GSM_HIGH;
		_delay_ms(1100);
		ON_GSM_LOW;
		_delay_ms(11000);
		if (STATUS)
		{
			gsm.stat = ENABLE;
			#ifdef LCD
				LCDGotoXY(0,0);
				LCDstring((uint8_t *)"     GSM ON     ",16);
			#endif
			_delay_ms(4000);
		}
		else
		{
			gsm.stat = DISABLE;
			#ifdef LCD
				LCDGotoXY(0,0);
				LCDstring((uint8_t *)"     NO GSM     ",16);
				_delay_ms(500);
			#endif
		}
	}
	else
	{
		gsm.stat = ENABLE;
		gsm.rdy = ENABLE;
	}
	
	//gsm.stat = ENABLE;
	
	if (gsm.stat == ENABLE)
	{	
		_delay_ms(1000);
		gsm_initializing();
		
		send2gsm(SIM_NAME);
		
		send2gsm(SIGNAL_Q);
		
		send2gsm(NET_STATUS);
		
		if (gsm.sim_operator==NO_SIM)
		{
			/*#ifdef LCD
				LCDGotoXY(0,0);
				LCDstring((uint8_t *)"   GSM OFF...   ",16);
			#endif*/
			//send2gsm(OFF_GSM);
			gsm.stat = DISABLE;
		}
		
		if(GSM_MODULE==SIM900_MODULE)gsm.rdy=ENABLE;
	}

}
//--------------------------------------
char get_info()
{
	return gsm.sim_operator;
}
//--------------------------------------
ISR(GSM_UART_ISR)
{
	gsm.number_of_charecter = uart_getstring(gsm.buffer,BUFFER_LEN);
	#ifdef DEBUGE_GSM
		uart_put_string(gsm.buffer,1);
	#endif
	detect_gsm();
	gsm.recive=ENABLE;
}
#endif