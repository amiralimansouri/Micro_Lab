#define F_CPU 1000000UL
#include <avr/io.h>
#include <string.h>
#include "lcd/lcd.h"
#include <util/delay.h>
#include <stdio.h>
unsigned char text_reciever[16];

int key_pad(void)    
{
	
	PORTC =0b01110111;
	if(!PINC0)
		return 3;
	if(!PINC1)
		return 2;
	if(!PINC2)
		return 1;
	PORTC = 0b01101111;
	if(!PINC0)
		return 6;
	if(!PINC1)
		return 5;
	if(!PINC2)
		return 4;
	PORTC = 0b01011111;
	if(!PINC0)
		return 9;
	if(!PINC1)
		return 8;
	if(!PINC2)
		return 7;
	PORTC = 0b00111111;
	return 12;
}

void lcd(int id)  
{
	if(id==1) lcd_putc('1');
	if(id==2) lcd_putc('2');
	if(id==3) lcd_putc('3');
	if(id==4) lcd_putc('4');
	if(id==5) lcd_putc('5');
	if(id==6) lcd_putc('6');
	if(id==7) lcd_putc('7');
	if(id==8) lcd_putc('8');
	if(id==9) lcd_putc('9');
	if(id==0) lcd_putc('0');
	if(id==10) lcd_clrscr();

}

int main(void)
{	 
	 UBRRH = 0;
	 UBRRL = 51;
	 UCSRA = 0x00;
	 UCSRB = 0x10;
	 UCSRC = 0x86;
	 int identifier;
	 DDRC=0b01111000;
	 PORTC=0b00000111;
	 DDRB = 0x00;
	 PORTB = 0x00;
	 lcd_init(LCD_DISP_ON_CURSOR);
	 lcd_clrscr();
    /* Replace with your application code */
    while (1) 
    {		
		  gets(text_reciever);
		  lcd_clrscr();
		  lcd_home();
		  lcd_puts(text_reciever);
		  _delay_ms(2000);
		  do
		  identifier=key_pad();    
		  while(identifier==12);
		  lcd(identifier);         
		  _delay_ms(250);
    }
}
