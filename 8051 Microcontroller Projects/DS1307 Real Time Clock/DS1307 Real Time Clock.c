
#include <reg51.h>

sbit rs  = P3^0;
sbit rw  = P3^1;
sbit en  = P3^2;

sbit SDA = P1^0;
sbit SCL = P1^1;

// ---------- Delay ----------
void delay()
{
    unsigned int i, j;

    for(i = 0; i < 20; i++)
        for(j = 0; j < 1275; j++);
}

// ---------- LCD Functions ----------
void lcdcmd(unsigned char cmd)
{
    P2 = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    delay();
    en = 0;
    delay();
}

void lcddata(unsigned char dat)
{
    P2 = dat;
    rs = 1;
    rw = 0;
    en = 1;
    delay();
    en = 0;
    delay();
}

void lcdstr(unsigned char *str)
{
    while(*str)
    {
        lcddata(*str++);
    }
}

void lcdinit()
{
    lcdcmd(0x38);
    lcdcmd(0x0C);
    lcdcmd(0x06);
    lcdcmd(0x01);
    lcdcmd(0x80);
}

// ---------- I2C Functions ----------
void i2c_delay()
{
    unsigned char i;

    for(i = 0; i < 10; i++);
}

void i2c_start()
{
    SDA = 1;
    SCL = 1;
    i2c_delay();

    SDA = 0;
    i2c_delay();

    SCL = 0;
}

void i2c_stop()
{
    SDA = 0;
    SCL = 1;
    i2c_delay();

    SDA = 1;
    i2c_delay();
}

// Returns 1 if ACK received, 0 otherwise
bit i2c_write(unsigned char dat)
{
    unsigned char i;
    bit ack;

    for(i = 0; i < 8; i++)
    {
        SDA = (dat & 0x80) ? 1 : 0;

        SCL = 1;
        i2c_delay();
        SCL = 0;

        dat <<= 1;
    }

    SDA = 1;      // Release SDA

    SCL = 1;
    i2c_delay();

    ack = (SDA == 0);

    SCL = 0;
    i2c_delay();

    return ack;
}

// ack = 0: send ACK
// ack = 1: send NACK
unsigned char i2c_read(bit ack)
{
    unsigned char i, dat = 0;

    SDA = 1;      // Release SDA

    for(i = 0; i < 8; i++)
    {
        dat <<= 1;

        SCL = 1;
        i2c_delay();

        if(SDA)
            dat |= 0x01;

        SCL = 0;
        i2c_delay();
    }

    SDA = ack ? 1 : 0;

    SCL = 1;
    i2c_delay();
    SCL = 0;

    SDA = 1;

    return dat;
}

// ---------- DS1307 Functions ----------
unsigned char bcd_to_dec(unsigned char val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}

unsigned char dec_to_bcd(unsigned char val)
{
    return ((val / 10) << 4) | (val % 10);
}

// Write one RTC register
bit rtc_write(unsigned char reg, unsigned char dat)
{
    bit ok = 1;

    i2c_start();

    if(!i2c_write(0xD0))
        ok = 0;

    if(ok && !i2c_write(reg))
        ok = 0;

    if(ok && !i2c_write(dat))
        ok = 0;

    i2c_stop();

    return ok;
}

// Read one RTC register
bit rtc_read(unsigned char reg, unsigned char *dat)
{
    bit ok = 1;

    i2c_start();

    if(!i2c_write(0xD0))
        ok = 0;

    if(ok && !i2c_write(reg))
        ok = 0;

    if(ok)
    {
        i2c_start();

        if(!i2c_write(0xD1))
            ok = 0;
    }

    if(ok)
        *dat = i2c_read(1);  // Final byte: NACK

    i2c_stop();

    return ok;
}

// ---------- Main Program ----------
void main()
{
    unsigned char sec, min, hour;
    unsigned char date, month, year;
    unsigned char temp;

    SDA = 1;
    SCL = 1;

    lcdinit();

    lcdcmd(0x80);
    lcdstr("DS1307 RTC");
    lcdcmd(0xC0);
    lcdstr("Initializing");
    delay();

    // Check RTC communication and release clock halt
    if(!rtc_read(0x00, &temp))
    {
        lcdcmd(0x01);
        lcdcmd(0x80);
        lcdstr("RTC NOT FOUND");
        while(1);
    }

    // Clear CH bit to ensure oscillator is running
    if(temp & 0x80)
    {
        temp &= 0x7F;

        if(!rtc_write(0x00, temp))
        {
            lcdcmd(0x01);
            lcdstr("RTC WRITE ERROR");
            while(1);
        }
    }

    while(1)
    {
        if(!rtc_read(0x00, &sec)   ||
           !rtc_read(0x01, &min)   ||
           !rtc_read(0x02, &hour)  ||
           !rtc_read(0x04, &date)  ||
           !rtc_read(0x05, &month) ||
           !rtc_read(0x06, &year))
        {
            lcdcmd(0x01);
            lcdcmd(0x80);
            lcdstr("RTC READ ERROR");
            while(1);
        }

        // Convert BCD to decimal
        sec   = bcd_to_dec(sec & 0x7F);
        min   = bcd_to_dec(min & 0x7F);
        hour  = bcd_to_dec(hour & 0x3F);
        date  = bcd_to_dec(date & 0x3F);
        month = bcd_to_dec(month & 0x1F);
        year  = bcd_to_dec(year);

        // Display time
        lcdcmd(0x80);

        lcddata('T');
        lcddata('I');
        lcddata('M');
        lcddata('E');
        lcddata(':');
        lcddata(' ');

        lcddata((hour / 10) + '0');
        lcddata((hour % 10) + '0');
        lcddata(':');

        lcddata((min / 10) + '0');
        lcddata((min % 10) + '0');
        lcddata(':');

        lcddata((sec / 10) + '0');
        lcddata((sec % 10) + '0');

        // Display date
        lcdcmd(0xC0);

        lcddata('D');
        lcddata('A');
        lcddata('T');
        lcddata('E');
        lcddata(':');
        lcddata(' ');

        lcddata((date / 10) + '0');
        lcddata((date % 10) + '0');
        lcddata('/');

        lcddata((month / 10) + '0');
        lcddata((month % 10) + '0');
        lcddata('/');

        lcddata('2');
        lcddata('0');
        lcddata((year / 10) + '0');
        lcddata((year % 10) + '0');

        delay();
    }
}
