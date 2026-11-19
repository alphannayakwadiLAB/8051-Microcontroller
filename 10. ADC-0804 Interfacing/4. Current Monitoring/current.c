
#include <reg51.h>

#define ADC_DATA P1

sbit ADC_RD   = P3^7;
sbit ADC_WR   = P3^6;
sbit ADC_INTR = P3^2;

unsigned char adc_value;
unsigned int timeout;
unsigned int current_dA;

void delay(void)
{
    unsigned int i;
    for(i = 0; i < 500; i++);
}

unsigned char ADC_Read(void)
{
    ADC_RD = 1;
    ADC_WR = 1;

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
        return 128;

    // Read ADC output
    ADC_RD = 0;
    delay();

    adc_value = ADC_DATA;

    ADC_RD = 1;

    return adc_value;
}

void main(void)
{
    ADC_DATA = 0xFF;

    ADC_RD = 1;
    ADC_WR = 1;

    P2 = 0;

    while(1)
    {
        adc_value = ADC_Read();

        // ACS712-5A:
        // 2.5V zero current
        // 185mV per ampere

        if(adc_value >= 128)
        {
            current_dA =
            ((unsigned int)(adc_value - 128) * 500) / 255;

            current_dA = (current_dA * 100) / 185;
        }
        else
        {
            current_dA =
            ((unsigned int)(128 - adc_value) * 500) / 255;

            current_dA = (current_dA * 100) / 185;
        }

        // Display current in 0.1A units
        P2 = current_dA;

        delay();
    }
}
