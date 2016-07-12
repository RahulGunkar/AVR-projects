/* 
		for 0 degree, pulse width required is 0.55ms  ; for 90 degree, pulse width of 1.55ms and for 180 degree, pulse width of 2.4ms is required
		which gives OCR values as 550,1500,2400 for 0,90,180 degree respectively...90 degree-= minus 0 degree gives 1500-550=950/90=10.55(OCR), per degree
		which implies 10.55*45=475(OCR) for 45 degree 
		
*/
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART_128.h"
volatile int m;





void init_pwm()
{
	DDRB = 0xFF;
	DDRC = 0xFF;
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) | (1<<WGM11) ;
	TCCR1B |= (1<<CS11) | (1<< WGM13) | (1<<WGM12);			//non inverting mode,prescaler 8
	ICR1 = 19999;
}


ISR(USART0_RX_vect)
{
	m=USART_Receive(0);
	USART_TransmitNumber(m,0);
	USART_Transmitchar(0x0d,0);
}


void move_to_angle(int m)
{
	    OCR1A=m*(10.55)+550;
}


int main(void) {
	
		init_pwm();
		while (1) 
		{
		move_to_angle(105);
			
		delay(1000);
	    }
}
 -
