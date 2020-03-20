/*
 *__delays work only if mclk~1Mhz
 */

#include <LCD.h>
#include"Timer.h"

void LCD4bit_Init(){

    //configure used Pins(see LCD.h for pin map)

    P1SEL  &= ~(0x08);
    P1SEL2 &= ~(0x08);
    P1DIR  |=   0xF7;
    P1OUT  &= ~(0x08);

    //~1 sec delay ( lcd boots slower that microcontroller)
    Timer_Delay(16384);

    LCD4bit_Cmd(0x02);         // Initialize Lcd in 4-bit mode
    LCD4bit_Cmd(0x28);         // enable 5x7 mode for chars
    LCD4bit_Cmd(0x0E);         // Display OFF, Cursor ON
    LCD4bit_Cmd(0x01);         // Clear Display
    LCD4bit_Cmd(0x80);         // Move the cursor to beginning of first line
    LCD4bit_Cmd(0x06);         // cursor increment
    LCD4bit_Cmd(0x01);         //clear display
    LCD4bit_Cmd(0x0F);         //turn on display without cursor (0x0F)->blinking cursor

    //on my display it won't work at powerup without these commands
    LCD4bit_Cmd(0x01);
    LCD4bit_Cmd(0x80);
    LCD4bit_Cmd(0x01);

}

void LCD4bit_Write_data_control(unsigned char data , unsigned char control){
    data &= 0xF0;           //get higher bits
    control &= 0x0F;        //get lower bits
    P1OUT = data + control ;
    P1OUT &= ~EN;
    Timer_Delay(4);         //~200us delay

    //Pulse on En Pin to confirm command
    P1OUT |= EN;
    Timer_Delay(4);         //~200us delay
    P1OUT &= ~EN;
    Timer_Delay(4);         //~200us delay

    P1OUT = data;

}

void LCD4bit_Cmd(unsigned char command){               //RS=0 -> send command

    LCD4bit_Write_data_control(command&(0xF0), 0);     //upper 4 bits   RS=0(command register)
    LCD4bit_Write_data_control(command<<4, 0);         //lower 4 bits RS=0(command register)

    if(command<4){                                      // first commands require more time
        Timer_Delay(40);                                //~2000us delay

    }
    else     __delay_cycles(40);                        //~40us  at 1MHz Mclk
}

void LCD4bit_Data(unsigned char data){                 //RS=1 -> send data

    LCD4bit_Write_data_control(data&(0xF0), 1);        //upper 4 bits  RS=1(data register)
    LCD4bit_Write_data_control(data<<4, 1);            //lower 4 bits  RS=1(data register)
    __delay_cycles(40);                                 //~40us  at 1MHz Mclk
}

void LCD4bit_SendString(char *buff){
    while(*buff!='\0'){

        LCD4bit_Data(*buff);
        buff++;

    }
}


void LCD4bit_Cursor_Position(int row , int column){
    LCD4bit_Cmd(0x02);                     //return to position 0 ,0
    if(row==1) LCD4bit_Cmd(0xC0);          //Row 1

    while(column>0){
        LCD4bit_Cmd(0x14);                 //Shift right by 1
        column--;
    }

}




inline void LCD4bit_Clear(){
    LCD4bit_Cmd(0x01); // Clear Display
}

inline void LCD4bit_Cursor_Blink(){
    LCD4bit_Cmd(0x0F); // Blink cursor

}

inline void LCD4bit_Cursor_StopBlink(){
    LCD4bit_Cmd(0x0E); // Don't blink cursor

}

inline void LCD4bit_Cursor_On(){
    LCD4bit_Cmd(0x0E); // Cursor On

}

inline void LCD4bit_Cursor_Off(){
    LCD4bit_Cmd(0x0C); // Cursor Off

}



