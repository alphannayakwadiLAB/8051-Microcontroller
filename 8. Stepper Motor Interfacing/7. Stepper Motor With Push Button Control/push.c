
#include <reg51.h>

#define MOTOR P2

sbit CW    = P1^0;
sbit CCW   = P1^1;
sbit STOP  = P1^2;
sbit SPEED = P1^3;

unsigned int delay_count = 20;
unsigned char direction = 0;

void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < delay_count; i++)
    {
        for(j = 0; j < 1000; j++);
    }
}

void step_motor(void)
{
    unsigned char seq_cw[4] =
    {
        0x05, 0x06, 0x0A, 0x09
    };

    unsigned char seq_ccw[4] =
    {
        0x09, 0x0A, 0x06, 0x05
    };

    unsigned char i;

    for(i = 0; i < 4; i++)
    {
        if(STOP == 0)
            return;

        if(direction == 1)
            MOTOR = (MOTOR & 0xF0) | seq_cw[i];
        else
            MOTOR = (MOTOR & 0xF0) | seq_ccw[i];

        delay();
    }
}

void main(void)
{
    CW = 1;
    CCW = 1;
    STOP = 1;
    SPEED = 1;

    MOTOR = 0x00;

    while(1)
    {
        if(CW == 0)
        {
            direction = 1;
            while(CW == 0);
        }

        if(CCW == 0)
        {
            direction = 2;
            while(CCW == 0);
        }

        if(SPEED == 0)
        {
            if(delay_count > 5)
                delay_count -= 5;
            else
                delay_count = 30;

            while(SPEED == 0);
        }

        if(STOP == 0)
        {
            direction = 0;
            MOTOR = 0x00;

            while(STOP == 0);
        }

        if(direction != 0)
        {
            step_motor();
        }
    }
}
