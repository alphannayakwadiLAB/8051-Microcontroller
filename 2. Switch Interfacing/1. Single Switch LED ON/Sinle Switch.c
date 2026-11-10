#include <reg51.h>

sbit SW = P1^0;
sbit LED = P2^0;

void main()
{
    SW = 1;       // Configure switch as input

    while(1)
    {
        if(SW == 0)
        {
            LED = 1;  // LED ON
        }
        else
        {
            LED = 0;  // LED OFF
        }
    }
}
