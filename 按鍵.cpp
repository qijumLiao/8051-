unsigned char keypad(void)
{
  code char row[]={0x0f,0x1f,0x2f,0x3f};    //code ��� �᭱��ƥ����s�b ROM ���O�s�b RAM �]���L���|��   ���y�T�� 
  unsigned char k,KeyData;   
  unsigned char key=0xff;   //16�ӫ��� �ҥH�^�e�T�� 0~F 

/*
*    write data to PC to enable   
*  ���e�X���y�T���A�n�e�X�h�n�q8255 PC�e PA�O00 PB�O01 PC�O10
* 
* 
*/
  for(k=0; k<4; k++)    // �n�ˬd4�� �e�@��0�X�� �ˬd4����  �`�@4��  
  { 
    A1_8255=1;
    A0_8255=0;
    Data_8255=row[k];   
  /* read data from PB */
    delayms(1);   //������1�@��A���q��í�w�@�U�C 
    A1_8255=0;    //�^���T���qPB�^�� 01  
    A0_8255=1;
    KeyData=Data_8255|0xf0;   //���^�T����bKeyData    1111 0000   - - - - ,PB3 PB2 PB1 PB0
    if(KeyData==0xf7)  key=4*k+3;	// 1111 0111 ��3		//*K �D�n�O�b��ĴX�� 4*0+3 3 �O�Ĥ@�� 
    if(KeyData==0xfb)  key=4*k+2;	// 1111 1011 ��2		//*K �D�n�O�b��ĴX�� 4*1+3 7 �O�ĤG��
    if(KeyData==0xfd)  key=4*k+1;	// 1111 1101 ��1
    if(KeyData==0xfe)  key=4*k+0;	// 1111 1110 ��0 
  }
    return key;   //���S���N�OFF 
}
