
#include<msp430.h>

#ifndef SOFTWAREI2C_H_
#define SOFTWAREI2C_H_

#define ACK  0x00
#define NACK 0xFF

#define SDA BIT7
#define SCL BIT6

#define I2C_IN  P1IN
#define I2C_OUT P1OUT

#define SDA_DIR_OUT P1DIR |= SDA
#define SDA_DIR_IN  P1DIR &= ~SDA

#define SCL_DIR_OUT P1DIR |= SCL

#define SDA_LOW P1OUT &= ~SDA
#define SCL_LOW P1OUT &= ~SCL

#define SDA_HIGH P1OUT |= SDA
#define SCL_HIGH P1OUT |= SCL



//functions

void I2C_SOFTWARE_INIT();

void I2C_SOFTWARE_START();

void I2C_SOFTWARE_STOP();

char I2C_SOFTWARE_WAIT_ACK();

void I2C_SOFTWARE_WRITE(int data , int readOrWrite);

char I2C_SOFTWARE_WRITE_SEQUENCE(int address , int data);

unsigned char I2C_SOFTWARE_READ(unsigned char ackOrNack);

void I2C_SOFTWARE_SEND_ACK_NACK(unsigned char ackOrNack);


#endif /* SOFTWAREI2C_H_ */
