//Interfacin ldr to atmega8

#include <avr/io.h>//header to enable data flow control over pins
#include <util/delay.h>//header to enable delay function in program
int main(void)
{
	DDRC = 0;//Taking portC as input.
	DDRD=(1<<PD6);//led
	PORTD=(1<<PD6);
	ADMUX |=(1<<REFS0);//setting the reference of ADC
	ADCSRA |=(1<<ADEN)|(1<<ADFR)|(1<<ADPS0);
	float i =0;
	float LDR= 0; //storing digital output
	ADCSRA |=(1<<ADSC);  //starting the ADC conversion  
	while(1)
	{
		i=ADC/204.8;
// Now since it’s a 10bit ADC for every Vref(5V)/1024=5mV(4.88mV) we get one digital increment or for every 1V increment in input we get 204.8 count increment. So for finding voltage at ADC pin.
	LDR = (i*10/(5-i));
		_delay_ms(50);
	if(LDR>=6)
	{
		PORTD&=~(1<<PD6);
	}
	else
	PORTD|=(1<<PD6);
} 
	}    
