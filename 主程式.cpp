main()
{
   unsigned char n;    
   init_8255(); 		//呼叫函數8255 
   G_LED=0;  R_LED=0;   //2顆LED都給他亮 
 
  while(1)
   {
     /*even-GLED, odd-RLED*/
      n=keypad();				//傳回一個按鍵值 給 n  
      delayms(500);
      while (n>=0 && n<=15)      //代表有按鍵值 
         {
             if ((n%2)==1)			//奇數R-LED亮 
               { 
                 G_LED=1;  R_LED=1;  //先把2顆關掉 
                 delayms(200);
                 G_LED=1;  R_LED=0; //在打開紅色 
	  break;
               }
             else
               {
                  G_LED=1;  R_LED=1;	//先把2顆關掉
                  delayms(200);
                  G_LED=0; R_LED=1;		//在打開綠色
	   break;
	}
         }
   }
}



/*
*
*用到的副程式
* 
*/ 


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











