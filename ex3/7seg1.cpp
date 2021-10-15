 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
	int sevenseg [10] = {0b1000000,0b1111001,0b0100100,0b0110000,0b0011001,0b0010010,0b0000010,0b1111000,0b0000000,0b0010000};
	DDRD=0xff;
	DDRC = 0xff;
	TCCR1B = (1<<CS10) | (1<<CS12); 
	OCR1A = 1562; 	   
	TCNT1 = 0;   
    while (1) 
    {
		//while((TIFR & (1<<OCF1A)) == 0);
		int i =0;
		//PORTC = 0b1000001;
		for(i=0;i<10;i++){
			PORTD=sevenseg[i];
			PORTD = 0b11011010;
			_delay_ms(10);
		}
		//TCNT1 = 0;
		//TIFR |= (1<<OCF1A) ;
		
		
		
    }
}

