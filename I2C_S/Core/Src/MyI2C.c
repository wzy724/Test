/*
 * MyI2C.c
 *
 *  Created on: 2026年2月10日
 *      Author: 17629
 */

#include "stm32f1xx_hal.h"
#include "gpio.h"

void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

void SI2C_W_SCL(uint8_t Bit)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, Bit);
	Delay_us(10);
}
void SI2C_W_SDA(uint8_t Bit)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, Bit);
	Delay_us(10);
}

uint8_t SI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11);
	Delay_us(10);
	return BitValue;
}

void SI2C_Start(void)
{
	SI2C_W_SDA(1);
	SI2C_W_SCL(1);

	SI2C_W_SDA(0);
	SI2C_W_SCL(0);
}

void SI2C_Stop(void)
{
	SI2C_W_SDA(0);

	SI2C_W_SCL(1);
	SI2C_W_SDA(1);
}

void SI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SI2C_W_SDA(Byte&(0x80>>i));
		SI2C_W_SCL(1);
		SI2C_W_SCL(0);
	}
}

uint8_t SI2C_ReceiveByte(void)
{
	SI2C_W_SDA(1);

	uint8_t i;
	uint8_t Value=0x00;
	for(i=0;i<8;i++)
	{
		SI2C_W_SCL(1);
		if(SI2C_R_SDA())
		{
			Value|=(0x80>>i);
		}
		SI2C_W_SCL(0);
	}
	return Value;
}

void SI2C_SendAck(uint8_t Ack)
{
	SI2C_W_SDA(Ack);
	SI2C_W_SCL(1);
	SI2C_W_SCL(0);
}

uint8_t SI2C_ReceiveAck(void)
{
	uint8_t Ack;
	SI2C_W_SDA(1);
	SI2C_W_SCL(1);
	Ack=SI2C_R_SDA();
	SI2C_W_SCL(0);
	return Ack;
}
