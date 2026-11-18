
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

// Servo 180 degree control
void servo_180_degree(void)
{
    SERVO = 1;
    delay_us(2000);   // 2 ms HIGH

    SERVO = 0;
    delay_us(18000);  // 18 ms LOW
}

void main()
{
    TMOD = 0x01;      // Timer 0 Mode 1

    SERVO = 0;

    while(1)
    {
        servo_180_degree();
    }
}
