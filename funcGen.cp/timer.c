
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

/*************	功能说明	**************

本程序演示3个定时器的使用, 本例程均使用16位自动重装.

下载时, 选择时钟 24MHZ (用户可自行修改频率).

定时器0做16位自动重装, 中断频率为1000HZ，中断函数从P1.7取反输出500HZ方波信号.

定时器1做16位自动重装, 中断频率为2000HZ，中断函数从P1.6取反输出1000HZ方波信号.

定时器2做16位自动重装, 中断频率为3000HZ，中断函数从P4.7取反输出1500HZ方波信号.

******************************************/


#define 	MAIN_Fosc		24000000UL	//定义主时钟

#include	"STC15Fxxxx.H"

#define	Timer0_Reload	(MAIN_Fosc / 100000)		//Timer 0 中断频率, 1000次/秒




//========================================================================
// 函数: void	Timer0_init(void)
// 描述: timer0初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void	Timer0_init(void)
{
		TR0 = 0;	//停止计数

	#if (Timer0_Reload < 64)	// 如果用户设置值不合适， 则不启动定时器
		#error "Timer0设置的中断过快!"

	#elif ((Timer0_Reload/12) < 65536UL)	// 如果用户设置值不合适， 则不启动定时器
		ET0 = 1;	//允许中断
	//	PT0 = 1;	//高优先级中断
		TMOD &= ~0x03;
		TMOD |= 0;	//工作模式, 0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
	//	TMOD |=  0x04;	//对外计数或分频
		TMOD &= ~0x04;	//定时
	//	INT_CLKO |=  0x01;	//输出时钟
		INT_CLKO &= ~0x01;	//不输出时钟

		#if (Timer0_Reload < 65536UL)
			AUXR |=  0x80;	//1T mode
			TH0 = (u8)((65536UL - Timer0_Reload) / 256);
			TL0 = (u8)((65536UL - Timer0_Reload) % 256);
		#else
			AUXR &= ~0x80;	//12T mode
			TH0 = (u8)((65536UL - Timer0_Reload/12) / 256);
			TL0 = (u8)((65536UL - Timer0_Reload/12) % 256);
		#endif

		TR0 = 1;	//开始运行

	#else
		#error "Timer0设置的中断过慢!"
	#endif
}
void LED_BLINK(void);
void SendString(char *s);
/*
func:10us定时器,用于中断性周期任务

*/
void timer0_int (void) interrupt TIMER0_VECTOR
{
	{	//	系统正常运行
		static unsigned long counter=0;
		counter++;
		if(counter>100000){		//1s定时器
			LED_BLINK();				
			counter=0;
		}
	
	}
}
