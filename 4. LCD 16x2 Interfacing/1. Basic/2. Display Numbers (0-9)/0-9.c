
#include <reg51.h>

#define LCD P1

sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

void delay()
{
    int i, j;
    for(i = 0; i < 100; i++)
        for(j = 0; j < 1275; j++);
}

void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    delay();
    EN = 0;
}

void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS = 1;
    RW = 0;
    EN = 1;
    delay();
    EN = 0;
}

void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x80);
}

void main()
{
    unsigned char i;

    lcd_init();

    for(i = '0'; i <= '9'; i++)
    {
        lcd_data(i);
        delay();
    }

    while(1);
}
