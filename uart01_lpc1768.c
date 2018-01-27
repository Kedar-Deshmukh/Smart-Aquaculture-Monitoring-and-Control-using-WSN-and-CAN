#include<lpc17xx.h>
#include<lpc_types.h>
#include<lpc17xx_clkpwr.h>
#include<lpc17xx_gpio.h>
#include<lpc17xx_libcfg_default.h>
#include<lpc17xx_uart.h>
#include<stdio.h>

void uart0_init(uint32_t );
char uart0_rx(void);
void uart0_tx(char *ch);

void uart1_init(uint32_t );
char uart1_rx(void);
void uart1_tx(char *ch);

void delayMs(uint8_t timer_num, uint32_t delayInMs);
void make_a_call();
//void send_message();



int main(void)
{
		 SystemInit();
		 uart0_init(9600);
		 uart1_init(9600);
		 make_a_call();

return 0;
}





void uart0_init(uint32_t baudrate)
{

	 uint32_t var_UartPclk_u32,var_Pclk_u32,var_RegValue_u32;

  	LPC_SC->PCONP					|=(1<<3);// POWER AND CLOCK IS ON OF UART1;
	LPC_PINCON->PINSEL0				&=~(1<<4);
	LPC_PINCON->PINSEL0				&=~(1<<5);  //CLEAR PINSEL 0 BITS
	LPC_PINCON->PINSEL0				&=~(1<<6);
	LPC_PINCON->PINSEL0				&=~(1<<7);

	LPC_PINCON->PINSEL0				|=(1<<4);
	LPC_PINCON->PINSEL0				|=(1<<6);// SELECT TX RX PINS


	LPC_UART0->LCR 					|=(1<<0)|(1<<1)|(1<<7);// 8 BIT DATA IS SELECT AND DLAB IS ENABLE;
	LPC_UART0->FCR					|=(1<<0)|(1<<1)|(1<<2); // RX TX FIFO IS ENABLE //RX TX IS RESET;;
	LPC_UART0->TER					|=(1<<7); // TRANSMIT ENABLE



    var_UartPclk_u32 = (LPC_SC->PCLKSEL0 >> 6) & 0x03;

    switch( var_UartPclk_u32 )
    {
    case 0x00:
        var_Pclk_u32 = SystemCoreClock/4;
        break;
    case 0x01:
        var_Pclk_u32 = SystemCoreClock;
        break;
    case 0x02:
        var_Pclk_u32 = SystemCoreClock/2;
        break;
    case 0x03:
        var_Pclk_u32 = SystemCoreClock/8;
        break;
    }

    var_RegValue_u32 = ( var_Pclk_u32 / (16 * baudrate ));
    LPC_UART0->DLL =  var_RegValue_u32 & 0xFF;
    LPC_UART0->DLM = (var_RegValue_u32 >> 0x08) & 0xFF;


    LPC_UART0->LCR					 &=~(1<<7);   // Clear DLAB BIT

}


void uart0_tx(char *ch)
{
	int i;
	 for(i=0;ch[i]!='\0';i++)
	  {
		 while(!(LPC_UART0->LSR &(1<<5)));// Wait for Previous transmission
		 LPC_UART0->THR=ch[i];   // Load the data to be transmitted
		 delayMs(0,500);
	  }

}


char uart0_rx()
{
    while(!(LPC_UART0->LSR &(1<<0)));  // Wait till the data is received
    return LPC_UART0->RBR;// Read received data

}




void uart1_init(uint32_t baudrate)
{

	 uint32_t var_UartPclk_u32,var_Pclk_u32,var_RegValue_u32;

  	LPC_SC->PCONP					|= (1<<4);// POWER AND CLOCK IS ON OF UART1;

  	LPC_PINCON->PINSEL4				&=~(1<<0);
	LPC_PINCON->PINSEL4				&=~(1<<1);  //CLEAR PINSEL 0 BITS
	LPC_PINCON->PINSEL4				&=~(1<<2);
	LPC_PINCON->PINSEL4				&=~(1<<3);

	LPC_PINCON->PINSEL4				|=(1<<1);
	LPC_PINCON->PINSEL4				|=(1<<3);// SELECT TX RX PINS


	LPC_UART1->LCR 					|=(1<<0)|(1<<1)|(1<<7);// 8 BIT DATA IS SELECT AND DLAB IS ENABLE;
	LPC_UART1->FCR					|=(1<<0)|(1<<1)|(1<<2); // RX TX FIFO IS ENABLE //RX TX IS RESET;;
	LPC_UART1->TER					|=(1<<7); // TRANSMIT ENABLE



    var_UartPclk_u32 = (LPC_SC->PCLKSEL0 >> 8) & 0x03;

    switch( var_UartPclk_u32 )
    {
    case 0x00:
        var_Pclk_u32 = SystemCoreClock/4;
        break;
    case 0x01:
        var_Pclk_u32 = SystemCoreClock;
        break;
    case 0x02:
        var_Pclk_u32 = SystemCoreClock/2;
        break;
    case 0x03:
        var_Pclk_u32 = SystemCoreClock/8;
        break;
    }

    var_RegValue_u32 = ( var_Pclk_u32 / (16 * baudrate ));
    LPC_UART1->DLL =  var_RegValue_u32 & 0xFF;
    LPC_UART1->DLM = (var_RegValue_u32 >> 0x08) & 0xFF;

    LPC_UART1->LCR					 &=~(1<<7);   // Clear DLAB BIT

}


void uart1_tx(char *ch)
{
	int i;
	 for(i=0;ch[i]!='\0';i++)
	  {
		 while(!(LPC_UART1->LSR &(1<<5)));// Wait for Previous transmission
		 LPC_UART1->THR=ch[i];   // Load the data to be transmitted

	  }

}


char uart1_rx(void)
{

    while(!(LPC_UART1->LSR &(1<<0)));  // Wait till the data is received
    LPC_UART1->RBR;// Read received data

}




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


void make_a_call()
{
char ch;



char  arr[]={"Uart Initializing.."};
char  arr1[]={"Sending AT Command"};
char  arr2[]={"Calling. To User"};
char  arr3[]={"Call Disconnect.."};

		//	GLCD_clearLn(10) ;
			//GLCD_displayStringLn(10, arr);
			printf("Uart Initializing...\n\r");
			delayMs(0,2000);

				//GLCD_clearLn(10) ;
				//GLCD_displayStringLn(10, arr1);
				printf("Uart sending AT command\n\r");
				uart0_tx("AT\r\n");

					printf("Delay call for 1sec\n\r");
					delayMs(0,1000);

					printf("Uart receiving data\n\r");
					ch=uart0_rx();
					uart1_tx(ch);

						printf("Uart Receive AFTER AT:%c\n",ch);
						printf("Delay call for 1sec\n\r");
						delayMs(0,1000);


							printf("Uart sending Mobile No\n\r");
							uart0_tx("ATD9728357365;\r\n");
					//		GLCD_clearLn(10) ;
						//	GLCD_displayStringLn(10, arr2);

								printf("Uart receiving data\n\r");
								ch=uart0_rx();
								uart1_tx(ch);


									printf("Uart Receiving:%c\n",ch);
									printf("Delay call for 5sec\n\r");
									delayMs(0,35000);
									uart0_tx("ATH\r\n");
									ch=uart0_rx();
									uart1_tx(ch);
							//		GLCD_clearLn(10) ;
								//	GLCD_displayStringLn(10, arr3);
									delayMs(0,3000);
								//	GLCD_clearLn(10) ;

}










