
#include <reg51.h>

sbit M1_IN1 = P1^0;
sbit M1_IN2 = P1^1;

sbit M2_IN1 = P1^2;
sbit M2_IN2 = P1^3;

sbit M1_EN = P1^4;
sbit M2_EN = P1^5;

sbit SW1 = P3^2;
sbit SW2 = P3^3;

void delay()
{
    unsigned int i;

    for(i = 0; i < 1000; i++);
}

void main()
{
    SW1 = 1;
    SW2 = 1;

    M1_EN = 0;
    M2_EN = 0;

    M1_IN1 = 0;
    M1_IN2 = 0;

    M2_IN1 = 0;
    M2_IN2 = 0;

    while(1)
    {
        // Motor 1 independent control
        if(SW1 == 0)
        {
            M1_IN1 = 1;
            M1_IN2 = 0;
            M1_EN = 1;
        }
        else
        {
            M1_EN = 0;
            M1_IN1 = 0;
            M1_IN2 = 0;
        }

        // Motor 2 independent control
        if(SW2 == 0)
        {
            M2_IN1 = 1;
            M2_IN2 = 0;
            M2_EN = 1;
        }
        else
        {
            M2_EN = 0;
            M2_IN1 = 0;
            M2_IN2 = 0;
        }
    }
}
