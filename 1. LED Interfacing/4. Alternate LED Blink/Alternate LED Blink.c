#include <reg51.h>

void delay()
{
    unsigned int i;

    for(i = 0; i < 1000; i++);
}

void main()
{
    while(1)
    {
        P1 = 0x55;    // Alternate LEDs ON
        delay();

        P1 = 0xAA;    // Remaining LEDs ON
        delay();
    }
}
