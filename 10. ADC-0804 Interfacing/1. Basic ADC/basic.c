
#include <reg51.h>

#define ADC_DATA P1

sbit ADC_RD   = P3^7;
sbit ADC_WR   = P3^6;
sbit ADC_INTR = P3^2;

unsigned char adc_value;

void delay(void)
{
    unsigned int i;
    for(i = 0; i < 500; i++);
}

unsigned char ADC_Read(void)
{
    unsigned char value;

    ADC_RD = 1;
    ADC_WR = 1;

    // Start ADC conversion
    ADC_WR = 0;
    delay();
    ADC_WR = 1;

    // Wait until conversion completes
    while(ADC_INTR == 1);

    // Read digital output
    ADC_RD = 0;
    delay();

    value = ADC_DATA;

    ADC_RD = 1;

    return value;
}

void main(void)
{
    ADC_DATA = 0xFF;

    ADC_RD = 1;
    ADC_WR = 1;

    while(1)
    {
        adc_value = ADC_Read();

        P2 = adc_value;

        delay();
    }
}
