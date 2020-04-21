#include "PCF8574.h"
#include "HardwareI2C.h"

void PCF8574_WRITE(unsigned char data)
{

    I2C_HARDWARE_WRITE_BYTE(PCF8574_actual_address,data);
}



