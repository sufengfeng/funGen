/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
void CheckBusy(void);
void ReadID(void);
void ReadData(void);
void WriteData(void);
#define u32 uint32_t
#define u16 uint16_t
#define u8  uint8_t
u32 SPI_FLASH_ReadID(void);
u32 SPI_FLASH_ReadDeviceID(void);
void  FlashTest(void);


#include <cstdio>
#include <cstdarg>

#include "stdio.h"
#include "stdlib.h"

#include "string.h"
#include <stdarg.h>

#include "usart.h"
#include "lcd.h"
#ifndef LOG_EMERG
#define LOG_EMERG       0       /* system is unusable */
#endif

#ifndef LOG_ALERT
#define LOG_ALERT       1       /* action must be taken immediately */
#endif

#ifndef LOG_CRIT
#define LOG_CRIT        2       /* critical conditions */
#endif

#ifndef LOG_ERR
#define LOG_ERR         3       /* error conditions */
#endif

#ifndef LOG_WARNING
#define LOG_WARNING     4       /* warning conditions */
#endif

#ifndef LOG_NOTICE
#define LOG_NOTICE      5       /* normal but significant condition */
#endif

#ifndef LOG_INFO
#define LOG_INFO        6       /* informational */
#endif

#ifndef LOG_DEBUG
#define LOG_DEBUG       7       /* debug-level messages */
#endif

extern uint8_t g_nDEBUG_LEVEL;//调试等级


void log_(int logLevel,const char * fmt, ...);

#define LOG(flag, fmt, args...)\
        do{\
                if( flag>g_nDEBUG_LEVEL)\
                        continue;\
                if(flag <= LOG_ERR){\
                        printf("\nLOG_ERR: %s  %s <L%d> : " fmt , __FILE__, __FUNCTION__, __LINE__, ##args);\
                }else if(flag <= LOG_WARNING){\
                        printf("\nLOG_WARNING: %s  %s <L%d> : " fmt , __FILE__, __FUNCTION__, __LINE__, ##args);\
                }else if(flag <= LOG_NOTICE){\
                        printf("\nLOG_NOTICE: %s  %s <L%d> : " fmt , __FILE__, __FUNCTION__, __LINE__, ##args);\
                }else if(flag <= LOG_INFO){\
                        printf("\nLOG_INFO: %s  %s <L%d> : " fmt , __FILE__, __FUNCTION__, __LINE__, ##args);\
                }else {\
                        printf("\nLOG_DEBUG: %s  %s <L%d> : " fmt , __FILE__, __FUNCTION__, __LINE__, ##args);\
                }\
        }while(0)




//flash中保存的波形个数和种类
typedef struct _WaveType{
	char counter;					//保存波形个数
	char reserver;				//保留位（四字节对其）
	char sectNum[64];			//保存波形类型
}WaveType;
#define MAX_WAVENUME (384*3)
//波形数据缓存
typedef struct _WaveBuff{
	int counter;					//数据个数
	char sectNum[MAX_WAVENUME];			//保存波形数据
}WaveBuff;

//预留8M空间，后面120M空间存储数据块
#define Addr__WaveType  (0x00000)
#define BasicAddress		(0x80000)		
void waveTypeTest(void);
void PC_receive(void);
int lcdShowMark(WaveType *waveType);
extern volatile WaveType g_allWaveType;	//全局参数
extern volatile uint8_t g_WaveID;					//当前波形ID
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
