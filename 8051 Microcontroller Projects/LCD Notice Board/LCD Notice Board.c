
#include <reg51.h>

// LCD Pin Connections
sbit rs = P2^0;
sbit rw = P2^1;
sbit en = P2^2;

// Function Declarations
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void delay(void);

void main()
{
    unsigned char x;

    // UART Initialization
    SCON = 0x50;       // UART Mode 1, REN Enabled
    TMOD = 0x20;       // Timer1 Mode 2
    TH1 = 0xFD;        // 9600 Baud @ 11.0592 MHz
    TL1 = 0xFD;
    TR1 = 1;           // Start Timer1

    // LCD Initialization
    lcdcmd(0x38);      // 8-bit, 2-line LCD
    lcdcmd(0x0C);      // Display ON, Cursor OFF
    lcdcmd(0x01);      // Clear LCD
    lcdcmd(0x06);      // Auto Increment Cursor
    lcdcmd(0x80);      // First Row, First Column

    while(1)
    {
        // Receive Data
        while(RI == 0);

        x = SBUF;
        RI = 0;

        // Transmit Received Data
        SBUF = x;

        while(TI == 0);
        TI = 0;

        // Display Received Data on LCD
        lcddat(x);

        delay();
    }
}

// LCD Command Function
void lcdcmd(unsigned char val)
{
    P1 = val;
    rs = 0;
    rw = 0;
    en = 1;
    delay();
    en = 0;
    delay();
}

// LCD Data Function
void lcddat(unsigned char dat)
{
    P1 = dat;
    rs = 1;
    rw = 0;
    en = 1;
    delay();
    en = 0;
    delay();
}

// Delay Function
void delay(void)
{
    unsigned int i, j;

    for(i = 0; i < 1200; i++)
    {
        for(j = 0; j < 10; j++);
    }
}
