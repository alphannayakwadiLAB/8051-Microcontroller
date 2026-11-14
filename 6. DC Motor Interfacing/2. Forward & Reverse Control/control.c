
#include <reg51.h>

sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit EN  = P1^2;

sbit FWD = P3^2;
sbit REV = P3^3;

void main()
{
    FWD = 1;
    REV = 1;

    EN = 0;
    IN1 = 0;
    IN2 = 0;

    while(1)
    {
        if(FWD == 0 && REV == 1)
        {
            IN1 = 1;
            IN2 = 0;
            EN = 1;
        }
        else if(REV == 0 && FWD == 1)
        {
            IN1 = 0;
            IN2 = 1;
            EN = 1;
        }
        else
        {
            EN = 0;
            IN1 = 0;
            IN2 = 0;
        }
    }
}
