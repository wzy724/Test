/*
 * U8G2.c
 *
 *  Created on: 2026年2月9日
 *      Author: 17629
 */

#include "U8G2.h"

// 1. 原main.c里的硬件I2C传输函数（完整迁移，逻辑不变）
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    static uint8_t buffer[128];
    static uint8_t buf_idx;
    uint8_t *data;

    switch (msg)
    {
        case U8X8_MSG_BYTE_INIT:
            MX_I2C1_Init(); // I2C初始化
            break;

        case U8X8_MSG_BYTE_START_TRANSFER:
            buf_idx = 0;
            break;

        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;
            while (arg_int > 0)
            {
                buffer[buf_idx++] = *data;
                data++;
                arg_int--;
            }
            break;

        case U8X8_MSG_BYTE_END_TRANSFER:
            if (HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDRESS, buffer, buf_idx, 1000) != HAL_OK)
            {
                return 0;
            }
            break;

        case U8X8_MSG_BYTE_SET_DC:
            break;

        default:
            return 0;
    }
    return 1;
}

// 2. 原main.c里的GPIO与延时函数（完整迁移，逻辑不变）
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_DELAY_100NANO:
            __NOP();
            break;

        case U8X8_MSG_DELAY_10MICRO:
            for (uint16_t n = 0; n < 320; n++)
            {
                __NOP();
            }
            break;

        case U8X8_MSG_DELAY_MILLI:
            HAL_Delay(1);
            break;

        case U8X8_MSG_DELAY_I2C:
            break;

        case U8X8_MSG_GPIO_I2C_CLOCK:
        case U8X8_MSG_GPIO_I2C_DATA:
        case U8X8_MSG_GPIO_MENU_SELECT:
        case U8X8_MSG_GPIO_MENU_NEXT:
        case U8X8_MSG_GPIO_MENU_PREV:
        case U8X8_MSG_GPIO_MENU_HOME:
            break;

        default:
            u8x8_SetGPIOResult(u8x8, 1);
            break;
    }
    return 1;
}

// 3. 原main.c里的u8g2初始化函数（完整迁移，逻辑不变）
void u8g2Init(u8g2_t *u8g2)
{
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
    u8g2_InitDisplay(u8g2);
    u8g2_SetPowerSave(u8g2, 0);
    u8g2_ClearBuffer(u8g2);
}
