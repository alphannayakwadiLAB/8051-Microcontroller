#include <reg51.h>

void main()
{
    SCON = 0x50;      // UART Mode 1, 8-bit UART
    TMOD = 0x20;      // Timer 1, Mode 2 (Auto Reload)
    TH1 = 0xFD;        // 9600 baud for 11.0592 MHz crystal
    TL1 = 0xFD;
    TR1 = 1;           // Start Timer 1

    while(1)
    {
        SBUF = 'A';    // Transmit character A

        while(TI == 0); // Wait until transmission completes
        TI = 0;         // Clear transmit flag
    }
}