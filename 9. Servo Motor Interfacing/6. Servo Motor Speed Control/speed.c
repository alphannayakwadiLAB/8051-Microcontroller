
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

// Servo PWM signal
void servo_position(unsigned int pulse)
{
    SERVO = 1;
    delay_us(pulse);

    SERVO = 0;
    delay_us(20000 - pulse);
}

// Move servo gradually
void servo_move(unsigned int start,
                unsigned int end,
                unsigned int step_delay)
{
    unsigned int angle;
    unsigned int pulse;
    unsigned char i;

    if(start < end)
    {
        for(angle = start; angle <= end; angle++)
        {
            pulse = 1000 + (angle * 1000UL) / 180;

            for(i = 0; i < step_delay; i++)
            {
                servo_position(pulse);
            }
        }
    }
    else
    {
        for(angle = start; angle >= end; angle--)
        {
            pulse = 1000 + (angle * 1000UL) / 180;

            for(i = 0; i < step_delay; i++)
            {
                servo_position(pulse);
            }
        }
    }
}

void main()
{
    TMOD = 0x01;

    SERVO = 0;

    while(1)
    {
        // Clockwise movement
        servo_move(0, 180, 2);

        // Anticlockwise movement
        servo_move(180, 0, 2);
    }
}
