/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t g_nDEBUG_LEVEL=LOG_DEBUG;//调试等级
//////////////////////////////////////////////////////////////////////////
void log_(int logLevel,const char * fmt, ...)
{
        int n, size = 128;
        char p[1024];
        va_list ap;
				va_start(ap, fmt);
				n = vsnprintf(p, size, fmt, ap);
				va_end(ap);
				 printf("%s",(const char*)p);
}


volatile WaveType g_allWaveType;	//全局参数
volatile uint8_t g_WaveID;					//当前波形ID
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim3); //使用定时器的时候调用这个函数启动
	
	HAL_UART_Receive_DMA(&huart1, g_UsartType01.RX_pData, RX_LEN);  
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); 
	
	HAL_UART_Receive_DMA(&huart3, g_UsartType03.RX_pData, RX_LEN);  
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE); 
		
	printf("*********(C) COPYRIGHT 2020-10-25 *****************\r\n");
	printf("*                                                 *\r\n");
	printf("*               展翔电子工作室                    *\r\n");
	printf("*                                                 *\r\n");
	printf("*         zhanxiangElectronicstudio               *\r\n");
	printf("***************************************************\r\n\r\n"); 
	HAL_Delay(1000);
	
//	uint32_t DeviceID = 0;
//	uint32_t FlashID = 0;
//	
//	/* Get SPI Flash Device ID */
//	DeviceID = SPI_FLASH_ReadDeviceID();
//	
//	HAL_Delay( 200 );
//	
//	/* Get SPI Flash ID */
//	FlashID = SPI_FLASH_ReadID();
//	
//	printf("\r\n FlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	//FlashTest();
	//waveTypeTest();
	
	//lcd_showpic(2);
//	lcd_sendword(0xe002,1);
//	while(1)HAL_Delay(1);
	//lcd_readword(0xF000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		#define uin8_t unsigned char 
		static uin8_t g_nIsInitial=1;
		if(g_nIsInitial){				//初始化设备所有参数，并重新载入配置
			
			GetWaveType(&g_allWaveType);		//
			lcdShowMark(&g_allWaveType);
			g_nIsInitial=0;
		}
		
			if(g_UsartType01.RX_flag)    	// Receive flag
			{  
					g_UsartType01.RX_flag=0;	// clean flag
					HAL_UART_Transmit(&huart1, g_UsartType01.RX_pData, g_UsartType01.RX_Size, 0xFFFF);
					PC_receive();		//处理PC下发命令
			} 
			if(g_UsartType03.RX_flag)    	// Receive flag
			{  
					g_UsartType03.RX_flag=0;	// clean flag
					HAL_UART_Transmit(&huart1, g_UsartType03.RX_pData, g_UsartType03.RX_Size, 0xFFFF);
					lcd_receive();		//处理串口屏数据
			} 
			HAL_Delay(8);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
