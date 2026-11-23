
#include <reg51.h>

#define LCD P2

// LCD control pins
sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

// ADC0804 control pins
sbit ADC_INTR = P3^3;
sbit ADC_WR   = P3^6;
sbit ADC_RD   = P3^7;

// Function declarations
void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_string(unsigned char *);
void lcd_number(unsigned int);
unsigned char ADC_Read(void);

unsigned char adc_value;
unsigned int temperature;

void main()
{
    lcd_init();

    P1 = 0xFF;

    ADC_RD = 1;
    ADC_WR = 1;

    lcd_cmd(0x80);
    lcd_string("TEMPERATURE");

    lcd_cmd(0xC0);
    lcd_string("MONITOR SYSTEM");

    delay(50000);

    while(1)
    {
        // Read ADC value
        adc_value = ADC_Read();

        // Convert ADC value into temperature
        temperature = ((unsigned int)adc_value * 500) / 256;

        // Display temperature
        lcd_cmd(0x80);
        lcd_string("TEMP MONITOR   ");

        lcd_cmd(0xC0);
        lcd_string("TEMP: ");

        lcd_number(temperature);

        lcd_data(0xDF);
        lcd_data('C');

        lcd_string("    ");

        delay(30000);
    }
}

// ADC0804 reading function
unsigned char ADC_Read(void)
{
    unsigned char value;

    P1 = 0xFF;

    ADC_RD = 1;
    ADC_WR = 1;

    // Start conversion
    ADC_WR = 0;
    delay(10);
    ADC_WR = 1;

    // Wait for conversion complete
    while(ADC_INTR == 1);

    // Read ADC output
    ADC_RD = 0;
    delay(10);

    value = P1;

    ADC_RD = 1;

    return value;
}

// LCD initialization
void lcd_init(void)
{
    delay(50000);

    RW = 0;

    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x80);
}

// LCD command
void lcd_cmd(unsigned char cmd)
{
    RS = 0;
    RW = 0;

    LCD = cmd;

    EN = 1;
    delay(500);
    EN = 0;

    delay(5000);
}

// LCD data
void lcd_data(unsigned char dat)
{
    RS = 1;
    RW = 0;

    LCD = dat;

    EN = 1;
    delay(500);
    EN = 0;

    delay(5000);
}

// LCD string
void lcd_string(unsigned char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

// Display decimal number
void lcd_number(unsigned int num)
{
    lcd_data((num / 100) + '0');
    lcd_data(((num / 10) % 10) + '0');
    lcd_data((num % 10) + '0');
}

// Delay
void delay(unsigned int t)
{
    unsigned int i;

    for(i = 0; i < t; i++);
}
