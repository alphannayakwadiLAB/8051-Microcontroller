
#include <reg51.h>

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < 100; j++);
    }
}

void main()
{
    unsigned char value;

    while(1)
    {
        for(value = 0; value < 255; value++)
        {
            P1 = value;
            delay();
        }

        P1 = 128;
        delay();
    }
}
