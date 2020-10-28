
#include "main.h"
#include "spi.h"




/* ��ID */
void ReadID(void)
{
	/* W25Q64��ָ�� */
uint8_t w25x_read_id = 0x90;					// ��ID


	uint8_t temp_ID[5] = {0,0,0,0,0};						// ���ջ���
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &w25x_read_id, 1, 100);		// ��ID����ָ��
	HAL_SPI_Receive(&hspi1, temp_ID, 5, 100);				// ��ȡID
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
	
	/* ���Դ�ӡ */
	printf("\nreadID is %x%x\n",temp_ID[3],temp_ID[4]);
}

/* ����Ƿ�æ */
void CheckBusy(void)
{

uint8_t check_addr   = 0x05;					// �����·�Ƿ�æ

	uint8_t status=1;
	uint32_t timeCount=0;
	do
	{
		timeCount++;
		if(timeCount > 0xEFFFFFFF) //�ȴ���ʱ
		{
			return ;
		}
		
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS	
		HAL_SPI_Transmit(&hspi1, &check_addr, 1, 100);			// ����ָ��
		HAL_SPI_Receive(&hspi1, &status, 1, 100);				// ��ȡ
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
		
	}while((status&0x01)==0x01);
}


/* д������ */
void ReadData(void)
{
	/* W25Q64��ָ�� */
uint8_t w25x_read_id = 0x90;					// ��ID
uint8_t m_addr[3]    = {0,0,0};					// ���Ե�ַ0x000000
uint8_t check_addr   = 0x05;					// �����·�Ƿ�æ
uint8_t enable_write = 0x06;					// ʹ���˲��ܸı�оƬ����
uint8_t erase_addr   = 0x20;					// ��������
uint8_t write_addr   = 0x02;					// д��������
uint8_t read_addr    = 0x03;					// ����������

	uint8_t temp_wdata[5] = {0x99,0x88,0x77,0x66,0x55};		// ��Ҫд�������
	
	/* ����Ƿ�æ */
	CheckBusy();
	
	/* дʹ�� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// ����ָ��
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
	
	/* ���� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &erase_addr, 1, 100);			// ����ָ��
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// ���͵�ַ
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
	
	/* �ٴμ���Ƿ�æ */
	CheckBusy();
	
	/* дʹ�� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// ����ָ��
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS

	/* д���� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &write_addr, 1, 100);			// ����ָ��
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// ��ַ
	HAL_SPI_Transmit(&hspi1, temp_wdata, 5, 100);			// д������
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
}

/* ��ȡ���� */
void WriteData(void)
{
	/* W25Q64��ָ�� */
uint8_t w25x_read_id = 0x90;					// ��ID
uint8_t m_addr[3]    = {0,0,0};					// ���Ե�ַ0x000000
uint8_t check_addr   = 0x05;					// �����·�Ƿ�æ
uint8_t enable_write = 0x06;					// ʹ���˲��ܸı�оƬ����
uint8_t erase_addr   = 0x20;					// ��������
uint8_t write_addr   = 0x02;					// д��������
uint8_t read_addr    = 0x03;					// ����������
	uint8_t temp_rdata[5] = {0,0,0,0,0};					// �������ݱ����buff
	
	
	/* ����Ƿ�æ */
	CheckBusy();	
	
	/* ��ʼ������ */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &read_addr, 1, 100);			// ������ָ��
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// ��ַ
	HAL_SPI_Receive(&hspi1, temp_rdata, 5, 100);			// �õ�����
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
	
	/* ���Դ�ӡ */
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
#define SPI_FLASH_CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)	// ʧ��CS
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadDeviceID(void)
{

	uint8_t temp_rdata[] = {W25X_DeviceID,Dummy_Byte,Dummy_Byte,Dummy_Byte};					// �������ݱ����buff
  SPI_FLASH_CS_LOW();
	HAL_SPI_Transmit(&hspi1, temp_rdata, 4, 100);			// ����ָ��
	HAL_SPI_Receive(&hspi1, temp_rdata, 1, 100);				// ��ȡ
	
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
  
	uint8_t temp_rdata[5] ;					// �������ݱ����buff
	temp_rdata[0]= W25X_JedecDeviceID;

  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
	HAL_SPI_Transmit(&hspi1, temp_rdata, 1, 100);			// ����ָ��

	HAL_SPI_Receive(&hspi1, temp_rdata, 3, 100);				// ��ȡ

  SPI_FLASH_CS_HIGH();
	
  return ((temp_rdata[0] << 16) | (temp_rdata[1] << 8) | temp_rdata[2]);

}
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;


/* ��ȡ�������ĳ��� */
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
	uint8_t enable_write = 0x06;					// ʹ���˲��ܸı�оƬ����
	uint8_t erase_addr   = 0x20;					// ��������
	uint8_t write_addr   = 0x02;					// д��������

	/* ����Ƿ�æ */
	CheckBusy();
	
	/* дʹ�� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// ����ָ��
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
	
	/* ���� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &erase_addr, 1, 100);			// ����ָ��
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// ���͵�ַ
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
	
	/* �ٴμ���Ƿ�æ */
	CheckBusy();
	
	/* дʹ�� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &enable_write, 1, 100);		// ����ָ��
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS

	/* д���� */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &write_addr, 1, 100);			// ����ָ��
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// ��ַ
	HAL_SPI_Transmit(&hspi1, pBuffer, NumByteToWrite, 100);			// д������
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
}


