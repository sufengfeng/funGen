/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ������ 2M����flash���ԣ�����������Ϣͨ������1�ڵ��Եĳ����ն��д�ӡ������         

**********************************************************************************/
#include "global.h"

// ����ԭ������
void Delay(__IO uint32_t nCount);

void usart3_init(u32 bound);
/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 	
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init(72);	     //��ʱ��ʼ��
	/* ���ô���1Ϊ��115200 8-N-1 */
	USART1_Config();
	
	LED_Init();
	Timerx_Init(5000,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	usart3_init(115200);
//	uint8_t tmpStr[]="��ʼ���ɹ�";
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
