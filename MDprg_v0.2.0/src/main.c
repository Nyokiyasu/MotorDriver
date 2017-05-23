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

	GPIO_InitTypeDef init_buf;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

		/*GPIO setting*/
		/*PORTB*/
		GPIO_StructInit(&init_buf);
		init_buf.GPIO_Pin &= 0x0003;	//0,1Çê›íË
		init_buf.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(GPIOB,&init_buf);
		/*PORTA*/
		GPIO_StructInit(&init_buf);
		init_buf.GPIO_Pin &= 0x0010;	//4Çê›íË
		init_buf.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(GPIOA,&init_buf);
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
