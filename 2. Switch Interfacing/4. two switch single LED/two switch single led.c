#include <reg51.h>

sbit SW1 = P1^0;
sbit SW2 = P1^1;
sbit LED = P2^0;

void main()
{
    SW1 = 1;
    SW2 = 1;

    while(1)
    {
        if((SW1 == 0) || (SW2 == 0))
        {
            LED = 1;    // LED ON
        }
        else
        {
            LED = 0;    // LED OFF
        }
    }
}
