
#include <reg51.h>

#define ADC_DATA P1

sbit ADC_RD   = P3^7;
sbit ADC_WR   = P3^6;
sbit ADC_INTR = P3^2;

unsigned char adc_value;
unsigned char current_mA;

unsigned int timeout;

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
        return 0;

    // Read ADC value
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

        // Convert ADC value to current (mA)
        current_mA = ((unsigned int)adc_value * 20) / 255;

        // Limit display to 4-20mA range
        if(current_mA < 4)
            current_mA = 0;

        if(current_mA > 20)
            current_mA = 20;

        // Display current value on Port 2
        P2 = current_mA;

        delay();
    }
}
