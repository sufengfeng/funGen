#include "spi.h"
#include "spi_flash.h"
//*************** 写允许（将WEL置位） **************************** OK
void WriteEnable  (void)
{
    CS=0;
    SPI_WriteByte(W25X_WriteEnable);  
    CS=1;
}
//*************** 写禁止（将WEL清0） ****************************  OK
void WriteDisable (void)
{
    CS=0;
    SPI_WriteByte(W25X_WriteDisable);  
    CS=1;
}
// 功能：读取W25Q16芯片的状态。
// 返回值：状态寄存器数据字节
// 注：W25X16内部状态寄存器第0位=0表示空闲，0位=1表示忙。
unsigned  char W25Q16_ReadStatus()
{
    unsigned char status=0;
    CS=0;
    SPI_WriteByte(W25X_ReadStatus);   // 0x05读取状态的命令字
    status=SPI_ReadByte();        // 读取状态字节
    CS=1;                         // 关闭片选
    return status;
}  
// 功能：写W25Q16芯片的状态寄存器。
// 只有SPR、TB、BP2、BP1、BP0 (bit7、5、4、3、2)可以写、
// 注：W25X16内部状态寄存器第0位=0表示空闲，0位=1表示忙。
void W25Q16_WriteStatus(unsigned  char Status)
{
    CS=0;
    SPI_WriteByte(W25X_WriteStatus);  // 0x01读取状态的命令字
    SPI_WriteByte(Status);            // 写入一个字节
    CS=1;                         // 关闭片选
}
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pbuf:数据存储区
//WriteAddr:开始写入的地址(24bit)
//Len:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!  
void W25X_Flash_Write_Page(u8* pbuf,u32  WriteAddr,u16 Len)
{
    u16 i;
    while(W25Q16_ReadStatus()&0x01);    //判断是否忙
   WriteEnable();                  //SET WEL
    CS=0;                            //使能器件   
   SPI_WriteByte(W25X_Writepage);      //发送写页命令
   SPI_WriteByte((u8)((WriteAddr)>>16)); //发送24bit地址   
   SPI_WriteByte((u8)((WriteAddr)>>8));   
   SPI_WriteByte((u8)WriteAddr);  
    for(i=0;i<Len;i++)               //循环写数
    {
        SPI_WriteByte(*pbuf++);      
    }
    CS=1;                              //取消片选
    while(W25Q16_ReadStatus()&0x01);   //等待写入结束   
}
//无检验写SPI FLASH
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能
//在指定地址开始写入指定长度的数据
//pbuf:数据存储区
//WriteAddr:开始写入的地址(24bit)
//Len:要写入的字节数(最大65535)
void SPI_Flash_Write_NoCheck(u8 * pbuf,u32  WriteAddr,u16 Len)
{
    u16 PageLen;                  // 页内写入字节长度
    PageLen=256-WriteAddr%256;    // 单页剩余的字节数 （单页剩余空间）
    if(Len<=PageLen) PageLen=Len; // 不大于256 个字节
    while(1)
    {
        W25X_Flash_Write_Page(pbuf,WriteAddr,PageLen);
        if(PageLen==Len)break;   // 写入结束了
        else
        {
            pbuf+=PageLen;
            WriteAddr+=PageLen;
            Len-=PageLen;              //  减去已经写入了的字节数
            if(Len>256)PageLen=256;   // 一次可以写入256 个字节
            else PageLen=Len;          // 不够256 个字节了
        }
    }
}
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pbuf:数据存储区
//ReadAddr:开始读取的地址(24bit)
//Len:要读取的字节数(最大65535)
void SPI_Flash_Read(u8 * pbuf,u32 ReadAddr,u16 Len)   
{
    u16 i;  
    while(W25Q16_ReadStatus()&0x01);      // 判断是否忙                                                     
    CS=0;                                 // 使能器件   
    SPI_WriteByte(W25X_ReadDATA8);        // 发送读取命令   
    SPI_WriteByte((u8)((ReadAddr)>>16));  // 发送24bit地址   
   SPI_WriteByte((u8)((ReadAddr)>>8));   
   SPI_WriteByte((u8)ReadAddr);  
   for(i=0;i<Len;i++)
    {
       *pbuf++=SPI_ReadByte();            // 读一个字节   
    }
    CS=1;                                  // 取消片选            
}  
//*************** 4K扇擦除************************OK
//擦除一个扇区
//Dst_Addr:扇区地址 0~511 for w25x16
//擦除一个扇区的最少时间:150ms
void W25X_SectorErase(unsigned  long Addr24) //擦除资料图示的4KB空间
{
    unsigned char Addr1;       // 最低地址字节
    unsigned char Addr2;       // 中间地址字节
    unsigned char Addr3;       // 最高地址字节  
    Addr1=Addr24;
    Addr24=Addr24>>8;
    Addr2=Addr24;
    Addr24=Addr24>>8;
    Addr3=Addr24;                      // 把地址拆开来  
    while(W25Q16_ReadStatus()&0x01);   // 判断是否忙   
    WriteEnable();                     // 写允许
    CS=0;
    SPI_WriteByte(W25X_S_Erase);       // 整扇擦除命令
    SPI_WriteByte(Addr3);
    SPI_WriteByte(Addr2);
    SPI_WriteByte(Addr1);
    CS=1;
    while(W25Q16_ReadStatus()&0x01);   // 等待擦除完成
}
//*************** 块擦除/64K页************************* OK
void W25X_BlockErase(unsigned  long Addr24)  //擦除资料图示的64KB空间
{
    unsigned char Addr1;       // 最低地址字节
    unsigned char Addr2;       // 中间地址字节
    unsigned char Addr3;       // 最高地址字节  
    Addr1=Addr24;
    Addr24=Addr24>>8;
    Addr2=Addr24;
    Addr24=Addr24>>8;
    Addr3=Addr24;                      // 把地址拆开来  
    while(W25Q16_ReadStatus()&0x01);   // 判断是否忙   
    WriteEnable();                     // 写允许
    CS=0;
    SPI_WriteByte(W25X_B_Erase);       // 整扇擦除命令
    SPI_WriteByte(Addr3);
    SPI_WriteByte(Addr2);
    SPI_WriteByte(Addr1);
    CS=1;
    while(W25Q16_ReadStatus()&0x01);   // 等待擦除完成
}
//**************片擦除  ****************** OK
// W25X16：25S     W25X32：40S   W25X64：40S
void W25X_ChipErase(void)
{
    while(W25Q16_ReadStatus()&0x01);   // 判断是否忙   
    WriteEnable();                     // 写允许
    CS=0;
    SPI_WriteByte(W25X_C_Erase);       // 整片擦除命令
    CS=1;                              // 从CS=1时开始执行擦除
    while(W25Q16_ReadStatus()&0x01);   // 等待擦除完成   
}