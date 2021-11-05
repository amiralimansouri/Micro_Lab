/*
 * GccApplication7.c
 *
 * Created: 2021-11-03 10:49:01 PM
 * Author : miral
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include "lcd/lcd.h"
#include <stdio.h>
#include <util/delay.h>
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))    
unsigned int read_adc(unsigned char adc_input)
{
	ADMUX=adc_input | ADC_VREF_TYPE;
	ADCSRA|=(1<<ADSC);
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADCW;
}
int main(void)
{
	DDRA = 0x00;
	PORTA = 0x00;
	DDRB = 0x00;
	PORTB = 0x00;
	int to_read=0;              
	int temp;
	char lcd_buff[10];
	ADMUX=ADC_VREF_TYPE;       
	ADCSRA = 0b10000010;
	SFIOR = 0b000;
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_clrscr();
	
	

    /* Replace with your application code */
    while (1) 
    {
		to_read=read_adc(0);           
		temp=to_read/2.054;  
		sprintf(lcd_buff,"%d",temp+1);
		lcd_clrscr();
		lcd_home();
		lcd_puts("temperature:");
		lcd_gotoxy(0,13);
		lcd_puts(lcd_buff);
		if(temp<24 ){
			lcd_gotoxy(1,0);
			lcd_puts("COLD    ");
		}
		if(24<=temp && temp<=39){
			lcd_gotoxy(1,0);
			lcd_puts("PLEASANT");
		}
		if(temp>39){
			lcd_gotoxy(1,0);
			lcd_puts("HOT     ");
		}
		_delay_ms(1000);
	
    }
}
