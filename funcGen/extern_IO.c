/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了宏晶科技的资料及程序   */
/*---------------------------------------------------------------------*/


/*************	本程序功能说明	**************

用STC的MCU的IO方式控制74HC595驱动8位数码管。

用户可以修改宏来选择时钟频率.

显示效果为: 左边为INT0(SW17)中断计数, 右边为INT1(SW18)中断计数, 计数范围为0~255.

由于按键是机械按键, 按下有抖动, 而本例程没有去抖动处理, 所以按一次有多个计数也是正常的.

******************************************/

#define MAIN_Fosc		24000000UL	//定义主时钟

#include	"STC15Fxxxx.H"

u8	INT0_cnt, INT1_cnt;	//测试用的计数变量

/********************** 主函数 ************************/
void maintest2(void)
{
	u8	i;
	
	P0M1 = 0;	P0M0 = 0;	//设置为准双向口
	P1M1 = 0;	P1M0 = 0;	//设置为准双向口
	P2M1 = 0;	P2M0 = 0;	//设置为准双向口
	P3M1 = 0;	P3M0 = 0;	//设置为准双向口
	P4M1 = 0;	P4M0 = 0;	//设置为准双向口
	P5M1 = 0;	P5M0 = 0;	//设置为准双向口
	P6M1 = 0;	P6M0 = 0;	//设置为准双向口
	P7M1 = 0;	P7M0 = 0;	//设置为准双向口	
	
	INT0_cnt = 0;
	INT1_cnt = 0;

	IE1  = 0;	//外中断1标志位
	IE0  = 0;	//外中断0标志位
	EX1 = 1;	//INT1 Enable
	EX0 = 1;	//INT0 Enable

	IT0 = 1;		//INT0 下降沿中断		
//	IT0 = 0;		//INT0 上升,下降沿中断	
	IT1 = 1;		//INT1 下降沿中断		
//	IT1 = 0;		//INT1 上升,下降沿中断	
	EA = 1;		//允许总中断

} 

/********************* INT0中断函数 *************************/
void INT0_int (void) interrupt INT0_VECTOR		//进中断时已经清除标志
{
	INT0_cnt++;	//中断+1
}

/********************* INT1中断函数 *************************/
void INT1_int (void) interrupt INT1_VECTOR		//进中断时已经清除标志
{
	INT1_cnt++;	//中断+1
}
/*


static void driver(){
  if (encoderPos_ > 0){
    onPosSide_ = true;  
  } else {
    onPosSide_ = false;  
  }

  goingPosDirLast_ = goingPosDir_;
  if ((encoderPos_ - encoderPosLast_) > 0) {
    goingPosDir_ = true;  
  } else{
    goingPosDir_ = false;  
  }

  // we've changed directions
  if (goingPosDir_ != goingPosDirLast_) {
    peakSwing_ = abs(encoderPos_);
  }
}
//优先执行管理程序回调函数，然后执行用户回调函数
// Interrupt on A changing state
static void doEncoderA() {
  // Test transition
  A_set_ = digitalRead_supervised(encoderPinA) == HIGH;
  // and adjust counter + if A leads B
  encoderPosLast_ = encoderPos_;
  encoderPos_ += (A_set_ != B_set_) ? +1 : -1;
  
  driver();
  (*doEncoderA_user)();
}

// Interrupt on B changing state
static void doEncoderB() {
  // Test transition
  B_set_ = digitalRead_supervised(encoderPinB) == HIGH;
  // and adjust counter + if B follows A
  encoderPosLast_ = encoderPos_;
  encoderPos_ += (A_set_ == B_set_) ? +1 : -1;
  
  driver();
  (*doEncoderB_user)();
}
*/