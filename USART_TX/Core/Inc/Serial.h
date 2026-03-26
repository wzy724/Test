/*
 * Serial.h
 *
 *  Created on: 2026年2月4日
 *      Author: 17629
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

void Serial_SendByte(uint8_t TxData);
void Serial_SendArray(uint8_t* Array,uint16_t Length);
void Serial_SendString(char* String);
uint32_t Serial_Pow(uint32_t X,uint32_t Y);
void Serial_SendNumber(uint32_t Number,uint16_t Length);

#endif /* INC_SERIAL_H_ */
