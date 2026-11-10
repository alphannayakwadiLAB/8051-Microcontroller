
#include <reg51.h>

sbit SW1 = P1^0;
sbit SW2 = P1^1;
sbit SW3 = P1^2;
sbit SW4 = P1^3;

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
    unsigned char i, count;

    P1 = 0xFF;
    P2 = 0x00;

    while(1)
    {
        if(SW1 == 0)
        {
            for(i = 0; i < 8; i++)
            {
                if(SW1 == 1) break;

                P2 = (1 << i);
                delay();
            }
        }

        else if(SW2 == 0)
        {
            for(i = 0; i < 8; i++)
            {
                if(SW2 == 1) break;

                P2 = (0x80 >> i);
                delay();
            }
        }

        else if(SW3 == 0)
        {
            P2 = 0xFF;
            delay();

            P2 = 0x00;
            delay();
        }

        else if(SW4 == 0)
        {
            for(count = 0; count < 255; count++)
            {
                if(SW4 == 1) break;

                P2 = count;
                delay();
            }
        }

        else
        {
            P2 = 0x00;
        }
    }
}
