/*
 * MySPI.c
 *
 *  Created on: 2026年2月12日
 *      Author: 17629
 */

#include "MySPI.h"

void SSPI_W_SS(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,BitValue);
}

void SSPI_W_SCK(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,BitValue);
}

void SSPI_W_MOSI(uint8_t BitValue)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,BitValue);
}

uint8_t SSPI_R_MISO(void)
{
	return HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6);
}

void SSPI_Start(void)
{
	SSPI_W_SS(0);
}

void SSPI_Stop(void)
{
	SSPI_W_SS(1);
}

uint8_t SSPI_SwapByte(uint8_t ByteSend)
{
	uint8_t ByteReceive=0x00;
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SSPI_W_MOSI(ByteSend&(0x80>>i));
		SSPI_W_SCK(1);
		if(!(!SSPI_R_MISO()))
		{
			ByteReceive|=0x80>>i;
		}
		SSPI_W_SCK(0);
	}
	return ByteReceive;
}
