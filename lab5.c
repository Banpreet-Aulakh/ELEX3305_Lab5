
#include "msp.h"
#include "lab5.h"


    void adcInit(int channel)
    {

        ADC14->CTL0 = ADC14_CTL0_ON; // turning on the ADC and ensure ADC14ENC = 0

        // Use ADC module clock, single channel, single conversion, 32 cycle sample time,
        ADC14->CTL0 = ADC14_CTL0_ON | ADC14_CTL0_SHP | ADC14_CTL0_SHT0__32;

        // use 10-bit resolution and set result address to ADC14MEM0
        ADC14->CTL1 = ADC14_CTL1_RES__14BIT;

        // select input channel to sample and use Vcc and Vss as reference voltages
        ADC14->MCTL[0] = channel;
        ADC14->CTL0 |= ADC14_CTL0_ENC;

    }

    int adcSample()
        {
        volatile int result; // store ADC result
        ADC14->CTL0 |= ADC14_CTL0_ENC;

        while ((ADC14->IFGR0 & ADC14_IFGR0_IFG0) == 0) {}

        result = ADC14->MEM[0];

        return(result);
        }
  void adcInterruptInit(unsigned int channel)
  {
     ADC14->IER0 |= ADC14_IER0_IE0;
      NVIC_EnableIRQ(ADC14_IRQn);
    ADC14->CTL0 |= ADC14_CTL0_SC;
  }

  void ADC14_IRQHandler(void)
  {
      volatile int result; // store ADC result

          result = ADC14->MEM[0];

          ADC14->CTL0 |= ADC14_CTL0_SC;
  }
