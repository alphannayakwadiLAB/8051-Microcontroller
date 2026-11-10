
#include <reg51.h>

sbit UNIT = P3^0;
sbit TENS = P3^1;
sbit HUND = P3^2;

unsigned char digit[] = {
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F   // 9
};

void delay()
{
    unsigned int i;

    for(i = 0; i < 500; i++);
}

void display(unsigned int num)
{
    unsigned char i;

    for(i = 0; i < 100; i++)
    {
        // Units digit
        UNIT = 0;
        TENS = 0;
        HUND = 0;

        P2 = digit[num % 10];
        UNIT = 1;
        delay();

        // Tens digit
        UNIT = 0;

        P2 = digit[(num / 10) % 10];
        TENS = 1;
        delay();

        // Hundreds digit
        TENS = 0;

        P2 = digit[num / 100];
        HUND = 1;
        delay();

        HUND = 0;
    }
}

void main()
{
    unsigned int count;

    UNIT = 0;
    TENS = 0;
    HUND = 0;

    while(1)
    {
        for(count = 0; count < 1000; count++)
        {
            display(count);
        }
    }
}
