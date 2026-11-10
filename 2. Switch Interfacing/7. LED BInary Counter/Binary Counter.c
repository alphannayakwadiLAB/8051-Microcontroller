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
    unsigned char count;

    while(1)
    {
        for(count = 0; count <= 255; count++)
        {
            P2 = count;
            delay();
        }
    }
}
