/*
 * ADC.C
 *
 * Created: 10/29/2022 2:04:28 PM
 *  Author: Afifi
 */ 

#include "ADC.h"


void ADC_init()
{	
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel)
{
	CLR_BIT(DDRA,channel);
	ADMUX = ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		    /* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	
	return((int)ADCL & (int)ADCH*256);			/* Return digital value*/
}
