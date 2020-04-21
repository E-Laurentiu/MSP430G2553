#include <msp430.h>
#include <LCD.h>
#include"Timer.h"
#include"PCF8574.h"

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
   __delay_cycles(500000);
    I2C_HARDWARE_INIT();

    LCD4bit_Init();

    LCD4bit_SendString("Hello");
    LCD4bit_Cursor_Position(1,4);
    LCD4bit_SendString("World");

    Timer_Delay_SMCLK(65535);             //~1.2sec delay
    LCD4bit_Clear();
    LCD4bit_Cursor_Off();
    Timer_Delay_SMCLK(65535);             //~1.2sec delay

    LCD4bit_SendString("Line 1");
    LCD4bit_Cursor_Position(1,4);
    LCD4bit_SendString("Line 2");

    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt (CPU->OFF)


    return 0;

}
