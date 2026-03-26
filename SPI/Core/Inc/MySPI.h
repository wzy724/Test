/*
 * MySPI.h
 *
 *  Created on: 2026年2月12日
 *      Author: 17629
 */

#ifndef INC_MYSPI_H_
#define INC_MYSPI_H_

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "spi.h"

void SSPI_Start(void);
void SSPI_Stop(void);
uint8_t SSPI_SwapByte(uint8_t ByteSend);

#endif /* INC_MYSPI_H_ */
