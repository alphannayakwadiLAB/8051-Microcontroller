
#include <reg51.h>

#define MOTOR P2

sbit ANGLE_90  = P1^0;
sbit ANGLE_180 = P1^1;
sbit ANGLE_360 = P1^2;

#define STEPS_90  50
#define STEPS_180 100
#define STEPS_360 200

void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 1200; j++);
    }
}

void rotate_clockwise(unsigned int steps)
{
    unsigned int i;

    unsigned char seq[4] =
    {
        0x05, 0x06, 0x0A, 0x09
    };

    for(i = 0; i < steps; i++)
    {
        MOTOR = (MOTOR & 0xF0) | seq[i % 4];
        delay();
    }

    MOTOR = MOTOR & 0xF0;
}

void main(void)
{
    ANGLE_90 = 1;
    ANGLE_180 = 1;
    ANGLE_360 = 1;

    MOTOR = 0x00;

    while(1)
    {
        if(ANGLE_90 == 0)
        {
            while(ANGLE_90 == 0);

            rotate_clockwise(STEPS_90);
        }

        if(ANGLE_180 == 0)
        {
            while(ANGLE_180 == 0);

            rotate_clockwise(STEPS_180);
        }

        if(ANGLE_360 == 0)
        {
            while(ANGLE_360 == 0);

            rotate_clockwise(STEPS_360);
        }
    }
}
