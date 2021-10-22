/*
 * lcd_1.c
 *
 * Created: 2021-10-22 1:12:45 PM
 * Author : miral
 */ 

#include <avr/io.h>
#include "lcd/lcd.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
volatile uint8_t ovf_max;

void timer2_init()
{	
	TCCR2 |= (1 << CS22)|(1 << CS21);
	TCNT2 = 0;
	TIMSK |= (1 << TOIE2);	
	sei();	
	ovf_max = 0;
}


ISR(TIMER2_OVF_vect)
{
	
	ovf_max++;
}

int main(void)
{
	int m;
	int s=0;
	int h;
	char lcd_buff[10];
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_home();
	lcd_puts("time :");
	lcd_gotoxy(0,8);
	lcd_puts(":");
	lcd_gotoxy(0,11);
	lcd_puts(":");
	DDRC |= (1 << 0);
	
	
	timer2_init();
	
	
	while(1)
	{
		
		if (ovf_max >= 12) //by calculation... this will be equal to 1 second
		{
			
			if (TCNT2 >= 53)
			{	
				s++;
				lcd_gotoxy(0,12); 
				sprintf(lcd_buff,"%d",s);
				lcd_puts(lcd_buff);
				if(s==60){//if 60 seconds pass, m is gonna increase by one
					s=0;
					m++;
					lcd_gotoxy(0,9);
					sprintf(lcd_buff,"%d",m);
					lcd_puts(lcd_buff);
				}
				if(m==60){//if 60 minutes pass, h is gonna increase by one 
					m=0;
					h++;
					lcd_gotoxy(0,6);
					sprintf(lcd_buff,"%d",h);
					lcd_puts(lcd_buff);
				}
				if(h==24){//if 24 hours pass, all the variables will change to zero
					h=0;
					s=0;
					m=0;
					lcd_home();
					lcd_puts("one day passed");//in case on day has been passed this message is gonna appear on the lcd
					lcd_clrscr();
				}
				TCNT2 = 0;           
				ovf_max = 0;    
			}
		}
	}
   
}

