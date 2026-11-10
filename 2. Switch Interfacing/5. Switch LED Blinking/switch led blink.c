#include <reg51.h>

sbit SW = P1^0;
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
    SW = 1;
    LED = 0;

    while(1)
    {
        if(SW == 0)
        {
            LED = 1;
            delay();

            LED = 0;
            delay();
        }
        else
        {
            LED = 0;
        }
    }
}
