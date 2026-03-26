/*
 * MyI2C.h
 *
 *  Created on: 2026年2月10日
 *      Author: 17629
 */

#ifndef INC_MYI2C_H_
#define INC_MYI2C_H_

void SI2C_Start(void);
void SI2C_Stop(void);
void SI2C_SendByte(uint8_t Byte);
uint8_t SI2C_ReceiveByte(void);
void SI2C_SendAck(uint8_t Ack);
uint8_t SI2C_ReceiveAck(void);

#endif /* INC_MYI2C_H_ */
