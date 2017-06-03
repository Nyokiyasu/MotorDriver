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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	/*setting*/
	/*GPIO*/
	/*PORTB*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin &= 0x0003;	//0,1��ݒ�
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&init_gpio);
	/*PORTA*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin &= 0x001E;	//1,2,3,4��ݒ�
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA,&init_gpio);

	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin &= 0x0100;	//8
	init_gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA,&init_gpio);

	/*Timer*/
	/*TIM1*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_2);
	GPIO_PinLockConfig(GPIOA,GPIO_Pin_8);
	TIM_TimeBaseStructInit(&init_tmr);

	init_tmr.TIM_Period = 100;
	init_tmr.TIM_Prescaler = 48;
	TIM_TimeBaseInit(TIM1,&init_tmr);

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//出力するために使うかも
	TIM_OCStructInit(&init_OC);
	init_OC.TIM_OCMode = TIM_OCMode_PWM1;
	init_OC.TIM_Pulse = 50;
	init_OC.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM1,&init_OC);

	TIM_ARRPreloadConfig(TIM1,ENABLE);
//	TIM_ITConfig();	//タイマ割り込みをする際に使用する



	/*End setting*/

	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);

	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);


  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}
