unsigned char keypad(void)
{
  code char row[]={0x0f,0x1f,0x2f,0x3f};    //code 表示 後面資料全部存在 ROM 不是存在 RAM 因為他不會變   掃描訊號 
  unsigned char k,KeyData;   
  unsigned char key=0xff;   //16個按鍵 所以回送訊號 0~F 

/*
*    write data to PC to enable   
*  先送出掃描訊號，要送出去要從8255 PC送 PA是00 PB是01 PC是10
* 
* 
*/
  for(k=0; k<4; k++)    // 要檢查4次 送一個0出來 檢查4個鍵  總共4排  
  { 
    A1_8255=1;
    A0_8255=0;
    Data_8255=row[k];   
  /* read data from PB */
    delayms(1);   //先延遲1毫秒，讓電路穩定一下。 
    A1_8255=0;    //回收訊號從PB回收 01  
    A0_8255=1;
    KeyData=Data_8255|0xf0;   //取回訊號放在KeyData    1111 0000   - - - - ,PB3 PB2 PB1 PB0
    if(KeyData==0xf7)  key=4*k+3;	// 1111 0111 按3		//*K 主要是在算第幾排 4*0+3 3 是第一排 
    if(KeyData==0xfb)  key=4*k+2;	// 1111 1011 按2		//*K 主要是在算第幾排 4*1+3 7 是第二排
    if(KeyData==0xfd)  key=4*k+1;	// 1111 1101 按1
    if(KeyData==0xfe)  key=4*k+0;	// 1111 1110 按0 
  }
    return key;   //都沒按就是FF 
}
