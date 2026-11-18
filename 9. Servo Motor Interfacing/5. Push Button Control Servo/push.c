
#include <reg51.h>

sbit SERVO = P2^0;

sbit BUTTON_0   = P1^0;
sbit BUTTON_90  = P1^1;
sbit BUTTON_180 = P1^2;

// Timer 0 delay for 11.0592 MHz
void delay_us(unsigned int us)
{
    unsigned long count;
    unsigned int reload;

    count = ((unsigned long)us * 9216UL) / 10000UL;

    reload = 65536UL - count;

    TH0 = reload >> 8;
    TL0 = reload;

    TF0 = 0;
    TR0 = 1;

    while(TF0 == 0);

    TR0 = 0;
    TF0 = 0;
}

// Generate one servo signal frame
void servo_position(unsigned int pulse)
{
    SERVO = 1;
    delay_us(pulse);

    SERVO = 0;
    delay_us(20000 - pulse);
}

// Hold selected position
void servo_hold(unsigned int pulse)
{
    unsigned char i;

    for(i = 0; i < 5; i++)
    {
        servo_position(pulse);
    }
}

void main()
{
    TMOD = 0x01;   // Timer 0 Mode 1

    SERVO = 0;

    BUTTON_0 = 1;
    BUTTON_90 = 1;
    BUTTON_180 = 1;

    while(1)
    {
        if(BUTTON_0 == 0)
        {
            delay_us(20000); // Debounce

            if(BUTTON_0 == 0)
                servo_hold(1000);
        }

        else if(BUTTON_90 == 0)
        {
            delay_us(20000);

            if(BUTTON_90 == 0)
                servo_hold(1500);
        }

        else if(BUTTON_180 == 0)
        {
            delay_us(20000);

            if(BUTTON_180 == 0)
                servo_hold(2000);
        }
    }
}
