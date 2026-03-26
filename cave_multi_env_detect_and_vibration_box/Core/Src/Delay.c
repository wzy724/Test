#include "stm32f1xx_hal.h"
#include "tim.h"
/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
// 延时函数，直接读取定时器计数值实现阻塞等待

//换需要修改
void Delay_Init(void)
{
	HAL_TIM_Base_Start(&htim4);
}

void Delay_us(uint32_t us)
{
    uint32_t start = TIM4->CNT;   // 获取当前计数值
    uint32_t ticks = us;           // 需要等待的微秒数（因为 1 tick = 1us）
    while ((TIM4->CNT - start) < ticks);  // 等待计数器差值达到指定微秒数
}

// 毫秒延时（调用微秒延时）
void Delay_ms(uint32_t ms)
{
    while (ms--)
        Delay_us(1000);
}

// 秒级延时
void Delay_s(uint32_t s)
{
    while (s--)
        Delay_ms(1000);
}
