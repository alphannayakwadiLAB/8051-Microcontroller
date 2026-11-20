#include <reg51.h>

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 50; i++)
    {
        for(j = 0; j < 50; j++);
    }
}

void main()
{
    unsigned int value;

    while(1)
    {
        for(value = 0; value <= 255; value++)
        {
            P1 = value;
            delay();
        }

        // Reset DAC output
        P1 = 0x00;
        delay();
    }
}
