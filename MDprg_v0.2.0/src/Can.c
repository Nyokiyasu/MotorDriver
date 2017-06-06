/*
 * Can.c
 *
 *  Created on: 2017/05/21
 *      Author: mugi111
 */

#include <stm32f0xx.h>
#include "Can.h"


void CanInit()
{
	//↓ここ適当
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	CAN_InitTypeDef CAN_InitStructure;
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
//	CAN_InitStracture.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = ENABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Prescaler = 128;

	CAN_Init(CAN, &CAN_InitStructure);


//	じーぴーあいおーのしゅつりょくせってい

//	おるたねーとふぁんくしょんのせってい
}

void CanFilterInit(int id, int mode, int num, int scale, int fifo)
{
	//あいでぃーのぶんかつしょり　だいにゅうするための

	CAN_FilterInitTypeDef FilterInitStructure;
	FilterInitStructure.CAN_FilterActivation = ENABLE;
	FilterInitStructure.CAN_FilterMode = mode;
//	FilterInitStructure.CAN_FilterMaskIdHigh = ;
//	FilterInitStructure.CAN_FilterMaskIdLow = ;
//	FilterInitStructure.CAN_FilterIdHigh = ;
//	FilterInitStructure.CAN_FilterIdLow = ;
	if(num > 14)	num = 13;
	FilterInitStructure.CAN_FilterNumber = num;
	FilterInitStructure.CAN_FilterScale = scale;
	FilterInitStructure.CAN_FilterFIFOAssignment = fifo;

	CAN_FilterInit(&FilterInitStructure);
}

void CanReceive(uint8_t fifo, CanRxMsg* RxStructure)
{
	CAN_Receive(CAN, fifo, RxStructure);
}

uint8_t FifoCheck(uint8_t fifo)
{
	uint8_t fill;

	if(fifo == 0){
		fill = (CAN->RF0R)>>3 & 1;
	}else{
		fill = (CAN->RF1R)>>3 & 1;
	}

	return fill;
}


