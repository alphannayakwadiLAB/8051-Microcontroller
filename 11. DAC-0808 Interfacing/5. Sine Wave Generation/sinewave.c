#include <reg51.h>

unsigned char code sine_table[32] =
{
    128, 152, 176, 198, 218, 234, 246, 254,
    255, 254, 246, 234, 218, 198, 176, 152,
    128, 104, 80, 58, 38, 22, 10, 2,
    0, 2, 10, 22, 38, 58, 80, 104
};

void delay()
{
    unsigned int i;

    for(i = 0; i < 100; i++);
}

void main()
{
    unsigned char i;

    while(1)
    {
        for(i = 0; i < 32; i++)
        {
            P1 = sine_table[i];
            delay();
        }
    }
}