void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
		
	uint8_t m_addr[]={(ReadAddr&0XFF0000>>16),(ReadAddr&0X00FF00>>8),(ReadAddr&0X0000FF)};
	uint8_t read_addr    = 0x03;					// ����������
	/* ����Ƿ�æ */
	CheckBusy();	
	
	/* ��ʼ������ */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	// ʹ��CS
	HAL_SPI_Transmit(&hspi1, &read_addr, 1, 100);			// ������ָ��
	HAL_SPI_Transmit(&hspi1, m_addr, 3, 100);				// ��ַ
	HAL_SPI_Receive(&hspi1, pBuffer, NumByteToRead, 100);			// �õ�����
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	// ʧ��CS
	
	/* ���Դ�ӡ */
	//printf("Read flash data is:%x %x %x %x %x\n",pBuffer[0],pBuffer[1],pBuffer[2],pBuffer[3],pBuffer[4]);
}

//flash���ܲ���
void  FlashTest(void){
	/* ���ͻ�������ʼ�� */
	uint8_t Tx_Buffer[] = " ��л��ѡ�ð�������Ʒ               http://lctech-inc.taobao.com";
	uint8_t Rx_Buffer[BufferSize];
	__IO uint32_t DeviceID = 0;
	__IO uint32_t FlashID = 0;
	__IO TestStatus TransferStatus1 = FAILED;
	
	printf("\r\n ����һ��2M����flashʵ�� \r\n");

	
	/* Get SPI Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	
	HAL_Delay( 200 );
	
	/* Get SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	
	printf("\r\n FlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	if (FlashID == 0xEF4018)  /* #define  sFLASH_ID  0xEF3015 */
	{	
		printf("\r\n ��⵽�����flash W25Q128 !\r\n");

		/* �����ͻ�����������д��flash�� */
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\n д�������Ϊ��%s len:%d\r\t", Tx_Buffer,strlen(Tx_Buffer));
		
		/* ���ո�д������ݶ������ŵ����ջ������� */
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n ����������Ϊ��%s len:%d\r\n", Rx_Buffer,strlen(Rx_Buffer));
		
		/* ���д�������������������Ƿ���� */
		int ret = memcmp((void*)Tx_Buffer, (void*)Rx_Buffer, BufferSize);
		
		if( 0 == ret )
		{    
			LOG(LOG_INFO,"2M����flash(W25Q128)���Գɹ�!");
		}
		else
		{        
			LOG(LOG_ERR,"2M����flash(W25Q128)����ʧ�� %d!",ret);
		}
	}// if (FlashID == sFLASH_ID)
	else
	{    
		LOG(LOG_ERR,"��ȡ���� W25Q128 ID!");
	}
	
//	SPI_Flash_PowerDown();  
}




