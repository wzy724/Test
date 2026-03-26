/*
 * DHT11.c
 *
 *  Created on: 2026年3月10日
 *      Author: 17629
 */

#include "stm32f1xx_hal.h"
#include "Delay.h"

#define DHT11_PORT 		GPIOA
#define DHT11_PIN 		GPIO_PIN_5

void DHT11_Switch_to_PP(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = DHT11_PIN;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;


	  HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

void DHT11_Switch_to_IPU(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = DHT11_PIN;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Mode =GPIO_MODE_INPUT ;


	  HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

void DHT11_WakeUp(void)
{
	DHT11_Switch_to_PP();
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
	Delay_ms(20);
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
	Delay_us(30);
	DHT11_Switch_to_IPU();
}

uint8_t DHT11_AckCheck(void)
{
	uint16_t TempTime=0;
	uint8_t ExistFlag1=0;
	uint8_t ExistFlag2=0;

	while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) && TempTime<100)//因为上拉，所以初始是高电平，这是检测有高拉低得变化，如果超过100us就说明没有外设再操作
	{
		TempTime++;
		Delay_us(1);
	}
	if(TempTime<100) ExistFlag1=1;

	TempTime=0;

	while(!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) && TempTime<100)//因为是低电平，这是检测有低放高得变化，如果超过100us就说明没有外设再操作
	{
		TempTime++;
		Delay_us(1);
	}
	if(TempTime<100) ExistFlag2=1;

	return ExistFlag1 & ExistFlag2;
}

uint8_t DHT11_RXByte(void)
{
	uint16_t TimeOut=0;
	uint8_t Byte=0x00;
	uint8_t temp=0x80;
	for(uint8_t i=0;i<8;i++)
	{
		while(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) && TimeOut<1000)//因为应答后上拉，要同步一下时序，这是检测有高拉低得变化，
		{
			TimeOut++;
			Delay_us(10);
		}
		if(TimeOut>=1000) return 0xFF;
		TimeOut=0;
		while(!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) && TimeOut<1000)//因为是低电平，这是检测有低放高得变化
		{
			TimeOut++;
			Delay_us(10);
		}
		if(TimeOut>=1000) return 0xFF;

		Delay_us(40);//因为逻辑0和1之间得区别是高电平时间，低点平都为50us，高电平分别是是24，74。
					 //逻辑0切换至高电平延时后低电平计时40us会到下个电平得低电平处这时读取就是0，之后跳过第一个while，进而重新对下一个逻辑判断
					 //逻辑1切换至高电平时，延时40us会读到自身高电平，所以为1.之后经过两个while,不然时序会乱。进而重新对下一个逻辑判断
		if(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
		{
			Byte|=(temp>>i);
		}
	}
	return Byte;
}

uint8_t DHT11_RXData(uint8_t* Temper,uint8_t* Humidity)
{
	uint8_t Buff[5]={0};
	DHT11_WakeUp();
	if(DHT11_AckCheck())
	{
		for(uint8_t i=0;i<5;i++)
		{
			Buff[i]=DHT11_RXByte();
			if(Buff[i]==0xFF) return 0;
		}
		if ((Buff[0]+Buff[1]+Buff[2]+Buff[3])%256==Buff[4])
		{
			*Temper=Buff[2];
			*Humidity=Buff[0];
			return 1;
		}
		else return 0;
	}
	else return 0;
}
