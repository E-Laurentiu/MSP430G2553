/*
 *You don't need the read functions for controlling the lcd
 *I will add them later
 *
 */
#include<msp430.h>
#ifndef HARDWAREI2C_H_
#define HARDWAREI2C_H_

#define ACK 0x00
#define NACK 0xFF


void I2C_HARDWARE_INIT();
void I2C_HARDWARE_SET_ADDRESS(unsigned char address);

void I2C_HARDWARE_START_WRITE();
void I2C_HARDWARE_START_READ();
void I2C_SOFTWARE_STOP();

void I2C_HARDWARE_SEND_DATA(unsigned char data);

unsigned char I2C_HARDWARE_WRITE_BYTE(unsigned char address,unsigned char data);
unsigned char I2C_HARDWARE_WRITE_MULTIPLE_BYTES(unsigned char address, unsigned char *data );




#endif /* HARDWAREI2C_H_ */
