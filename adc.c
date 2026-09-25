/*
 * adc.c
 *
 * Created: 25-09-2026 23:39:31
 *  Author: hisan
 */ 
#include <avr/io.h>
#include "adc.h"

void ADC_Init(void)
{
   
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel)
{
    
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
    }
    return ADC;
}