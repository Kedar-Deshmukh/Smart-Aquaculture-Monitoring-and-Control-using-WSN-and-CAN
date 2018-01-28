/*
 * temperature.c
 *
 * Created: 28-Jan-18 7:13:10 PM
 *  Author: SAI
 */ 
//The temperature sensor connected to PC0
#include <avr/io.h>
#include <util/delay.h>


int ADC_Read(char channel)							
{
	ADMUX = 0x40 | (channel & 0x07);   /* set input channel to read */
	ADCSRA |= (1<<ADSC);               /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	_delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}

void ADC_Init()
{										
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;           /* Vref: Avcc, ADC channel: 0 */
}
int main(void)
{
	DDRC=DDRC&~(1<<0);
	ADC_Init();
	float celsius;
    while(1)
    {
		celsius = (ADC_Read(0)*4.88);
		celsius = (celsius/10.00);  
    }
}