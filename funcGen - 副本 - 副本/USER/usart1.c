/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��usart1.c
 * ����    ����printf�����ض���USART1�������Ϳ�����printf��������Ƭ��������
 *           ��ӡ��PC�ϵĳ����ն˻򴮿ڵ������֡�         

 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------

**********************************************************************************/

#include "global.h"

void usart1_send_byte(uint8_t byte)	//����Һ����
{
	USART_SendData(USART1, byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //���Ӣ�Ĳο���521ҳ����TXE������ʱ��һ֡���ݴ������ 
}
//����UART1�����ж�
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    
    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;     
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART1_Config(void)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //�������PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ��ʼ����������IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //��������PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* ��ʼ��GPIO */
	

	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
}

int fputc(int ch,FILE *f)
{
    USART1->SR;  //USART_GetFlagStatus(USART1, USART_FLAG_TC) �����һ���ַ�����ʧ�ܵ�����
    //һ��һ�������ַ�
    USART_SendData(USART1, (unsigned char) ch);
    //�ȴ��������
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    
    return(ch);
}

#define PC_COM_LEN 4096
static uint16_t receive_count = 0;
static uint8_t pc_buf[PC_COM_LEN];
static uint8_t pc_flag = 0;

static uint16_t receive_step  = 1;

#define HEAD01 0xFF
#define HEAD02 0xFF
#define HEAD03 0xFE
#define PC_RECEIVE_UART USART1
//#define PC_RECEIVE_UART USART3				//��ʱ�����ô�����


uint16_t data_length;	//��¼���ݳ���
/*-----------------------------------------------------------------------------*/
//�жϽ��գ����ݷŵ�������
//û�г�ʱ�����д�����
void PC_receive(void)
{
	uint8_t temp;
	temp=USART_ReceiveData(PC_RECEIVE_UART);
	printf( "%c", temp );    //���ش�ӡ			
	return ;
	switch(receive_step)
	{
		case 1:
			if (temp==HEAD01)
			{
				receive_step=3;			
			}
			break;
		case 3:
			if (temp==HEAD02)
			{
				receive_step=4;
			}
			else
			{
				LOG(LOG_ERR,"PC�������ݴ���current step :%d ��������Ϊ%d",receive_step,temp);				
				receive_step=1;
			}
			break;
		case 4:
			if (temp==HEAD03)
			{
				receive_step=5;
				data_length=4;		//����4�ֽڱ�־�ͳ�������
				receive_count=0;
			}
			else
			{
				LOG(LOG_ERR,"PC�������ݴ���current step :%d ��������Ϊ%d",receive_step,temp);				
				receive_step=1;
			}
			break;
		case 5:				//����H
			pc_buf[receive_count]=temp;
			receive_count++;
			if (receive_count>=data_length)
			{
				
				g_WaveID=pc_buf[0]&0x0F;		//����4�ֽڱ�־�ͳ�������
				g_WaveID=g_WaveID+(pc_buf[1]>>4);
				
				data_length = pc_buf[1] &0x0F;
				data_length = data_length +(pc_buf[2]>>4);
				data_length=data_length*3;
				
				receive_count=0;
				receive_step=8;
			}
			
		case 7:				//����L
				receive_step=1;
			break;
		case 8:		//���չ̶����ȵ�����
			pc_buf[receive_count]=temp;
			receive_count++;
			if (receive_count>=data_length)
			{
				pc_flag=1;
				receive_step=1;
				LOG(LOG_INFO,"���յ�����");				
			}
			break;
		default :
			receive_step=1;
			LOG(LOG_ERR,"PC�������ݴ���current step :%d ��������Ϊ%d",receive_step,temp);				
			break;
	}
}
//��ѭ��������յ�������
void process_uart1(void ){
	if(pc_flag){
		pc_flag=0;
		
	}
	
}

uint8_t ch;
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {     
      
			ch = USART_ReceiveData(USART1);     //��������
			printf( "%c", ch );    //���ش�ӡ
//			PC_receive();

			/* Clear the USART1 Receive interrupt */  
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);  
        
    } 
}

//�ض���scanf������USART1
int fgetc(FILE *f)
{
        /*�ȴ�����1��������*/
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

        return (int)USART_ReceiveData(USART1);
}
