
#include <reg51.h>

unsigned char keypad(void);

void delay(unsigned int t)
{
    unsigned int i, j;

    for(i = 0; i < t; i++)
        for(j = 0; j < 1275; j++);
}

unsigned char keypad(void)
{
    unsigned char row, col;
    unsigned char keymap[4][4] =
    {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'*','0','#','D'}
    };

    while(1)
    {
        P1 = 0xF0;

        if((P1 & 0xF0) != 0xF0)
        {
            delay(20);

            if((P1 & 0xF0) != 0xF0)
            {
                for(row = 0; row < 4; row++)
                {
                    P1 = 0xFF;
                    P1 &= ~(1 << row);

                    for(col = 0; col < 4; col++)
                    {
                        if((P1 & (0x10 << col)) == 0)
                        {
                            while((P1 & 0xF0) != 0xF0);
                            delay(20);

                            return keymap[row][col];
                        }
                    }
                }
            }
        }
    }
}

void main(void)
{
    unsigned char key;

    P1 = 0xFF;
    P2 = 0x00;

    while(1)
    {
        key = keypad();
        P2 = key;
    }
}
