
#include <reg51.h>

#define KEYPAD P3
#define LCD P1

sbit RS = P2^0;
sbit EN = P2^1;
sbit DOOR = P2^2;

unsigned char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

unsigned char password[] = "1234";
unsigned char entered[5];

unsigned char key;
unsigned char i;
unsigned char correct;

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

void main()
{
    DOOR = 0;

    lcd_init();

    while(1)
    {
        DOOR = 0;

        lcd_cmd(0x01);
        lcd_cmd(0x80);
        lcd_string("DOOR LOCKED");

        lcd_cmd(0xC0);
        lcd_string("Enter Password");

        i = 0;

        while(i < 4)
        {
            key = keypad_scan();

            if(key >= '0' && key <= '9')
            {
                entered[i] = key;
                lcd_data('*');
                i++;
            }
            else if(key == '*')
            {
                i = 0;
                lcd_cmd(0xC0);
                lcd_string("                ");
                lcd_cmd(0xC0);
            }
        }

        entered[4] = '\0';

        correct = 1;

        for(i = 0; i < 4; i++)
        {
            if(entered[i] != password[i])
            {
                correct = 0;
                break;
            }
        }

        lcd_cmd(0x01);

        if(correct == 1)
        {
            lcd_cmd(0x80);
            lcd_string("ACCESS GRANTED");

            lcd_cmd(0xC0);
            lcd_string("DOOR UNLOCKED");

            DOOR = 1;

            delay(5000);

            DOOR = 0;

            lcd_cmd(0x01);
            lcd_string("DOOR LOCKED");

            delay(1500);
        }
        else
        {
            DOOR = 0;

            lcd_cmd(0x80);
            lcd_string("WRONG PASSWORD");

            lcd_cmd(0xC0);
            lcd_string("DOOR LOCKED");

            delay(2500);
        }
    }
}
