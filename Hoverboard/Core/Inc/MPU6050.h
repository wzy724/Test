/*
 * MPU6050.h
 *
 *  Created on: 2026年3月11日
 *      Author: 17629
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "stm32f1xx_hal.h"
#include "MPU6050_Reg.h"

void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_ReadBurst(uint8_t startReg, uint8_t *pData, uint8_t len);
void MPU6050_GetData(int16_t* AccX,  int16_t* AccY,  int16_t* AccZ,
		 	 	 	 int16_t* GyroX, int16_t* GyroY, int16_t* GyroZ);
#endif /* INC_MPU6050_H_ */
