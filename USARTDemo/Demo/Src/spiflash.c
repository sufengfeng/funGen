
#include "main.h"
#include "spi.h"




/* 读ID */
void ReadID(void)
{
	/* W25Q64的指令 */
uint8_t w25x_read_id = 0x90;					// 读ID


	uint8_t temp_ID[5] = {0,0,0,0,0};						// 接收缓存
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &w25x_read_id, 1, 100);		// 读ID发送指令
	HAL_SPI_Receive(&hspi1, temp_ID, 5, 100);				// 读取ID
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
	
	/* 测试打印 */
	printf("\nreadID is %x%x\n",temp_ID[3],temp_ID[4]);
}

/* 检查是否繁忙 */
void CheckBusy(void)
{

uint8_t check_addr   = 0x05;					// 检查线路是否繁忙

	uint8_t status=1;
	uint32_t timeCount=0;
	do
	{
		timeCount++;
		if(timeCount > 0xEFFFFFFF) //等待超时
		{
			return ;
		}
		
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS	
		HAL_SPI_Transmit(&hspi1, &check_addr, 1, 100);			// 发送指令
		HAL_SPI_Receive(&hspi1, &status, 1, 100);				// 读取
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
		
	}while((status&0x01)==0x01);
}


/* 写入数据 */
void ReadData(void)
{
	/* W25Q64的指令 */
uint8_t w25x_read_id = 0x90;					// 读ID
uint8_t m_addr[3]    = {0,0,0};					// 测试地址0x000000
uint8_t check_addr   = 0x05;					// 检查线路是否繁忙
uint8_t enable_write = 0x06;					// 使能了才能改变芯片数据
uint8_t erase_addr   = 0x20;					// 擦除命令
uint8_t write_addr   = 0x02;					// 写数据命令
uint8_t read_addr    = 0x03;					// 读数据命令

	uint8_t temp_wdata[5] = {0x99,0x88,0x77,0x66,0x55};		// 需要写入的数据
	
	/* 检查是否繁忙 */
	CheckBusy();
	
	/* 写使能 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// 发送指令
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
	
	/* 擦除 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &erase_addr, 1, 100);			// 发送指令
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// 发送地址
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
	
	/* 再次检查是否繁忙 */
	CheckBusy();
	
	/* 写使能 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// 发送指令
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS

	/* 写数据 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &write_addr, 1, 100);			// 发送指令
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// 地址
	HAL_SPI_Transmit(&hspi1, temp_wdata, 5, 100);			// 写入数据
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
}

/* 读取数据 */
void WriteData(void)
{
	/* W25Q64的指令 */
uint8_t w25x_read_id = 0x90;					// 读ID
uint8_t m_addr[3]    = {0,0,0};					// 测试地址0x000000
uint8_t check_addr   = 0x05;					// 检查线路是否繁忙
uint8_t enable_write = 0x06;					// 使能了才能改变芯片数据
uint8_t erase_addr   = 0x20;					// 擦除命令
uint8_t write_addr   = 0x02;					// 写数据命令
uint8_t read_addr    = 0x03;					// 读数据命令
	uint8_t temp_rdata[5] = {0,0,0,0,0};					// 读出数据保存的buff
	
	
	/* 检查是否繁忙 */
	CheckBusy();	
	
	/* 开始读数据 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &read_addr, 1, 100);			// 读发送指令
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// 地址
	HAL_SPI_Receive(&hspi1, temp_rdata, 5, 100);			// 拿到数据
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
	
	/* 测试打印 */
	printf("Read flash data is:%x %x %x %x %x\n",temp_rdata[0],temp_rdata[1],temp_rdata[2],temp_rdata[3],temp_rdata[4]);
}



/* Private typedef -----------------------------------------------------------*/
//#define SPI_FLASH_PageSize      4096
#define SPI_FLASH_PageSize      256
#define SPI_FLASH_PerWritePageSize      256

/* Private define ------------------------------------------------------------*/
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F 

#define WIP_Flag                  0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                0xFF


#define SPI_FLASH_CS_LOW()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define SPI_FLASH_CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)	// 失能CS
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadDeviceID(void)
{

	uint8_t temp_rdata[] = {W25X_DeviceID,Dummy_Byte,Dummy_Byte,Dummy_Byte};					// 读出数据保存的buff
  SPI_FLASH_CS_LOW();
	HAL_SPI_Transmit(&hspi1, temp_rdata, 4, 100);			// 发送指令
	HAL_SPI_Receive(&hspi1, temp_rdata, 1, 100);				// 读取
	
  SPI_FLASH_CS_HIGH();

  return temp_rdata[0];
}



/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadID(void)
{
  
	uint8_t temp_rdata[5] ;					// 读出数据保存的buff
	temp_rdata[0]= W25X_JedecDeviceID;

  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
	HAL_SPI_Transmit(&hspi1, temp_rdata, 1, 100);			// 发送指令

	HAL_SPI_Receive(&hspi1, temp_rdata, 3, 100);				// 读取

  SPI_FLASH_CS_HIGH();
	
  return ((temp_rdata[0] << 16) | (temp_rdata[1] << 8) | temp_rdata[2]);

}
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;


/* 获取缓冲区的长度 */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress


void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
	uint8_t m_addr[]={(WriteAddr&0XFF0000>>16),(WriteAddr&0X00FF00>>8),(WriteAddr&0X0000FF)};
	uint8_t enable_write = 0x06;					// 使能了才能改变芯片数据
	uint8_t erase_addr   = 0x20;					// 擦除命令
	uint8_t write_addr   = 0x02;					// 写数据命令

	/* 检查是否繁忙 */
	CheckBusy();
	
	/* 写使能 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// 发送指令
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
	
	/* 擦除 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &erase_addr, 1, 100);			// 发送指令
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// 发送地址
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
	
	/* 再次检查是否繁忙 */
	CheckBusy();
	
	/* 写使能 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// 发送指令
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS

	/* 写数据 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &write_addr, 1, 100);			// 发送指令
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// 地址
	HAL_SPI_Transmit(&hspi1, pBuffer, NumByteToWrite, 100);			// 写入数据
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
}


void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
		
	uint8_t m_addr[]={(ReadAddr&0XFF0000>>16),(ReadAddr&0X00FF00>>8),(ReadAddr&0X0000FF)};
	uint8_t read_addr    = 0x03;					// 读数据命令
	/* 检查是否繁忙 */
	CheckBusy();	
	
	/* 开始读数据 */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// 使能CS
	HAL_SPI_Transmit(&hspi1, &read_addr, 1, 100);			// 读发送指令
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// 地址
	HAL_SPI_Receive(&hspi1, pBuffer, NumByteToRead, 100);			// 拿到数据
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// 失能CS
	
	/* 测试打印 */
	//printf("Read flash data is:%x %x %x %x %x\n",pBuffer[0],pBuffer[1],pBuffer[2],pBuffer[3],pBuffer[4]);
}

