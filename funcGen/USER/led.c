#include "usart1.h"
#include <stdarg.h>

//3?��??��PA8o��PD2?a��?3??��.2�騺1?��?a��????����?����?��		    
//LED IO3?��??��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //��1?��PA???������?��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PA.8 ???��????
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //��?������?3?
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 GPIO_SetBits(GPIOA,GPIO_Pin_2);						 //PA.8 ��?3???
GPIO_ResetBits(GPIOA,GPIO_Pin_2);						 //PA.8 ��?3???



// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);   //��1?��PD???������?��

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 ???��????
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //��?������?3?
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
// GPIO_Init(GPIOD, &GPIO_InitStructure);	
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 ��?3??? 
}
 