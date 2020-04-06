#include <msp430.h> 
#include"LCD8bit.h"
#include"Timer.h"

int main(void)
{


    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

     LCD8bit_Init();

     LCD8bit_SendString("Hello");
     LCD8bit_Cursor_Position(1,4);
     LCD8bit_SendString("World");

     Timer_Delay(65535);            //~2sec
     LCD8bit_Clear();
     LCD8bit_Cursor_Off();

     Timer_Delay(65535);            //~2sec
     LCD8bit_SendString("Line 1");
     LCD8bit_Cursor_Position(1,4);
     LCD8bit_SendString("Line 2");



     __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt


    return 0;
}