//flash功能测试
void  FlashTest(void){
	/* 发送缓冲区初始化 */
	uint8_t Tx_Buffer[] = " 感谢您选用艾尔赛产品               http://lctech-inc.taobao.com";
	uint8_t Rx_Buffer[BufferSize];
	__IO uint32_t DeviceID = 0;
	__IO uint32_t FlashID = 0;
	__IO TestStatus TransferStatus1 = FAILED;
	
	printf("\r\n 这是一个2M串行flash实验 \r\n");

	
	/* Get SPI Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	
	HAL_Delay( 200 );
	
	/* Get SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	
	printf("\r\n FlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	if (FlashID == 0xEF4018)  /* #define  sFLASH_ID  0xEF3015 */
	{	
		printf("\r\n 检测到华邦串行flash W25Q128 !\r\n");

		/* 将发送缓冲区的数据写到flash中 */
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\n 写入的数据为：%s len:%d\r\t", Tx_Buffer,strlen(Tx_Buffer));
		
		/* 将刚刚写入的数据读出来放到接收缓冲区中 */
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n 读出的数据为：%s len:%d\r\n", Rx_Buffer,strlen(Rx_Buffer));
		
		/* 检查写入的数据与读出的数据是否相等 */
		int ret = memcmp((void*)Tx_Buffer, (void*)Rx_Buffer, BufferSize);
		
		if( 0 == ret )
		{    
			LOG(LOG_INFO,"2M串行flash(W25Q128)测试成功!");
		}
		else
		{        
			LOG(LOG_ERR,"2M串行flash(W25Q128)测试失败 %d!",ret);
		}
	}// if (FlashID == sFLASH_ID)
	else
	{    
		LOG(LOG_ERR,"获取不到 W25Q128 ID!");
	}
	
//	SPI_Flash_PowerDown();  
}




//读取波形类型
int GetWaveType(WaveType *waveType){
	SPI_FLASH_BufferRead((uint8_t*)waveType, Addr__WaveType, sizeof(WaveBuff));
	return 0;
}

//设置波形类型
int SetWaveType(WaveType *waveType){
		WaveType buffer;
		SPI_FLASH_BufferWrite((uint8_t*)waveType, Addr__WaveType, sizeof(WaveType));
		HAL_Delay( 10 );
		SPI_FLASH_BufferRead((uint8_t*)&buffer, Addr__WaveType, sizeof(WaveType));
		int ret = memcmp((uint8_t*)waveType, (void*)&buffer, sizeof(WaveType));
		if( 0 == ret )
		{    
			LOG(LOG_INFO,"写入数据成功");
		}
		else
		{        
			LOG(LOG_ERR,"写入数据失败");
			
		}
	
	return 0;
}

