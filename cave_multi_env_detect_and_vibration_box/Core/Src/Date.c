/*
 * Date.c
 *
 *  Created on: 2026年3月12日
 *      Author: 17629
 */
#include <string.h>
#include <stdio.h>
#include "rtc.h"
#include "main.h"
#include "Meau.h"
#include "usart.h"

uint8_t CNT=0;
uint8_t state = 0;
uint8_t UART_ITFlag = 0;
char Temp[100];
char OrgRX_Local[100];

extern RTC_DateTypeDef RTC_Date;
extern RTC_TimeTypeDef RTC_Time;
extern char OrgRX[100];


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart==&huart1)
    {


        OrgRX[Size]='\0';
        strcpy(OrgRX_Local, OrgRX);
        UART_ITFlag=1;
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1,(uint8_t*)OrgRX,100);

    }
}


void Date_Process(void)
{
    if(UART_ITFlag==0) return;
    UART_ITFlag=0;

    if(state==0)
    {
        strcpy(Temp,"Do you want to change Date?(yes or no)\r\n");
        HAL_UART_Transmit(&huart1,(uint8_t*)Temp,strlen(Temp),100);
        state=1;
    }
    else if(state==1)
    {
        if(strcmp(OrgRX_Local, "yes")==0)
        {
            strcpy(Temp,"Please enter the value you want to modify in the format (20XX-XX-XX XX:XX:XX)\r\n");
            HAL_UART_Transmit(&huart1,(uint8_t*)Temp, strlen(Temp),150);
            state=2;
        }
        else
        {
            strcpy(Temp,"GoodBye\r\n");
            HAL_UART_Transmit(&huart1,(uint8_t*)Temp,strlen(Temp),50);
            state = 0;
        }
    }
    else if(state==2)
    {
        int year,month,day;
        int hour,minute,second;

        sscanf(OrgRX_Local,"20%d-%d-%d %d:%d:%d",//提取sscanf特定字符位置转int
               &year,&month,&day,
               &hour,&minute,&second);

        RTC_Date.Year=year;
        RTC_Date.Month=month;
        RTC_Date.Date=day;
        RTC_Date.WeekDay=RTC_WEEKDAY_MONDAY;

        RTC_Time.Hours=hour;
        RTC_Time.Minutes=minute;
        RTC_Time.Seconds=second;

        HAL_RTC_SetDate(&hrtc,&RTC_Date,RTC_FORMAT_BIN);
        HAL_RTC_SetTime(&hrtc,&RTC_Time,RTC_FORMAT_BIN);

        strcpy(Temp,"Editing Success!\r\n");
        HAL_UART_Transmit(&huart1,(uint8_t*)Temp,strlen(Temp),50);

        state=0; // 复位
    }
}

void Date_Init(RTC_DateTypeDef* RTC_Date, RTC_TimeTypeDef* RTC_Time)
{
    HAL_RTC_GetDate(&hrtc,RTC_Date,RTC_FORMAT_BIN);
    HAL_RTC_GetTime(&hrtc,RTC_Time,RTC_FORMAT_BIN);
}
