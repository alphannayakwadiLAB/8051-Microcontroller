#include <reg51.h>

sbit BUZZER = P2^0;

// Timer 0 delay of approximately 1 ms
void timer0_delay(void)
{
    unsigned int i;

    for(i = 0; i < 1000; i++)
    {
        TMOD = 0x01;   // Timer 0, Mode 1

        TH0 = 0xFC;
        TL0 = 0x66;    // Approximately 1 ms

        TF0 = 0;
        TR0 = 1;

        while(TF0 == 0);

        TR0 = 0;
        TF0 = 0;
    }
}

void delay_seconds(unsigned int sec)
{
    unsigned int i;

    for(i = 0; i < sec; i++)
    {
        timer0_delay();
    }
}

void main()
{
    BUZZER = 0;

    while(1)
    {
        BUZZER = 0;       // Buzzer OFF
        delay_seconds(5); // Wait 5 seconds

        BUZZER = 1;       // Buzzer ON
        delay_seconds(2); // Alarm for 2 seconds
    }
}
