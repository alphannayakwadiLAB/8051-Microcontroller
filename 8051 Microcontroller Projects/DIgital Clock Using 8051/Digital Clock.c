#include<reg51.h>

sbit seg1=P1^0;
sbit seg2=P1^1; //common anode pin connection
sbit seg3=P1^2;
sbit seg4=P1^3;

void main()
{	
  unsigned int i;
    seg1=seg2=seg3=seg4=0;
	  while(1)
		{
			seg1=1; // turn on first segment 1
			P2=0x90;
			for(i=0; i<2000; i++);
			seg1=0;
			seg2=1;
			P2=0xc0;
			for(i=0; i<2000; i++);
			seg2=0;
			seg3=1;
			P2=0xc0;
			for(i=0; i<2000; i++);
			seg3=0;
			seg4=1;
			P2=0x92;
			for(i=0; i<2000; i++);
			seg4=0;
		}
		
}