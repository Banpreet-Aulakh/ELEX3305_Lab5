#include "msp.h"
#include "lab5.h"

#define SAMPLE_CHAN 9// chooses channel 9
/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	adcInterruptInit(SAMPLE_CHAN);
	adcSample();
	// set P4.4 to be used as an analog input
	P4->SEL0 |= BIT4;
	P4->SEL1 |= BIT4;

	__enable_interrupts();

while (1)
{
    adcSample();
}
}

