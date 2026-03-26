/*
 * NEC.c
 *
 *  Created on: 2026年3月10日
 *      Author: 17629
 */
#include "NEC.h"
#include "tim.h"

volatile uint32_t NECData;
volatile uint8_t DataCnt;
volatile uint16_t ICTime;
volatile uint8_t EncodeFlag;
uint8_t ValidData = 0;            // 新增：有效数据标志

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3 && htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)//HAL_TIM_ACTIVE_CHANNEL_1不等于TIM_CHANNEL_1
	{

		/*#define __HAL_TIM_GET_COMPARE(__HANDLE__, __CHANNEL__)         htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1,不成立
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1) :\	 (__CHANNEL__) == TIM_CHANNEL_1)
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3) :\
   ((__HANDLE__)->Instance->CCR4))*/

		ICTime=__HAL_TIM_GET_COMPARE(htim,TIM_CHANNEL_1);
		__HAL_TIM_SET_COUNTER(htim,0);
		if(ICTime>=12500&&ICTime<=15000)
		{
			NECData=0;
			DataCnt=0;
			ValidData=0;
		}
		else if(ICTime>=900&&ICTime<=1300)
		{
			NECData>>=1;
			DataCnt+=1;
		}
		else if(ICTime>=2000&&ICTime<=2500)
		{
			NECData>>=1;
			NECData|=(0x80000000);
			DataCnt+=1;
		}
		else if(ICTime >= 10500 && ICTime < 12500)   // 重复码，根据实测调整
		{
		    if( ValidData==1 )  // 这样保证有引导码触发了才清零，这样就一定有数据。就不会按前干扰了
		    {
		        EncodeFlag = 1;   // 触发重复
		    }
		    DataCnt = 0;           // 重置计数器，避免干扰后续数据
		}

		if(DataCnt==32)
		{
			uint8_t add = (NECData)&(0xFF);
			uint8_t addi = (NECData>>8)&(0xFF);
			uint8_t cmd = (NECData>>16)&(0xFF);
			uint8_t cmdi = (NECData>>24)&(0xFF);

			if(add == (uint8_t)(~addi) && cmd == (uint8_t)(~cmdi))//取反后会变成int类型
			{
				EncodeFlag=1;
				ValidData=1;
			}
			DataCnt=0;//防止没有新的引导
		}
	}
}

void NEC_GetCmd(uint8_t* Cmd)
{
	if(EncodeFlag==1)
	{
		EncodeFlag=0;
		*Cmd = (NECData>>16)&(0xFF);
	}
	EncodeFlag=0;
	NECData=0x00000000;
}
