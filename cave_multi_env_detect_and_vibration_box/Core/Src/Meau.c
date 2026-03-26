/*
 * Meau.c
 *
 *  Created on: 2026年3月11日
 *      Author: 17629
 */
#include "main.h"
#include "Meau.h"
#include "stm32f1xx_hal.h"
#include "NEC.h"
#include "OLED.h"
#include "DHT11.h"
#include "Delay.h"
#include "MPU6050.h"
#include "Date.h"
#include "op.h"
#include "tim.h"


uint8_t Temper;
uint8_t Humidity;
RTC_DateTypeDef RTC_Date;
RTC_TimeTypeDef RTC_Time;
int8_t meau_index=0;
int8_t meau_indexed=0;

#define light ADC_DATA[0]
#define sound ADC_DATA[1]

void MANUALSet_Duty(void);

void Meau0_Init(void)
{
	OLED_ShowString(0,0,"Contenst",OLED_8X16);
	OLED_ShowString(0,16,"home             -1/4",OLED_6X8);
	OLED_ShowString(0,24,"light&sound      -2/4",OLED_6X8);
	OLED_ShowString(0,32,"Temper&Humidity  -3/4",OLED_6X8);
	OLED_ShowString(0,40,"attitude         -4/4",OLED_6X8);

	OLED_ShowString(56,56,"0/4",OLED_6X8);
	OLED_Update();
}

void Meau1_Init(void)
{
	Date_Init(&RTC_Date,&RTC_Time);
	OLED_ShowString(24,0,"智能感知盒",OLED_8X16);
	OLED_ShowString(0,16,"日期:20  :  :  ",OLED_8X16);
	OLED_ShowString(0,32,"时间:  :  :  ",OLED_8X16);

	OLED_ShowNum(56,16,RTC_Date.Year,2,OLED_8X16);
	OLED_ShowNum(80,16,RTC_Date.Month,2,OLED_8X16);
	OLED_ShowNum(104,16,RTC_Date.Date,2,OLED_8X16);

	OLED_ShowNum(40,32,RTC_Time.Hours,2,OLED_8X16);
	OLED_ShowNum(64,32,RTC_Time.Minutes,2,OLED_8X16);
	OLED_ShowNum(88,32,RTC_Time.Seconds,2,OLED_8X16);

	OLED_ShowString(0,56,"Left",OLED_6X8);
	OLED_ShowString(98,56,"Right",OLED_6X8);
	OLED_ShowString(56,56,"1/4",OLED_6X8);
	OLED_Update();
}
void Meau2_Init(void)
{
	OLED_ShowString(0,0,"LED光强:00%",OLED_8X16);
	if(ModeFlag==0)
	{
	OLED_ShowNum(64, 0, (ADC_DATA[0])*100/4095,2 , OLED_8X16);
	OLED_ShowString(88,0,"自动",OLED_8X16);

	}
	else
	{

		OLED_ShowNum(64, 0, __HAL_TIM_GET_COUNTER(&htim1) , 2,OLED_8X16);
		OLED_ShowString(88,0,"手动",OLED_8X16);
	}


	OLED_ShowString(0,16,"环境光强:00%",OLED_8X16);
	OLED_ShowNum(72, 16, (4095-ADC_DATA[0])*100/4095,2 , OLED_8X16);

	OLED_ShowString(0,32,"声音:000%",OLED_8X16);
	OLED_ShowNum(40, 32, (ADC_DATA[1])*100/4095  ,3 , OLED_8X16);
	OLED_ShowString(0,56,"Left",OLED_6X8);
	OLED_ShowString(98,56,"Right",OLED_6X8);
	OLED_ShowString(56,56,"2/4",OLED_6X8);

	OLED_Update();
}
void Meau3_Init(void)
{

	if(DHT11_RXData(&Temper,&Humidity)==1)
	{
		Delay_ms(90);//串行通信每次读取最好要大点的间隔，不加卡死
		OLED_ShowString(0,0,"温度:00摄氏度",OLED_8X16);
		OLED_ShowNum(40, 0,Temper,2 , OLED_8X16);

		OLED_ShowString(0,16,"湿度:000%",OLED_8X16);
		OLED_ShowNum(40, 16, Humidity,3 , OLED_8X16);
		OLED_ShowString(0,32,"DHT11读取成功",OLED_8X16);
	}
	else OLED_ShowString(0,32,"DHT11读取失败",OLED_8X16);

	OLED_ShowString(0,56,"Left",OLED_6X8);
	OLED_ShowString(98,56,"Right",OLED_6X8);
	OLED_ShowString(56,56,"3/4",OLED_6X8);

	OLED_Update();
}
void Meau4_Init(void)
{

	OLED_ShowString(0,0," 角速度  姿 态",OLED_8X16);
	OLED_ShowString(0,16,"Xg:",OLED_6X8);
	OLED_ShowSignedNum(18, 16, Xgyr, 5, OLED_6X8);

	OLED_ShowString(0,24,"Yg:",OLED_6X8);
	OLED_ShowSignedNum(18, 24, Ygyr, 5, OLED_6X8);

	OLED_ShowString(0,32,"Zg:",OLED_6X8);
	OLED_ShowSignedNum(18, 32, Zgyr, 5, OLED_6X8);

	OLED_ShowString(66,16,"Xa:",OLED_6X8);
	OLED_ShowSignedNum(84, 16, Xacc, 5, OLED_6X8);

	OLED_ShowString(66,24,"Ya:",OLED_6X8);
	OLED_ShowSignedNum(84, 24, Yacc, 5, OLED_6X8);

	OLED_ShowString(66,32,"Za:",OLED_6X8);
	OLED_ShowSignedNum(84, 32, Zacc, 5, OLED_6X8);

	OLED_ShowString(8,42,"ShakeCheck:",OLED_6X8);
	if(ModeFlag==0)
	{OLED_ShowString(74,42,"Enable ",OLED_6X8);}
	else
	{OLED_ShowString(74,42,"Disable",OLED_6X8);}
	OLED_ShowString(0,56,"Left",OLED_6X8);
	OLED_ShowString(98,56,"Right",OLED_6X8);
	OLED_ShowString(56,56,"4/4",OLED_6X8);

	OLED_Update();
}

//版本一是通过延时指令来也就是上一个指令作为判断条件，可以用极少的代码实现遥控器对应页切换，但为了条件左右键的作用，采用读取后计时清除旧指令，同步到新设菜单码来控制菜单刷新
void Meau_switch(void)
{
		uint8_t Cmd=0;
		NEC_GetCmd(&Cmd);
		switch(Cmd)
		{
			case key0:meau_index=0;break;
			case key1:meau_index=1;break;
			case key2:meau_index=2;break;
			case key3:meau_index=3;break;
			case key4:meau_index=4;break;
			case keyleft:meau_index--;if(meau_index<0){meau_index=4;};break;
			case keyright:meau_index++;if(meau_index>4){meau_index=0;};break;
			case 0:break;
		}
		if(meau_index!=meau_indexed)//还是那个思路记录是不是第一次改变来清除上一页菜单
		{
			OLED_Clear();
			OLED_Update();
			meau_indexed=meau_index;
		}
		switch(meau_index)
		{
			case 0:Meau0_Init();break;
			case 1:Meau1_Init();break;
			case 2:Meau2_Init();break;
			case 3:Meau3_Init();break;
			case 4:Meau4_Init();break;
		}
}


