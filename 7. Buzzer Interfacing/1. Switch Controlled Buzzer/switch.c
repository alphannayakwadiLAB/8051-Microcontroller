
#include <reg51.h>

sbit SW = P1^0;
sbit BUZZER = P2^0;

void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
        for(j = 0; j < 123; j++);
}

void main()
{
    SW = 1;
    BUZZER = 0;

    while(1)
    {
        if(SW == 0)
        {
            delay_ms(20);

            if(SW == 0)
            {
                BUZZER = 1;
            }
        }
        else
        {
            BUZZER = 0;
        }
    }
}
