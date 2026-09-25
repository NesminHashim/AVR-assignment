/*
 * lcd.c
 *
 * Created: 25-09-2026 23:44:38
 *  Author: nesminhashim
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "lcd.h"
#include "delay.h"

/* LCD pin connections */
#define LCD_PORT PORTB
#define LCD_DDR  DDRB

#define RS PB0
#define EN PB1
#define D4 PB2
#define D5 PB3
#define D6 PB4
#define D7 PB5


/* Generate enable pulse */
static void LCD_EnablePulse(void)
{
    LCD_PORT |= (1 << EN);

    delay_ms(1);

    LCD_PORT &= ~(1 << EN);

    delay_ms(1);
}


/* Send 4 bits to LCD */
static void LCD_Send4Bits(uint8_t data)
{
    /* D4 */
    if (data & 0x01)
        LCD_PORT |= (1 << D4);
    else
        LCD_PORT &= ~(1 << D4);

    /* D5 */
    if (data & 0x02)
        LCD_PORT |= (1 << D5);
    else
        LCD_PORT &= ~(1 << D5);

    /* D6 */
    if (data & 0x04)
        LCD_PORT |= (1 << D6);
    else
        LCD_PORT &= ~(1 << D6);

    /* D7 */
    if (data & 0x08)
        LCD_PORT |= (1 << D7);
    else
        LCD_PORT &= ~(1 << D7);

    LCD_EnablePulse();
}


/* Send command to LCD */
void LCD_Command(uint8_t command)
{
    /* RS = 0 ? command mode */
    LCD_PORT &= ~(1 << RS);

    /* Send upper 4 bits */
    LCD_Send4Bits(command >> 4);

    /* Send lower 4 bits */
    LCD_Send4Bits(command & 0x0F);

    delay_ms(2);
}


/* Send character to LCD */
void LCD_Data(uint8_t data)
{
    /* RS = 1 ? data mode */
    LCD_PORT |= (1 << RS);

    /* Send upper 4 bits */
    LCD_Send4Bits(data >> 4);

    /* Send lower 4 bits */
    LCD_Send4Bits(data & 0x0F);

    delay_ms(2);
}


/* Initialize LCD */
void LCD_Init(void)
{
    /* Make LCD pins outputs */
    LCD_DDR |= (1 << RS) |
               (1 << EN) |
               (1 << D4) |
               (1 << D5) |
               (1 << D6) |
               (1 << D7);

    delay_ms(20);

    /* RS = 0 */
    LCD_PORT &= ~(1 << RS);

    /*
     * LCD initialization
     * Start in 8-bit mode temporarily
     */
    LCD_Send4Bits(0x03);
    delay_ms(5);

    LCD_Send4Bits(0x03);
    delay_ms(1);

    LCD_Send4Bits(0x03);
    delay_ms(1);

    /* Change to 4-bit mode */
    LCD_Send4Bits(0x02);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x01);
    LCD_Command(0x06);
}


void LCD_String(const char *str)
{
    while (*str)
    {
        LCD_Data(*str);
        str++;
    }
}

void LCD_Clear(void)
{
    LCD_Command(0x01);
    delay_ms(2);
}



void LCD_SetCursor(uint8_t row, uint8_t column)
{
    uint8_t address;

    if (row == 0)
    {
        address = 0x80 + column;
    }
    else
    {
        address = 0xC0 + column;
    }

    LCD_Command(address);
}

void LCD_SendNumber(uint16_t number)
{
    char buffer[6];
    uint8_t i = 0;

    if (number == 0)
    {
        LCD_Data('0');
        return;
    }

    while (number > 0)
    {
        buffer[i] = '0' + (number % 10);
        number = number / 10;
        i++;
    }

    while (i > 0)
    {
        i--;
        LCD_Data(buffer[i]);
    }
}