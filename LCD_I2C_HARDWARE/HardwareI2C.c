/*
 *You don't need the read functions for controlling the lcd
 *I will add them later
 *
 */


#include"HardwareI2C.h"
#include <msp430.h>



void I2C_HARDWARE_INIT(){

    P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST+UCMODE_3+UCSYNC;         // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2+UCSWRST;              // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

}

void I2C_HARDWARE_SET_ADDRESS(unsigned char address){

    UCB0I2CSA = address;                         // Set slave address

}


void I2C_HARDWARE_START_WRITE(){

    while(UCB0CTL1 & UCTXSTP);                      // Ensure stop condition got sent
    UCB0CTL1 |= UCTXSTT | UCTR ;                    // I2C start condition transmitter mode

}

void I2C_HARDWARE_START_READ(){

    while(UCB0CTL1 & UCTXSTP);                // Ensure stop condition got sent
    UCB0CTL1 &= ~UCTR;                       // Receiver mode
    UCB0CTL1 |= UCTXSTT ;                    // I2C start condition transmission mode

}

void I2C_HARDWARE_SEND_DATA(unsigned char data){

    UCB0TXBUF = data;           //send data ( fill tx buffer)

}

void I2C_HARDWARE_STOP(){

    UCB0CTL1 |= UCTXSTP;
    IFG2 &= ~UCB0TXIFG;
}


unsigned char I2C_HARDWARE_CHECK_ACK(){

    while(!(IFG2 & UCB0TXIFG));         //wait until UCB0TXBUF is empty (finish transmitting data)
    if(UCB0STAT & UCNACKIFG)    return NACK;   // received NACK
    else                        return ACK;  // received ACK
}

unsigned char I2C_HARDWARE_WRITE_BYTE(unsigned char address,unsigned char data){

    I2C_HARDWARE_SET_ADDRESS(address);  //set I2C slave address

    I2C_HARDWARE_START_WRITE();         //send START condition in write mode

    if(I2C_HARDWARE_CHECK_ACK()==NACK) return NACK; //check if the slave acknowledged(if there is any slave with that address)

    I2C_HARDWARE_SEND_DATA(data);       //send data

    if(I2C_HARDWARE_CHECK_ACK()==NACK) return NACK; //check if the slave acknowledged

    I2C_HARDWARE_STOP();                //send STOP condition

    return ACK;                         // transmission finished successfully

}


unsigned char I2C_HARDWARE_WRITE_MULTIPLE_BYTES(unsigned char address, unsigned char *data )

{

    I2C_HARDWARE_SET_ADDRESS(address);//set I2C slave address

    I2C_HARDWARE_START_WRITE();//send START condition in write mode

    while(*data !='\0'){

        if(I2C_HARDWARE_CHECK_ACK()==NACK) return NACK;//check if the slave acknowledged/if there is any slave with that address

        I2C_HARDWARE_SEND_DATA(*data);//send data

        data++;
    }


    if(I2C_HARDWARE_CHECK_ACK()==NACK) return NACK; //check if the slave acknowledged/if there is any slave with that address

    I2C_HARDWARE_STOP();                    //send STOP condition

    return ACK;                         // transmission finished successfully

}

