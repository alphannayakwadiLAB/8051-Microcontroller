#include <reg51.h>

void delay(unsigned int i);
void lcd_cmd(unsigned char a);
void lcd_data(unsigned char b);
void lcd_init(void);
void lcd_str(unsigned char *str);

void I2C_Start(void);
void I2C_Stop(void);
unsigned char I2C_DataRead(void);
unsigned char I2C_DataWrite(unsigned char Data);

sbit rs  = P2^0;
sbit en  = P2^1;
sbit SCL = P3^0;
sbit SDA = P3^1;

sfr ldata = 0x90;    // LCD data port P1

void main()
{
    unsigned char x;
    unsigned char ack;

    lcd_init();

    lcd_cmd(0x80);
    lcd_str("   WELCOME TO   ");

    lcd_cmd(0xC0);
    lcd_str("   MY PROJECT   ");

    delay(50000);

    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_str("   Alphan   ");

    lcd_cmd(0xC0);
    lcd_str("   Nayakwadi    ");

    delay(50000);

    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_str(" I2C PROTOCOL R/W");

    delay(30000);

    // ---------------- I2C WRITE ----------------

    I2C_Start();

    ack = I2C_DataWrite(0xA0);    // EEPROM write address
    if(ack)
    {
        ack = I2C_DataWrite(0x00); // Memory address
    }

    if(ack)
    {
        ack = I2C_DataWrite('A');  // Write character A
    }

    I2C_Stop();

    // EEPROM write cycle delay
    delay(60000);

    // ---------------- I2C READ ----------------

    if(ack)
    {
        I2C_Start();

        ack = I2C_DataWrite(0xA0); // EEPROM write mode
        if(ack)
        {
            ack = I2C_DataWrite(0x00); // Memory location 0
        }

        if(ack)
        {
            I2C_Start();               // Repeated START
            ack = I2C_DataWrite(0xA1); // EEPROM read mode
        }

        if(ack)
        {
            x = I2C_DataRead();
        }

        I2C_Stop();
    }

    // ---------------- LCD RESULT ----------------

    lcd_cmd(0x01);
    lcd_cmd(0x80);

    if(ack)
    {
        lcd_str("READ SUCCESS");

        lcd_cmd(0xC0);
        lcd_str("DATA: ");
        lcd_data(x);
    }
    else
    {
        lcd_str("EEPROM ERROR");
        lcd_cmd(0xC0);
        lcd_str("CHECK I2C WIRE");
    }

    while(1);
}

// ---------------- LCD FUNCTIONS ----------------

void lcd_init(void)
{
    delay(50000);

    lcd_cmd(0x38);   // 8-bit, 2-line LCD
    lcd_cmd(0x0C);   // Display ON, cursor OFF
    lcd_cmd(0x01);   // Clear display
    lcd_cmd(0x06);   // Auto increment
    lcd_cmd(0x80);   // First line
}

void delay(unsigned int i)
{
    unsigned int j;

    for(j = 0; j < i; j++);
}

void lcd_cmd(unsigned char a)
{
    rs = 0;
    ldata = a;
    en = 1;
    delay(100);
    en = 0;
    delay(100);

    if(a == 0x01 || a == 0x02)
        delay(2000);
}

void lcd_data(unsigned char b)
{
    rs = 1;
    ldata = b;
    en = 1;
    delay(100);
    en = 0;
    delay(100);
}

void lcd_str(unsigned char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

// ---------------- I2C START ----------------

void I2C_Start(void)
{
    SDA = 1;
    SCL = 1;
    delay(100);

    SDA = 0;
    delay(100);

    SCL = 0;
}

// ---------------- I2C STOP ----------------

void I2C_Stop(void)
{
    SCL = 0;
    SDA = 0;
    delay(100);

    SCL = 1;
    delay(100);

    SDA = 1;
    delay(100);
}

// ---------------- I2C WRITE ----------------
// Returns 1 if ACK received, 0 if NACK

unsigned char I2C_DataWrite(unsigned char Data)
{
    unsigned char i;
    unsigned char ack;

    for(i = 0; i < 8; i++)
    {
        SCL = 0;

        SDA = (Data & 0x80) ? 1 : 0;

        delay(100);
        SCL = 1;
        delay(100);

        SCL = 0;
        Data = Data << 1;
    }

    // Release SDA for slave ACK
    SDA = 1;
    delay(100);

    SCL = 1;
    delay(100);

    ack = (SDA == 0) ? 1 : 0;

    SCL = 0;
    delay(100);

    return ack;
}

// ---------------- I2C READ ----------------

unsigned char I2C_DataRead(void)
{
    unsigned char i;
    unsigned char Dat = 0;

    SDA = 1;   // Release SDA

    for(i = 0; i < 8; i++)
    {
        SCL = 0;
        delay(100);

        SCL = 1;
        delay(100);

        Dat = Dat << 1;
        Dat = Dat | SDA;

        SCL = 0;
        delay(100);
    }

    // Send NACK after reading the final byte
    SDA = 1;
    SCL = 1;
    delay(100);
    SCL = 0;
    SDA = 1;

    return Dat;
}