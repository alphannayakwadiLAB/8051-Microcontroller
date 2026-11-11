
#include <reg51.h>

#define LCD P1

sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

unsigned char character1[8] =
{
    0x04,
    0x0E,
    0x15,
    0x04,
    0x04,
    0x0A,
    0x0A,
    0x00
};

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

void create_character()
{
    unsigned char i;

    lcd_cmd(0x40);

    for(i = 0; i < 8; i++)
    {
        lcd_data(character1[i]);
    }
}

void main()
{
    lcd_init();

    create_character();

    lcd_cmd(0x80);

    lcd_data(0);

    while(1);
}
