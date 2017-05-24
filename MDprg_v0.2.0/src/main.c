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
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	/*setting*/
	/*GPIO*/
	/*PORTB*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin &= 0x0003;	//0,1を設定
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&init_gpio);
	/*PORTA*/
	GPIO_StructInit(&init_gpio);
	init_gpio.GPIO_Pin &= 0x0010;	//4を設定
	init_gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA,&init_gpio);
	/*Timer*/
	/*TIM1*/
	TIM_TimeBaseStructInit(init_tmr);

	TIM_TimeBaseInit(TIM1,init_tmr);

	/*End etting*/

	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);

	//	GPIO_Write(GPIOB,0xAA00);

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}
