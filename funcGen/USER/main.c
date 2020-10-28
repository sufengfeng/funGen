/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：华邦 2M串行flash测试，并将测试信息通过串口1在电脑的超级终端中打印出来。         

**********************************************************************************/
#include "global.h"

// 函数原型声明
void Delay(__IO uint32_t nCount);

void usart3_init(u32 bound);
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{ 	
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init(72);	     //延时初始化
	/* 配置串口1为：115200 8-N-1 */
	USART1_Config();
	
	LED_Init();
	Timerx_Init(5000,7199);//10Khz的计数频率，计数到5000为500ms 
	usart3_init(115200);
//	uint8_t tmpStr[]="初始化成功";
//	
//	for(int i=0;i<sizeof(tmpStr);i++){
//		uart3_send_byte(tmpStr[i]);	
//	}
	GetWaveType(&g_allWaveType);
	LOG(LOG_INFO,"g_allWaveType.counter:%d",g_allWaveType.counter);
	while(1){
		Delay(20000000);
		
//		LOG(LOG_INFO,"running");
		process_uart1();
	}		
}


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
