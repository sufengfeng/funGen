#include "global.h"
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


