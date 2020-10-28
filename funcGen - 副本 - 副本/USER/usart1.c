/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：usart1.c
 * 描述    ：将printf函数重定向到USART1。这样就可以用printf函数将单片机的数据
 *           打印到PC上的超级终端或串口调试助手。         

 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------

**********************************************************************************/

#include "global.h"

void usart1_send_byte(uint8_t byte)	//用于液晶屏
{
	USART_SendData(USART1, byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //详见英文参考的521页，当TXE被置起时，一帧数据传输完成 
}
//配置UART1接收中断
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
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

	//USART1 初始化设置
	USART_InitStructure.USART_BaudRate = 115200;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
}

int fputc(int ch,FILE *f)
{
    USART1->SR;  //USART_GetFlagStatus(USART1, USART_FLAG_TC) 解决第一个字符发送失败的问题
    //一个一个发送字符
    USART_SendData(USART1, (unsigned char) ch);
    //等待发送完成
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
//#define PC_RECEIVE_UART USART3				//临时测试用串口四


uint16_t data_length;	//记录数据长度
/*-----------------------------------------------------------------------------*/
//中断接收，数据放到缓冲区
//没有超时处理，有待完善
void PC_receive(void)
{
	uint8_t temp;
	temp=USART_ReceiveData(PC_RECEIVE_UART);
	printf( "%c", temp );    //返回打印			
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
				LOG(LOG_ERR,"PC接收数据错误，current step :%d 接收数据为%d",receive_step,temp);				
				receive_step=1;
			}
			break;
		case 4:
			if (temp==HEAD03)
			{
				receive_step=5;
				data_length=4;		//接收4字节标志和长度数据
				receive_count=0;
			}
			else
			{
				LOG(LOG_ERR,"PC接收数据错误，current step :%d 接收数据为%d",receive_step,temp);				
				receive_step=1;
			}
			break;
		case 5:				//长度H
			pc_buf[receive_count]=temp;
			receive_count++;
			if (receive_count>=data_length)
			{
				
				g_WaveID=pc_buf[0]&0x0F;		//接收4字节标志和长度数据
				g_WaveID=g_WaveID+(pc_buf[1]>>4);
				
				data_length = pc_buf[1] &0x0F;
				data_length = data_length +(pc_buf[2]>>4);
				data_length=data_length*3;
				
				receive_count=0;
				receive_step=8;
			}
			
		case 7:				//长度L
				receive_step=1;
			break;
		case 8:		//接收固定长度的数据
			pc_buf[receive_count]=temp;
			receive_count++;
			if (receive_count>=data_length)
			{
				pc_flag=1;
				receive_step=1;
				LOG(LOG_INFO,"接收到数据");				
			}
			break;
		default :
			receive_step=1;
			LOG(LOG_ERR,"PC接收数据错误，current step :%d 接收数据为%d",receive_step,temp);				
			break;
	}
}
//主循环处理接收到的数据
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
      
			ch = USART_ReceiveData(USART1);     //接受数据
			printf( "%c", ch );    //返回打印
//			PC_receive();

			/* Clear the USART1 Receive interrupt */  
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);  
        
    } 
}

//重定向scanf函数到USART1
int fgetc(FILE *f)
{
        /*等待串口1输入数据*/
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

        return (int)USART_ReceiveData(USART1);
}
