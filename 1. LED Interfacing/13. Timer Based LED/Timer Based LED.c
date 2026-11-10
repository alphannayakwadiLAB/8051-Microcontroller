
#include <reg51.h>

sbit LED = P1^0;

void timer0_delay()
{
    unsigned int i;

    for(i = 0; i < 10; i++)
    {
        TMOD = 0x01;   // Timer 0, Mode 1

        TH0 = 0x4C;
        TL0 = 0x00;    // Approximately 50 ms

        TR0 = 1;       // Start Timer 0

        while(TF0 == 0);

        TR0 = 0;       // Stop Timer 0
        TF0 = 0;       // Clear overflow flag
    }
}

void main()
{
    while(1)
    {
        LED = 0;       // LED ON
        timer0_delay();

        LED = 1;       // LED OFF
        timer0_delay();
    }
}
