/*
 * U8G2.h
 *
 *  Created on: 2026年2月9日
 *      Author: 17629
 */

#ifndef INC_U8G2_H_
#define INC_U8G2_H_
//使用须知，当成模板文件改名时，下面两个路径也要改，路径中任何名称变动时也要改为绝对路径
//暂时没有更好的办法。这样的工程，只有自己方便，ai暂时问不明白，希望有招一日可以找到老师解决

// 1. 包含必需的头文件（原main.c里的）
#include "C:/Users/17629/STM32CubeIDE/workspace_1.19.0/U8G2/u8g2/u8g2.h"
#include "C:/Users/17629/STM32CubeIDE/workspace_1.19.0/U8G2/u8g2/u8x8.h"
#include <string.h>
#include "stm32f1xx_hal.h"
#include "i2c.h"

// 2. 原main.c里的宏定义（完整迁移）
#define u8          unsigned char  // 类型别名
#define MAX_LEN     128            // 最大长度
#define OLED_ADDRESS 0x78          // OLED I2C地址
#define OLED_CMD    0x00           // 命令标志
#define OLED_DATA   0x40           // 数据标志

// 3. 声明CubeMX生成的I2C句柄（回调函数需要）
extern I2C_HandleTypeDef hi2c1;

// 4. 声明对外暴露的函数（main.c需要调用）
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void u8g2Init(u8g2_t *u8g2);


#endif /* INC_U8G2_H_ */
