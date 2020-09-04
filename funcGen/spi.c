
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
unsigned char bdata dat; //dat是可位寻址的变量
sbit dat7=dat^7;
sbit dat6=dat^6;
sbit dat5=dat^5;
sbit dat4=dat^4;
sbit dat3=dat^3;
sbit dat2=dat^2;
sbit dat1=dat^1;
sbit dat0=dat^0;            // 取出dat的各个位
/******************************************************************
- 功能描述：IO模拟SPI，发送一个字节
- 参数说明：x:要发送的字节
- 注：很多情况下，SPI是需要有较高的速度的，此函数中不使用任何循环
       结构，如for(;;) while等等，并且使用了位寻址就是为了提高速度
******************************************************************/
void SPI_WriteByte(unsigned char x)
{
/*----这种使用循环与位运算的实现方式，速度要比直接用位寻址与顺序执行方式实现慢得多
----因为它把大部分的时间花在了循环因子的递增、比较与位运行上了
    unDIOgnedchar i=0;
    for(i=0;i<8;i++)
    {
        SPI_DIO=x&(0x80>>i);
        SPI_CLK=0;
        SPI_CLK=1;
    }
----------------------------------*/  
    dat=x;        // 将x的值赋给可位寻址的变量dat，以便取出各个位
        
    SPI_DIO=dat7;   // 取出第7个位，写到数据线上   （高位在前）
    SPI_CLK=0;
    SPI_CLK=1;     // 时钟线产生上升沿，数据被写入
   
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
- 功能描述：IO模拟SPI，读取一个字节
- 返回说明：读到的字节
- 注：很多情况下，SPI是需要有较高的速度的，此函数中不使用任何循环
   结构，如for(;;) while等等，并且使用了位寻址就是为了提高速度
******************************************************************/
unsigned char SPI_ReadByte()
{  
    /*----这种使用循环与位运算的实现方式，速度要比直接用位寻址与顺序执行方式实现慢得多
    ----因为它把大部分的时间花在了循环因子的递增、比较与位运行上了
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
    SPI_CLK=0;        // 时钟线产生下降沿，芯片输出数据（高位在前）
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