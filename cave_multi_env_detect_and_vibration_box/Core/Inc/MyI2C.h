/*
 * MyI2C.h
 *
 *  Created on: 2026年3月11日
 *      Author: 17629
 */

#ifndef INC_MYI2C_H_
#define INC_MYI2C_H_

#include "stm32f1xx_hal.h"

void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t Ack);
uint8_t MyI2C_ReceiveAck(void);

#endif /* INC_MYI2C_H_ */
