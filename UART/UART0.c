/*
 * UART0.c
 *
 *  Created on: Jan 19, 2020
 *      Author: E.Laurentiu
 */

#include <msp430.h>
#include <stdio.h>
#include "UART0.h"

char _buff[20]={0};


void UART0_Init(){
    P1SEL |= BIT1+BIT2; //init UART0 pins (P1.1RX & P1.2TX)
    P1SEL2|= BIT1+BIT2;
    UCA0CTL1 |= UCSWRST; //uart reset enable(configuration mode)
    UCA0CTL1 |= UCSSEL_2; //SMCLK ~1MHZ
    UCA0BR0 = 9; //1mhz/9=115200
    UCA0BR1 = 0; // baudrate = freq/(br0+256*br1);
    UCA0MCTL |= UCBRS_1 + UCBRF_0; // Modulation UCBRSx=1, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST; //uart reset disable(exit configuration mode)
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
    __bis_SR_register(GIE);                   // Interrupts enabled

}


void UART0_SendChar(char data){
    while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
    UCA0TXBUF = data;

}


void UART0_SendString_KnownLenght(char *buff,char length)
{
    int i;
    for(i=0;i<length;i++,buff++)
    {
        while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
        UCA0TXBUF = *buff;
    }
}

void UART0_SendString_UnknownLenght(char *buff)
{

    while(*buff != '\0'){
        while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
        UCA0TXBUF = *buff;
        buff++;
    }

}

char UART0_ReadChar(){
    //    while(!(UCA1IFG&UCRXIFG));
    return UCA0RXBUF;

}


void UART0_SendInt(int data){
    if(data>=0){
        int i,j=0;
        int lastdigit ;
        char string[10];

        while(data!=0){
            lastdigit=data%10;
            data=data/10;
            string[i]=lastdigit;
            i++;
        }
        i--;
        for(j=0;i!=-1;j++,i--){
            UART0_SendChar(string[i]+'0');
        }


    }
}

void UART0_SendFloat(float data)
{
    int n;
    n=sprintf (_buff, "%.2f\n\r", data);
    UART0_SendString_KnownLenght(_buff,n);
}






// Echo back RXed character, confirm TX buffer is ready first
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= BIT0;
    while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}
