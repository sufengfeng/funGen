
#include "main.h"


static uint8_t lcd_buf[LCD_COM_LEN];
static uint8_t lcd_flag = 0;

static uint16_t receive_step  = 0;
static uint16_t receive_count = 0;

int  uart3_send_byte(uint8_t data){
	
	return HAL_UART_Transmit(&huart3, &data, 1, 0xFFFF);
}

/*-----------------------------------------------------------------------------*/
//切换液晶屏页面
//5A A5 07 82 0084 5A01 0001
 void lcd_showpic(uint16_t num)
{
	uint8_t temp_wdata[] = {HEAD0,HEAD1,0x07,0x82,0x00,0x84,0x5A,0x01,num/256,num%256};		// 需要写入的数据
	HAL_UART_Transmit(&huart3, temp_wdata, sizeof(temp_wdata), 0xFFFF);
}

//向指定变量写入数据
//5A A5 05 82 E0 02 00 01

void lcd_sendword(uint16_t addr,uint16_t data)
{
	
	uint8_t temp_wdata[] = {HEAD0,HEAD1,0x05,0x82,addr/256,addr%256,data/256,data%256};		// 需要写入的数据
	HAL_UART_Transmit(&huart3, temp_wdata, sizeof(temp_wdata), 0xFFFF);
}
/*-----------------------------------------------------------------------------*/
//向指定变量写入字符串
void lcd_sendhz(uint16_t addr,uint8_t *str)
{
	uint8_t len;
	
	len = (uint8_t)strlen(str);
	
	uart3_send_byte(HEAD0);
	uart3_send_byte(HEAD1);
	uart3_send_byte(len+3);
	uart3_send_byte(LCD_WD);
	uart3_send_byte(addr/256);
	uart3_send_byte(addr%256);
	while(*str)
	{
		uart3_send_byte(*str);
		str++;
	}

}


/*-----------------------------------------------------------------------------*/
//向指定变量写入字符串
void lcd_clearhz(uint16_t addr)
{
	uint8_t len = 40;
	
	
	uart3_send_byte(HEAD0);
	uart3_send_byte(HEAD1);
	uart3_send_byte(len+3);
	uart3_send_byte(LCD_WD);
	uart3_send_byte(addr/256);
	uart3_send_byte(addr%256);
	while(len)
	{
		uart3_send_byte(0);
		len--;
	}

}

/*-----------------------------------------------------------------------------*/
//中断接收，数据放到缓冲区
//没有超时处理，有待完善
void lcd_receive(void)
{
	//5A A5 06 83 F0 00 01 00 01
	
	uint8_t *p_buf=g_UsartType03.RX_pData;
	uint8_t data_length=	g_UsartType03.RX_Size;
	
	if((p_buf[0]==HEAD0)&&(p_buf[1]==HEAD1)){
		switch(p_buf[3]){
			case 0x83:
					if((p_buf[4]==0xF0)&&(p_buf[5]==0x00)&&(p_buf[6]==0x01))
						lcd_showpic(1);
				break;
			default:
				break;
		}
	}{
		LOG(LOG_ERR,"串口屏下发数据格式错误");
	}
}
/*-----------------------------------------------------------------------------*/
//从缓冲区获取有效数据
void lcd_getdata(LCD_DATA *lcd)
{
	if((lcd_flag)&&(lcd_buf[0] == LCD_RD))
	{
		lcd_flag = 0;
		lcd->addr = lcd_buf[1]*256 + lcd_buf[2];
		lcd->num = lcd_buf[3];
		
		lcd->data = lcd_buf[4]*256 + lcd_buf[5];
	}
	else
	{
		lcd->data = 0;
		lcd->addr = 0;
	}
}
/*-----------------------------------------------------------------------------*/
//向指定变量读出数据
uint16_t lcd_readword(uint16_t addr)
{
	LCD_DATA lcd;
	
	uart3_send_byte(HEAD0);
	uart3_send_byte(HEAD1);
	uart3_send_byte(0X04);
	uart3_send_byte(LCD_RD);
	uart3_send_byte(addr/256);
	uart3_send_byte(addr%256);
	uart3_send_byte(1);
	
	while(!lcd_flag);
	lcd_getdata(&lcd);
	
	printf("lcd	%x	%x\r\n",lcd.addr,lcd.data);
	return lcd.data;
}



int lcdShowMark(WaveType *waveType){
	for(int i=0;i<waveType->counter;i++){
		uint16_t addr=0xE000+waveType->sectNum[i]/8*16+waveType->sectNum[i]%8;
		
		lcd_sendword(addr,1);
		//LOG(LOG_INFO," %d,%d %x ",waveType->counter,waveType->sectNum[i],addr);	 
	}
	
}