//��ȡ��������
int GetWaveType(WaveType *waveType){
	SPI_FLASH_BufferRead((uint8_t*)waveType, Addr__WaveType, sizeof(WaveBuff));
	return 0;
}

//���ò�������
int SetWaveType(WaveType *waveType){
		WaveType buffer;
		SPI_FLASH_BufferWrite((uint8_t*)waveType, Addr__WaveType, sizeof(WaveType));
		HAL_Delay( 10 );
		SPI_FLASH_BufferRead((uint8_t*)&buffer, Addr__WaveType, sizeof(WaveType));
		int ret = memcmp((uint8_t*)waveType, (void*)&buffer, sizeof(WaveType));
		if( 0 == ret )
		{    
			LOG(LOG_INFO,"д�����ݳɹ�");
		}
		else
		{        
			LOG(LOG_ERR,"д������ʧ��");
			
		}
	
	return 0;
}

//���Ӳ�������
int AddWaveType(int waveType){
	
	int j;
	int i;
	int ret=-1;

	for(i=0;i<g_allWaveType.counter;i++){
		if(g_allWaveType.sectNum[i]<waveType){
			continue;
		}else if(g_allWaveType.sectNum[i]==waveType){	//���ڵ�ǰ���ನ�Σ������ж�
			ret=-1;
			break;
		}else {
			for(j=g_allWaveType.counter;j>i;j--){		//����
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
			LOG(LOG_INFO,"д�����ݳɹ�");
		}
		else
		{        
			LOG(LOG_ERR,"д������ʧ��");
			
		}
	
	return ret;
}
//���Ժ���
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
//		 LOG(LOG_ERR,"������ݴ���");
//	 }
//	 		GetWaveType(&g_allWaveType);
//	ret=AddWaveType(2);
//	 if(ret!=0){
//		 LOG(LOG_ERR,"������ݴ���");
//	 }
//	 		GetWaveType(&g_allWaveType);
//	ret= AddWaveType(3);
//	 if(ret!=0){
//		 LOG(LOG_ERR,"������ݴ���");
//	 }
//	 		GetWaveType(&g_allWaveType);

//	 ret=AddWaveType(3);
//	 if(ret!=0){
//		 LOG(LOG_ERR,"������ݴ���");
//	 }
//	 		GetWaveType(&g_allWaveType);
//	 HAL_Delay(200);

}
 


#define HEAD01 0xFF
#define HEAD02 0xFF
#define HEAD03 0xFE
/*-----------------------------------------------------------------------------*/
//�жϽ��գ����ݷŵ�������
//û�г�ʱ�����д�����
void PC_receive(void)
{
	//
	uint8_t *pc_buf=g_UsartType01.RX_pData;
	uint8_t data_length=	g_UsartType01.RX_Size;
	uint16_t phase_length=0;
	if((pc_buf[0]==HEAD01)&&(pc_buf[1]==HEAD02)&&(pc_buf[2]==HEAD03)){
		
		g_WaveID=pc_buf[3]&0x0F;		//����4�ֽڱ�־�ͳ�������
		g_WaveID=g_WaveID+(pc_buf[4]>>4);
		
		phase_length = pc_buf[4] &0x0F;
		phase_length = phase_length +pc_buf[5];
		phase_length=phase_length*3;
		
		
		int ret=AddWaveType(g_WaveID);
	 if(ret!=0){
		 LOG(LOG_ERR,"�Ѵ���waveID %d ",g_WaveID);
	 }else{
		 LOG(LOG_INFO,"������ӳɹ� %d ",g_WaveID);				
	 }
	ret=SaveWaveBypeID(g_WaveID,pc_buf+7,phase_length);
	
	if(ret!=0){
		LOG(LOG_ERR,"���沨��ʧ�ܣ�����Ϊ%d",phase_length);
	}else{
		LOG(LOG_INFO,"���沨�γɹ�������Ϊ%d",phase_length);				
	}
		
	}else{
			LOG(LOG_ERR,"PC �·����ݸ�ʽ����");
	}
}

