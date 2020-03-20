/*
 * Library for LCD 16x2 8bit mode
 *
 * LCD pins
 *
 * RS = P2.0
 * RW = P2.1
 * EN  = P2.2
 *
 * D0 = P1.0
 * D1 = P1.1
 * ...
 * D7 = P1.7
 *
 */
#include<msp430.h>
#ifndef LCD8BIT_H_
#define LCD8BIT_H_


void LCD8bit_Init(void);
void LCD8bit_Cmd(unsigned char command);
void LCD8bit_Data(unsigned char data);
void LCD8bit_SendString(char *buff);
void LCD8bit_Cursor_Position(int row , int column);
inline void LCD8bit_Clear();
inline void LCD8bit_Cursor_Blink();
inline void LCD8bit_Cursor_StopBlink();
inline void LCD8bit_Cursor_On();
inline void LCD8bit_Cursor_Off();


#endif /* LCD8BIT_H_ */
