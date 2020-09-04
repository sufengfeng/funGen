#include "spi.h"
#include "spi_flash.h"
//*************** д������WEL��λ�� **************************** OK
void WriteEnable  (void)
{
    CS=0;
    SPI_WriteByte(W25X_WriteEnable);  
    CS=1;
}
//*************** д��ֹ����WEL��0�� ****************************  OK
void WriteDisable (void)
{
    CS=0;
    SPI_WriteByte(W25X_WriteDisable);  
    CS=1;
}
// ���ܣ���ȡW25Q16оƬ��״̬��
// ����ֵ��״̬�Ĵ��������ֽ�
// ע��W25X16�ڲ�״̬�Ĵ�����0λ=0��ʾ���У�0λ=1��ʾæ��
unsigned  char W25Q16_ReadStatus()
{
    unsigned char status=0;
    CS=0;
    SPI_WriteByte(W25X_ReadStatus);   // 0x05��ȡ״̬��������
    status=SPI_ReadByte();        // ��ȡ״̬�ֽ�
    CS=1;                         // �ر�Ƭѡ
    return status;
}  
// ���ܣ�дW25Q16оƬ��״̬�Ĵ�����
// ֻ��SPR��TB��BP2��BP1��BP0 (bit7��5��4��3��2)����д��
// ע��W25X16�ڲ�״̬�Ĵ�����0λ=0��ʾ���У�0λ=1��ʾæ��
void W25Q16_WriteStatus(unsigned  char Status)
{
    CS=0;
    SPI_WriteByte(W25X_WriteStatus);  // 0x01��ȡ״̬��������
    SPI_WriteByte(Status);            // д��һ���ֽ�
    CS=1;                         // �ر�Ƭѡ
}
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pbuf:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//Len:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!  
void W25X_Flash_Write_Page(u8* pbuf,u32  WriteAddr,u16 Len)
{
    u16 i;
    while(W25Q16_ReadStatus()&0x01);    //�ж��Ƿ�æ
   WriteEnable();                  //SET WEL
    CS=0;                            //ʹ������   
   SPI_WriteByte(W25X_Writepage);      //����дҳ����
   SPI_WriteByte((u8)((WriteAddr)>>16)); //����24bit��ַ   
   SPI_WriteByte((u8)((WriteAddr)>>8));   
   SPI_WriteByte((u8)WriteAddr);  
    for(i=0;i<Len;i++)               //ѭ��д��
    {
        SPI_WriteByte(*pbuf++);      
    }
    CS=1;                              //ȡ��Ƭѡ
    while(W25Q16_ReadStatus()&0x01);   //�ȴ�д�����   
}
//�޼���дSPI FLASH
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ����
//��ָ����ַ��ʼд��ָ�����ȵ�����
//pbuf:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//Len:Ҫд����ֽ���(���65535)
void SPI_Flash_Write_NoCheck(u8 * pbuf,u32  WriteAddr,u16 Len)
{
    u16 PageLen;                  // ҳ��д���ֽڳ���
    PageLen=256-WriteAddr%256;    // ��ҳʣ����ֽ��� ����ҳʣ��ռ䣩
    if(Len<=PageLen) PageLen=Len; // ������256 ���ֽ�
    while(1)
    {
        W25X_Flash_Write_Page(pbuf,WriteAddr,PageLen);
        if(PageLen==Len)break;   // д�������
        else
        {
            pbuf+=PageLen;
            WriteAddr+=PageLen;
            Len-=PageLen;              //  ��ȥ�Ѿ�д���˵��ֽ���
            if(Len>256)PageLen=256;   // һ�ο���д��256 ���ֽ�
            else PageLen=Len;          // ����256 ���ֽ���
        }
    }
}
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pbuf:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//Len:Ҫ��ȡ���ֽ���(���65535)
void SPI_Flash_Read(u8 * pbuf,u32 ReadAddr,u16 Len)   
{
    u16 i;  
    while(W25Q16_ReadStatus()&0x01);      // �ж��Ƿ�æ                                                     
    CS=0;                                 // ʹ������   
    SPI_WriteByte(W25X_ReadDATA8);        // ���Ͷ�ȡ����   
    SPI_WriteByte((u8)((ReadAddr)>>16));  // ����24bit��ַ   
   SPI_WriteByte((u8)((ReadAddr)>>8));   
   SPI_WriteByte((u8)ReadAddr);  
   for(i=0;i<Len;i++)
    {
       *pbuf++=SPI_ReadByte();            // ��һ���ֽ�   
    }
    CS=1;                                  // ȡ��Ƭѡ            
}  
//*************** 4K�Ȳ���************************OK
//����һ������
//Dst_Addr:������ַ 0~511 for w25x16
//����һ������������ʱ��:150ms
void W25X_SectorErase(unsigned  long Addr24) //��������ͼʾ��4KB�ռ�
{
    unsigned char Addr1;       // ��͵�ַ�ֽ�
    unsigned char Addr2;       // �м��ַ�ֽ�
    unsigned char Addr3;       // ��ߵ�ַ�ֽ�  
    Addr1=Addr24;
    Addr24=Addr24>>8;
    Addr2=Addr24;
    Addr24=Addr24>>8;
    Addr3=Addr24;                      // �ѵ�ַ����  
    while(W25Q16_ReadStatus()&0x01);   // �ж��Ƿ�æ   
    WriteEnable();                     // д����
    CS=0;
    SPI_WriteByte(W25X_S_Erase);       // ���Ȳ�������
    SPI_WriteByte(Addr3);
    SPI_WriteByte(Addr2);
    SPI_WriteByte(Addr1);
    CS=1;
    while(W25Q16_ReadStatus()&0x01);   // �ȴ��������
}
//*************** �����/64Kҳ************************* OK
void W25X_BlockErase(unsigned  long Addr24)  //��������ͼʾ��64KB�ռ�
{
    unsigned char Addr1;       // ��͵�ַ�ֽ�
    unsigned char Addr2;       // �м��ַ�ֽ�
    unsigned char Addr3;       // ��ߵ�ַ�ֽ�  
    Addr1=Addr24;
    Addr24=Addr24>>8;
    Addr2=Addr24;
    Addr24=Addr24>>8;
    Addr3=Addr24;                      // �ѵ�ַ����  
    while(W25Q16_ReadStatus()&0x01);   // �ж��Ƿ�æ   
    WriteEnable();                     // д����
    CS=0;
    SPI_WriteByte(W25X_B_Erase);       // ���Ȳ�������
    SPI_WriteByte(Addr3);
    SPI_WriteByte(Addr2);
    SPI_WriteByte(Addr1);
    CS=1;
    while(W25Q16_ReadStatus()&0x01);   // �ȴ��������
}
//**************Ƭ����  ****************** OK
// W25X16��25S     W25X32��40S   W25X64��40S
void W25X_ChipErase(void)
{
    while(W25Q16_ReadStatus()&0x01);   // �ж��Ƿ�æ   
    WriteEnable();                     // д����
    CS=0;
    SPI_WriteByte(W25X_C_Erase);       // ��Ƭ��������
    CS=1;                              // ��CS=1ʱ��ʼִ�в���
    while(W25Q16_ReadStatus()&0x01);   // �ȴ��������   
}