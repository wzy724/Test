/*
 * PID.h
 *
 *  Created on: 2026年3月25日
 *      Author: 17629
 */

#ifndef INC_PID_H_
#define INC_PID_H_

typedef struct
{
	float Target;
	float Actual;
	float Out;

	float Kp;
	float Ki;
	float Kd;

	float Error;
	float Errored;
	float ErrorSum;

	float OutMAX;
	float OutMIN;

}PID_T;

void PID_Init(PID_T* p);
void PID_UpState(PID_T* p);


#endif /* INC_PID_H_ */
