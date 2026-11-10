
#include <reg51.h>

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
    unsigned char count = 0;

    while(1)
    {
        P1 = ~count;       // Display LED pattern
        delay();

        count = (count << 1) | (~(count >> 7) & 0x01);
    }
}
