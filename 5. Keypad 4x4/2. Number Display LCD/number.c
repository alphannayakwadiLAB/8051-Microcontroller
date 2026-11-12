
#include <reg51.h>

#define LCD P1
#define KEYPAD P3

sbit RS = P2^0;
sbit EN = P2^1;

unsigned char keymap[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

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

void lcd_string(char *str)
{
    while(*str)
        lcd_data(*str++);
}

unsigned char keypad_scan(void)
{
    unsigned char row, col;

    while(1)
    {
        KEYPAD = 0xF0;

        if((KEYPAD & 0xF0) != 0xF0)
        {
            delay(20);

            for(row = 0; row < 4; row++)
            {
                KEYPAD = 0xFF;
                KEYPAD = 0xF0 | (0x0F & ~(1 << row));

                for(col = 0; col < 4; col++)
                {
                    if((KEYPAD & (0x10 << col)) == 0)
                    {
                        delay(20);

                        if((KEYPAD & (0x10 << col)) == 0)
                        {
                            while(1)
                            {
                                KEYPAD = 0xF0;

                                if((KEYPAD & 0xF0) == 0xF0)
                                    break;
                            }

                            delay(20);

                            return keymap[row][col];
                        }
                    }
                }
            }
        }
    }
}

void main(void)
{
    unsigned char key;

    P1 = 0x00;
    P3 = 0xFF;

    lcd_init();

    lcd_string("Press Number:");
    lcd_cmd(0xC0);

    while(1)
    {
        key = keypad_scan();

        if(key >= '0' && key <= '9')
        {
            lcd_data(key);
        }
    }
}
