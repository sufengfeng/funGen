/*-----------------------------------------------------------------------------------*/
//文件名：	MINI_DGUS.H
//作者：	魏开林
//时间：	2016.05.11
//版本：	v1.0
//说明：	DGUS串口屏的命令、寄存器地址等描述文件
/*-----------------------------------------------------------------------------------*/


#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "stdint.h"
#include "main.h"

#define HEAD0		0X5A		//串口屏
#define HEAD1		0XA5		//串口屏

#define LCD_COM_LEN		(250)		//串口屏通信缓冲区长度
#define LCD_DATA_ADDL	(0X0000)	//变量区地址范围	双字节访问	32KByte
#define LCD_DATA_ADDH	(0X6FFF)	//

#define LCD_PIC_NUM		(384)		//最多384幅图片
#define LCD_LINE_NUM	(4)			//最多4条曲线显示
/*--------------命令定义--------------*/

#define LCD_WR	0X80
#define LCD_RR	0X81

#define LCD_WD	0X82
#define LCD_RD	0X83

#define LCD_WL	0X84

/*------------寄存器地址定义-----------*/
//系统参数
#define LCD_VERSION	0X00	//BCD CODE
#define LCD_NOW		0X01	//LCD LIGHT	0X00-->0X40
#define BZ_TIME		0X02	//BEEP TIME	/10ms
//运行参数
#define PIC_ID		0X03	//2Byte
#define TP_FLAG		0X05	//0X5A-->FRESHED	OTHERS-->NON
#define TP_STA		0X06	//0X01-->1ST PUSH	0X02-->RELEASE	0X03-->PUSHING
#define TP_EN		0X07	//0X00-->TOUCH OFF	OTHERS-->TOUCH ON	

//SD卡配置寄存器映射
#define LCD_R0		0X10	//RO
#define LCD_R1		0X11	//RO
#define LCD_R2		0X12	//RW	SYS_CFG：0X00-->200ms	0X01-->160ms	0X02-->120ms	0X03-->80ms
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

//用户键码
#define KEY_CODE	0X4F	//0X01-->0XFF

//清除曲线缓冲区
#define LINE_CLR	0XEB	//0X5A-->LINE0	0X5B-->LINE1

//快速刷新模式
#define FAST_REF	0XEC	//0X5A-->FAST	0X00-->NORMAL	FAST_MODE-->RR = 0X5C

/*-----------------------------------------------------------------------------*/
//按钮地址分类
#define BUTTON_OP		0X0000
// #define BUTTON_SET		0X0200
#define BUTTON_SMOT		0X0050
#define BUTTON_DMOT		0X0040
#define BUTTON_TEST		0X0500
#define BUTTON_NUM		0X1000


//图标地址
// #define ADDR_MC_STATE	0X0017 
// #define ADDR_COM_STATE	0X0018 
#define ADDR_SEN_BASE	0X0300 		//传感器图标基址

//变量显示地址
#define ADDR_CASH_TYEP	0X0010 		//运行界面数据
#define ADDR_TOTAL_NUM	0X0011 
#define ADDR_ATM_NUM	0X0012 
#define ADDR_LTC_NUM	0X0013
#define ADDR_CSC_NUM	0X0014 
#define ADDR_INK_VAL	0X0015

#define ADDR_STATE_TEXT	0X0100
#define ADDR_COM_TEXT	0X0140

#define ADDR_DEVICE_ADDR	0X0021	//设置界面数据 
#define ADDR_IP_ADDR0	0X0022		//IP基址
#define ADDR_IP_ADDR1	0X0023		//
#define ADDR_IP_ADDR2	0X0024		//
#define ADDR_IP_ADDR3	0X0025		//
#define ADDR_CODE_EN	0X0026 		//0-OFF	1-ON
#define ADDR_ZB_POS		0X0027 		//0-OFF	1-ON
#define ADDR_CASH_VAL	0X0028		//
#define ADDR_MODE_VAL	0X0029		//0-JL900	1-OKI	2-JLK4 	

#define ADDR_VERSION	0X0030		//软件版本

#define ADDR_ERR_TEXT1	0X1100		//故障界面数据
#define ADDR_ERR_TEXT2	0X1140

//页面地址
#define PIC_START		0 	//0X00
#define PIC_RUN			10 	//0X0A
#define PIC_HOME		11 	//0X0B
#define PIC_SET1		20 	//0X14
#define PIC_SENSOR		30 	//0X1E
#define PIC_DEBUG1		40 	//0X28
#define PIC_TEST		50 	//0X32
#define PIC_ERR			110 //0X6E
#define PIC_DOC			120 //0X78

//按钮键值分类	用于切换页面和数据保存	返回值即切换页面

#define VAL_ENTER		0X00FF 
#define VAL_RESET		0XFFFF 

//数字键盘键值
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

//电机控制键值
#define VAL_MOT_TRAN1	0X0050		//下传输电机
#define VAL_MOT_RISE1	0X0051		//顶升电机
#define VAL_MOT_MOVE	0X0052		//横移电机
#define VAL_MOT_TRAN2	0X0053		//盖章喷码部传输电机
#define VAL_MOT_TRAN3	0X0054		//提升传输电机
#define VAL_DCT			0X0055		//挡币电磁铁

#define VAL_MOT_RISE2_BACKWARD		0X0040	//盖章顶升电机
#define VAL_MOT_RISE2_FORWARD		0X0041	
#define VAL_MOT_PRINT_BACKWARD		0X0042	//打印电机
#define VAL_MOT_PRINT_FORWARD		0X0043	
#define VAL_MOT_PRPOS_BACKWARD		0X0044	//打印定位电机
#define VAL_MOT_PRPOS_FORWARD		0X0045	
#define VAL_MOT_CASHPOS_BACKWARD	0X0046	//把币定位电机
#define VAL_MOT_CASHPOS_FORWARD		0X0047	
#define VAL_MOT_RISE3_BACKWARD		0X0048	//提升机电机
#define VAL_MOT_RISE3_FORWARD		0X0049	

//测试按钮键值
#define VAL_TEST1		0X0001 	//下传输测试
#define VAL_TEST2		0X0002 	//盖章喷码测试
#define VAL_TEST3		0X0003 	//提升功能测试
#define VAL_TEST4		0X0004 	//打印机清洗



/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
//液晶屏数据返回
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
