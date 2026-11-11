
#include <reg51.h>

#define LCD P1

sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

sbit LED = P2^0;
sbit SW = P2^1;

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
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}

void main()
{
    lcd_init();

    while(1)
    {
        if(SW == 0)
        {
            LED = 1;

            lcd_cmd(0x80);
            lcd_string("LED STATUS:");

            lcd_cmd(0xC0);
            lcd_string("LED IS ON ");
        }
        else
        {
            LED = 0;

            lcd_cmd(0x80);
            lcd_string("LED STATUS:");

            lcd_cmd(0xC0);
            lcd_string("LED IS OFF");
        }
    }
}
