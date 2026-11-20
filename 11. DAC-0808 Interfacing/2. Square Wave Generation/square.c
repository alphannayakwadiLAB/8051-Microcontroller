#include <reg51.h>

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < 100; j++);
    }
}

void main()
{
    while(1)
    {
        // HIGH level
        P1 = 0xFF;
        delay();

        // LOW level
        P1 = 0x00;
        delay();
    }
}
