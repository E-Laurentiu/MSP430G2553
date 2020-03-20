/*
 *
 *AClk = 32.768 kHz
 *1 period= 2*(1/32768) ~ = 61.03515625 us
 *
 */

#include"Timer.h"

inline void Timer_Start(){
    CCTL0 = CCIE;
    TACTL = MC_1+TASSEL_1;         // ACLK, upmode
}

inline void Timer_Stop(){
    TACTL = MC_0;                  // MC_0 = STOP
}

void Timer_Delay(unsigned int calculatedValue ){
    //calculatedValue = delayWanted/61.03515625
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
