
#include <reg51.h>

sbit SERVO1 = P2^0;
sbit SERVO2 = P2^1;

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

// Control two servos
void servo_control(unsigned int pulse1,
                   unsigned int pulse2)
{
    // Both servos ON
    SERVO1 = 1;
    SERVO2 = 1;

    // Servo 1 pulse
    delay_us(pulse1);
    SERVO1 = 0;

    // Servo 2 pulse remaining
    if(pulse2 > pulse1)
        delay_us(pulse2 - pulse1);

    SERVO2 = 0;

    // Complete 20ms frame
    if(pulse1 > pulse2)
        delay_us(pulse1 - pulse2);

    delay_us(20000 - (pulse1 > pulse2 ?
                      pulse1 : pulse2));
}

void main()
{
    TMOD = 0x01;

    SERVO1 = 0;
    SERVO2 = 0;

    while(1)
    {
        // Servo 1 = 0°, Servo 2 = 90°
        servo_control(1000, 1500);

        // Servo 1 = 90°, Servo 2 = 180°
        servo_control(1500, 2000);

        // Servo 1 = 180°, Servo 2 = 0°
        servo_control(2000, 1000);
    }
}
