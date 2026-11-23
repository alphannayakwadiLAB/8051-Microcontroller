#include <reg51.h>

sbit mot1p = P1^0;
sbit mot1n = P1^1;
sbit mot2p = P1^2;
sbit mot2n = P1^3;

// Motor control switches
sbit sw1 = P2^0;  // Forward
sbit sw2 = P2^1;  // Reverse
sbit sw3 = P2^2;  // Left
sbit sw4 = P2^3;  // Right
sbit sw5 = P2^4;  // Stop

void main()
{
    // Motor outputs OFF
    mot1p = 0;
    mot1n = 0;
    mot2p = 0;
    mot2n = 0;

    // Configure switches as inputs
    P2 = 0xFF;

    while(1)
    {
        if(sw5 == 0)       // STOP
        {
            mot1p = mot1n = 0;
            mot2p = mot2n = 0;
        }

        else if(sw1 == 0)  // FORWARD
        {
            mot1p = 1;
            mot1n = 0;
            mot2p = 1;
            mot2n = 0;
        }

        else if(sw2 == 0)  // REVERSE
        {
            mot1p = 0;
            mot1n = 1;
            mot2p = 0;
            mot2n = 1;
        }

        else if(sw3 == 0)  // LEFT
        {
            mot1p = 0;
            mot1n = 1;
            mot2p = 1;
            mot2n = 0;
        }

        else if(sw4 == 0)  // RIGHT
        {
            mot1p = 1;
            mot1n = 0;
            mot2p = 0;
            mot2n = 1;
        }

        else                // No switch pressed
        {
            mot1p = mot1n = 0;
            mot2p = mot2n = 0;
        }
    }
}