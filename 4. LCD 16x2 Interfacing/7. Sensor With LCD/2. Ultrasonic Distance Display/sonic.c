
#include <reg51.h>
#include <intrins.h>

#define LCD P1

// LCD pins
sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

// HC-SR04 pins
sbit TRIG = P2^0;
sbit ECHO = P2^1;

unsigned int distance;
unsigned int count;

// Delay function
void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 123; j++);
    }
}

// LCD enable pulse
void lcd_enable()
{
    EN = 1;
    delay_ms(1);
    EN = 0;
}

// LCD command
void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS = 0;
    RW = 0;

    lcd_enable();
    delay_ms(2);
}

// LCD data
void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS = 1;
    RW = 0;

    lcd_enable();
    delay_ms(2);
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
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
}

// Display three digit number
void lcd_number(unsigned int num)
{
    lcd_data((num / 100) + '0');
    lcd_data(((num / 10) % 10) + '0');
    lcd_data((num % 10) + '0');
}

// Timer initialization
void timer_init()
{
    TMOD = 0x01;
}

// Generate approximately 10us trigger pulse
void ultrasonic_trigger()
{
    TRIG = 0;
    delay_ms(1);

    TRIG = 1;

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    TRIG = 0;
}

// Measure ultrasonic distance
unsigned int measure_distance()
{
    unsigned int timeout;

    ultrasonic_trigger();

    // Wait for Echo HIGH
    TR0 = 0;
    TH0 = 0;
    TL0 = 0;
    TF0 = 0;

    timeout = 0;

    while(ECHO == 0)
    {
        timeout++;

        if(timeout > 60000)
            return 0;
    }

    // Start timer
    TH0 = 0;
    TL0 = 0;
    TF0 = 0;
    TR0 = 1;

    // Wait for Echo LOW
    while(ECHO == 1)
    {
        if(TF0 == 1)
        {
            TR0 = 0;
            return 0;
        }
    }

    TR0 = 0;

    count = ((unsigned int)TH0 << 8) | TL0;

    // Distance calculation for 12MHz crystal
    distance = count / 58;

    return distance;
}

// Main function
void main()
{
    lcd_init();
    timer_init();

    TRIG = 0;
    ECHO = 1;

    while(1)
    {
        distance = measure_distance();

        lcd_cmd(0x80);
        lcd_string("Distance:");

        lcd_cmd(0xC0);

        if(distance == 0)
        {
            lcd_string("OUT OF RANGE   ");
        }
        else
        {
            lcd_number(distance);
            lcd_string(" CM     ");
        }

        delay_ms(300);
    }
}
