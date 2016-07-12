/*
 * GccApplication3.c
 *
 * Created: 14-12-2015 16:22:36
 *  Author: rahulgunkar
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile int val=0;

void pwm(int a)
{
	
	if(a<= 1024 && a>=900)
	{
		OCR0A=200;
			
	}
	else if(a<900 && a>800)
	{
		OCR0A=180;
	}
	else if(a<700 && a>600)
	{
		OCR0A=150;
	}
	
	else if(a<600 && a>500)
	{
		OCR0A=130;
	}
	else if(a<500 && a>400)
	{
		OCR0A=100;
	}
	else if(a<400 && a>300)
	{
		OCR0A=80;
	}
	else if(a<300 && a>200)
	{
		OCR0A=50;
	}
	else
		OCR0A=30;
}	



void DELAY(int i)

{
	while(i--)
	{
		_delay_ms(1);
	}
}


ISR(ADC_vect)
{
	
	//uint8_t low=ADCL;
	val =ADC;
	ADCSRA|=(1<<ADSC);
	
}



void init_pwm_adc()
{
	DDRB |=1<<PINB0;
	DDRB&=~(1<<PINB5);
	sei();
	TCCR0A |=1<<COM0A1 |1<<WGM01|1<<WGM00;
	TCCR0B |=1<<CS00;
	//ADMUX |=~(1<<REFS0);
	ADCSRA |=1<<ADEN | 1<<ADIE |1<<ADPS0;
	
	ADCSRA |=1<<ADSC;
    
	
	for (int i=0;i<10;i++)
	{
		OCR0A=i*20;
		DELAY(2000);
	}
	
}



int main(void)
{
	init_pwm_adc();
	while(1)
    {
		pwm(val);    
    }
}


	
	
	
	
	
