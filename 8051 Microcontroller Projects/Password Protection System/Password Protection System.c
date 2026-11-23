
#include <reg51.h>

// -------- KEYPAD CONNECTIONS --------
sbit r1 = P1^0;
sbit r2 = P1^1;
sbit r3 = P1^2;
sbit r4 = P1^3;

sbit c1 = P1^4;
sbit c2 = P1^5;
sbit c3 = P1^6;

// -------- LCD CONNECTIONS --------
sbit rs = P3^0;
sbit rw = P3^1;
sbit en = P3^2;

// -------- MOTOR CONNECTIONS --------
sbit motp = P3^3;
sbit motn = P3^4;

// -------- FUNCTION DECLARATIONS --------
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void lcddis(unsigned char *);
void delay(void);
void delay_ms(unsigned int);
unsigned char keypad(void);
void check(void);
void motor_control(void);

// -------- PASSWORD --------
unsigned char pwd[10];
unsigned char password[10] = "7071748181";
unsigned char i;

// -------- MAIN PROGRAM --------
void main()
{
    P1 = 0xFF;

    motp = 0;
    motn = 0;

    // Timer 0 initialization
    TMOD = (TMOD & 0xF0) | 0x01;

    // LCD initialization
    delay();
    lcdcmd(0x38);
    lcdcmd(0x0C);
    lcdcmd(0x01);
    delay();
    lcdcmd(0x06);

    lcdcmd(0x80);
    lcddis("Password System");

    delay_ms(2000);

    while(1)
    {
        i = 0;

        lcdcmd(0x01);
        lcdcmd(0x80);
        lcddis("Enter Password");

        lcdcmd(0xC0);

        // Password entry
        while(i < 10)
        {
            unsigned char key;

            key = keypad();

            if(key >= '0' && key <= '9')
            {
                pwd[i] = key;
                lcddat('*');
                i++;
            }
        }

        check();

        delay_ms(2000);

        motp = 0;
        motn = 0;
    }
}

// -------- PASSWORD VERIFICATION --------
void check(void)
{
    unsigned char j;

    for(j = 0; j < 10; j++)
    {
        if(pwd[j] != password[j])
        {
            lcdcmd(0x01);
            lcdcmd(0x80);
            lcddis("Password Wrong");

            motp = 0;
            motn = 0;

            return;
        }
    }

    lcdcmd(0x01);
    lcdcmd(0x80);
    lcddis("Password Matched");

    motor_control();
}

// -------- MOTOR CONTROL --------
void motor_control(void)
{
    // Clockwise rotation
    lcdcmd(0xC0);
    lcddis("Clockwise");

    motp = 1;
    motn = 0;

    delay_ms(2000);

    // Motor stop
    motp = 0;
    motn = 0;

    // Wait 10 seconds
    lcdcmd(0x01);
    lcdcmd(0x80);
    lcddis("Waiting 10 Sec");

    delay_ms(10000);

    // Anticlockwise rotation
    lcdcmd(0x01);
    lcdcmd(0x80);
    lcddis("Returning Back");

    motp = 0;
    motn = 1;

    delay_ms(2000);

    // Motor stop
    motp = 0;
    motn = 0;

    lcdcmd(0x01);
    lcdcmd(0x80);
    lcddis("Motor Stopped");
}

// -------- KEYPAD SCANNING --------
unsigned char keypad(void)
{
    unsigned char key;

    while(1)
    {
        key = 0;

        // Row 1
        P1 = 0xFE;

        if(c1 == 0) key = '1';
        else if(c2 == 0) key = '2';
        else if(c3 == 0) key = '3';

        if(key != 0) goto pressed;

        // Row 2
        P1 = 0xFD;

        if(c1 == 0) key = '4';
        else if(c2 == 0) key = '5';
        else if(c3 == 0) key = '6';

        if(key != 0) goto pressed;

        // Row 3
        P1 = 0xFB;

        if(c1 == 0) key = '7';
        else if(c2 == 0) key = '8';
        else if(c3 == 0) key = '9';

        if(key != 0) goto pressed;

        // Row 4
        P1 = 0xF7;

        if(c1 == 0) key = '*';
        else if(c2 == 0) key = '0';
        else if(c3 == 0) key = '#';

        if(key != 0) goto pressed;
    }

pressed:

    delay();

    // Wait for key release
    while(c1 == 0 || c2 == 0 || c3 == 0)
    {
        P1 = 0xF0;
    }

    delay();

    P1 = 0xFF;

    return key;
}

// -------- LCD COMMAND --------
void lcdcmd(unsigned char val)
{
    P2 = val;
    rs = 0;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

// -------- LCD DATA --------
void lcddat(unsigned char val)
{
    P2 = val;
    rs = 1;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

// -------- LCD STRING --------
void lcddis(unsigned char *s)
{
    while(*s)
    {
        lcddat(*s);
        s++;
    }
}

// -------- TIMER 0 DELAY --------
// For 11.0592 MHz crystal
void delay_ms(unsigned int ms)
{
    unsigned int i;

    for(i = 0; i < ms; i++)
    {
        TH0 = 0xFC;
        TL0 = 0x66;

        TF0 = 0;
        TR0 = 1;

        while(TF0 == 0);

        TR0 = 0;
        TF0 = 0;
    }
}

// -------- LCD SHORT DELAY --------
void delay(void)
{
    unsigned int i;

    for(i = 0; i < 1000; i++);
}
