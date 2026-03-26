/*
 * op.c
 *
 *  Created on: 2026年3月13日
 *      Author: 17629
 */

#include "op.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "tim.h"
#include "Meau.h"
#include "Delay.h"
#include "MPU6050.h"
#include "Date.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include <stdio.h>

uint32_t BuzzTime=0;
uint32_t BLTTime=0;
int8_t I2C_DATA[14];
uint8_t WarnFlag=0;
uint8_t ModeFlag=0;
uint8_t BuzzFlag=0;

void MANUALSet_Duty(void)
{
	int16_t temp=__HAL_TIM_GET_COUNTER(&htim1);
	  if(temp > 100)
	  {
	    temp = 100;
	    __HAL_TIM_SET_COUNTER(&htim1, 100);
	  }
	  else if(temp < 0)
	  {
	    temp = 0;
	    __HAL_TIM_SET_COUNTER(&htim1, 0);
	  }

		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, temp);


}

void Mode_Switch(void)
{
	if(password==1)//中断里只置1，就不会反复反转，挪到外面确认中断完成后才进行反转
	{
		ModeFlag=!ModeFlag;
		Delay_ms(100);
		password=0;
	}
	if(ModeFlag==0)
		{
		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,(ADC_DATA[0])*100/4095);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
		}
		else
		{
			MANUALSet_Duty();
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
		}
}

void Warning_Switch(int16_t AccX,  int16_t AccY,  int16_t AccZ,
		 int16_t GyroX, int16_t GyroY, int16_t GyroZ)
{
	int16_t temp1,temp2,temp3,temp4,temp5,temp6;
	MPU6050_ReadBurst(MPU6050_ACCEL_XOUT_H, I2C_DATA, 14);
	if(Xacc>AccX){temp1=Xacc-AccX;}
		else {temp1=AccX-Xacc;}

	if(Yacc>AccY){temp2=Yacc-AccY;}
		else {temp2=AccY-Yacc;}

	if(Zacc>AccZ){temp3=Zacc-AccZ;}
		else {temp3=AccZ-Zacc;}

	if(Xgyr>GyroX){temp4=Xgyr-GyroX;}
		else {temp4=GyroX-Xgyr;}

	if(Ygyr>GyroY){temp5=Ygyr-GyroY;}
		else {temp5=GyroY-Ygyr;}

	if(Zgyr>GyroZ){temp6=Zgyr-GyroZ;}
		else {temp6=GyroZ-Zgyr;}

	if(temp1>45||temp2>45||temp3>45||temp4>45||temp5>45||temp6>45)
	{
		WarnFlag=1;

	}
	else {WarnFlag=0;}

	if(ModeFlag==0&&WarnFlag==1)
	{

		if(HAL_GetTick()>BuzzTime+500)
		{
			BuzzFlag=!BuzzFlag;
			BuzzTime=HAL_GetTick();
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			if(BuzzFlag==0)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
			}
			else if(BuzzFlag)
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
			}
		}

		    Date_Init(&RTC_Date, &RTC_Time);
		    char temp[64];
		    sprintf(temp, "Date:20%02d-%02d-%02d %02d:%02d:%02d Warning!!!",
		            RTC_Date.Year, RTC_Date.Month, RTC_Date.Date,
		            RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
		    if(HAL_GetTick()>BLTTime+3000)
		    {
		    	HAL_UART_Transmit(&huart1, (uint8_t*)temp, strlen(temp), 100);
		    	BLTTime=HAL_GetTick();
		    }

	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	}


}
