/*
 * op.h
 *
 *  Created on: 2026年3月13日
 *      Author: 17629
 */

#ifndef INC_OP_H_
#define INC_OP_H_
#include "stm32f1xx_hal.h"

extern int8_t I2C_DATA[14];
extern uint8_t ModeFlag;
extern uint8_t WarnFlag;

#define Xacc (int16_t)((I2C_DATA[0]<<8)|(I2C_DATA[1]))
#define Yacc (int16_t)((I2C_DATA[2]<<8)|(I2C_DATA[3]))
#define Zacc (int16_t)((I2C_DATA[4]<<8)|(I2C_DATA[5]))
#define Xgyr (int16_t)((I2C_DATA[8]<<8)|(I2C_DATA[9]))
#define Ygyr (int16_t)((I2C_DATA[10]<<8)|(I2C_DATA[11]))
#define Zgyr (int16_t)((I2C_DATA[12]<<8)|(I2C_DATA[13]))


void Mode_Switch(void);
void Warning_Switch(int16_t AccX,  int16_t AccY,  int16_t AccZ,
		 int16_t GyroX, int16_t GyroY, int16_t GyroZ);
#endif /* INC_OP_H_ */
