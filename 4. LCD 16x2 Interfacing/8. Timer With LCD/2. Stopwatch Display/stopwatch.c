
#include <reg51.h>

#define LCD P1

// LCD connections
sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

// Push button connections (active LOW)
sbit START = P2^0;
sbit STOP  = P2^1;
sbit RESET = P2^2;

// Stopwatch variables
unsigned char hours = 0;
unsigned char minutes = 0;
unsigned char seconds = 0;

unsigned int tick = 0;
bit running = 0;

// Delay function
void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 123; j++);
    }
}

// LCD enable
void lcd_enable()
{
    EN = 1;
    delay_ms(1);
    EN = 0;
    delay_ms(1);
}

// LCD command
void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS = 0;
    RW = 0;
    lcd_enable();

    if(cmd == 0x01 || cmd == 0x02)
        delay_ms(2);
}

// LCD data
void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS = 1;
    RW = 0;
    lcd_enable();
}

// LCD string
void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

// LCD initialization
void lcd_init()
{
    delay_ms(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
}

// Display two digits
void display_number(unsigned char num)
{
    lcd_data((num / 10) + '0');
    lcd_data((num % 10) + '0');
}

// Timer 0 interrupt
void timer0_ISR(void) interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x18;

    if(running)
    {
        tick++;

        if(tick >= 1000)
        {
            tick = 0;

            seconds++;

            if(seconds >= 60)
            {
                seconds = 0;
                minutes++;

                if(minutes >= 60)
                {
                    minutes = 0;
                    hours++;

                    if(hours >= 100)
                        hours = 0;
                }
            }
        }
    }
}

// Timer initialization
void timer_init()
{
    TMOD = 0x01;

    TH0 = 0xFC;
    TL0 = 0x18;

    TF0 = 0;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

// Display stopwatch
void display_stopwatch()
{
    lcd_cmd(0xC0);

    display_number(hours);
    lcd_data(':');

    display_number(minutes);
    lcd_data(':');

    display_number(seconds);

    lcd_string("   ");
}

// Main function
void main()
{
    START = 1;
    STOP = 1;
    RESET = 1;

    lcd_init();
    timer_init();

    lcd_cmd(0x80);
    lcd_string("STOPWATCH");

    while(1)
    {
        if(START == 0)
        {
            delay_ms(30);

            if(START == 0)
                running = 1;

            while(START == 0);
        }

        if(STOP == 0)
        {
            delay_ms(30);

            if(STOP == 0)
                running = 0;

            while(STOP == 0);
        }

        if(RESET == 0)
        {
            delay_ms(30);

            if(RESET == 0)
            {
                running = 0;

                EA = 0;
                hours = 0;
                minutes = 0;
                seconds = 0;
                tick = 0;
                EA = 1;
            }

            while(RESET == 0);
        }

        display_stopwatch();
    }
}
