
#include <reg51.h>

sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit EN  = P1^2;

sbit INC  = P3^2;
sbit DEC  = P3^3;
sbit STOP = P3^4;

unsigned char speed = 0;

void delay(unsigned int t)
{
    unsigned int i;

    while(t--)
    {
        for(i = 0; i < 10; i++);
    }
}

void pwm()
{
    unsigned char i;

    for(i = 0; i < 100; i++)
    {
        if(i < speed)
            EN = 1;
        else
            EN = 0;

        delay(1);
    }
}

void main()
{
    INC = 1;
    DEC = 1;
    STOP = 1;

    IN1 = 1;
    IN2 = 0;
    EN = 0;

    while(1)
    {
        if(INC == 0)
        {
            delay(20);

            if(INC == 0)
            {
                if(speed < 100)
                    speed += 25;

                while(INC == 0);
            }
        }

        if(DEC == 0)
        {
            delay(20);

            if(DEC == 0)
            {
                if(speed >= 25)
                    speed -= 25;

                while(DEC == 0);
            }
        }

        if(STOP == 0)
        {
            speed = 0;
            while(STOP == 0);
        }

        pwm();
    }
}
