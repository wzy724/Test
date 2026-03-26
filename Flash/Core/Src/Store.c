/*
 * Store.c
 *
 *  Created on: 2026年2月19日
 *      Author: 17629
 */
#include "MyFlash.h"

uint16_t Store_Data[512];
void Store_Init(void)
{
	if(MyFlash_ReadHalfWord(0x0800FC00)!=(0xA5A5))
	{
		MyFlash_ErasePage(0x0800FC00);
		MyFlash_ProgramHalfWord(0x0800FC00,0xA5A5);
		for(uint16_t i=1;i<512;i++)
		{
			MyFlash_ProgramHalfWord(0x0800FC00+i*2,0x0000);
		}
	}
	//如果不是第一次,读到sram数组里
	for(uint16_t i=0;i<512;i++)
	{
		Store_Data[i]=MyFlash_ReadHalfWord(0x0800FC00+i*2);
	}
}

void Store_Save(void)
{
	MyFlash_ErasePage(0x0800FC00);
	HAL_FLASH_Unlock();
	for(uint16_t i=0;i<512;i++)
		{
			MyFlash_ProgramHalfWord(0x0800FC00+i*2,Store_Data[i]);
		}
	HAL_FLASH_Lock();
}

void Store_Clear(void)
{
	for(uint16_t i=1;i<512;i++)
		{
			Store_Data[i]=0x0000;
		}
		Store_Save();
}
