/*
 * NEC.h
 *
 *  Created on: 2026年3月10日
 *      Author: 17629
 */

#ifndef INC_NEC_H_
#define INC_NEC_H_

#include "main.h"

extern volatile uint32_t NECData;

#define key1 0x45
#define key2 0x46
#define key3 0x47

#define key4 0x44
#define key5 0x40
#define key6 0x43

#define key7 0x07
#define key8 0x15
#define key9 0x09

#define keyX 0x16
#define keyJ 0x0D
#define key0 0x19

#define keyup 0x18
#define keydown 0x52
#define keyleft 0x08
#define keyright 0x5A
#define keyok 0x1C

void NEC_GetCmd(uint8_t* Cmd);

#endif /* INC_NEC_H_ */
