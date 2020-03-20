
#include <msp430.h>
#include "UART0.h"

void initClock();


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

    initClock();
    UART0_Init();

    UART0_SendString_UnknownLenght("Aka45");
    UART0_SendChar('\n');
    UART0_SendInt(4621);


}

void initClock(){
    if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
    {
        while(1);                               // do not load, trap CPU!!
    }
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;
}
