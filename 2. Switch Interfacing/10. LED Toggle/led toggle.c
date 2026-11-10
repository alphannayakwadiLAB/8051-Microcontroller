#include <reg51.h>

sbit LED = P2^0;

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < 1275; j++);
    }
}

void main()
{
    while(1)
    {
        LED = 1;    // LED ON
        delay();

        LED = 0;    // LED OFF
        delay();
    }
}
