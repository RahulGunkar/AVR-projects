


#define F_CPU 8000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include "USART_128.h"

volatile long tickcount = 0;

ISR(INT7_vect){
	tickcount++;

	}
	
	
	
ISR(INT6_vect)
{
	tickcount--;
}


	
void interrupt_config()
{
	DDRF |=(1<<PF0) | (1<<PF1); //extra vcc and ground
	PORTF &=~(1<<PF0);
	PORTF |= (1<<PF1);
	EIMSK |= (1<<INT7)|(1<<INT6);
	EICRB |= (1<<ISC70)|(1<<ISC60);
}	



	int main(void)
{
	interrupt_config();
	USART_Init(51,0);
	USART_Init(51,1);
	
	while(1)
	{
		_delay_ms(1000);
		USART_TransmitNumber(tickcount,0);
		USART_Transmitchar(0x0d,0);
	
    }
}





