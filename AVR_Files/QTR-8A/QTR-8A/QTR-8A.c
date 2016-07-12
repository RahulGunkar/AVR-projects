/*
 * QTR_8A.c
 *
 * Created: 27-12-2015 16:11:50
 *  Author: Admin
 */ 


#include <avr/io.h>
#include "USART_128.h"

volatile uint8_t sensorData[8],i = 0,j=0;

void startADCconversion(void) {
	ADCSRA |= 1<<ADSC;
}

void clearMUX(void) {
		ADMUX &= ~(1<<MUX0);
		ADMUX &= ~(1<<MUX1);
		ADMUX &= ~(1<<MUX2);
		ADMUX &= ~(1<<MUX3);
		ADMUX &= ~(1<<MUX4);
}

void configure_ADC(void) {
	ADCSRA |= 1<<ADPS0 | 1<<ADPS1 | 1<<ADPS2;
	ADMUX |= 1<<REFS0 | 1<<ADLAR;
	ADCSRA |= 1<<ADEN;
	clearMUX();
}

void readSensor(void) {
	for(int j = 0;j<8;j++) {
		startADCconversion();
		while(!(ADCSRA & 1<<ADIF));
		sensorData[i] = ADCH;
		clearMUX();
		/*switch(i) {
			case 0:
			sensorData[0]= (sensorData[0]*50)/70;
			break;
			/case 1:
			sensorData[1] = (sensorData[1]*50)/40;
			break;
			case 2:
			sensorData[2] = (sensorData[2]*50)/40;
			break;
			case 3:
			sensorData[3] = (sensorData[3]*50)/40;
			break;
			case 4:
			sensorData[4] = (sensorData[4]*50)/40;
			break;
			case 5:
			sensorData[5] = (sensorData[5]*50)/40;
			case 6:
			sensorData[6] = (sensorData[6]*50)/40;
			break;
			case 7:
			sensorData[7] = (sensorData[7]*50)/40;
			break;
		}*/
	USART_TransmitNumber(sensorData[0],0);
	USART_Transmitchar(0x0d,0);

		if(i<8) {
			i++;
		}
		else {
			i =0;
		}
		ADMUX |= i;
	}
	
/*	for(int j = 0 ;j<8;j++) {
		if(sensorData[j]>100)
		{sensorData[j]=1;}
		else
		{sensorData[j]=0;}
			
		USART_TransmitNumber(sensorData[0],0);
		USART_Transmitchar(' ',0);
	} */
	
	USART_Transmitchar(0x0D,0);
	_delay_ms(1000);
}

int main(void)
{
	USART_Init(12,0);
    configure_ADC();
	while(1)
    {
		readSensor();
	}
}