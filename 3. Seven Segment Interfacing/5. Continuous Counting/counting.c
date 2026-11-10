#include <reg51.h>

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
    unsigned int i, j;

    for(i = 0; i < 500; i++)
    {
        for(j = 0; j < 1275; j++);
    }
}

void main()
{
    unsigned char i;

    while(1)
    {
        for(i = 0; i < 10; i++)
        {
            P2 = digit[i];
            delay();
        }
    }
}
