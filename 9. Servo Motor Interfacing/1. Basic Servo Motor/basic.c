
#include <reg51.h>

sbit SERVO = P2^0;

// Timer 0 delay using 11.0592 MHz crystal
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

// Generate one 20 ms servo frame
void servo_position(unsigned int pulse)
{
    SERVO = 1;
    delay_us(pulse);

    SERVO = 0;
    delay_us(20000 - pulse);
}

// Hold a position
void servo_hold(unsigned int pulse)
{
    unsigned char i;

    for(i = 0; i < 50; i++)
    {
        servo_position(pulse);
    }
}

void main()
{
    TMOD = 0x01;    // Timer 0, Mode 1

    SERVO = 0;

    while(1)
    {
        // 0 Degree
        servo_hold(1000);

        // 90 Degree
        servo_hold(1500);

        // 180 Degree
        servo_hold(2000);
    }
}
