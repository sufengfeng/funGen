/*-----------------------------------------------------------------------------------*/
//�ļ�����	MINI_DGUS.H
//���ߣ�	κ����
//ʱ�䣺	2016.05.11
//�汾��	v1.0
//˵����	DGUS������������Ĵ�����ַ�������ļ�
/*-----------------------------------------------------------------------------------*/


#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "stdint.h"
#include "main.h"

#define HEAD0		0X5A		//������
#define HEAD1		0XA5		//������

#define LCD_COM_LEN		(250)		//������ͨ�Ż���������
#define LCD_DATA_ADDL	(0X0000)	//��������ַ��Χ	˫�ֽڷ���	32KByte
#define LCD_DATA_ADDH	(0X6FFF)	//

#define LCD_PIC_NUM		(384)		//���384��ͼƬ
#define LCD_LINE_NUM	(4)			//���4��������ʾ
/*--------------�����--------------*/

#define LCD_WR	0X80
#define LCD_RR	0X81

#define LCD_WD	0X82
#define LCD_RD	0X83

#define LCD_WL	0X84

/*------------�Ĵ�����ַ����-----------*/
//ϵͳ����
#define LCD_VERSION	0X00	//BCD CODE
#define LCD_NOW		0X01	//LCD LIGHT	0X00-->0X40
#define BZ_TIME		0X02	//BEEP TIME	/10ms
//���в���
#define PIC_ID		0X03	//2Byte
#define TP_FLAG		0X05	//0X5A-->FRESHED	OTHERS-->NON
#define TP_STA		0X06	//0X01-->1ST PUSH	0X02-->RELEASE	0X03-->PUSHING
#define TP_EN		0X07	//0X00-->TOUCH OFF	OTHERS-->TOUCH ON	

//SD�����üĴ���ӳ��
#define LCD_R0		0X10	//RO
#define LCD_R1		0X11	//RO
#define LCD_R2		0X12	//RW	SYS_CFG��0X00-->200ms	0X01-->160ms	0X02-->120ms	0X03-->80ms
#define LCD_R3		0X13	//RO
#define LCD_R4		0X14	//RO
#define LCD_R5		0X15	//RO
#define LCD_R6		0X16	//RO
#define LCD_R7		0X17	//RO
#define LCD_R8		0X18	//RO
#define LCD_R9		0X19	//RO
#define LCD_RA		0X1A	//RO

//RTC	16Byete
#define LCD_RTC		0X20	//YY:MM:DD:HH:MM:SS

//�û�����
#define KEY_CODE	0X4F	//0X01-->0XFF

//������߻�����
#define LINE_CLR	0XEB	//0X5A-->LINE0	0X5B-->LINE1

//����ˢ��ģʽ
#define FAST_REF	0XEC	//0X5A-->FAST	0X00-->NORMAL	FAST_MODE-->RR = 0X5C

/*-----------------------------------------------------------------------------*/
//��ť��ַ����
#define BUTTON_OP		0X0000
// #define BUTTON_SET		0X0200
#define BUTTON_SMOT		0X0050
#define BUTTON_DMOT		0X0040
#define BUTTON_TEST		0X0500
#define BUTTON_NUM		0X1000


//ͼ���ַ
// #define ADDR_MC_STATE	0X0017 
// #define ADDR_COM_STATE	0X0018 
#define ADDR_SEN_BASE	0X0300 		//������ͼ���ַ

//������ʾ��ַ
#define ADDR_CASH_TYEP	0X0010 		//���н�������
#define ADDR_TOTAL_NUM	0X0011 
#define ADDR_ATM_NUM	0X0012 
#define ADDR_LTC_NUM	0X0013
#define ADDR_CSC_NUM	0X0014 
#define ADDR_INK_VAL	0X0015

#define ADDR_STATE_TEXT	0X0100
#define ADDR_COM_TEXT	0X0140

