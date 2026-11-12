
#include <reg51.h>

#define KEYPAD P3
#define LCD P1

sbit RS = P2^0;
sbit EN = P2^1;
sbit LED = P2^2;

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

void display_menu()
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string("1:LED ON  2:OFF");

    lcd_cmd(0xC0);
    lcd_string("3:BLINK 4:COUNT");
}

void display_counter()
{
    unsigned int temp;
    unsigned char digits[5];
    unsigned char i = 0;

    temp = count;

    if(temp == 0)
    {
        lcd_data('0');
        return;
    }

    while(temp > 0)
    {
        digits[i++] = (temp % 10) + '0';
        temp /= 10;
    }

    while(i > 0)
        lcd_data(digits[--i]);
}

void main()
{
    LED = 0;
    lcd_init();

    while(1)
    {
        display_menu();

        key = keypad_scan();

        if(key == '1')
        {
            LED = 1;
            lcd_cmd(0x01);
            lcd_string("LED IS ON");
            delay(1500);
        }

        else if(key == '2')
        {
            LED = 0;
            lcd_cmd(0x01);
            lcd_string("LED IS OFF");
            delay(1500);
        }

        else if(key == '3')
        {
            lcd_cmd(0x01);
            lcd_string("LED BLINKING");

            LED = 1;
            delay(500);
            LED = 0;
            delay(500);

            LED = 1;
            delay(500);
            LED = 0;
            delay(500);
        }

        else if(key == '4')
        {
            count++;

            lcd_cmd(0x01);
            lcd_string("Counter Value:");

            lcd_cmd(0xC0);
            display_counter();

            delay(1500);
        }

        else if(key == '*')
        {
            count = 0;
            LED = 0;
        }
    }
}
