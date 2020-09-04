#ifndef __SPI_FLASH_H
#define  __SPI_FLASH_H

#include	"config.h"
#include<intrins.h>  // 包含位移和_nop_();
    sbit CS    = P1^2;    // 片选     
    #define u8 unsigned char
    #define u16 unsigned int
    #define u32 unsigned long
    #define W25X_ReadStatus       0x05      //读状态寄存器
    #define W25X_WriteStatus      0x01      //写状态寄存器
    #define W25X_ReadDATA8        0x03      //普读_数据
    #define W25X_FastRead         0x0B      //快读_数据
    #define W25X_DualOutput       0x3B      //快读_双输出
    #define W25X_Writepage        0x02      //写_数据_0~255个字节
    #define W25X_S_Erase          0x20      //扇区擦除4KB
    #define W25X_B_Erase          0xD8      //块区擦除64KB
    #define W25X_C_Erase          0xC7      //整片格式化
    #define W25X_PowerDown        0xB9      //待机
    #define W25X_PowerON_ID       0xAB      //开机或是读ID
    #define W25X_JEDEC_ID         0x9F      //十六位的JEDEC_ID
    #define W25X_WriteEnable      0x06      //写允许
    #define W25X_WriteDisable     0x04      //写禁止
   
    void W25X_SectorErase(unsigned long Addre24);   //擦除资料图示的4KB空间
    void SPI_Flash_Write_NoCheck(u8 * pbuf,u32 WriteAddr,u16 Len);
    void SPI_Flash_Read(u8* pbuf,u32 ReadAddr,u16 Len) ;
		

#endif /* __SPI_FLASH_H */

