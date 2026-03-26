/*
 * MySPI.c
 *
 *  Created on: 2026年3月15日
 *      Author: 17629
 */
#include "stm32f1xx_hal.h"
#include "gpio.h"

void MySPI_W_SS(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, BitValue?GPIO_PIN_SET:GPIO_PIN_RESET);
}

void MySPI_W_SCK(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, BitValue?GPIO_PIN_SET:GPIO_PIN_RESET);
}

void MySPI_W_MOSI(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, BitValue?GPIO_PIN_SET:GPIO_PIN_RESET);
}

uint8_t MySPI_R_MISO(void)
{
	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
}

void MySPI_Init(void)
{
	MySPI_W_SS(1);
	MySPI_W_SCK(0);
}

void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

uint8_t MySPI_Swapbyte(uint8_t ByteSend)
{
	uint8_t ByteReceive=0x00;
	uint8_t i=0;
	for(i=0;i<8;i++)
	{
		MySPI_W_MOSI(ByteSend&&0x80>>i);
		MySPI_W_SCK(1);
		if(MySPI_R_MISO()==1)
		{}
	}
}
