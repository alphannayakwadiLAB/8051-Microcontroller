#include <reg51.h>

sbit SW = P1^0;
sbit LED = P2^0;

void delay()
{
    unsigned int i;
    for(i = 0; i < 3000; i++);
}

void main()
{
    bit led_state = 0;

    SW = 1;
    LED = 0;

    while(1)
    {
        if(SW == 0)
        {
            delay();          // Debouncing

            if(SW == 0)
            {
                led_state = !led_state;
                LED = led_state;

                while(SW == 0);  // Wait for release
                delay();
            }
        }
    }
}
