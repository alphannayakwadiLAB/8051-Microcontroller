
#include <reg51.h>

sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit IN3 = P2^2;
sbit IN4 = P2^3;

sbit SPEED_UP = P1^0;
sbit SPEED_DOWN = P1^1;

unsigned int delay_count = 20;

void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < delay_count; i++)
    {
        for(j = 0; j < 1000; j++);
    }
}

void stepper_step(void)
{
    // Step 1
    IN1 = 1; IN2 = 0;
    IN3 = 1; IN4 = 0;
    delay();

    // Step 2
    IN1 = 0; IN2 = 1;
    IN3 = 1; IN4 = 0;
    delay();

    // Step 3
    IN1 = 0; IN2 = 1;
    IN3 = 0; IN4 = 1;
    delay();

    // Step 4
    IN1 = 1; IN2 = 0;
    IN3 = 0; IN4 = 1;
    delay();
}

void main(void)
{
    SPEED_UP = 1;
    SPEED_DOWN = 1;

    while(1)
    {
        if(SPEED_UP == 0)
        {
            if(delay_count > 5)
                delay_count -= 5;

            while(SPEED_UP == 0);
        }

        if(SPEED_DOWN == 0)
        {
            if(delay_count < 50)
                delay_count += 5;

            while(SPEED_DOWN == 0);
        }

        stepper_step();
    }
}
