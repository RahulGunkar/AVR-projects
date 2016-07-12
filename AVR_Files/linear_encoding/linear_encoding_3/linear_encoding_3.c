
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_128.h"

#define directionPin1	PA0
#define direcitonPin2	PA1
#define pwmPin			OCR1A
#define speedRatio		2
volatile int cw_flag = 0;
volatile int acw_flag = 0;
volatile int mileStone = 0;

void init()
{
	
	EICRB |= (1<<ISC50)|(1<<ISC51);     //rising edge causes an interrupt..for IR sensor
	EIMSK |= (1<<INT5) ;
	DDRD |=~ 0x03;
	//PWM initialization
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) | (1<<WGM11) ;
    TCCR1B |= (1<<CS10) | (1<< WGM13) | (1<<WGM12);
	ICR1 = 65535;
	DDRB = (1 << PB5);		//pwm pin 
	
	//direction pins for motor
	DDRA |=(1<<PA0)|(1<<PA1);
	
	//USART_Init(12, 1);
	USART_Init(12, 0);
}


void clockwise()
{
	PORTA |= 0x01;
	pwmPin = ICR1 / speedRatio;
	cw_flag = 1;
	acw_flag = 0;
}

void anticlockwise()
{
	PORTA  = 0x02;
	pwmPin = ICR1 / speedRatio;
	acw_flag = 1;
	cw_flag = 0;
}

void stop_motor()
{
	pwmPin = 0;
}

//position 1,2,3
void gotomilestone(int x)  {
	
	if(mileStone > x) {
		anticlockwise();
		if(mileStone == x) stop_motor();
	}
	
	else if (mileStone < x) {
		clockwise();
		if(mileStone == x) stop_motor();
		
	}
}

int main(void) {
	
	sei();
	init();
	//anticlockwise();
	clockwise();
	  //;gotomilestone(1);
    while(1)
    {
		
       USART_TransmitNumber(1,0);
    }
}


ISR(INT5_vect) {
	if(acw_flag)		 ++mileStone;
	else if(cw_flag)	 --mileStone;
	//USART_TransmitNumber(100,0);
}



