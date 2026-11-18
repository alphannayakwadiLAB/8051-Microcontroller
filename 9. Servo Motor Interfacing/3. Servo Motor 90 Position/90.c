
#include <reg51.h>

sbit SERVO = P2^0;

// Timer 0 delay function
void delay_us(unsigned int us)
{
    unsigned long count;
    unsigned int reload;

    count = ((unsigned long)us * 9216UL) / 10000UL;

    reload = 65536UL - count;

    TH0 = reload >> 8;
    TL0 = reload;

    TF0 = 0;
    TR0 = 1;

    while(TF0 == 0);

    TR0 = 0;
    TF0 = 0;
}

// Servo 90 degree control
void servo_90_degree(void)
{
    SERVO = 1;
    delay_us(1500);   // 1.5 ms HIGH

    SERVO = 0;
    delay_us(18500);  // 18.5 ms LOW
}

void main()
{
    TMOD = 0x01;      // Timer 0 Mode 1

    SERVO = 0;

    while(1)
    {
        servo_90_degree();
    }
}