#define ADDR_DEVICE_ADDR	0X0021	//���ý������� 
#define ADDR_IP_ADDR0	0X0022		//IP��ַ
#define ADDR_IP_ADDR1	0X0023		//
#define ADDR_IP_ADDR2	0X0024		//
#define ADDR_IP_ADDR3	0X0025		//
#define ADDR_CODE_EN	0X0026 		//0-OFF	1-ON
#define ADDR_ZB_POS		0X0027 		//0-OFF	1-ON
#define ADDR_CASH_VAL	0X0028		//
#define ADDR_MODE_VAL	0X0029		//0-JL900	1-OKI	2-JLK4 	

#define ADDR_VERSION	0X0030		//����汾

#define ADDR_ERR_TEXT1	0X1100		//���Ͻ�������
#define ADDR_ERR_TEXT2	0X1140

//ҳ���ַ
#define PIC_START		0 	//0X00
#define PIC_RUN			10 	//0X0A
#define PIC_HOME		11 	//0X0B
#define PIC_SET1		20 	//0X14
#define PIC_SENSOR		30 	//0X1E
#define PIC_DEBUG1		40 	//0X28
#define PIC_TEST		50 	//0X32
#define PIC_ERR			110 //0X6E
#define PIC_DOC			120 //0X78

//��ť��ֵ����	�����л�ҳ������ݱ���	����ֵ���л�ҳ��

#define VAL_ENTER		0X00FF 
#define VAL_RESET		0XFFFF 

//���ּ��̼�ֵ
// #define VAL_ESC			0X00F0 
// #define VAL_OK			0X0D0D 
// #define VAL_0			0X0000 
// #define VAL_1			0X0001 
// #define VAL_2			0X0002 
// #define VAL_3			0X0003 
// #define VAL_4			0X0004 
// #define VAL_5			0X0005 
// #define VAL_6			0X0006 
// #define VAL_7`			0X0007 
// #define VAL_8			0X0008 
// #define VAL_9			0X0009 

//������Ƽ�ֵ
#define VAL_MOT_TRAN1	0X0050		//�´�����
#define VAL_MOT_RISE1	0X0051		//�������
#define VAL_MOT_MOVE	0X0052		//���Ƶ��
#define VAL_MOT_TRAN2	0X0053		//�������벿������
#define VAL_MOT_TRAN3	0X0054		//����������
#define VAL_DCT			0X0055		//���ҵ����

#define VAL_MOT_RISE2_BACKWARD		0X0040	//���¶������
#define VAL_MOT_RISE2_FORWARD		0X0041	
#define VAL_MOT_PRINT_BACKWARD		0X0042	//��ӡ���
#define VAL_MOT_PRINT_FORWARD		0X0043	
#define VAL_MOT_PRPOS_BACKWARD		0X0044	//��ӡ��λ���
#define VAL_MOT_PRPOS_FORWARD		0X0045	
#define VAL_MOT_CASHPOS_BACKWARD	0X0046	//�ѱҶ�λ���
#define VAL_MOT_CASHPOS_FORWARD		0X0047	
#define VAL_MOT_RISE3_BACKWARD		0X0048	//���������
#define VAL_MOT_RISE3_FORWARD		0X0049	

//���԰�ť��ֵ
#define VAL_TEST1		0X0001 	//�´������
#define VAL_TEST2		0X0002 	//�����������
#define VAL_TEST3		0X0003 	//�������ܲ���
#define VAL_TEST4		0X0004 	//��ӡ����ϴ



/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
//Һ�������ݷ���
typedef struct 
{
	uint16_t data;
	uint16_t num;
	uint16_t addr;
	
}LCD_DATA;

/*-----------------------------------------------------------------------------*/

extern void lcd_showpic(uint16_t num);
extern void lcd_sendword(uint16_t addr,uint16_t data);
extern void lcd_sendhz(uint16_t addr,uint8_t *str);
extern void lcd_clearhz(uint16_t addr);

extern void lcd_receive(void);
extern void lcd_getdata(LCD_DATA *lcd);
extern uint16_t lcd_readword(uint16_t addr);

/*-----------------------------------------------------------------------------*/




#endif

/*-----------------------------end----------------------------------------------------*/
