#include <reg51.h>
#include <intrins.h>

/* 8255 DataSet 
4x4 鍵盤輸入
→輸入偶數G-LED亮
→輸入奇數R-LED亮
*/

unsigned char pdata Data_8255;
sbit A0_8255=P2^0;
sbit A1_8255=P2^1;
/*================*/
sbit R_LED = P2^2;		//從P2^2  送出0 他就亮 
sbit G_LED = P2^3;		//從P2^3  送出0 他就亮

void init_8255(void);   //啟動8255函式 
unsigned char keypad(void);  //掃描鍵盤函示 
void delayms(unsigned int time);  

