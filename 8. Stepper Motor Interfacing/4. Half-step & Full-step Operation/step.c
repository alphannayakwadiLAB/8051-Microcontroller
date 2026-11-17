
#include <reg51.h>

#define MOTOR P2

sbit FULL_STEP = P1^0;
sbit HALF_STEP = P1^1;

void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 1200; j++);
    }
}

// Full-step operation: 4 states
void full_step(void)
{
    unsigned char full[4] =
    {
        0x05,
        0x06,
        0x0A,
        0x09
    };

    unsigned char i;

    for(i = 0; i < 4; i++)
    {
        MOTOR = (MOTOR & 0xF0) | full[i];
        delay();
    }
}

// Half-step operation: 8 states
void half_step(void)
{
    unsigned char half[8] =
    {
        0x05,
        0x04,
        0x06,
        0x02,
        0x0A,
        0x08,
        0x09,
        0x01
    };

    unsigned char i;

    for(i = 0; i < 8; i++)
    {
        MOTOR = (MOTOR & 0xF0) | half[i];
        delay();
    }
}

void main(void)
{
    MOTOR = 0x00;

    FULL_STEP = 1;
    HALF_STEP = 1;

    while(1)
    {
        if(FULL_STEP == 0)
        {
            while(FULL_STEP == 0);

            while(1)
            {
                if(HALF_STEP == 0)
                    break;

                full_step();
            }
        }

        if(HALF_STEP == 0)
        {
            while(HALF_STEP == 0);

            while(1)
            {
                if(FULL_STEP == 0)
                    break;

                half_step();
            }
        }
    }
}
