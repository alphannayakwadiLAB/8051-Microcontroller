
#include <reg51.h>

#define LCD P1
#define ADC_DATA P0

sbit RS_PIN = P3^0;
sbit RW_PIN = P3^1;
sbit EN_PIN = P3^2;

sbit ADC_RD = P3^3;
sbit ADC_WR = P3^4;
sbit ADC_INTR = P3^5;
sbit ADC_CS = P3^6;

unsigned char temperature;

void delay()
{
    unsigned int i, j;

    for(i = 0; i < 100; i++)
        for(j = 0; j < 1275; j++);
}

void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS_PIN = 0;
    RW_PIN = 0;
    EN_PIN = 1;
    delay();
    EN_PIN = 0;
}

void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS_PIN = 1;
    RW_PIN = 0;
    EN_PIN = 1;
    delay();
    EN_PIN = 0;
}

void lcd_string(unsigned char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    delay();
}

unsigned char adc_read()
{
    unsigned char value;

    ADC_DATA = 0xFF;

    ADC_CS = 0;
    ADC_RD = 1;
    ADC_WR = 1;

    ADC_WR = 0;
    delay();
    ADC_WR = 1;

    while(ADC_INTR == 1);

    ADC_RD = 0;
    value = ADC_DATA;
    ADC_RD = 1;

    ADC_CS = 1;

    return value;
}

void lcd_number(unsigned char num)
{
    lcd_data((num / 100) + '0');
    lcd_data(((num / 10) % 10) + '0');
    lcd_data((num % 10) + '0');
}

void main()
{
    lcd_init();

    ADC_CS = 1;
    ADC_RD = 1;
    ADC_WR = 1;

    while(1)
    {
        temperature = adc_read();

        lcd_cmd(0x80);
        lcd_string("TEMPERATURE:");

        lcd_cmd(0xC0);
        lcd_string("TEMP: ");

        lcd_number(temperature);
        lcd_string(" C   ");

        delay();
    }
}
