
#include "global.h"

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;


/* 获取缓冲区的长度 */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)




#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
//#define  sFLASH_ID              0xEF3015     //W25X16
//#define  sFLASH_ID              0xEF4015	 //W25Q16
//#define  sFLASH_ID              0xEF4014	 //W25Q80
//#define  sFLASH_ID              0xEF4016	 //W25Q32



TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/*
 * 函数名：Buffercmp
 * 描述  ：比较两个缓冲区中的数据是否相等
 * 输入  ：-pBuffer1     src缓冲区指针
 *         -pBuffer2     dst缓冲区指针
 *         -BufferLength 缓冲区长度
 * 输出  ：无
 * 返回  ：-PASSED pBuffer1 等于   pBuffer2
 *         -FAILED pBuffer1 不同于 pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
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
	
	/* 2M串行flash W25X16初始化 */
	SPI_FLASH_Init();
	
	/* Get SPI Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	
	Delay( 200 );
	
	/* Get SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	
	printf("\r\n FlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	if (FlashID == 0xEF4018)  /* #define  sFLASH_ID  0xEF3015 */
	{	
		printf("\r\n 检测到华邦串行flash W25Q128 !\r\n");
		
		/* Erase SPI FLASH Sector to write on */
		SPI_FLASH_SectorErase(FLASH_SectorToErase);	 	 
		
		/* 将发送缓冲区的数据写到flash中 */
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\n 写入的数据为：%s \r\t", Tx_Buffer);
		
		/* 将刚刚写入的数据读出来放到接收缓冲区中 */
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n 读出的数据为：%s \r\n", Tx_Buffer);
		
		/* 检查写入的数据与读出的数据是否相等 */
		int ret = memcmp((void*)Tx_Buffer, (void*)Rx_Buffer, BufferSize);
		
		if( 0 == ret )
		{    
			printf("\r\n 2M串行flash(W25Q128)测试成功!\n\r");
		}
		else
		{        
			printf("\r\n 2M串行flash(W25Q128)测试失败!\n\r");
		}
	}// if (FlashID == sFLASH_ID)
	else
	{    
		printf("\r\n 获取不到 W25Q128 ID!\n\r");
	}
	
	SPI_Flash_PowerDown();  
}






void  FlashInit(void){

	__IO uint32_t DeviceID = 0;
	__IO uint32_t FlashID = 0;
	__IO TestStatus TransferStatus1 = FAILED;
	
	/* 2M串行flash W25X16初始化 */
	SPI_FLASH_Init();
	/* Get SPI Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	Delay( 200 );
	/* Get SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	printf("\r\n FlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	if (FlashID == 0xEF4018)  /* #define  sFLASH_ID  0xEF3015 */
	{	
		printf("\r\n初始化flash W25Q128 成功!\r\n");
	}
	GetWaveType(&g_allWaveType);
}
//Flash掉电
void FlashClose(void){
	SPI_Flash_PowerDown();
}


//读取波形类型
int GetWaveType(WaveType *waveType){

		__IO uint32_t DeviceID = 0;
	__IO uint32_t FlashID = 0;
	/* 2M串行flash W25X16初始化 */
	SPI_FLASH_Init();
	/* Get SPI Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	Delay( 200 );
	/* Get SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	SPI_FLASH_BufferRead((uint8_t*)waveType, Addr__WaveType, sizeof(WaveBuff));
	return 0;
}

//设置波形类型
int SetWaveType(WaveType *waveType){
		WaveType buffer;

	__IO uint32_t DeviceID = 0;
	__IO uint32_t FlashID = 0;
	/* 2M串行flash W25X16初始化 */
	SPI_FLASH_Init();
	/* Get SPI Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	Delay( 200 );
	/* Get SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	if (FlashID == 0xEF4018)  /* #define  sFLASH_ID  0xEF3015 */
	{	
		SPI_FLASH_SectorErase(Addr__WaveType);	 	 
		SPI_FLASH_BufferWrite((uint8_t*)waveType, Addr__WaveType, sizeof(WaveType));
		Delay( 200 );
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
	}// if (FlashID == sFLASH_ID)
	else
	{    
		LOG(LOG_ERR,"获取不到 Flash ID!");
	}
	
	SPI_Flash_PowerDown();  
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

//测试函数
 void waveTypeTest(void){
		
	 //FlashTest();
	 int i;
//		
		g_allWaveType.counter=4;
		g_allWaveType.sectNum[0]=1;
		g_allWaveType.sectNum[1]=2;
		g_allWaveType.sectNum[2]=4;
		g_allWaveType.sectNum[3]=5;
		SetWaveType(&g_allWaveType);
	 GetWaveType(&g_allWaveType);
	 g_allWaveType.counter=5;
	 g_allWaveType.sectNum[4]=19;
		SetWaveType(&g_allWaveType);
GetWaveType(&g_allWaveType);
	 int ret=AddWaveType(4);
	 if(ret!=0){
		 
		 LOG(LOG_ERR,"添加数据错误");
	 }
	 		GetWaveType(&g_allWaveType);
	ret=AddWaveType(2);
	 if(ret!=0){
		 LOG(LOG_ERR,"添加数据错误");
	 }
	 		GetWaveType(&g_allWaveType);
	ret= AddWaveType(3);
	 if(ret!=0){
		 LOG(LOG_ERR,"添加数据错误");
	 }
	 		GetWaveType(&g_allWaveType);

	 ret=AddWaveType(3);
	 if(ret!=0){
		 LOG(LOG_ERR,"添加数据错误");
	 }
	 		GetWaveType(&g_allWaveType);
	 Delay(200);

}