//增加波形种类
int AddWaveType(int waveType){
	
	int j;
	int i;
	int ret=-1;

	for(i=0;i<g_allWaveType.counter;i++){
		if(g_allWaveType.sectNum[i]<waveType){
			continue;
		}else if(g_allWaveType.sectNum[i]==waveType){	//存在当前种类波形，覆盖判定
			ret=-1;
			break;
		}else {
			for(j=g_allWaveType.counter;j>i;j--){		//插入
				g_allWaveType.sectNum[j]=g_allWaveType.sectNum[j-1];
			}
			g_allWaveType.sectNum[i]=waveType;
			g_allWaveType.counter++;
			SetWaveType(&g_allWaveType);
			ret=0;
			break;
		}
	}
	
	return ret;
}
int SaveWaveBypeID(int waveID,uint8_t *p_Buff,uint16_t phase_length){
		int ret=-1;
		WaveBuff waveBuffer;
		WaveBuff tmp_WaveBuffer;
		waveBuffer.counter=phase_length;
		memcpy(waveBuffer.sectNum,p_Buff,phase_length);
		SPI_FLASH_BufferWrite((uint8_t*)&waveBuffer, BasicAddress+(waveID*2048), phase_length);
		HAL_Delay( 10 );
		SPI_FLASH_BufferRead((uint8_t*)&tmp_WaveBuffer, BasicAddress+(waveID*2048), phase_length);
		ret = memcmp((uint8_t*)&waveBuffer, (void*)&tmp_WaveBuffer, phase_length);
		if( 0 == ret )
		{    
			LOG(LOG_INFO,"写入数据成功");
		}
		else
		{        
			LOG(LOG_ERR,"写入数据失败");
			
		}
	
	return ret;
}
//测试函数
 void waveTypeTest(void){
		
	 //FlashTest();
//	 ReadID();
//  WriteData();
//  ReadData();
	 int i;
		
		g_allWaveType.counter=4;
		g_allWaveType.sectNum[0]=1;
		g_allWaveType.sectNum[1]=2;
		g_allWaveType.sectNum[2]=4;
		g_allWaveType.sectNum[3]=5;
		SetWaveType(&g_allWaveType);
	 GetWaveType(&g_allWaveType);
		 LOG(LOG_ERR,"%d,%d",g_allWaveType.counter, g_allWaveType.sectNum[2]);	 
//	 g_allWaveType.counter=5;
//	 g_allWaveType.sectNum[4]=19;
//		SetWaveType(&g_allWaveType);
//	GetWaveType(&g_allWaveType);
//	 int ret=AddWaveType(4);
//	 if(ret!=0){
//		 
//		 LOG(LOG_ERR,"添加数据错误");
//	 }
//	 		GetWaveType(&g_allWaveType);
//	ret=AddWaveType(2);
//	 if(ret!=0){
//		 LOG(LOG_ERR,"添加数据错误");
//	 }
//	 		GetWaveType(&g_allWaveType);
//	ret= AddWaveType(3);
//	 if(ret!=0){
//		 LOG(LOG_ERR,"添加数据错误");
//	 }
//	 		GetWaveType(&g_allWaveType);

//	 ret=AddWaveType(3);
//	 if(ret!=0){
//		 LOG(LOG_ERR,"添加数据错误");
//	 }
//	 		GetWaveType(&g_allWaveType);
//	 HAL_Delay(200);

}
 


#define HEAD01 0xFF
#define HEAD02 0xFF
#define HEAD03 0xFE
/*-----------------------------------------------------------------------------*/
//中断接收，数据放到缓冲区
//没有超时处理，有待完善
void PC_receive(void)
{
	//
	uint8_t *pc_buf=g_UsartType01.RX_pData;
	uint8_t data_length=	g_UsartType01.RX_Size;
	uint16_t phase_length=0;
	if((pc_buf[0]==HEAD01)&&(pc_buf[1]==HEAD02)&&(pc_buf[2]==HEAD03)){
		
		g_WaveID=pc_buf[3]&0x0F;		//接收4字节标志和长度数据
		g_WaveID=g_WaveID+(pc_buf[4]>>4);
		
		phase_length = pc_buf[4] &0x0F;
		phase_length = phase_length +pc_buf[5];
		phase_length=phase_length*3;
		
		
		int ret=AddWaveType(g_WaveID);
	 if(ret!=0){
		 LOG(LOG_ERR,"已存在waveID %d ",g_WaveID);
	 }else{
		 LOG(LOG_INFO,"波形添加成功 %d ",g_WaveID);				
	 }
	ret=SaveWaveBypeID(g_WaveID,pc_buf+7,phase_length);
	
	if(ret!=0){
		LOG(LOG_ERR,"保存波形失败，长度为%d",phase_length);
	}else{
		LOG(LOG_INFO,"保存波形成功，长度为%d",phase_length);				
	}
		
	}else{
			LOG(LOG_ERR,"PC 下发数据格式错误");
	}
}

