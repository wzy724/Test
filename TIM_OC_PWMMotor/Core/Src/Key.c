/*
 * Key.c
 *
 *  Created on: 2026年1月26日
 *      Author: 17629
 */
#include "stm32f1xx_hal.h"

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum=0;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==0);
		HAL_Delay(20);
		KeyNum=1;
	}

	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==0);
		HAL_Delay(20);
		KeyNum=2;
	}

	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)==GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)==0);
		HAL_Delay(20);
		KeyNum=3;
	}

	return KeyNum;
}
