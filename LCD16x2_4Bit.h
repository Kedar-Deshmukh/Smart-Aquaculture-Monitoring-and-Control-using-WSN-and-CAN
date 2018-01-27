/*
 * LCD16x2_4Bit.h
 *
 * Created: 27-Jan-18 6:41:14 AM
 *  Author: SAI
 */ 


#ifndef LCD16X2_4BIT_H_
#define LCD16X2_4BIT_H_


void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcdinit();
void lcd_print_xy(char row, char pos, char* str);
void lcd_print(char *str);
void lcd_clear();


#endif /* LCD16X2_4BIT_H_ */