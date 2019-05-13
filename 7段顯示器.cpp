#include <reg51.h>
#include <intrins.h>

/* ====8255 DataSet== */
/*
把輸入的按鍵值要顯示在7段顯示器上 
*/
unsigned char pdata Data_8255;
sbit A0_8255=P2^0;
sbit A1_8255=P2^1;
/*====Segmnet Set==*/
sbit s74164clr=P1^6;
sbit s74164clk=P1^7;
sbit s74164data=P1^0;
sbit R_LED=P2^2;/*RED LED*/
sbit G_LED=P2^3;/*GREEN LED */

void init_8255(void);
void wrdata74164(char number);
unsigned char keypad(void);
void delayms(unsigned int time);
code char table[]={0xc0,0xf9,0xa4,0xb0,                   
                                 0x99,0x92,0x82,0xf8, 
                                 0x80,0x90,0x88,0x83, 
                                 0xc6,0xa1,0x86,0x8e};

unsigned char keypad(void)
{
  code char row[]={0x0f,0x1f,0x2f,0x3f};
  unsigned char k,KeyData;
  unsigned char key=0xff;

  for(k=0; k<4; k++)
  {
   /* write data to PC to enable */
    A1_8255=1;
    A0_8255=0;
    Data_8255=row[k];
  /* read data from PB */
    delayms(1);
    A1_8255=0;
    A0_8255=1;
    KeyData=Data_8255|0xf0;
    if(KeyData==0xf7)  key=4*k+3;
    if(KeyData==0xfb)  key=4*k+2;
    if(KeyData==0xfd)  key=4*k+1;
    if(KeyData==0xfe)  key=4*k+0;
  }
    return key;
}

void wrdata74164(char number)
{
   unsigned  char k,transnumber;
   
   s74164clr=1;
   for(k=0; k<8; k++)
    {
      transnumber=number;
      transnumber=transnumber&0x80;
      if (transnumber==0)
        {
           s74164data=0;
        }
     else
       {
           s74164data=1;
       }	    
      s74164clk=0;  
      s74164clk=1;
      number=number<<1;	  
    }     
}

void init_8255(void)
{
  A1_8255=1;
  A0_8255=1;
  Data_8255=0x82;
}


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


