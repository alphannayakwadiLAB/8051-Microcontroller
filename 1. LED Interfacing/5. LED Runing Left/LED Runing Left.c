
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
        for(i = 0; i < 8; i++)
        {
            P1 = ~(1 << i);  // LED ON
            delay();
        }
    }
}
