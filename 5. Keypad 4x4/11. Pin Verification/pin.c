
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

unsigned char correct_pin[] = "1234";
unsigned char entered_pin[5];

unsigned char key;
unsigned char i;
unsigned char verified;

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
    lcd_init();

    while(1)
    {
        lcd_cmd(0x01);
        lcd_cmd(0x80);
        lcd_string("Enter Your PIN:");

        lcd_cmd(0xC0);

        i = 0;

        while(i < 4)
        {
            key = keypad_scan();

            if(key >= '0' && key <= '9')
            {
                entered_pin[i] = key;
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

        entered_pin[4] = '\0';

        verified = 1;

        for(i = 0; i < 4; i++)
        {
            if(entered_pin[i] != correct_pin[i])
            {
                verified = 0;
                break;
            }
        }

        lcd_cmd(0x01);
        lcd_cmd(0x80);

        if(verified == 1)
        {
            lcd_string("PIN VERIFIED");
            lcd_cmd(0xC0);
            lcd_string("Access Granted");
        }
        else
        {
            lcd_string("WRONG PIN");
            lcd_cmd(0xC0);
            lcd_string("Try Again!");
        }

        delay(2500);
    }
}
