/*
 * PID.c
 *
 *  Created on: 2026年3月25日
 *      Author: 17629
 */
#include "stm32f1xx_hal.h"

#include "PID.h"

void PID_Init(PID_T* p)
{
	p->Error=0;
	p->Errored=0;
	p->ErrorSum=0;
	p->Target=0;
	p->Actual=0;
	p->Out=0;
}

void PID_UpState(PID_T* p)
{
	p->Errored=p->Error;

	p->Error=p->Target-p->Actual;

	if(p->Ki==0)p->ErrorSum=0;
	else p->ErrorSum+=p->Error;

	p->Out=p->Kp*p->Error  +  p->Ki*p->ErrorSum  +  p->Kd*(p->Error-p->Errored);

	if(p->Out>p->OutMAX)p->Out=p->OutMAX;
	if(p->Out<p->OutMIN)p->Out=p->OutMIN;
}
