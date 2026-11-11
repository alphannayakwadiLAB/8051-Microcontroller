
#include <reg51.h>

#define LCD P1
#define KEYPAD P2

sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

unsigned char key;

unsigned char keypad[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
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

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}

unsigned char get_key()
{
    unsigned char row, col;
    unsigned char row_data;

    while(1)
    {
        for(row = 0; row < 4; row++)
        {
            KEYPAD = 0xFF;
            KEYPAD &= ~(1 << row);

            row_data = KEYPAD & 0xF0;

            if(row_data != 0xF0)
            {
                delay();

                row_data = KEYPAD & 0xF0;

                if(row_data != 0xF0)
                {
                    for(col = 0; col < 4; col++)
                    {
                        if(!(row_data & (0x10 << col)))
                        {
                            while((KEYPAD & 0xF0) != 0xF0);
                            delay();
                            return keypad[row][col];
                        }
                    }
                }
            }
        }
    }
}

void main()
{
    lcd_init();

    lcd_string("KEY PRESSED:");

    while(1)
    {
        key = get_key();

        lcd_cmd(0xC0);
        lcd_data(key);
        lcd_data(' ');
    }
}
