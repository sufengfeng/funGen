#include "REG51.h"
#include "oled.h"
#include "bmp.h"

sbit LED0=P3^0;
sbit LED1=P3^1;
sbit LED2 =P3^2;
sbit LED3 =P3^3;

void LED_BLINK(void){
	static u8 flag=0;
	
	if(flag){
		LED1=1;
		LED2=1;
		LED3=1;
	}else{
		LED1=0;
		LED2=0;
		LED3=0;
	}
	flag?flag=0:flag=1;
}
		