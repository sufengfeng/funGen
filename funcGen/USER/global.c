#include "global.h"
uint8_t g_nDEBUG_LEVEL=LOG_DEBUG;//���Եȼ�
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


volatile WaveType g_allWaveType;	//ȫ�ֲ���
volatile uint8_t g_WaveID;					//��ǰ����ID


