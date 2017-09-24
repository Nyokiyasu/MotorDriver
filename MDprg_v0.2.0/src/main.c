/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include <stdio.h>
#include "stm32f0xx_conf.h"

#define BRAKE_VALUE -128

typedef enum {coast=0,forward,backforward,brake} SUPPLY_STATE_t;

void PWM_control(uint8_t ch , int8_t  duty);
void LDEs_init(void);
void ch0_init(void);
void CurrentSensor_init(void);
void RotarySW_init(void);
uint8_t RotarySW_Read(void);

//	TIM_ITConfig();	//タイマ割り込みをする際に使用する

int main()
{
	GPIO_InitTypeDef init_gpio;
	uint8_t addr = 0;

	/*setting*/
	/*メインクロックを8MHzから48MHzへ変更*/
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_12);
	RCC_PLLCmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	LDEs_init();
	ch0_init();
	CurrentSensor_init();
	RotarySW_init();

	/*LED確認用,PWMのピンをGPIOで初期化*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_4;
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA,&init_gpio);
	/*End setting*/

	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);


//	PWM_control(0,50);

	while (1)
    {
	  addr = RotarySW_Read();
	  switch (addr){
	  case 0:
		  PWM_control(0,0);
		  break;
	  case 1:
		  PWM_control(0,25);
		  break;
	  case 2:
		  PWM_control(0,50);
		  break;
	  case 3:
		  PWM_control(0,75);
		  break;
	  case 4:
		  PWM_control(0,40);
		  break;
	  case 5:
		  PWM_control(0,50);
		  break;
	  case 6:
		  PWM_control(0,60);
		  break;
	  case 7:
		  PWM_control(0,70);
		  break;
	  case 8:
		  PWM_control(0,80);
		  break;
	  case 9:
		  PWM_control(0,90);
		  break;
	  case 10:
		  PWM_control(0,100);
		  break;
	  default:
		  PWM_control(0,0);
		  break;
	  }
    }
}


/****************************
 * COAST:H=0,L=0,PHASE=X
 * Forward:H=1,L=PWM,PHASE=1
 * BackForward:H=1,L=PWM,PHASE=0
 * Brake:H=1,L=0,PHASE=X
 ****************************/

/**
 * @brief	Set PWM by frame of A3941.
 * @param	ch: Select the apply channel.
 * @param	duty: You must keep the value between -100 and 100
 * @note	If you want apply a brake , then pass -128.
 * @retaval	None
 */

void PWM_control(uint8_t ch , int8_t  duty)
{
	SUPPLY_STATE_t dir=coast;

	if (duty == BRAKE_VALUE)
	{
		dir = brake;
		duty = 0;
	}
	else if (duty>0) dir = forward;
	else if (duty<0)
	{
		dir = backforward;
		duty = -duty;
	}

	if(duty > 100)	duty = 100;

	switch (ch){
	case 0:
		GPIO_WriteBit(GPIOA,GPIO_Pin_3,!(dir&0b1));		//PHASEの設定
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,!!(dir&0b11));	//PWM_Hの設定
		TIM_SetCompare3(TIM2,duty);						//PWM_Lの出力
		break;
	case 1:
		break;
		//何もないけどチャンネル増えたら書き加える
	}
	return;
}


/**
 * @brief	Set PWM by frame of A3941. Param is CAN_frame.
 *
 */
void PWM_control_CF(void)
{

}

/**
 * @brief
 */
void LDEs_init(void)
{
	GPIO_InitTypeDef init_gpio;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/*DIR0&DIR1*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&init_gpio);

	/*PWM*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_4;	//1
	init_gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&init_gpio);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource4,GPIO_AF_4);
	//タイマー14の初期化必要


	return;
}

/* -------------------------------------------------
 * @関数名		:	RotarySW_init
 * @概要		:	RotarySWに使うGPIOの初期化
 * @戻り値		:	なし
 * ---------------------------------------------- */
void RotarySW_init(void)
{
	GPIO_InitTypeDef init_gpio;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/*DipSW*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	//
	init_gpio.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB,&init_gpio);

	return;
}

/* -------------------------------------------------
 * @関数名		:	RotarySW_read
 * @概要		:	RotarySWの読出し
 * @戻り値		:	なし
 * ---------------------------------------------- */
uint8_t RotarySW_Read(void)
{
	uint8_t data = 0;
	data = data|(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) << 0);
	data = data|(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) << 1);
	data = data|(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) << 3);
	data = data|GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) << 2;
	return (~data)&0x0f;
}

void CurrentSensor_init(void)
{

}

void ch0_init(void)
{
	TIM_TimeBaseInitTypeDef init_tmr;
	TIM_OCInitTypeDef init_OC;
	GPIO_InitTypeDef init_gpio;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	/*PORTA 1,2,3*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_1;	//
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA,&init_gpio);

	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_2;	//1
	init_gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&init_gpio);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_2);

	/*timer2 ch1*/
	init_tmr.TIM_Period = 100-1;
	init_tmr.TIM_Prescaler = 16-1;
	init_tmr.TIM_ClockDivision = TIM_CKD_DIV1;
	init_tmr.TIM_CounterMode = TIM_CounterMode_Up;
	init_tmr.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM2,&init_tmr);

	init_OC.TIM_OCMode = TIM_OCMode_PWM1;
	init_OC.TIM_Pulse = 0;
	init_OC.TIM_OutputState = TIM_OutputState_Enable;
	init_OC.TIM_OCIdleState = TIM_OCIdleState_Set;
	init_OC.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2,&init_OC);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	PWM_control(0,0);

	TIM_Cmd(TIM2,ENABLE);

	return;
}
