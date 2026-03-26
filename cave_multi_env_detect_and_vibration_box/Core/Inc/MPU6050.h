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
#define MPU6050_ADDRESS		0xD0		//MPU6050的I2C从机地址


void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX,  int16_t *AccY,  int16_t *AccZ,
					 int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
void MPU6050_ReadBurst(uint8_t startReg, int8_t *pData, uint8_t len);
#endif /* INC_MPU6050_H_ */
