/*
 * Can.h
 *
 *  Created on: 2017/05/21
 *      Author: mugi111
 */

#ifndef CAN_H_
#define CAN_H_


void CanInit();
void CanFilterInit(int id, int mode, int num, int scale, int fifo);
void CanReceive(uint8_t fifo, CanRxMsg* RxStructure);
//↓作ったはいいけど動くかわからないやつ
uint8_t FifoCheck(uint8_t fifo);

#endif /* CAN_H_ */
