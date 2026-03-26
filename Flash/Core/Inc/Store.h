/*
 * Store.h
 *
 *  Created on: 2026年2月19日
 *      Author: 17629
 */

#ifndef INC_STORE_H_
#define INC_STORE_H_
extern uint16_t Store_Data[512];
void Store_Init(void);
void Store_Save(void);
void Store_Clear(void);
#endif /* INC_STORE_H_ */
