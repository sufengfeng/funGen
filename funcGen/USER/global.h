#ifndef __GLOBAL_H
#define	__GLOBAL_H

#include <cstdio>
#include <cstdarg>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdarg.h>
#include "misc.h"

#include "stm32f10x.h"

#include "usart1.h"
#include "spi_flash.h"
#include "lcd.h"
#include "string.h"






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
//波形数据缓存
typedef struct _WaveBuff{
	int counter;					//数据个数
	char sectNum[1024];			//保存波形数据
}WaveBuff;

//预留8M空间，后面120M空间存储数据块
#define Addr__WaveType  (0x00000)
#define BasicAddress		(0x80000)		


//void u3_printf(char* fmt,...); //...表示可变参数（多个可变参数组成一个列表，后面有专门的指针指向他），不限定个数和类型

void  FlashTest(void);
void  FlashInit(void);
int SetWaveType(WaveType *waveType);
int GetWaveType(WaveType *waveType);
int AddWaveType(int waveType);
void waveTypeTest(void);

void PC_receive(void);


extern volatile WaveType g_allWaveType;	//全局参数
extern volatile uint8_t g_WaveID;					//当前波形ID
#endif