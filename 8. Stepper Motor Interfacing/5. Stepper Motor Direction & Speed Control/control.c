#include <reg51.h>

#define MOTOR P2

sbit CW       = P1^0;
sbit CCW      = P1^1;
sbit SPEED_UP = P1^2;
sbit SPEED_DN = P1^3;

unsigned int delay_count = 20;

void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < delay_count; i++)
    {
        for(j = 0; j < 1000; j++);
    }
}

void clockwise(void)
{
    unsigned char seq[4] =
    {
        0x05, 0x06, 0x0A, 0x09
    };

    unsigned char i;

    for(i = 0; i < 4; i++)
    {
        MOTOR = (MOTOR & 0xF0) | seq[i];
        delay();
    }
}

void anticlockwise(void)
{
    unsigned char seq[4] =
    {
        0x09, 0x0A, 0x06, 0x05
    };

    unsigned char i;

    for(i = 0; i < 4; i++)
    {
        MOTOR = (MOTOR & 0xF0) | seq[i];
        delay();
    }
}

void main(void)
{
    CW = 1;
    CCW = 1;
    SPEED_UP = 1;
    SPEED_DN = 1;

    MOTOR = 0x00;

    while(1)
    {
        if(SPEED_UP == 0)
        {
            if(delay_count > 5)
                delay_count -= 5;

            while(SPEED_UP == 0);
        }

        if(SPEED_DN == 0)
        {
            if(delay_count < 50)
                delay_count += 5;

            while(SPEED_DN == 0);
        }

        if(CW == 0)
        {
            while(CW == 0);
            clockwise();
        }
        else if(CCW == 0)
        {
            while(CCW == 0);
            anticlockwise();
        }
    }
}
