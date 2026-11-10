
#include <reg51.h>

sbit LED = P2^0;

void delay(unsigned int count)
{
    unsigned int i;

    for(i = 0; i < count; i++);
}

void pwm(unsigned char duty)
{
    LED = 1;
    delay(duty);

    LED = 0;
    delay(255 - duty);
}

void main()
{
    unsigned char brightness;

    while(1)
    {
        // Increase brightness
        for(brightness = 0; brightness < 255; brightness++)
        {
            pwm(brightness);
        }

        // Decrease brightness
        for(brightness = 255; brightness > 0; brightness--)
        {
            pwm(brightness);
        }
    }
}
