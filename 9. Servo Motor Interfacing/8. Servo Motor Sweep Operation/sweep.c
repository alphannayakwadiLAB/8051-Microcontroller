
#include <reg51.h>

sbit SERVO = P2^0;

// Timer 0 delay for 11.0592 MHz
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
void servo_position(unsigned int pulse)
{
    SERVO = 1;
    delay_us(pulse);

    SERVO = 0;
    delay_us(20000 - pulse);
}

// Hold position for some time
void servo_hold(unsigned int pulse)
{
    unsigned char i;

    for(i = 0; i < 10; i++)
    {
        servo_position(pulse);
    }
}

// Automatic sweep operation
void main()
{
    unsigned int angle;
    unsigned int pulse;

    TMOD = 0x01;   // Timer 0 Mode 1

    SERVO = 0;

    while(1)
    {
        // Clockwise: 0 to 180 degrees
        for(angle = 0; angle <= 180; angle += 5)
        {
            pulse = 1000 + (angle * 1000UL) / 180;

            servo_hold(pulse);
        }

        // Anticlockwise: 180 to 0 degrees
        for(angle = 180; angle >= 5; angle -= 5)
        {
            pulse = 1000 + (angle * 1000UL) / 180;

            servo_hold(pulse);
        }

        // Return to exactly 0 degrees
        servo_hold(1000);
    }
}
