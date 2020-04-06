#include <LCD.h>
#include <msp430.h> 
#include"Timer.h"


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    LCD4bit_Init();

    LCD4bit_SendString("Hello");
    LCD4bit_Cursor_Position(1,4);
    LCD4bit_SendString("World");

    Timer_Delay(65535);             //~2sec
    LCD4bit_Clear();
    LCD4bit_Cursor_Off();

    Timer_Delay(65535);             //~2sec
    LCD4bit_SendString("Line 1");
    LCD4bit_Cursor_Position(1,4);
    LCD4bit_SendString("Line 2");



    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt

    return 0;
}



