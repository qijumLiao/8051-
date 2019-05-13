#include <reg51.h>
#include <intrins.h>

/* 8255 DataSet 
4x4 ��L��J
����J����G-LED�G
����J�_��R-LED�G
*/

unsigned char pdata Data_8255;
sbit A0_8255=P2^0;
sbit A1_8255=P2^1;
/*================*/
sbit R_LED = P2^2;		//�qP2^2  �e�X0 �L�N�G 
sbit G_LED = P2^3;		//�qP2^3  �e�X0 �L�N�G

void init_8255(void);   //�Ұ�8255�禡 
unsigned char keypad(void);  //���y��L��� 
void delayms(unsigned int time);  

