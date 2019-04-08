#include <reg51.h>
#include <intrins.h>
sbit P1_SW=P1^4;    //DIP-SW 
sbit P3_5=P3^5;		//BUZZER
sbit P3_3=P3^3;		//BTN_SW
void delayms(unsigned int time); // DELAY 1ms
int sound=(65536-11059000/(12*2*698)); // F=1KHz
code char led[]={0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00};
unsigned char count;	

void main()
{
  TMOD=0x01; 
  IE=0x84;  
  TCON=0x00;		
  while(1)
 	{
      if(P1_SW==0)   //按下去 
	    {  
		for(count=0;count<10;count++)    
		{	P2=~led[count];
		delayms(800);
			}
		P2=0xff;
		delayms(1000);					
		              
          /////P2=0x00;  //LED 給0亮  給1不亮 
        }
       else
		{
	 	  P2=0xff;  //全不亮 
	    }
	}
}

/* Time Delay 1 ms Subroutine */
void delayms(unsigned int time) 
{
  unsigned int n;
  while(time>0)
   {
    n=120;
    while(n>0)  n--;
    time--;
   }
} 

/* Buzzer Sound Subroutine */
void int1(void) interrupt 2 
{
  unsigned char j;
   for(j=1;j<=200;j++)	
	{
     P3_5=1;
	 TH0=sound/256;
	 TL0=sound%256;
	 TR0=1;
	  while(TF0==0);
		TF0=0;

     P3_5=0;
	 TH0=sound/256;
	 TL0=sound%256;				
	 TR0=1;
	  while(TF0==0);
	 	TF0=0;
	}

}
