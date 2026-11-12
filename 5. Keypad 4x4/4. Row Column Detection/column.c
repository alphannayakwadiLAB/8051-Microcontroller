
#include <reg51.h>

#define LCD P1
#define KEYPAD P3

sbit RS = P2^0;
sbit EN = P2^1;

unsigned char row, col;

void delay(unsigned int t)
{
    unsigned int i, j;

    for(i = 0; i < t; i++)
        for(j = 0; j < 1275; j++);
}

void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS = 0;
    EN = 1;
    delay(2);
    EN = 0;
    delay(2);
}

void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS = 1;
    EN = 1;
    delay(2);
    EN = 0;
    delay(2);
}

void lcd_string(char *str)
{
    while(*str)
        lcd_data(*str++);
}

void lcd_init(void)
{
    delay(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay(5);
    lcd_cmd(0x80);
}

void lcd_number(unsigned char num)
{
    lcd_data(num + '0');
}

void keypad_scan(void)
{
    unsigned char r, c;

    while(1)
    {
        KEYPAD = 0xF0;

        if((KEYPAD & 0xF0) != 0xF0)
        {
            delay(20);

            for(r = 0; r < 4; r++)
            {
                KEYPAD = 0xFF;
                KEYPAD = 0xF0 | (0x0F & ~(1 << r));

                for(c = 0; c < 4; c++)
                {
                    if((KEYPAD & (0x10 << c)) == 0)
                    {
                        delay(20);

                        if((KEYPAD & (0x10 << c)) == 0)
                        {
                            row = r + 1;
                            col = c + 1;

                            while(1)
                            {
                                KEYPAD = 0xF0;

                                if((KEYPAD & 0xF0) == 0xF0)
                                    break;
                            }

                            return;
                        }
                    }
                }
            }
        }
    }
}

void main(void)
{
    P3 = 0xFF;
    P1 = 0x00;

    lcd_init();

    while(1)
    {
        keypad_scan();

        lcd_cmd(0x01);
        lcd_cmd(0x80);

        lcd_string("Row: ");
        lcd_number(row);

        lcd_cmd(0xC0);

        lcd_string("Column: ");
        lcd_number(col);
    }
}
