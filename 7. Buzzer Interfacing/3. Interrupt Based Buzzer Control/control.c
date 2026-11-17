
#include <reg51.h>

sbit BUZZER = P2^0;

unsigned int count = 0;
bit buzzer_state = 0;

// Timer 0 Interrupt Service Routine
void timer0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x66;      // Approximately 1 ms

    count++;

    if(count >= 1000)
    {
        count = 0;

        buzzer_state = !buzzer_state;

        if(buzzer_state == 1)
        {
            BUZZER = 1;  // Buzzer ON
        }
        else
        {
            BUZZER = 0;  // Buzzer OFF
        }
    }
}

void main()
{
    BUZZER = 0;

    TMOD = 0x01;     // Timer 0 Mode 1

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1;         // Enable Timer 0 interrupt
    EA = 1;          // Enable global interrupt

    TR0 = 1;         // Start Timer 0

    while(1)
    {
        // Main program runs independently
    }
}
