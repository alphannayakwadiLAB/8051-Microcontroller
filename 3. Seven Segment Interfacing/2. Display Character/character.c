
#include <reg51.h>

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 500; i++)
    {
        for(j = 0; j < 1275; j++);
    }
}

void main()
{
    while(1)
    {
        P2 = 0x77;   // A
        delay();

        P2 = 0x38;   // L
        delay();

        P2 = 0x73;   // P (approximation)
        delay();

        P2 = 0x76;   // H
        delay();

        P2 = 0x77;   // A
        delay();

        P2 = 0x54;   // n (approximation)
        delay();
    }
}
