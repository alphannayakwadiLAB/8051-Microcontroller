
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

unsigned int num1 = 0, num2 = 0;
unsigned int result;
unsigned char key;
unsigned char operation;
unsigned char digits;

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
    unsigned char digits_array[5];
    unsigned char i = 0;

    if(n == 0)
    {
        lcd_data('0');
        return;
    }

    while(n > 0)
    {
        digits_array[i++] = (n % 10) + '0';
        n = n / 10;
    }

    while(i > 0)
        lcd_data(digits_array[--i]);
}

void get_number(unsigned char number)
{
    unsigned int value = 0;
    unsigned char count = 0;

    while(1)
    {
        key = keypad_scan();

        if(key >= '0' && key <= '9')
        {
            if(count < 2)
            {
                value = (value * 10) + (key - '0');
                lcd_data(key);
                count++;
            }
        }
        else if(key == '#')
        {
            if(count > 0)
            {
                if(number == 1)
                    num1 = value;
                else
                    num2 = value;

                return;
            }
        }
        else if(key == '*')
        {
            value = 0;
            count = 0;
            lcd_cmd(0xC0);
            lcd_string("                ");
            lcd_cmd(0xC0);
        }
    }
}

void main()
{
    lcd_init();

START:

    num1 = 0;
    num2 = 0;

    lcd_cmd(0x01);
    lcd_string("ARITH CALCULATOR");
    delay(1000);

    lcd_cmd(0x01);
    lcd_string("Enter Number 1:");

    lcd_cmd(0xC0);
    get_number(1);

    lcd_cmd(0x01);
    lcd_string("Select Operator:");
    lcd_cmd(0xC0);
    lcd_string("A+ B- C* D/");

    while(1)
    {
        key = keypad_scan();

        if(key == 'A' || key == 'B' ||
           key == 'C' || key == 'D')
        {
            operation = key;
            break;
        }
        else if(key == '*')
        {
            goto START;
        }
    }

    lcd_cmd(0x01);
    lcd_string("Enter Number 2:");
    lcd_cmd(0xC0);
    get_number(2);

    lcd_cmd(0x01);
    lcd_string("Press # = Result");

    while(1)
    {
        key = keypad_scan();

        if(key == '#')
            break;

        if(key == '*')
            goto START;
    }

    lcd_cmd(0x01);
    lcd_string("Result:");

    lcd_cmd(0xC0);

    if(operation == 'A')
    {
        result = num1 + num2;
        display_number(result);
    }
    else if(operation == 'B')
    {
        if(num1 >= num2)
        {
            result = num1 - num2;
            display_number(result);
        }
        else
        {
            lcd_data('-');
            display_number(num2 - num1);
        }
    }
    else if(operation == 'C')
    {
        result = num1 * num2;
        display_number(result);
    }
    else if(operation == 'D')
    {
        if(num2 == 0)
        {
            lcd_string("Divide by Zero");
            delay(2000);
            goto START;
        }

        result = num1 / num2;
        display_number(result);
    }

    delay(3000);

    goto START;
}
