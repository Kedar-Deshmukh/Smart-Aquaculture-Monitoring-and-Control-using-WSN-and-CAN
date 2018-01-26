//This module is to interface Hall sensor to atmega8
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1<<PD6); //Nakes first pin of PORTC as Output
	DDRD=DDRD&(0<<PD7);//Makes firs pin of PORTD as Input 
	PORTD=PORTD|(1<<PD7);
	while(1) //infinite loop
	{
		if((PIND & (1<<PD7)) == 0) //If switch is pressed
		{
			PORTD |= (1<<PD6);  //Turns ON LED
			_delay_ms(3000);    //3 second delay
			PORTD &= ~(1<<PD0); //Turns OFF LED
		}
	}
}
