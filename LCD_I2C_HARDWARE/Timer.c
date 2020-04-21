/*
 *
 *AClk = 32.768 kHz (External crystal)
 *1 period=(1/32768) ~ = 30.517578125 us
 *
 *SMClk = ~1Mhz
 *We use SMCLK/ 8 = ~ 125Khz
 *1 period = ~ 8 us
 *
 */

#include"Timer.h"


void Timer_Start_SMCLK(){
    CCTL0 = CCIE;
    TACTL = MC_1+TASSEL_2+ID_3;         // SMCLK/8 ~= 125KHz , upmode

}

void Timer_Delay_SMCLK(unsigned int calculatedValue ){
    //calculatedValue = delayWanted/8    (delayWanted = [us])
    //max(calculatedValue) = 2^16 = 65536

    CCR0 = calculatedValue-1;
    Timer_Start_SMCLK();
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt (CPU->OFF)
    Timer_Stop();

}




inline void Timer_Start(){
    CCTL0 = CCIE;
    TACTL = MC_1+TASSEL_1;         // ACLK, upmode
}

inline void Timer_Stop(){
    TACTL = MC_0;                  // MC_0 = STOP
}

void Timer_Delay(unsigned int calculatedValue ){
    //calculatedValue = delayWanted/30.517578125    (delayWanted = [us])
    //max(calculatedValue) = 2^16 = 65536

    CCR0 = calculatedValue-1;
    Timer_Start();
    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt (CPU->OFF)
    Timer_Stop();

}


// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{

    __bic_SR_register_on_exit(LPM3_bits);   //Exit LPM3 (CPU->ON)

}
