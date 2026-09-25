/*
 * delay.c
 *
 * Created: 25-09-2026 23:48:33
 *  Author: nesminhashim
 */ 
#define F_CPU 16000000UL

#include <util/delay.h>
#include "delay.h"

void delay_ms(uint16_t milliseconds)
{
	while (milliseconds--)
	{
		_delay_ms(1);
	}
}