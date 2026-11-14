
#include <reg51.h>

sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit EN  = P1^2;

sbit START = P3^2;
sbit STOP  = P3^3;

unsigned char speed = 0;
unsigned char target = 100;

void delay(unsigned int t)
{
    unsigned int i, j;

    for(i = 0; i < t; i++)
        for(j = 0; j < 120; j++);
}

void pwm(unsigned char duty)
{
    unsigned char i;

    for(i = 0; i < 100; i++)
    {
        if(i < duty)
            EN = 1;
        else
            EN = 0;

        delay(1);
    }
}

void soft_start()
{
    while(speed < target)
    {
        speed += 5;

        if(speed > target)
            speed = target;

        pwm(speed);
        delay(100);
    }
}

void soft_stop()
{
    while(speed > 0)
    {
        if(speed >= 5)
            speed -= 5;
        else
            speed = 0;

        pwm(speed);
        delay(100);
    }

    EN = 0;
}

void main()
{
    START = 1;
    STOP = 1;

    IN1 = 1;
    IN2 = 0;
    EN = 0;

    while(1)
    {
        if(START == 0 && speed == 0)
        {
            delay(20);

            if(START == 0)
            {
                soft_start();

                while(START == 0);
            }
        }

        if(STOP == 0 && speed > 0)
        {
            delay(20);

            if(STOP == 0)
            {
                soft_stop();

                while(STOP == 0);
            }
        }
    }
}
