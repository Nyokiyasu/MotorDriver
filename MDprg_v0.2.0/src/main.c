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
	init_gpio.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;	//
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA,&init_gpio);

	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin = GPIO_Pin_1;	//1
	init_gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&init_gpio);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_2);

	/*Timer*/
	/*TIM2*/
	init_tmr.TIM_Period = 100-1;
	init_tmr.TIM_Prescaler = 4-1;
	init_tmr.TIM_ClockDivision = TIM_CKD_DIV1;
	init_tmr.TIM_CounterMode = TIM_CounterMode_Up;
	init_tmr.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM2,&init_tmr);

	init_OC.TIM_OCMode = TIM_OCMode_PWM1;
	init_OC.TIM_Pulse = 50;
	init_OC.TIM_OutputState = TIM_OutputState_Enable;
	init_OC.TIM_OCIdleState = TIM_OCIdleState_Set;
	init_OC.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM2,&init_OC);
	TIM_Cmd(TIM2,ENABLE);

	TIM_ARRPreloadConfig(TIM2,ENABLE);
//	TIM_ITConfig();	//タイマ割り込みをする際に使用する



	/*End setting*/

//	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);

	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);


  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}
