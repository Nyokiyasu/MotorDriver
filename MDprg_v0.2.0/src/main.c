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

int main()
{
  // At this stage the system clock should have already been configured
  // at high speed.

	GPIO_InitTypeDef init_gpio;
	TIM_TimeBaseInitTypeDef init_tmr;
	TIM_OCInitTypeDef init_OC;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	/*setting*/
	/*GPIO*/
	/*PORTB*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&init_gpio);
	/*PORTA*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_1;	//
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA,&init_gpio);

	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_2;	//1
	init_gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&init_gpio);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_2);

	/*Timer*/
	/*TIM2*/
	init_tmr.TIM_Period = 100-1;
	init_tmr.TIM_Prescaler = 4-1;
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
	TIM_Cmd(TIM2,ENABLE);

	TIM_ARRPreloadConfig(TIM2,ENABLE);
//	TIM_ITConfig();	//タイマ割り込みをする際に使用する



	/*End setting*/

	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
//	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);

	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);


	PWM_control(0,30);
  // Infinite loop
  while (1)
    {
       // Add your code here.
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
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,(dir&0b11));	//PWM_Hの設定
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
