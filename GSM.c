
/*GSM interfacing with LPC1768*/

#include "stdint.h"
#include "stdlib.h"
#include "uart.h"
#include "misc.h"
/* device includes */
#include "system_LPC17xx.h"
#include "LPC17xx.h"
#include "stdio.h"

#include "string.h"

/* process */
void prvSetupHardware(void);
void debug_out(char *);
void modem_out(char *);
uint8_t process_response(char * ptr, uint16_t len);
static void monModem(void);
static void CallModem(void);
static void CutModem(void);
static void SMSModemconfig(void);
static void SMSsend(void);

void delayMs(uint8_t timer_num, uint32_t delayInMs);

int main(void)
{
	/* Setup the Hardware */
	prvSetupHardware();
	debug_out("In main function\r\n");
	monModem();
	//SMSModemconfig();
	//SMSsend();
	CallModem();
	delayMs(0,25000);
	CutModem();
	while(1);
	/* Never reach here */
	return 0;
}
/* setup hardware */
void prvSetupHardware(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	uart0_init(9600);
	uart1_init(9600);
	debug_out("system started\r\n");
}
/* debug print */
void debug_out(char * ptr)
{
	uint8_t i;
	for(i = 0;ptr[i] != '\0';i++)
	{
		uart1_putc(ptr[i]);
	}
}
/* modem print */
void modem_out(char * ptr)
{
	uint8_t i;
	for(i = 0;ptr[i] != '\0';i++)
	{
		uart0_putc(ptr[i]);
	}
}
/* modem response line types */
#define __LINE_BLANK 	0
#define __LINE_ERROR 	2
#define __LINE_OTHER	3

