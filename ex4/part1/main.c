/*
 * lcd_1.c
 *
 * Created: 2021-10-22 1:12:45 PM
 * Author : miral
 */ 

#include <avr/io.h>
#include "lcd/lcd.h"

int main(void)
{
	DDRB = 0x00;
	PORTB = 0x00;
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_clrscr();
	lcd_home();
	lcd_puts("hello i'm");
	lcd_gotoxy(1,0);
	lcd_puts("amirali mansouri");
    while (1) 
    {
    }
}

