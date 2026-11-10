
#include <reg51.h>

sbit D1 = P3^0;
sbit D2 = P3^1;
sbit D3 = P3^2;
sbit D4 = P3^3;

unsigned char seg_code[] = {
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

    for(i = 0; i < 200; i++);
}

void display(unsigned int num)
{
    unsigned char i;

    for(i = 0; i < 100; i++)
    {
        // Thousands
        D1 = 0;
        D2 = 0;
        D3 = 0;
        D4 = 0;

        P2 = seg_code[num / 1000];
        D1 = 1;
        delay();
        D1 = 0;

        // Hundreds
        P2 = seg_code[(num / 100) % 10];
        D2 = 1;
        delay();
        D2 = 0;

        // Tens
        P2 = seg_code[(num / 10) % 10];
        D3 = 1;
        delay();
        D3 = 0;

        // Units
        P2 = seg_code[num % 10];
        D4 = 1;
        delay();
        D4 = 0;
    }
}

void main()
{
    unsigned int count;

    while(1)
    {
        // Up counting
        for(count = 0; count <= 9999; count++)
        {
            display(count);
        }

        // Down counting
        for(count = 9999; count > 0; count--)
        {
            display(count - 1);
        }
    }
}
