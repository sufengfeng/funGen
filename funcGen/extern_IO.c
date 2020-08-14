/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ���˺꾧�Ƽ������ϼ�����   */
/*---------------------------------------------------------------------*/


/*************	��������˵��	**************

��STC��MCU��IO��ʽ����74HC595����8λ����ܡ�

�û������޸ĺ���ѡ��ʱ��Ƶ��.

��ʾЧ��Ϊ: ���ΪINT0(SW17)�жϼ���, �ұ�ΪINT1(SW18)�жϼ���, ������ΧΪ0~255.

���ڰ����ǻ�е����, �����ж���, ��������û��ȥ��������, ���԰�һ���ж������Ҳ��������.

******************************************/

#define MAIN_Fosc		24000000UL	//������ʱ��

#include	"STC15Fxxxx.H"

u8	INT0_cnt, INT1_cnt;	//�����õļ�������

/********************** ������ ************************/
void maintest2(void)
{
	u8	i;
	
	P0M1 = 0;	P0M0 = 0;	//����Ϊ׼˫���
	P1M1 = 0;	P1M0 = 0;	//����Ϊ׼˫���
	P2M1 = 0;	P2M0 = 0;	//����Ϊ׼˫���
	P3M1 = 0;	P3M0 = 0;	//����Ϊ׼˫���
	P4M1 = 0;	P4M0 = 0;	//����Ϊ׼˫���
	P5M1 = 0;	P5M0 = 0;	//����Ϊ׼˫���
	P6M1 = 0;	P6M0 = 0;	//����Ϊ׼˫���
	P7M1 = 0;	P7M0 = 0;	//����Ϊ׼˫���	
	
	INT0_cnt = 0;
	INT1_cnt = 0;

	IE1  = 0;	//���ж�1��־λ
	IE0  = 0;	//���ж�0��־λ
	EX1 = 1;	//INT1 Enable
	EX0 = 1;	//INT0 Enable

	IT0 = 1;		//INT0 �½����ж�		
//	IT0 = 0;		//INT0 ����,�½����ж�	
	IT1 = 1;		//INT1 �½����ж�		
//	IT1 = 0;		//INT1 ����,�½����ж�	
	EA = 1;		//�������ж�

} 

/********************* INT0�жϺ��� *************************/
void INT0_int (void) interrupt INT0_VECTOR		//���ж�ʱ�Ѿ������־
{
	INT0_cnt++;	//�ж�+1
}

/********************* INT1�жϺ��� *************************/
void INT1_int (void) interrupt INT1_VECTOR		//���ж�ʱ�Ѿ������־
{
	INT1_cnt++;	//�ж�+1
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
//����ִ�й������ص�������Ȼ��ִ���û��ص�����
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