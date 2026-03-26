/*
 * Key.c
 *
 *  Created on: 2026年2月19日
 *      Author: 17629
 */
#include "Key.h"
#include "gpio.h"

uint8_t Get_KeyNum(void)
{
	uint8_t KeyNum=0;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_RESET);
		HAL_Delay(20);
		KeyNum=1;
	}
	else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)==GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11)==GPIO_PIN_RESET);
		HAL_Delay(20);
		KeyNum=2;
	}
	return KeyNum;
}
