
#include <reg51.h>

void main()
{
    P1 = 0xFF;  // Configure Port 1 as input
    P2 = 0x00;  // Initialize LEDs OFF

    while(1)
    {
        P2 = ~P1;  // Display DIP switch value
    }
}
