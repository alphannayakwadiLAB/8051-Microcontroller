
#include <reg51.h>

sbit EMERGENCY = P3^2;
sbit RESET_BTN = P1^0;

sbit BUZZER = P2^0;
sbit LED = P2^1;

bit alarm_status = 0;

// External Interrupt 0 Service Routine
void external0_ISR(void) interrupt 0
{
    alarm_status = 1;
}

void main()
{
    EMERGENCY = 1;
    RESET_BTN = 1;

    BUZZER = 0;
    LED = 0;

    IT0 = 1;    // Falling edge triggered interrupt
    EX0 = 1;    // Enable external interrupt 0
    EA = 1;     // Enable global interrupt

    while(1)
    {
        if(RESET_BTN == 0)
        {
            alarm_status = 0;
        }

        if(alarm_status == 1)
        {
            BUZZER = 1;
            LED = 1;
        }
        else
        {
            BUZZER = 0;
            LED = 0;
        }
    }
}
