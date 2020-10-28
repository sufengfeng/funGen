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

extern uint8_t g_nDEBUG_LEVEL;//���Եȼ�


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




//flash�б���Ĳ��θ���������
typedef struct _WaveType{
	char counter;					//���沨�θ���
	char reserver;				//����λ�����ֽڶ��䣩
	char sectNum[64];			//���沨������
}WaveType;
//�������ݻ���
typedef struct _WaveBuff{
	int counter;					//���ݸ���
	char sectNum[1024];			//���沨������
}WaveBuff;

//Ԥ��8M�ռ䣬����120M�ռ�洢���ݿ�
#define Addr__WaveType  (0x00000)
#define BasicAddress		(0x80000)		


//void u3_printf(char* fmt,...); //...��ʾ�ɱ����������ɱ�������һ���б�������ר�ŵ�ָ��ָ�����������޶�����������

void  FlashTest(void);
void  FlashInit(void);
int SetWaveType(WaveType *waveType);
int GetWaveType(WaveType *waveType);
int AddWaveType(int waveType);
void waveTypeTest(void);

void PC_receive(void);


extern volatile WaveType g_allWaveType;	//ȫ�ֲ���
extern volatile uint8_t g_WaveID;					//��ǰ����ID
#endif