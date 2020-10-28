#include "usart1.h"
#include <stdarg.h>

//3?那??‘PA8o赤PD2?a那?3??迆.2⊿那1?邦?a芍????迆米?那㊣?車		    
//LED IO3?那??‘
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //那1?邦PA???迆那㊣?車
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PA.8 ???迆????
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //赤?赤足那?3?
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 GPIO_SetBits(GPIOA,GPIO_Pin_2);						 //PA.8 那?3???
GPIO_ResetBits(GPIOA,GPIO_Pin_2);						 //PA.8 那?3???



// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);   //那1?邦PD???迆那㊣?車

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 ???迆????
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //赤?赤足那?3?
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
// GPIO_Init(GPIOD, &GPIO_InitStructure);	
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 那?3??? 
}
 