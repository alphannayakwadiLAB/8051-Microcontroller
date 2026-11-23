#include <reg51.h>

sbit SCLK = P1^0;
sbit MOSI = P1^1;
sbit MISO = P1^2;
sbit SS   = P1^3;

void delay(unsigned int t);

void SPI_Write(unsigned char dat)
{
    unsigned char i;

    SS = 0;               // Select slave
    SCLK = 0;

    for(i = 0; i < 8; i++)
    {
        MOSI = (dat & 0x80) ? 1 : 0;

        SCLK = 1;          // Clock rising edge
        delay(100);

        SCLK = 0;          // Clock falling edge
        delay(100);

        dat = dat << 1;
    }

    SS = 1;               // Release slave
}

void main()
{
    SCLK = 0;
    MOSI = 0;
    SS = 1;

    while(1)
    {
        SPI_Write('A');
        delay(50000);
    }
}

void delay(unsigned int t)
{
    unsigned int i;
    for(i = 0; i < t; i++);
}