uint8_t process_response(char * ptr, uint16_t len)
{
	if(isblankstr(uart0_fifo.line, len))
	{
		debug_out("received blank line\r\n");
		debug_out(ptr);
		debug_out("\r\n");
		return __LINE_BLANK;
	}
	if(strstr(ptr,"ERROR") != NULL)
	{
		// error case
		debug_out("Received from modem error line\r\n");
		debug_out(ptr);
		debug_out("\r\n");
		return __LINE_ERROR;
	}
	else
	{
		// this is ok
		debug_out("Received from modem other line\r\n");
		debug_out(ptr);
		debug_out("\r\n");
		return __LINE_OTHER;
	}
}
/* monModem */
static void monModem(void)
{
	uint16_t len, resp;
	debug_out("sending 'AT'\r\n");
	modem_out("AT\r");
	debug_out("'AT' sent\r\n");
	debug_out("reading 1st line\r\n");
	len=uart0_readline();
	resp=process_response(uart0_fifo.line,len);
	debug_out("read 1st line\r\n");
	debug_out("processing line, expecting a blank\r\n");
	if(resp == __LINE_BLANK)
	{
		debug_out("got __BLANK line\r\n");
	}
	else
	{
		debug_out("error occurred\nExpected __BLANK, but got something else\r\n");
	}
	debug_out("reading 2nd line\r\n");
	len = uart0_readline();
	debug_out("read 2nd line\r\n");
	debug_out("processing line, expected is __OTHER line\r\n");
	resp = process_response(uart0_fifo.line,len);
	if(resp == __LINE_OTHER)
	{
		debug_out("got __OTHER line\r\n");
		debug_out("searching for 'OK'\r\n");
		if(strstr(uart0_fifo.line, "OK"))
		{
			debug_out("found ok\r\n");
			debug_out("'AT' 'OK' success\r\n");
		}
		else
		{
			debug_out("expected is __OTHER, but got something else\r\n");
		}
	}
	else
	{
		debug_out("'OK' not found\r\n");
	}
}
/*SMS modem*//*
static void SMSModemconfig(void)
{
	uint16_t len, resp;
	debug_out("sending 'AT+CMGF=1'\r\n");
	modem_out("AT+CMGF=1\r");
	debug_out("'AT+CMGF=1;' sent\r\n");
	debug_out("reading 1st line\r\n");
	len = uart0_readline();
	resp = process_response(uart0_fifo.line,len);
	debug_out("read 1st line\r\n");
	debug_out("processing line, expecting a blank\r\n");
	if(resp == __LINE_BLANK)
	{
		debug_out("got __BLANK line\r\n");
	}
	else
	{
		debug_out("error occurred\nExpected __BLANK, but got something else\r\n");
	}

	debug_out("reading 2nd line\r\n");
	// read 2nd line
	len = uart0_readline();
	debug_out("read 2nd line\r\n");
	debug_out("processing line, expected is __OTHER line\r\n");

	resp = process_response(uart0_fifo.line,len);

	if(resp == __LINE_OTHER)
	{
		debug_out("got __OTHER line\r\n");
		debug_out("searching for 'OK'\r\n");

		if(strstr(uart0_fifo.line, "OK"))
		{
			debug_out("found ok\r\n");
			debug_out("'AT+CMGF=1' 'OK' success\r\n");
		}
		else
		{
			debug_out("expected is __OTHER, but got something else\r\n");
		}
	}
	else
	{
		debug_out("'OK' not found\r\n");
	}
}
*/
/*SMS sending*/
/*
static void SMSsend(void)
{
	uint16_t len, resp;

	debug_out("sending 'AT+CMGS=\"9492435022\"'\r\n");
	modem_out("AT+CMGS=\"7893217004\"\r");
	debug_out("AT+CMGS=\"9492435022\"' sent\r\n");
	debug_out("reading 1st line\r\n");
	len = uart0_readline();
	resp = process_response(uart0_fifo.line,len);
	debug_out("read 1st line\r\n");
	debug_out("processing line, expecting a blank\r\n");
	if(resp == __LINE_BLANK)
	{
		debug_out("got __BLANK line\r\n");
	}
	else
	{
		debug_out("error occurred\nExpected __BLANK, but got something else\r\n");
	}
	debug_out("reading 2nd line\r\n");
	// read 2nd line
	len = uart0_readline();
	debug_out("read 2nd line\r\n");
	debug_out("processing line, expected is __OTHER line\r\n");
	resp = process_response(uart0_fifo.line,len);
	delayMs(0,5000);
	modem_out("Hello Siri\r\n");
	if(resp == __LINE_OTHER)
	{
		debug_out("got __OTHER line\r\n");
		debug_out("searching for 'OK'\r\n");
		if(strstr(uart0_fifo.line, ">"))
		{
			debug_out("found >\r\n");
			/*Type your message*//*
			modem_out("Hello Siri\r");
			debug_out("Sending message");
		}
		else
		{
			debug_out("expected is __OTHER, but got something else\r\n");
		}
	}
	else
	{
		debug_out("'OK' not found\r\n");
	}
	// read 3rd line
		len = uart0_readline();
		debug_out("read 3nd line\r\n");
		debug_out("processing line, expected is __OTHER line\r\n");
		resp = process_response(uart0_fifo.line,len);
		if(resp == __LINE_OTHER)
		{
			debug_out("got __OTHER line\r\n");
			debug_out("searching for 'OK'\r\n");
			if(strstr(uart0_fifo.line, "OK"))
			{
				debug_out("found ok\r\n");
				debug_out("Message sent: 'OK' success\r\n");
			}
			else
			{
				debug_out("expected is __OTHER, but got something else\r\n");
			}
		}
		else
		{
			debug_out("'OK' not found\r\n");
		}
}
*/
static void CallModem(void)
{
	uint16_t len, resp;

	debug_out("sending 'ATD9492435022;'\r\n");
	modem_out("ATD8109324063;\r");
	debug_out("'ATD9492435022;' sent\r\n");
	debug_out("reading 1st line\r\n");
	len = uart0_readline();
	resp = process_response(uart0_fifo.line,len);
	debug_out("read 1st line\r\n");
	debug_out("processing line, expecting a blank\r\n");
	if(resp == __LINE_BLANK)
	{
		debug_out("got __BLANK line\r\n");
	}
	else
	{
		debug_out("error occurred\nExpected __BLANK, but got something else\r\n");
	}
	debug_out("reading 2nd line\r\n");
	// read 2nd line
	len = uart0_readline();
	debug_out("read 2nd line\r\n");
	debug_out("processing line, expected is __OTHER line\r\n");
	resp = process_response(uart0_fifo.line,len);
	if(resp == __LINE_OTHER)
	{
		//debug_out("got __OTHER line\r\n");
		debug_out("searching for 'OK'\r\n");
		if(strstr(uart0_fifo.line, "OK"))
		{
			debug_out("found ok\r\n");
			debug_out("'ATD9492435022;' 'OK' success\r\n");
		}
		else
		{
			debug_out("expected is __OTHER, but got something else\r\n");
		}
	}
	else
	{
		debug_out("'OK' not found\r\n");
	}
}
/*Cut the call*/
static void CutModem(void)
{
	uint16_t len, resp;
	debug_out("sending 'ATH'\r\n");
	modem_out("ATH\r");
	debug_out("'ATH' sent\r\n");
	debug_out("reading 1st line\r\n");
	len = uart0_readline();
	resp = process_response(uart0_fifo.line,len);
	debug_out("read 1st line\r\n");
	debug_out("processing line, expecting a blank\r\n");
	if(resp == __LINE_BLANK)
	{
		debug_out("got __BLANK line\r\n");
	}
	else
	{
		debug_out("error occurred\nExpected __BLANK, but got something else\r\n");
	}
	debug_out("reading 2nd line\r\n");
	// read 2nd line
	len = uart0_readline();
	debug_out("read 2nd line\r\n");
	debug_out("processing line, expected is __OTHER line\r\n");
	resp = process_response(uart0_fifo.line,len);
	if(resp == __LINE_OTHER)
	{
		debug_out("got __OTHER line\r\n");
		debug_out("searching for 'OK'\r\n");
		if(strstr(uart0_fifo.line, "OK"))
		{
			debug_out("found ok\r\n");
			debug_out("'ATH' 'OK' success\r\n");
		}
		else
		{
			debug_out("expected is __OTHER, but got something else\r\n");
		}
	}
	else
	{
		debug_out("'OK' not found\r\n");
	}
}
/* Timer0 delay */
void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  if ( timer_num == 0 )
  {
        LPC_TIM0->TCR = 0x02;                /* reset timer */
        LPC_TIM0->PR  = 0x00;                /* set prescaler to zero */
        LPC_TIM0->MR0 = delayInMs * (9000000 / 1000-1);
        LPC_TIM0->IR  = 0xff;                /* reset all interrrupts */
        LPC_TIM0->MCR = 0x04;                /* stop timer on match */
        LPC_TIM0->TCR = 0x01;                /* start timer */
        /* wait until delay time has elapsed */
        while (LPC_TIM0->TCR & 0x01);
  }
  else if ( timer_num == 1 )
  {
        LPC_TIM1->TCR = 0x02;                /* reset timer */
        LPC_TIM1->PR  = 0x00;                /* set prescaler to zero */
        LPC_TIM1->MR0 = delayInMs * (9000000 / 1000-1);
        LPC_TIM1->IR  = 0xff;                /* reset all interrrupts */
        LPC_TIM1->MCR = 0x04;                /* stop timer on match */
        LPC_TIM1->TCR = 0x01;                /* start timer */
        /* wait until delay time has elapsed */
        while (LPC_TIM1->TCR & 0x01);
  }
  return;
}
