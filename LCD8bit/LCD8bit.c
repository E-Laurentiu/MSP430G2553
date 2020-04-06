/*
 *
 * I've let the delays a bit longer(you can shorten the delays and it would still work)
 * The ACK (external 32768 Hz crystal) can be unstable because of the enviroment
 *  so if you face problems use __delay_cycles(cycles) instead
 *                                                           (cycles = time in us)  if smclk~1MHz
 *__delays work only if mclk~1MHz
 */

#include"LCD8bit.h"
#include"Timer.h"


void LCD8bit_Init(){

    //configure used Pins(see LCD8bit.h for pin map)

    P1SEL  = 0x00;
    P1SEL2 = 0x00;
    P1DIR  = 0xFF;
    P1OUT  = 0x00;

    P2SEL  &= ~(0x07);
    P2SEL2 &= ~(0x07);
    P2DIR  |=   0x07;
    P2OUT  &= ~(0x07);

    //~0.5 sec delay ( lcd boots slower that microcontroller)
    Timer_Delay(16384);

    LCD8bit_Cmd(0x38);                      //8-bit 2line display 5x7 font
    LCD8bit_Cmd(0x06);                      //increment automatically
    LCD8bit_Cmd(0x0C);
    LCD8bit_Cmd(0x01);                      //clear display

}

void LCD8bit_Cmd(unsigned char command) {   //RS=0 -> send command
    P2OUT &= ~(0x07);                       //RS=0,RW=0,En=0
    P1OUT = command;                        //Write command

    //Pulse on En Pin to confirm command

    P2OUT |= 0x04;                          // En=1
    Timer_Delay(3);                         //~100us
    P2OUT &= ~(0x07);                       //En=0
    if(command<4)  Timer_Delay(50);         //~3000us (first commands require more time)
    else __delay_cycles(2);                 //~80us

}

void LCD8bit_Data(unsigned char data){      //RS=1 -> send data
    P2OUT &= ~(0x07);                       //RS=0,RW=0,nE=0
    P2OUT |= 0x01;                          //RS=1
    P1OUT = data;                           //Write data

    //Pulse on En Pin to confirm command

    P2OUT |= 0x04;                          // En=1
    Timer_Delay(3);                         //~100us
    P2OUT &= ~(0x07);                       //En=0
    Timer_Delay(3);                         //~100us


}


void LCD8bit_SendString(char *buff){
    while(*buff!='\0'){

        LCD8bit_Data(*buff);
        buff++;

    }
}


void LCD8bit_Cursor_Position(int row , int column){
    LCD8bit_Cmd(0x02);                     //return to position 0 ,0
    if(row==1) LCD8bit_Cmd(0xC0);          //Row 1

    while(column>0){
        LCD8bit_Cmd(0x14);                 //Shift right by 1
        column--;
    }

}




inline void LCD8bit_Clear(){
    LCD8bit_Cmd(0x01); // Clear Display
}

inline void LCD8bit_Cursor_Blink(){
    LCD8bit_Cmd(0x0F); // Blink cursor

}

inline void LCD8bit_Cursor_StopBlink(){
    LCD8bit_Cmd(0x0E); // Don't blink cursor

}

inline void LCD8bit_Cursor_On(){
    LCD8bit_Cmd(0x0E); // Cursor On

}

inline void LCD8bit_Cursor_Off(){
    LCD8bit_Cmd(0x0C); // Cursor Off

}


