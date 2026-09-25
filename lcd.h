/*
 * lcd.h
 *
 * Created: 25-09-2026 23:42:41
 *  Author: nesminhashim
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

void LCD_Init(void);
void LCD_Command(uint8_t command);
void LCD_Data(uint8_t data);
void LCD_String(const char *str);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t column);
void LCD_SendNumber(uint16_t number);

#endif
