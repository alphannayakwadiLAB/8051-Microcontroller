
#include <reg51.h>

sbit ADC_RD = P3^7;
sbit ADC_WR = P3^6;
sbit ADC_INTR = P3^2;

unsigned char adc_value;
unsigned int timeout;

void delay(void)
{
    unsigned int i;
    for(i=0; i<500; i++);
}

void main(void)
{
    P1 = 0xFF;
    P2 = 0x00;

    ADC_RD = 1;
    ADC_WR = 1;

    while(1)
    {
        // Start conversion
        ADC_WR = 0;
        delay();
        ADC_WR = 1;

        // Wait for conversion
        timeout = 60000;

        while(ADC_INTR == 1 && timeout > 0)
        {
            timeout--;
        }

        if(timeout == 0)
        {
            P2 = 0x00;
        }
        else
        {
            // Read ADC data
            ADC_RD = 0;
            delay();

            adc_value = P1;

            ADC_RD = 1;

            P2 = adc_value;
        }
    }
}
