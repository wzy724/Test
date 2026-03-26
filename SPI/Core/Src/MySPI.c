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

	HAL_SPI_TransmitReceive(&hspi1,&ByteSend,&ByteReceive,1,HAL_MAX_DELAY);

	return ByteReceive;
}
