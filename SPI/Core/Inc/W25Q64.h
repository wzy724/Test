/*
 * W25Q64.h
 *
 *  Created on: 2026年2月12日
 *      Author: 17629
 */

#ifndef INC_W25Q64_H_
#define INC_W25Q64_H_

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);
void W25Q64_SectorErase(uint32_t Address);
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);

#endif /* INC_W25Q64_H_ */
