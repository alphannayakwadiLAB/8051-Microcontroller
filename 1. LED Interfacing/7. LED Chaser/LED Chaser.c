
#include <reg51.h>

void delay()
{
    unsigned int i;

    for(i = 0; i < 1000; i++);
}

void main()
{
    unsigned char i;

    while(1)
    {
        // LED Chasing Left to Right
        for(i = 0; i < 8; i++)
        {
            P1 = ~(1 << i);
            delay();
        }

        // LED Chasing Right to Left
        for(i = 6; i > 0; i--)
        {
            P1 = ~(1 << i);
            delay();
        }
    }
}
