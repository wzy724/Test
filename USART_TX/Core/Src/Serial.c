/*
 * Serial.c
 *
 *  Created on: 2026年2月4日
 *      Author: 17629
 */
#include "stm32f1xx_hal.h"
#include "usart.h"
void Serial_SendByte(uint8_t TxData)
{
	HAL_UART_Transmit(&huart1,&TxData,1, HAL_MAX_DELAY);
}
void Serial_SendArray(uint8_t* Array,uint16_t Length)
{
	if(Array==NULL||Length==0)return;
	HAL_UART_Transmit(&huart1,Array,Length, HAL_MAX_DELAY);
}
void Serial_SendString(char* String)
{
	if(String == NULL) return;
	uint16_t i=0;
	while(String[i]!='\0')
	{
		i++;
	}
	HAL_UART_Transmit(&huart1,(const uint8_t *)String,i, HAL_MAX_DELAY);
}
uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result=1;
	while(Y--)
	{
		Result*=X;
	}
	return Result;
}
void Serial_SendNumber(uint32_t Number,uint16_t Length)
{
	if(Length>10||Length==0)return;
	for(uint8_t i=0;i<Length;i++)
	{
		uint8_t Temp=Number/Serial_Pow(10,Length-i-1)%10+'0';
		HAL_UART_Transmit(&huart1,&Temp,1, HAL_MAX_DELAY);
	}
}
