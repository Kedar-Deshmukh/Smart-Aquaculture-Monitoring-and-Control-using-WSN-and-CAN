/*
 * IncFile1.h
 *
 * Created: 27-Jan-18 6:40:20 AM
 *  Author: SAI
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
void I2C_Init();								/* I2C initialize function */
uint8_t  I2C_Start(char write_address);			/* I2C start function */
uint8_t  I2C_Repeated_Start(char read_address);	/* I2C repeated start function */
void I2C_Stop();								/* I2C stop function */
void I2C_Start_Wait(char write_address);		/* I2C start wait function */
uint8_t  I2C_Write(char data);					/* I2C write function */
int I2C_Read_Ack();							/* I2C read ack function */
int I2C_Read_Nack();							/* I2C read nack function */


#endif /* INCFILE1_H_ */