/*
 * uart.c
 *
 * Created: 25-09-2026 23:51:08
 *  Author: nesminhashim
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "uart.h"

#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void UART_Init(void)
{
    
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) |
             (1 << UCSZ00);
}

void UART_SendChar(char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = data;
}

void UART_SendString(const char *str)
{
    while (*str)
    {
        UART_SendChar(*str);
        str++;
    }
}

void UART_SendNumber(uint16_t number)
{
    char buffer[6];
    uint8_t i = 0;

    if (number == 0)
    {
        UART_SendChar('0');
        return;
    }

    while (number > 0)
    {
        buffer[i++] = '0' + (number % 10);
        number /= 10;
    }

    while (i > 0)
    {
        UART_SendChar(buffer[--i]);
    }
}