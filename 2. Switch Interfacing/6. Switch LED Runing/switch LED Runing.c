#include <reg51.h>

sbit SW = P1^0;

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
    unsigned char i;

    SW = 1;
    P2 = 0x00;

    while(1)
    {
        if(SW == 0)
        {
            for(i = 0; i < 8; i++)
            {
                if(SW == 1)
                    break;

                P2 = (1 << i);

                delay();
            }
        }
        else
        {
            P2 = 0x00;
        }
    }
}
