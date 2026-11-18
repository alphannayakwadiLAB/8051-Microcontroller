
#include <reg51.h>

sbit SERVO = P2^0;

// Generate delay using Timer 0
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

// Generate servo signal
void servo_0_degree(void)
{
    SERVO = 1;
    delay_us(1000);   // 1 ms pulse

    SERVO = 0;
    delay_us(19000);  // 19 ms low
}

void main()
{
    TMOD = 0x01;      // Timer 0 Mode 1

    SERVO = 0;

    while(1)
    {
        servo_0_degree();
    }
}
