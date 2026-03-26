/*
 * MyFlash.h
 *
 *  Created on: 2026年2月18日
 *      Author: 17629
 */

#ifndef INC_MYFLASH_H_
#define INC_MYFLASH_H_
#include "stm32f1xx_hal.h"
uint32_t MyFlash_ReadWord(uint32_t Address);
uint16_t MyFlash_ReadHalfWord(uint32_t Address);
uint8_t MyFlash_ReadByte(uint32_t Address);
HAL_StatusTypeDef MyFlash_ErasePage(uint32_t PageAddress);
HAL_StatusTypeDef MyFlash_EraseAllPages(void);
void MyFlash_ProgramHalfWord(uint32_t Address,uint16_t Data);
void MyFlash_ProgramWord(uint32_t Address,uint32_t Data);

#endif /* INC_MYFLASH_H_ */
