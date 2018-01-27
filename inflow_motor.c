/*
 * inflow_motor.c
 *
 * Created: 27-Jan-18 12:51:49 PM
 *  Author: SAI
 */ 

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRD=DDRD&&0X1F; //PD7 CONNECTED TO UPPER LEVEL SENSOR AND PD6 CONNECTED TO LOWER LEVEL SENSOR,PD5 SENSOR CONNECTED TO PIPE SENSOR
	PORTD=0XFF;
	DDRB=DDRB|0X10;	//PB4 CONNECTED TO MOTOR
	DDRC=DDRC&&0XFB;	//PC2 CONNECTED TO VIBRATION SENSOR
    while(1)
    {
		if(PIND&&(1<<7))  //THIS CHECKS THE PD6 LOWER LEVEL GPIO PIN IF IT HIGH MOTOR WILL BE ON
		{
			PORTB=PORTB|(1<<5);	  
			_delay_ms(5000);
			 if((PINC&&(1<<3))&&(PIND&&(1<<6)))	//IF VIBRATION SENSOR IS DETECTS MOTOR CONDITION AS ON AND PIPE ALSO THAT IDICATES MOTOR POURS WATER INTO POND
			{
				PORTB=PORTB|(1<5);
				if(PIND&&(1<<8))				//THIS CONDITION CHECKS THE MOTOR HIGH LEVEL,IF WATER REACHED TO HIGH LEVEL MOTOR WILL TURN OFF
					PORTB=PORTB|(~(1<5));
			}		
			else
			{
				PORTB=PORTB|(~(1<5));		//ABOVE TWO CONDITIONS FAILS THE MOTOR WILL BE SWITCHED OFF
			}
		}
										     
    }
}