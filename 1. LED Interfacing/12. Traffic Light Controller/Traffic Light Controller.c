
#include <reg51.h>

sbit RED    = P1^0;
sbit YELLOW = P1^1;
sbit GREEN  = P1^2;

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 1000; i++)
    {
        for(j = 0; j < 1275; j++);
    }
}

void main()
{
    while(1)
    {
        // RED LIGHT ON
        RED = 1;
        YELLOW = 0;
        GREEN = 0;
        delay();

        // YELLOW LIGHT ON
        RED = 0;
        YELLOW = 1;
        GREEN = 0;
        delay();

        // GREEN LIGHT ON
        RED = 0;
        YELLOW = 0;
        GREEN = 1;
        delay();
    }
}
