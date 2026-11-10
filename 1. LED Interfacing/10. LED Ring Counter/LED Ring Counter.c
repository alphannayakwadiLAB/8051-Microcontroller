
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
    unsigned char pattern = 0x01;

    while(1)
    {
        P1 = ~pattern;   // Display LED pattern
        delay();

        pattern = pattern << 1;

        if(pattern == 0x00)
        {
            pattern = 0x01;
        }
    }
}
