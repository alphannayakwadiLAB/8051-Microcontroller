
#include <reg51.h>

sbit TEMP_FAULT = P1^0;
sbit VOLT_FAULT = P1^1;
sbit EMERGENCY  = P1^2;

sbit BUZZER = P2^0;

void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 123; j++);
    }
}

void main()
{
    TEMP_FAULT = 1;
    VOLT_FAULT = 1;
    EMERGENCY = 1;

    BUZZER = 0;

    while(1)
    {
        if((TEMP_FAULT == 0) ||
           (VOLT_FAULT == 0) ||
           (EMERGENCY == 0))
        {
            BUZZER = 1;  // Alarm ON
        }
        else
        {
            BUZZER = 0;  // Alarm OFF
        }

        delay_ms(50);
    }
}
