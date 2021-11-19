/*
 * GccApplication15.c
 *
 * Created: 2021-11-20 2:43:13 AM
 * Author : miral
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "lcd/lcd.h"
#include <util/delay.h>

int usernames[5] = {1234,4321,3214,2134,3421};
int passwords[5] = {1234,4321,3214,2134.3421};
char lcd_buff[10];
int key_pad(void)
{
	PORTA = 0b01110111;
	if(PINA0 & 0b00000001)
	return 3;
	if(PINA1 & 0b00000010)
	return 2;
	if(PINA2 & 0b00000100)
	return 1;
	PORTA = 0b01101111;
	if(PINA0 & 0b00000001)
	return 6;
	if(PINA1 & 0b00000010)
	return 5;
	if(PINA2 & 0b00000100)
	return 4;
	PORTA = 0b01011111;
	if(PINA0 & 0b00000001)
	return 9;
	if(PINA1 & 0b00000010)
	return 8;
	if(PINA2 & 0b00000100)
	return 7;
	PORTA = 0b00111111;
	if(PINA1 & 0b00000010)
	return 0;
	if(PINA2 & 0b00000100)
	return 10;
	return 12;
}

void lcd(int key)
{
	if(key==1) lcd_putc('1');
	if(key==2) lcd_putc('2');
	if(key==3) lcd_putc('3');
	if(key==4) lcd_putc('4');
	if(key==5) lcd_putc('5');
	if(key==6) lcd_putc('6');
	if(key==7) lcd_putc('7');
	if(key==8) lcd_putc('8');
	if(key==9) lcd_putc('9');
	if(key==0) lcd_putc('0');
	if(key==10) lcd_clrscr();
	
}


int main(void)
{
	  DDRA = 0b01111000;
	  PORTA = 0b00000111;
	  int key;
	  char * str;
	  lcd_init(LCD_DISP_ON_CURSOR);
	  lcd_home();
    /* Replace with your application code */
    while (1) 
    {
		   do
		   key=key_pad();
		   while(key==12);
		   char check = key +'0';
		   lcd_putc(check);
		   _delay_ms(350);
		   str = str + check;
		   
    }
}

