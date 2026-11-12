
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
unsigned char num1, num2;
char operation;
int result;

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

void display_number(int n)
{
    unsigned char digits[6];
    unsigned char i = 0;

    if(n < 0)
    {
        lcd_data('-');
        n = -n;
    }

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

void main()
{
    lcd_init();

START:

    lcd_cmd(0x01);
    lcd_string("Keypad Calculator");
    lcd_cmd(0xC0);
    lcd_string("Enter Number:");

    // Enter first number
    while(1)
    {
        key = keypad_scan();

        if(key >= '0' && key <= '9')
        {
            num1 = key - '0';

            lcd_cmd(0x01);
            lcd_string("First Number:");
            lcd_cmd(0xC0);
            lcd_data(key);
            break;
        }

        if(key == '*')
            goto START;
    }

    // Select operation
    while(1)
    {
        key = keypad_scan();

        if(key == 'A' || key == 'B' ||
           key == 'C' || key == 'D')
        {
            operation = key;

            lcd_cmd(0x01);
            lcd_string("Operation:");
            lcd_cmd(0xC0);

            if(operation == 'A')
                lcd_data('+');
            else if(operation == 'B')
                lcd_data('-');
            else if(operation == 'C')
                lcd_data('*');
            else
                lcd_data('/');

            break;
        }

        if(key == '*')
            goto START;
    }

    // Enter second number
    while(1)
    {
        key = keypad_scan();

        if(key >= '0' && key <= '9')
        {
            num2 = key - '0';

            lcd_cmd(0x01);
            lcd_string("Second Number:");
            lcd_cmd(0xC0);
            lcd_data(key);
            break;
        }

        if(key == '*')
            goto START;
    }

    // Wait for equals key
    while(1)
    {
        key = keypad_scan();

        if(key == '#')
            break;

        if(key == '*')
            goto START;
    }

    // Perform calculation
    lcd_cmd(0x01);
    lcd_string("Result:");

    lcd_cmd(0xC0);

    if(operation == 'A')
        result = num1 + num2;

    else if(operation == 'B')
        result = num1 - num2;

    else if(operation == 'C')
        result = num1 * num2;

    else if(operation == 'D')
    {
        if(num2 == 0)
        {
            lcd_string("Divide by Zero");
            delay(2000);
            goto START;
        }

        result = num1 / num2;
    }

    display_number(result);

    delay(3000);

    goto START;
}
