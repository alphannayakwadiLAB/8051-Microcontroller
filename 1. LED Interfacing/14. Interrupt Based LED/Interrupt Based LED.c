
#include <reg51.h>

sbit LED = P1^0;

unsigned int count = 0;

void timer0_ISR(void) interrupt 1
{
    TH0 = 0x4C;
    TL0 = 0x00;

    count++;

    if(count >= 10)
    {
        LED = !LED;
        count = 0;
    }
}

void main()
{
    TMOD = 0x01;    // Timer 0, Mode 1

    TH0 = 0x4C;
    TL0 = 0x00;

    ET0 = 1;        // Enable Timer 0 interrupt
    EA = 1;         // Enable global interrupt

    TR0 = 1;        // Start Timer 0

    LED = 1;        // Initially OFF

    while(1)
    {
        // Main program does nothing
    }
}
