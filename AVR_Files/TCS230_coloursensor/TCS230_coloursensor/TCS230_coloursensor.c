#include <avr/io.h>
#define F_CPU 8000000UL

#include <util/delay.h>
#include "USART_128.h"
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

uint32_t TCSMeasure()
{
	//If the function is entered when the level on OUT line was low
	//Then wait for it to become high.
	if(bit_is_clear(PINA,PA1))
	{
		while(bit_is_clear(PINA,PA1));   //Wait for rising edge
	}


	while(bit_is_set(PINA,PA1));   //Wait for falling edge

	TCNT1=0x0000;//Reset Counter

	TCCR1B=(1<<CS10); //Prescaler = F_CPU/1 (Start Counting)

	while(bit_is_clear(PINA,PA1));   //Wait for rising edge

	//Stop Timer
	TCCR1B=0x00;

	return ((float)4000000UL/TCNT1);

}

colour_config()
{
	DDRC =0xFF;  //for extra vcc
	PORTC=0x0F;
	DDRA|=(1<<PA0);
	//	DDRD|=(1<<PD0);
	DDRA&=~(1<<PA1);
	//DDRA|=(1<<PA0);
	USART_Init(12,0);
	//USART_TransmitNumber(11);
	PORTA|=(1<<PA0);
	//PORTD|=(1<<PDO);
	
}


int main(void)
{
	colour_config();
	
	
	while(1)
	{
		
		uint32_t r;

		_delay_ms(10);
		r=TCSMeasure();
		
		_delay_ms(10);
		r+=TCSMeasure();

		_delay_ms(10);
		r+=TCSMeasure();
		
		USART_TransmitNumber(((float)r/3.3),0);
		USART_Transmitchar(0x0D,0);
		_delay_ms(200);
		//New_Line(0);
		
		// 		 if(((float)r/3.3) > 3300 && ((float)r/3.3) <3400)
		// 		 {
		// 			 //PORTA|=(1<<PA7);
		// 			 USART_TransmitString("achieved");
		// 		 }
		//
	}

}