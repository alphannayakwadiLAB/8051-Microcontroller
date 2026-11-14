
#include <reg51.h>

sbit MOTOR = P2^0;
sbit SW = P3^2;

void main()
{
    SW = 1;       // Configure switch input
    MOTOR = 0;    // Motor initially OFF

    while(1)
    {
        if(SW == 0)
        {
            MOTOR = 1;    // Motor ON
        }
        else
        {
            MOTOR = 0;    // Motor OFF
        }
    }
}
