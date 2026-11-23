
#include <reg51.h>

// Common pins for 7-segment displays
sbit com1 = P1^0;
sbit com2 = P1^1;

// 7-segment codes for COMMON ANODE (0-F)
unsigned char disp[16] =
{
    0xC0,  // 0
    0xF9,  // 1
    0xA4,  // 2
    0xB0,  // 3
    0x99,  // 4
    0x92,  // 5
    0x82,  // 6
    0xF8,  // 7
    0x80,  // 8
    0x90,  // 9
    0x88,  // A
    0x83,  // b
    0xC6,  // C
    0xA1,  // d
    0x86,  // E
    0x8E   // F
};

void delay(void);

void main()
{
    unsigned char count;
    unsigned char low;
    unsigned char high;

    unsigned int i;

    com1 = 0;
    com2 = 0;

    P2 = 0xFF;

    // Timer 1: Counter Mode 2 (8-bit auto-reload)
    TMOD = 0x60;

    TH1 = 0x00;
    TL1 = 0x00;

    TR1 = 1;

    while(1)
    {
        count = TL1;

        low = count & 0x0F;
        high = (count & 0xF0) >> 4;

        // Display lower digit
        com1 = 1;
        com2 = 0;

        P2 = disp[low];

        delay();

        // Turn off displays during switching
        com1 = 0;
        com2 = 0;

        // Display upper digit
        com1 = 0;
        com2 = 1;

        P2 = disp[high];

        delay();

        com1 = 0;
        com2 = 0;
    }
}

// Multiplexing delay
void delay(void)
{
    unsigned int i;

    for(i = 0; i < 1000; i++);
}
