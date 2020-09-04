
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

    
#include<intrins.h>      // ����λ�ƺ�_nop_();           
sbit SPI_DIO   = P1^4;    // ֻ������ (��Ƭ�� TO оƬ)
sbit SPI_DO    = P1^3;    // ���     (оƬ TO ��Ƭ��)
sbit SPI_CLK   = P1^5;    // ʱ��
// Ƭѡ����W25Q16.H���壬W25Q16.C����
void SPI_WriteByte(unsigned char x);      // ��ȡ״̬��������
unsigned char SPI_ReadByte();             // ��ȡ״̬�ֽ�

#endif

