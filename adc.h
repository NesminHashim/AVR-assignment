/*
 * adc.h
 *
 * Created: 25-09-2026 23:38:05
 *  Author: nesminhashim
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

#endif