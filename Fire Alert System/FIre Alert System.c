
#include <reg51.h>

sbit sensor = P1^0;

sbit rs = P1^1;
sbit rw = P1^2;
sbit en = P1^3;

sbit buzzer = P3^0;

void delay(void);
void lcdinit(void);
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void lcddis(unsigned char *);

void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < 50; i++)
        for(j = 0; j < 1275; j++);
}

void lcdcmd(unsigned char cmd)
{
    P2 = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

void lcddat(unsigned char dat)
{
    P2 = dat;
    rs = 1;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

void lcddis(unsigned char *str)
{
    while(*str)
        lcddat(*str++);
}

void lcdinit(void)
{
    lcdcmd(0x38);
    lcdcmd(0x0C);
    lcdcmd(0x06);
    lcdcmd(0x01);
    delay();
}

void main(void)
{
    unsigned char count = 0;
    unsigned char i;
    bit fire;

    sensor = 1;
    buzzer = 0;

    lcdinit();

    while(1)
    {
        count = 0;

        // Check sensor 10 times
        for(i = 0; i < 10; i++)
        {
            if(sensor == 1)
                count++;

            delay();
        }

        // Confirm fire if HIGH in at least 8 samples
        if(count >= 8)
            fire = 1;
        else
            fire = 0;

        if(fire == 1)
        {
            lcdcmd(0x01);
            lcdcmd(0x80);
            lcddis("FIRE DETECTED");

            lcdcmd(0xC0);
            lcddis("ALARM ACTIVE");

            buzzer = 1;
        }
        else
        {
            lcdcmd(0x01);
            lcdcmd(0x80);
            lcddis("SYSTEM NORMAL");

            lcdcmd(0xC0);
            lcddis("NO FIRE");

            buzzer = 0;
        }
    }
}
