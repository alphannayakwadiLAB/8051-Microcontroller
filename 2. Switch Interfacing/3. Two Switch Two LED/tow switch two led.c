
#include <reg51.h>

sbit SW1 = P1^0;
sbit SW2 = P1^1;

sbit LED1 = P2^0;
sbit LED2 = P2^1;

void main()
{
    SW1 = 1;
    SW2 = 1;

    while(1)
    {
        if(SW1 == 0)
        {
            LED1 = 1;   // LED1 ON
        }
        else
        {
            LED1 = 0;   // LED1 OFF
        }

        if(SW2 == 0)
        {
            LED2 = 1;   // LED2 ON
        }
        else
        {
            LED2 = 0;   // LED2 OFF
        }
    }
}
