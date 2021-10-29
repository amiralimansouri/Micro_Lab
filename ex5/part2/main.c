/*
 * GccApplication6.c
 *
 * Created: 2021-10-28 6:55:08 PM
 * Author : miral
 */ 

#include <avr/io.h>
unsigned char move[4] = {0b00000001 , 0b00000010 , 0b00000100 , 0b00001000};
#include <avr/interrupt.h>
#include <stdio.h>	
volatile uint8_t ovf_max;
int i=-1;
int j=4;

void timer1_init()
{
	TCCR1B |= (1 << CS11);
	TCNT1 = 0;
	TIMSK |= (1 << TOIE1);
	sei();
	ovf_max = 0;
}


ISR(TIMER1_OVF_vect)
{
	
	ovf_max++;
	
	if (~PINC & 0b00000100){
		i=(i+1)%4;
		PORTA = move[i];
	}
	if (~PIND & 0b00000100){
		j = (j-1)%4;
		PORTA = move[j];
	}
	
	
}

int main(void)
{
	DDRA = 0xff;
	DDRC = 0x00;
	
	
	
	timer1_init();
    /* Replace with your application code */
    while (1) 
    {
		//if(ovf_max >= 12){
	
		//}
		
	
}
}

