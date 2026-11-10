
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
        P2 = 0x3F;  // 0
        delay();

        P2 = 0x06;  // 1
        delay();

        P2 = 0x5B;  // 2
        delay();

        P2 = 0x4F;  // 3
        delay();

        P2 = 0x66;  // 4
        delay();

        P2 = 0x6D;  // 5
        delay();

        P2 = 0x7D;  // 6
        delay();

        P2 = 0x07;  // 7
        delay();

        P2 = 0x7F;  // 8
        delay();

        P2 = 0x6F;  // 9
        delay();
    }
}
