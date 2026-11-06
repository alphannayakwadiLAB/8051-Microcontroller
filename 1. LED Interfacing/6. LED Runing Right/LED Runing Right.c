#include <reg51.h>

void delay()
{
    unsigned int i;

    for(i = 0; i < 1000; i++);
}

void main()
{
    signed char i;

    while(1)
    {
        for(i = 7; i >= 0; i--)
        {
            P1 = ~(1 << i);  // LED ON
            delay();
        }
    }
}
