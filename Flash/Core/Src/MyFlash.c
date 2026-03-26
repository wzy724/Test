/*
 * MyFlash.c
 *
 *  Created on: 2026年2月18日
 *      Author: 17629
 */
#include "MyFlash.h"
uint32_t MyFlash_ReadWord(uint32_t Address)
{
	return *((volatile uint32_t*)Address);
}

uint16_t MyFlash_ReadHalfWord(uint32_t Address)
{
	return *((volatile uint16_t*)Address);
}

uint8_t MyFlash_ReadByte(uint32_t Address)
{
	return *((volatile uint8_t*)Address);
}

HAL_StatusTypeDef MyFlash_ErasePage(uint32_t PageAddress)
{
	HAL_StatusTypeDef status= HAL_OK;
	uint32_t sectorError=0;

	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef eraseInit={0};
	eraseInit.Banks=FLASH_BANK_1;
	eraseInit.NbPages=1;
	eraseInit.PageAddress=PageAddress;
	eraseInit.TypeErase=FLASH_TYPEERASE_PAGES;

	status = HAL_FLASHEx_Erase(&eraseInit,&sectorError);
	HAL_FLASH_Lock();

	if(status!=HAL_OK)
	{
		//错误处理
		return status;
	}
	return HAL_OK;
}

HAL_StatusTypeDef MyFlash_EraseAllPages(void)
{
	HAL_StatusTypeDef status= HAL_OK;
	uint32_t sectorError=0;

	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef eraseInit={0};
	eraseInit.Banks=FLASH_BANK_1;
	eraseInit.TypeErase=FLASH_TYPEERASE_MASSERASE;

	status = HAL_FLASHEx_Erase(&eraseInit,&sectorError);
	HAL_FLASH_Lock();

	if(status!=HAL_OK)
	{
		//错误处理
		return status;
	}
	return HAL_OK;
}
//写入前要先解锁，再上锁
void MyFlash_ProgramHalfWord(uint32_t Address,uint16_t Data)
{
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Address,Data);
}

void MyFlash_ProgramWord(uint32_t Address,uint32_t Data)
{
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Address,Data);
}
