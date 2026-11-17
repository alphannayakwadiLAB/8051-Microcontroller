
#include <reg51.h>

sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit IN3 = P2^2;
sbit IN4 = P2^3;

void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 1000; j++);
    }
}

void main(void)
{
    while(1)
    {
        // Step 1
        IN1 = 1;
        IN2 = 0;
        IN3 = 0;
        IN4 = 1;
        delay();

        // Step 2
        IN1 = 0;
        IN2 = 1;
        IN3 = 0;
        IN4 = 1;
        delay();

        // Step 3
        IN1 = 0;
        IN2 = 1;
        IN3 = 1;
        IN4 = 0;
        delay();

        // Step 4
        IN1 = 1;
        IN2 = 0;
        IN3 = 1;
        IN4 = 0;
        delay();
    }
}
