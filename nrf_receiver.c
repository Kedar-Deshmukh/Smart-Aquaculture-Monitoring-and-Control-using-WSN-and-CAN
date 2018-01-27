
/*
 * @author
 * Copyright (C) 2012 Luis R. Hilario http://www.luisdigital.com
 *
 *
 * SSP1 pins:
 * MOSI: P0.9
 * MISO: P0.8
 * SCK : P0.7
 * CSN : P0.6
 * CE  : P0.17
 */


#include "LPC17xx.h"
#include "lpc_types.h"
#include "lpc17xx_ssp.h"
#include "cpu_lpc1000.h"
#include "nrf24l01.h"
#include "lpc17xx_clkpwr.h"

#define	_CH 1			// Channel 0..125
#define	_Address_Width	5	// 3..5
#define _Buffer_Size 5 // 1..32

// Define OUT/ON/OFF Demo board LED
#define LED_DIR_OUT LPC_GPIO1->FIODIR |= (1<<28) /*D2 LED*/
#define LED_OFF LPC_GPIO1->FIOCLR |= (1<<28)
#define LED_ON  LPC_GPIO1->FIOSET |= (1<<28)


void NRF24L01_Receive(char Buf[_Buffer_Size]) {
	NRF24L01_CE_HIGH;
	Delay_us(130);

	while ((NRF24L01_Get_Status() & _RX_DR) != _RX_DR);

	NRF24L01_CE_LOW;

	NRF24L01_Read_RX_Buf(Buf, _Buffer_Size);
	NRF24L01_Clear_Interrupts();
}


void NRF24L01_Send(char Buf[_Buffer_Size]) {
	NRF24L01_Write_TX_Buf(Buf, _Buffer_Size);

	NRF24L01_RF_TX();

	while ((NRF24L01_Get_Status() & _TX_DS) != _TX_DS);

	NRF24L01_Clear_Interrupts();

}

void Led_Blink(void) {
	LED_ON;


	Delay_us(50000);
	LED_OFF;
	Delay_us(50000);
}

void main(void)
{
	char Buf[_Buffer_Size];

	SSPInit();

	Delay_Init();

	LED_DIR_OUT;
	Led_Blink();
	char Address[_Address_Width] = { 0x11, 0x22, 0x33, 0x44, 0x55 };

	NRF24L01_Init(_RX_MODE, _CH, _1Mbps, Address, _Address_Width, _Buffer_Size);

	while (1) {
		NRF24L01_Receive(Buf);

		if (Buf[0] == 0x48) {
			LED_ON;
			Delay_us(1000);
			LED_OFF;
		}

	}

}

