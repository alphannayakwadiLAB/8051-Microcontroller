
#include <reg51.h>

#define LCD P1
#define KEYPAD P2

sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

unsigned char keypad[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

unsigned char password[] = "1234";
unsigned char entered[5];

unsigned char i, key;

void delay()
{
    int x, y;
    for(x = 0; x < 100; x++)
        for(y = 0; y < 1275; y++);
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
    unsigned char row, col, temp;

    while(1)
    {
        for(row = 0; row < 4; row++)
        {
            KEYPAD = 0xFF;
            KEYPAD &= ~(1 << row);

            temp = KEYPAD & 0xF0;

            if(temp != 0xF0)
            {
                delay();
                temp = KEYPAD & 0xF0;

                if(temp != 0xF0)
                {
                    for(col = 0; col < 4; col++)
                    {
                        if(!(temp & (0x10 << col)))
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

    while(1)
    {
        lcd_cmd(0x01);
        lcd_string("ENTER PASSWORD");
        lcd_cmd(0xC0);

        for(i = 0; i < 4; i++)
        {
            key = get_key();

            if(key >= '0' && key <= '9')
            {
                entered[i] = key;
                lcd_data('*');
            }
            else
            {
                i--;
            }
        }

        entered[4] = '\0';

        lcd_cmd(0x01);

        if(entered[0] == password[0] &&
           entered[1] == password[1] &&
           entered[2] == password[2] &&
           entered[3] == password[3])
        {
            lcd_string("PASSWORD OK");
        }
        else
        {
            lcd_string("WRONG PASSWORD");
        }

        delay();
        delay();
    }
}
