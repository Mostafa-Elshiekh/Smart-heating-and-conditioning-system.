#include <avr/io.h>
void ADC_init(void)
{
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);       //Enable ADC and Select Prescaler (8)
	ADMUX|=(1<<ADLAR);                                                    //8 bit mood (just ADCH) (left adjusted 
	ADMUX|=(1<<MUX0);                                                     // Select Channel 
	ADMUX|=(1<<REFS0)|(1<<REFS1);                              //reference voltage for ADC
}