#define F_CPU 1000000UL
#define __DELAY_BACKWARD_COMPATIBLE__ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void ADC_Init()
{
	DDRA=0x00;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel)
{
	int Ain, AinLow;
	float Afloat;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
		
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and Multiply with weight */
	Afloat = Ain + AinLow;
	return (Afloat);
}

int main(void)
{
	int value1,value2;
	DDRC=0XFF;
	ADC_Init();
	
	while (1)
	{
		value1 =ADC_Read(0);  //direction
		value2 =ADC_Read(1);  
		value2 =300+3.61*value2 ;  // speed
		
		if (value1>500)
		{
			PORTC=0X03;
			_delay_us(value);
			PORTC=0X01;
			_delay_us(value);
		}
		else if(value2<500)
		{
			PORTC=0X02;
			_delay_us(value);
			PORTC=0X00;
			_delay_us(value);
		} 
	}
}


