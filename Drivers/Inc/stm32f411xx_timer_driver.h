#ifndef INC_STM32F411XX_TIMER_DRIVER_H_
#define INC_STM32F411XX_TIMER_DRIVER_H_

#include "stm32f411xx.h"

typedef enum
{
	TIM_OK = 0U,
	TIM_ERROR = 1U
} TIM_StatusTypeDef;

typedef struct
{
	uint32_t TimerClockHz;
	uint32_t CounterFrequencyHz;
	uint32_t Period;
} TIM_ConfigTypedef;

typedef struct
{
	TIM_RegDefTypedef *pTIMx;
	TIM_ConfigTypedef Config;
	uint8_t IsInitialized;
	uint8_t IsRunning;
} TIM_HandleTypedef;

TIM_StatusTypeDef TIM_BaseInit(TIM_HandleTypedef *pTIMHandle);
TIM_StatusTypeDef TIM_Start(TIM_HandleTypedef *pTIMHandle);
TIM_StatusTypeDef TIM_Stop(TIM_HandleTypedef *pTIMHandle);
TIM_StatusTypeDef TIM_GetCounter(TIM_HandleTypedef *pTIMHandle,
								 uint32_t *counter);

#endif /* INC_STM32F411XX_TIMER_DRIVER_H_ */
