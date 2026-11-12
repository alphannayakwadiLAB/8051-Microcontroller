
#include <reg51.h>

#define KEYPAD P3
#define LCD P1

sbit RS = P2^0;
sbit EN = P2^1;
sbit LED = P2^2;
sbit BUZZER = P2^3;

unsigned char keymap[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

unsigned char key;
unsigned int count = 0;

// Delay function
void delay(unsigned int t)
{
    unsigned int x, y;

    for(x = 0; x < t; x++)
        for(y = 0; y < 1275; y++);
}

// LCD command
void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS = 0;
    EN = 1;
    delay(2);
    EN = 0;
}

// LCD data
void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS = 1;
    EN = 1;
    delay(2);
    EN = 0;
}

// LCD string
void lcd_string(unsigned char *str)
{
    while(*str)
        lcd_data(*str++);
}

// LCD initialization
void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay(5);
}

// Keypad scanning
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

// Function 1: LED ON
void led_on()
{
    LED = 1;

    lcd_cmd(0x01);
    lcd_string("LED IS ON");
    delay(1500);
}

// Function 2: LED OFF
void led_off()
{
    LED = 0;

    lcd_cmd(0x01);
    lcd_string("LED IS OFF");
    delay(1500);
}

// Function 3: LED BLINK
void led_blink()
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

// Function 4: Counter
void counter()
{
    count++;

    lcd_cmd(0x01);
    lcd_string("COUNTER VALUE:");

    lcd_cmd(0xC0);

    if(count >= 1000)
    {
        lcd_data((count / 1000) + '0');
        count = count % 1000;
    }

    lcd_data((count / 100) + '0');
    lcd_data(((count / 10) % 10) + '0');
    lcd_data((count % 10) + '0');

    delay(1500);
}

// Function 5: Buzzer ON
void buzzer_on()
{
    BUZZER = 1;

    lcd_cmd(0x01);
    lcd_string("BUZZER IS ON");
    delay(1500);
}

// Function 6: Buzzer OFF
void buzzer_off()
{
    BUZZER = 0;

    lcd_cmd(0x01);
    lcd_string("BUZZER IS OFF");
    delay(1500);
}

// Display menu
void display_menu()
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string("1:ON 2:OFF 3:BL");

    lcd_cmd(0xC0);
    lcd_string("4:COUNT 5:BUZ 6");
}

// Main program
void main()
{
    LED = 0;
    BUZZER = 0;

    lcd_init();

    while(1)
    {
        display_menu();

        key = keypad_scan();

        switch(key)
        {
            case '1':
                led_on();
                break;

            case '2':
                led_off();
                break;

            case '3':
                led_blink();
                break;

            case '4':
                counter();
                break;

            case '5':
                buzzer_on();
                break;

            case '6':
                buzzer_off();
                break;

            case '*':
                LED = 0;
                BUZZER = 0;
                count = 0;
                break;

            default:
                break;
        }
    }
}
