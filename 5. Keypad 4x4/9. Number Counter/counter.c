#include <reg51.h>

#define KEYPAD P3
#define LCD P1

sbit RS = P2^0;
sbit EN = P2^1;

unsigned char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

unsigned char key;
unsigned int count = 0;

void delay(unsigned int t)
{
    unsigned int x, y;

    for(x = 0; x < t; x++)
        for(y = 0; y < 1275; y++);
}

void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS = 0;
    EN = 1;
    delay(2);
    EN = 0;
}

void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS = 1;
    EN = 1;
    delay(2);
    EN = 0;
}

void lcd_string(unsigned char *str)
{
    while(*str)
        lcd_data(*str++);
}

void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay(5);
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

            if((KEYPAD & 0xF0) != 0xF0)
            {
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
                                KEYPAD = 0xF0;

                                while((KEYPAD & 0xF0) != 0xF0);

                                delay(20);
                                return keymap[row][col];
                            }
                        }
                    }
                }
            }
        }
    }
}

void display_number(unsigned int n)
{
    unsigned char digits[5];
    unsigned char i = 0;

    if(n == 0)
    {
        lcd_data('0');
        return;
    }

    while(n > 0)
    {
        digits[i++] = (n % 10) + '0';
        n = n / 10;
    }

    while(i > 0)
        lcd_data(digits[--i]);
}

void display_count()
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string("Number Counter:");

    lcd_cmd(0xC0);
    lcd_string("Count: ");

    display_number(count);
}

void main()
{
    lcd_init();
    display_count();

    while(1)
    {
        key = keypad_scan();

        if(key == '1')
        {
            if(count < 65535)
                count++;

            display_count();
        }

        else if(key == '2')
        {
            if(count > 0)
                count--;

            display_count();
        }

        else if(key == '3')
        {
            count = 0;
            display_count();
        }

        else if(key == '4')
        {
            display_count();
        }
    }
}
