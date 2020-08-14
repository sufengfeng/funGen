//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P1^4（SCL）
//              D1   P1^3（SDA）
//              RES  接P12
//              DC   接P11
//              CS   接P10               
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018/3/16
//All rights reserved
//******************************************************************************/
//******************************************************************************/
#include "REG51.h"
#include "oled.h"
#include "bmp.h"



void Delay1ms()		//@24.000MHz
{
	unsigned char i, j;

	i = 24;
	j = 85;
	do
	{
		while (--j);
	} while (--i);
}
void DelayNms(unsigned int N){
	
	while(N--){
		Delay1ms();
	}
}

//extern void LED_BLINK(void);
 int main(void)
 {	u8 t;
	OLED_Init();			//初始化OLED  
	oled_show_two();	//显示
	Timer0_init();
	
	GPIO_config();
	UartInit();			//调试串口具有最高优先级
	EA = 1;					//打开总中断
	while(1) 
	{			
		SendString("running...\r\n");
		DelayNms(500);
	}	  
	
}


