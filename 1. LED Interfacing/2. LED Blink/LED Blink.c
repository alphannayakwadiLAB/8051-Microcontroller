#include <reg51.h>

sbit LED = P1^0;

void delay()
{
    unsigned int i;

    for(i = 0; i < 1000; i++);
}

void main()
{
    while(1)
    {
        LED = 0;    // LED ON
        delay();

        LED = 1;    // LED OFF
        delay();
    }
}
