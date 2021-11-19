/*
 * GccApplication14.c
 *
 * Created: 2021-11-19 6:58:13 PM
 * Author : miral
 */ 
#define F_CPU		8000000UL	
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))
#define BAUD RATE	9600
#include <avr/io.h>
#include <stdio.h>
#include "lcd/lcd.h"
#include <util/delay.h>


int usernames[5] = {1234,4321,3214,2134,3421};
int passwords[5] = {1234,4321,3214,2134.3421};
unsigned char move[4] = {0b00000001 , 0b00000010 , 0b00000100 , 0b00001000};

	
void usart_initialize(void);		
void usart_transfer(char x);		
char usart_recieve(void);		
void usart_print(char *c);	
int isnumber(int num);
void make_empty(char *c);
char transfered_d;
char a;
unsigned int read_adc(unsigned char adc_input)
{
	ADMUX=adc_input | ADC_VREF_TYPE;
	ADCSRA|=(1<<ADSC);
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADCW;
}

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
   DDRC = 0xff;
   DDRA = 0x00;
   PORTA = 0x00;
  // int key ;f
   char for_temp[10];
   usart_initialize();
   usart_print("hi friend. this is amirali");	
   usart_transfer(0x0d);
   usart_print("start the motor =>(?) rounds");
   usart_transfer(0x0d);
   usart_print("check the temperature=>t");
   usart_transfer(0x0d);
   int to_read=0;
   int temp;
  ADMUX=ADC_VREF_TYPE;
  ADCSRA = 0b10000010;
  SFIOR = 0b000;
   lcd_init(LCD_DISP_ON_CURSOR);
   lcd_home();  
   while (1)
   {    
	
	   	 transfered_d = usart_recieve();
		 a = transfered_d;
		 int num = a - '0';
		 if((isnumber(num)) == 1){
			 lcd_clrscr();
			 lcd_puts("starting...");
			 int j;
			 for(j=0;j<(4*num);j++){
				 PORTC=move[(j%4)];
				 _delay_ms(250);
			 }
			}
			else if((isnumber(num )==0) && a !='t'){
				lcd_clrscr();
				lcd_puts("invalid input");
				_delay_ms(1000);
				lcd_clrscr();
			}
			
			else{
				to_read=read_adc(0);
				temp=to_read/2.054;
				sprintf(for_temp,"%d",temp);
				lcd_clrscr();
				lcd_home();
				lcd_puts("temperature:");
				lcd_gotoxy(0,13);
				lcd_puts(for_temp);
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
		 //}
		 
	  
   }
}

void usart_initialize()
{
	UBRRH = 0x00;						
	UBRRL = 0x33;						
	UCSRB = (1<<TXEN) | (1<<RXEN);		
	UCSRC = (1<<URSEL) | (3<<UCSZ0);	
}

void usart_transfer(char x)
{
	UDR = x;					
	while (!(UCSRA & (1<<UDRE)));		
}

char usart_recieve()
{
	while (!(UCSRA & (1<<RXC)));		
	return(UDR);						
}

void usart_print(char *c)
{
	while (*c != 0)						
	usart_transfer(*c++);					
}
int isnumber (int num){
	
	if (num==0)
		return 1;
	if (num==1)
		return 1;
	if (num==2)
		return 1;
	if (num==3)
		return 1;
	if (num==4)
		return 1;
	if (num==5)
		return 1;
	if (num==6)
		return 1;
	if (num==7)
		return 1;
	if (num==8)
		return 1;
	if (num==9)
		return 1;
	return 0;
}

