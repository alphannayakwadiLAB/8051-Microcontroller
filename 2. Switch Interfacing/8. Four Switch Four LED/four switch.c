#include <reg51.h>

sbit SW1 = P1^0;
sbit SW2 = P1^1;
sbit SW3 = P1^2;
sbit SW4 = P1^3;

sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;

void main()
{
    SW1 = 1;
    SW2 = 1;
    SW3 = 1;
    SW4 = 1;

    while(1)
    {
        if(SW1 == 0)
            LED1 = 1;
        else
            LED1 = 0;

        if(SW2 == 0)
            LED2 = 1;
        else
            LED2 = 0;

        if(SW3 == 0)
            LED3 = 1;
        else
            LED3 = 0;

        if(SW4 == 0)
            LED4 = 1;
        else
            LED4 = 0;
    }
}
