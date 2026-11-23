
#include <reg51.h>

sbit load1 = P1^0;
sbit load2 = P1^1;
sbit load3 = P1^2;
sbit load4 = P1^3;

unsigned char x;

void main()
{
    SCON = 0x50;     // UART Mode 1, 8-bit UART, REN enabled
    TMOD = 0x20;     // Timer1 Mode 2 (Auto Reload)
    TH1  = 0xFD;     // Baud rate 9600 for 11.0592 MHz
    TL1  = 0xFD;
    TR1  = 1;         // Start Timer1

    // Initialize all loads OFF
    load1 = 1;
    load2 = 1;
    load3 = 1;
    load4 = 1;

    while(1)
    {
        // Receive data
        while(RI == 0);
        x = SBUF;
        RI = 0;

        // Echo received character
        SBUF = x;
        while(TI == 0);
        TI = 0;

        // Load control
        if(x == '1')
            load1 = 1;     // Load 1 OFF

        else if(x == '2')
            load1 = 0;     // Load 1 ON

        else if(x == '3')
            load2 = 1;     // Load 2 OFF

        else if(x == '4')
            load2 = 0;     // Load 2 ON

        else if(x == '5')
            load3 = 1;     // Load 3 OFF

        else if(x == '6')
            load3 = 0;     // Load 3 ON

        else if(x == '7')
            load4 = 1;     // Load 4 OFF

        else if(x == '8')
            load4 = 0;     // Load 4 ON
    }
}
