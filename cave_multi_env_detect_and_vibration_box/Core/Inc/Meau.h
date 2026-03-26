/*
 * Meau.h
 *
 *  Created on: 2026年3月11日
 *      Author: 17629
 */

#ifndef INC_MEAU_H_
#define INC_MEAU_H_
extern uint8_t ModeFlag;
extern int8_t I2C_DATA[14];
extern RTC_DateTypeDef RTC_Date;
extern RTC_TimeTypeDef RTC_Time;
void Meau_switch(void);
void Meau0_Init(void);
#endif /* INC_MEAU_H_ */
