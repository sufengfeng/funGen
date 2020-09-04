
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


#ifndef	__SPI_H
#define	__SPI_H

#include	"config.h"

    
#include<intrins.h>      // 包含位移和_nop_();           
sbit SPI_DIO   = P1^4;    // 只作输入 (单片机 TO 芯片)
sbit SPI_DO    = P1^3;    // 输出     (芯片 TO 单片机)
sbit SPI_CLK   = P1^5;    // 时钟
// 片选脚由W25Q16.H定义，W25Q16.C控制
void SPI_WriteByte(unsigned char x);      // 读取状态的命令字
unsigned char SPI_ReadByte();             // 读取状态字节

#endif

