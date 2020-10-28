#ifndef __USART1_H
#define	__USART1_H

#include "global.h"

//uart01########################################相关头文件
void USART1_Config(void);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void process_uart1(void );
//led########################################相关头文件
void LED_Init(void);
//########################################定时器相关头文件
void Timerx_Init(u16 arr,u16 psc);

//########################################uart3相关头文件
void uart3_send_byte(uint8_t byte);	//用于液晶屏

//########################################定时器相关头文件
//使用SysTick的普通计数模式对延迟进行管理
//包括delay_us,delay_ms
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void usart1_send_byte(uint8_t byte);
#endif /* __USART1_H */
