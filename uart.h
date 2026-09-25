/*
 * uart.h
 *
 * Created: 25-09-2026 23:50:11
 *  Author: nesminhashim
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void UART_Init(void);
void UART_SendChar(char data);
void UART_SendString(const char *str);
void UART_SendNumber(uint16_t number);

#endif
