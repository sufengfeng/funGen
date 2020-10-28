
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
void lcd_showpic(uint16_t num)
{
	uart3_send_byte(HEAD0);
	uart3_send_byte(HEAD1);
	uart3_send_byte(0X04);
	uart3_send_byte(LCD_WR);
	uart3_send_byte(PIC_ID);
	uart3_send_byte(num/256);
	uart3_send_byte(num%256);
	
}
/*-----------------------------------------------------------------------------*/
//向指定变量写入数据
void lcd_sendword(uint16_t addr,uint16_t data)
{
	uart3_send_byte(HEAD0);
	uart3_send_byte(HEAD1);
	uart3_send_byte(0X05);
	uart3_send_byte(LCD_WD);
	uart3_send_byte(addr/256);
	uart3_send_byte(addr%256);
	uart3_send_byte(data/256);
	uart3_send_byte(data%256);	
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






