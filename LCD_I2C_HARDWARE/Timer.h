#include<msp430.h>
#ifndef TIMER_H_
#define TIMER_H_

void Timer_Start();
void Timer_Stop();
void Timer_Delay(unsigned int calculatedValue);


void Timer_Start_SMCLK();

void Timer_Delay_SMCLK(unsigned int calculatedValue );

#endif /* TIMER_H_ */
