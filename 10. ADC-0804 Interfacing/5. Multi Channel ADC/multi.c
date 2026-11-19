
#include <reg51.h>

#define ADC_DATA P1

sbit ADD_A = P3^0;
sbit ADD_B = P3^1;
sbit ADD_C = P3^2;

sbit ALE   = P3^3;
sbit START = P3^4;
sbit EOC   = P3^5;
sbit OE    = P3^6;

unsigned char adc_value;
unsigned char channel;

void delay(void)
{
    unsigned int i;
    for(i = 0; i < 1000; i++);
}

unsigned char ADC_Read(unsigned char ch)
{
    // Select ADC channel
    ADD_A = ch & 0x01;
    ADD_B = (ch >> 1) & 0x01;
    ADD_C = (ch >> 2) & 0x01;

    // Latch address
    ALE = 1;
    START = 1;
    delay();

    ALE = 0;
    START = 0;

    // Start conversion
    START = 1;
    delay();
    START = 0;

    // Wait for conversion to complete
    while(EOC == 1);
    while(EOC == 0);

    // Read ADC data
    OE = 1;
    delay();

    adc_value = ADC_DATA;

    OE = 0;

    return adc_value;
}

void main(void)
{
    ADC_DATA = 0xFF;

    ALE = 0;
    START = 0;
    OE = 0;

    P2 = 0x00;

    while(1)
    {
        for(channel = 0; channel < 8; channel++)
        {
            adc_value = ADC_Read(channel);

            P2 = adc_value;

            delay();
        }
    }
}
