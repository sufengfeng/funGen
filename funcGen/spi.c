
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/


#include	"spi.h"
unsigned char bdata dat; //dat�ǿ�λѰַ�ı���
sbit dat7=dat^7;
sbit dat6=dat^6;
sbit dat5=dat^5;
sbit dat4=dat^4;
sbit dat3=dat^3;
sbit dat2=dat^2;
sbit dat1=dat^1;
sbit dat0=dat^0;            // ȡ��dat�ĸ���λ
/******************************************************************
- ����������IOģ��SPI������һ���ֽ�
- ����˵����x:Ҫ���͵��ֽ�
- ע���ܶ�����£�SPI����Ҫ�нϸߵ��ٶȵģ��˺����в�ʹ���κ�ѭ��
       �ṹ����for(;;) while�ȵȣ�����ʹ����λѰַ����Ϊ������ٶ�
******************************************************************/
void SPI_WriteByte(unsigned char x)
{
/*----����ʹ��ѭ����λ�����ʵ�ַ�ʽ���ٶ�Ҫ��ֱ����λѰַ��˳��ִ�з�ʽʵ�����ö�
----��Ϊ���Ѵ󲿷ֵ�ʱ�仨����ѭ�����ӵĵ������Ƚ���λ��������
    unDIOgnedchar i=0;
    for(i=0;i<8;i++)
    {
        SPI_DIO=x&(0x80>>i);
        SPI_CLK=0;
        SPI_CLK=1;
    }
----------------------------------*/  
    dat=x;        // ��x��ֵ������λѰַ�ı���dat���Ա�ȡ������λ
        
    SPI_DIO=dat7;   // ȡ����7��λ��д����������   ����λ��ǰ��
    SPI_CLK=0;
    SPI_CLK=1;     // ʱ���߲��������أ����ݱ�д��
   
    SPI_DIO=dat6;
    SPI_CLK=0;
    SPI_CLK=1;
   
    SPI_DIO=dat5;
    SPI_CLK=0;
    SPI_CLK=1;
   
    SPI_DIO=dat4;
    SPI_CLK=0;
    SPI_CLK=1;
   
    SPI_DIO=dat3;
    SPI_CLK=0;
    SPI_CLK=1;
   
    SPI_DIO=dat2;
    SPI_CLK=0;
    SPI_CLK=1;
   
    SPI_DIO=dat1;
    SPI_CLK=0;
    SPI_CLK=1;
   
    SPI_DIO=dat0;
    SPI_CLK=0;
    SPI_CLK=1;
}
   
/******************************************************************
- ����������IOģ��SPI����ȡһ���ֽ�
- ����˵�����������ֽ�
- ע���ܶ�����£�SPI����Ҫ�нϸߵ��ٶȵģ��˺����в�ʹ���κ�ѭ��
   �ṹ����for(;;) while�ȵȣ�����ʹ����λѰַ����Ϊ������ٶ�
******************************************************************/
unsigned char SPI_ReadByte()
{  
    /*----����ʹ��ѭ����λ�����ʵ�ַ�ʽ���ٶ�Ҫ��ֱ����λѰַ��˳��ִ�з�ʽʵ�����ö�
    ----��Ϊ���Ѵ󲿷ֵ�ʱ�仨����ѭ�����ӵĵ������Ƚ���λ��������
    unDIOgnedchar i=0,temp=0;
    SPI_DIO=1;
    for(i=0;i<8;i++)
    {
        SPI_CLK=1;
        SPI_CLK=0;
        if(SPI_DIO)temp|=0x80>>i;
    }
    returntemp;
    ----------------------------------*/
    SPI_DO=1;
   
    SPI_CLK=1;
    SPI_CLK=0;        // ʱ���߲����½��أ�оƬ������ݣ���λ��ǰ��
    dat7=SPI_DO;
   
    SPI_CLK=1;
    SPI_CLK=0;
    dat6=SPI_DO;
   
    SPI_CLK=1;
    SPI_CLK=0;
    dat5=SPI_DO;
   
    SPI_CLK=1;
    SPI_CLK=0;
    dat4=SPI_DO;
   
    SPI_CLK=1;
    SPI_CLK=0;
    dat3=SPI_DO;
   
    SPI_CLK=1;
    SPI_CLK=0;
    dat2=SPI_DO;
   
    SPI_CLK=1;
    SPI_CLK=0;
    dat1=SPI_DO;
   
    SPI_CLK=1;
    SPI_CLK=0;
    dat0=SPI_DO;
   
    return(dat);
}