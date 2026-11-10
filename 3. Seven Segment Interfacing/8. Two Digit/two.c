
#include <reg51.h>

sbit UNIT = P3^0;
sbit TENS = P3^1;

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

void display(unsigned char num)
{
    unsigned char i;

    for(i = 0; i < 100; i++)
    {
        // Display units digit
        UNIT = 0;
        TENS = 0;

        P2 = digit[num % 10];

        UNIT = 1;
        delay();
        UNIT = 0;

        // Display tens digit
        P2 = digit[num / 10];

        TENS = 1;
        delay();
        TENS = 0;
    }
}

void main()
{
    unsigned char count;

    UNIT = 0;
    TENS = 0;

    while(1)
    {
        for(count = 0; count < 100; count++)
        {
            display(count);
        }
    }
}
