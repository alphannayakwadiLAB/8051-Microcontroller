#include <reg51.h>

sbit SCLK = P1^0;
sbit MOSI = P1^1;
sbit MISO = P1^2;
sbit SS   = P1^3;

sbit RS = P3^5;
sbit EN = P3^6;

void delay(unsigned int t);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_init(void);

unsigned char SPI_Read(void)
{
    unsigned char i;
    unsigned char dat = 0;

    for(i = 0; i < 8; i++)
    {
        while(SCLK == 0);       // Wait for rising edge
        dat = (dat << 1) | MOSI;

        while(SCLK == 1);       // Wait for falling edge
    }

    return dat;
}

void main()
{
    unsigned char received;

    SCLK = 1;   // Input/released
    MOSI = 1;   // Input/released
    SS = 1;      // Slave not selected

    lcd_init();

    lcd_cmd(0x80);
    lcd_data('S');
    lcd_data('P');
    lcd_data('I');
    lcd_data(' ');
    lcd_data('R');
    lcd_data('E');
    lcd_data('C');
    lcd_data('E');
	  lcd_data('I');
	  lcd_data('V');
	  lcd_data('E');

    while(1)
    {
        while(SS == 1);        // Wait for Master selection

        received = SPI_Read();

        while(SS == 0);        // Wait for transmission to finish

        lcd_cmd(0xC0);
        lcd_data(received);
    }
}

void lcd_init(void)
{
    delay(20000);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x80);
}

void lcd_cmd(unsigned char cmd)
{
    RS = 0;
    P2 = cmd;
    EN = 1;
    delay(100);
    EN = 0;
    delay(100);
}

void lcd_data(unsigned char dat)
{
    RS = 1;
    P2 = dat;
    EN = 1;
    delay(100);
    EN = 0;
    delay(100);
}

void delay(unsigned int t)
{
    unsigned int i;
    for(i = 0; i < t; i++);
}