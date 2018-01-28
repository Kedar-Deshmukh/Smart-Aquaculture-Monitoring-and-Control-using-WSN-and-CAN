/*
 * vibration_sensor.c
 *
 * Created: 28-Jan-18 6:29:00 PM
 *  Author: SAI
 */ 
//Here PC2 pin is used to interface vibration sensor 
#include <avr/io.h>

int main(void)
{
	DDRC=DDRD&(~(1<2));
	DDRD=DDRD|(1<<7);   //Make PD7 pin as a output.This pin is connected to led is for checking the status of vibration sensor
    while(1)
    {
        if(PIND&(1<<2))			//if vibration sensor detects vibration,led connected at PD7 will blink other wise it will not blink
		{
			PORTD=PORTD|(1<<7);
		}			 
		else
		{
			PORTD=PORTD|~(1<<7);	//led turn off
		}			
    }
}