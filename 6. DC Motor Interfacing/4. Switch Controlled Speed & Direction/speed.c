
#include <reg51.h>

sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit EN  = P1^2;

sbit FWD  = P3^2;
sbit REV  = P3^3;
sbit INC  = P3^4;
sbit DEC  = P3^5;
sbit STOP = P3^6;

unsigned char speed = 50;
unsigned char direction = 0;

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
    FWD = 1;
    REV = 1;
    INC = 1;
    DEC = 1;
    STOP = 1;

    EN = 0;
    IN1 = 0;
    IN2 = 0;

    while(1)
    {
        if(FWD == 0)
        {
            delay(20);

            if(FWD == 0)
            {
                direction = 1;
                while(FWD == 0);
            }
        }

        if(REV == 0)
        {
            delay(20);

            if(REV == 0)
            {
                direction = 2;
                while(REV == 0);
            }
        }

        if(INC == 0)
        {
            delay(20);

            if(INC == 0)
            {
                if(speed <= 75)
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
            direction = 0;

            while(STOP == 0);
        }

        if(direction == 1 && speed > 0)
        {
            IN1 = 1;
            IN2 = 0;
        }
        else if(direction == 2 && speed > 0)
        {
            IN1 = 0;
            IN2 = 1;
        }
        else
        {
            IN1 = 0;
            IN2 = 0;
            EN = 0;
        }

        if(direction != 0 && speed > 0)
            pwm();
    }
}
