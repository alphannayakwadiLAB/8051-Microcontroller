
#include <reg51.h>

#define ENCODER_PPR 20
#define TARGET_RPM 600

sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit EN  = P1^2;

sbit ENCODER = P3^2;

volatile unsigned int pulse_count = 0;
volatile unsigned int sample_ticks = 0;

volatile bit sample_ready = 0;

volatile unsigned char duty = 8;
unsigned int actual_rpm = 0;

unsigned char pwm_phase = 0;

// External Interrupt 0 - Encoder
void external0_ISR(void) interrupt 0
{
    pulse_count++;
}

// Timer0 Interrupt
void timer0_ISR(void) interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0x1A;

    // Software PWM
    if(pwm_phase < duty)
        EN = 1;
    else
        EN = 0;

    pwm_phase++;

    if(pwm_phase >= 20)
        pwm_phase = 0;

    // Speed measurement interval
    sample_ticks++;

    if(sample_ticks >= 400)
    {
        sample_ticks = 0;
        sample_ready = 1;
    }
}

void main()
{
    unsigned int pulses;

    // Motor forward direction
    IN1 = 1;
    IN2 = 0;

    // Encoder input
    ENCODER = 1;

    // Initial PWM duty cycle
    duty = 8;

    // Timer0 mode 1
    TMOD = (TMOD & 0xF0) | 0x01;

    TH0 = 0xFF;
    TL0 = 0x1A;

    // External Interrupt 0
    IT0 = 1;
    EX0 = 1;

    // Timer0 Interrupt
    ET0 = 1;

    EA = 1;
    TR0 = 1;

    while(1)
    {
        if(sample_ready == 1)
        {
            // Read encoder pulses safely
            EA = 0;

            sample_ready = 0;

            pulses = pulse_count;
            pulse_count = 0;

            EA = 1;

            // Calculate RPM
            actual_rpm =
                ((unsigned long)pulses * 600UL)
                / ENCODER_PPR;

            // Speed control
            if(actual_rpm + 15 < TARGET_RPM)
            {
                if(duty < 20)
                    duty++;
            }
            else if(actual_rpm > TARGET_RPM + 15)
            {
                if(duty > 0)
                    duty--;
            }
        }
    }
}
