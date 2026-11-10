
#include <reg51.h>

unsigned char digit[] = {
    0x06,  // 1
    0x4F,  // 3
    0x6D,  // 5
    0x07,  // 7
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
        for(i = 0; i < 5; i++)
        {
            P2 = digit[i];
            delay();
        }
    }
}
