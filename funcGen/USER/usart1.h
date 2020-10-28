#ifndef __USART1_H
#define	__USART1_H

#include "global.h"

//uart01########################################���ͷ�ļ�
void USART1_Config(void);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void process_uart1(void );
//led########################################���ͷ�ļ�
void LED_Init(void);
//########################################��ʱ�����ͷ�ļ�
void Timerx_Init(u16 arr,u16 psc);

//########################################uart3���ͷ�ļ�
void uart3_send_byte(uint8_t byte);	//����Һ����

//########################################��ʱ�����ͷ�ļ�
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
//����delay_us,delay_ms
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void usart1_send_byte(uint8_t byte);
#endif /* __USART1_H */
