#include "stm32f411xx_timer_driver.h"

#define TIM_CR1_CEN       (1U << 0)
#define TIM_CR1_ARPE      (1U << 7)
#define TIM_EGR_UG        (1U << 0)
#define TIM2_TIM5_MAX_ARR 0xFFFFFFFFU
#define TIM3_TIM4_MAX_ARR 0xFFFFU
#define TIM_MAX_PRESCALER 0x10000U

static uint8_t TIM_IsSupported(TIM_RegDefTypedef *pTIMx)
{
	return (uint8_t)((pTIMx == TIM2) || (pTIMx == TIM3) ||
					 (pTIMx == TIM4) || (pTIMx == TIM5));
}

static uint8_t TIM_Is32Bit(TIM_RegDefTypedef *pTIMx)
{
	return (uint8_t)((pTIMx == TIM2) || (pTIMx == TIM5));
}

static void TIM_EnableClock(TIM_RegDefTypedef *pTIMx)
{
	if (pTIMx == TIM2)
	{
		TIM2_PCLK_EN();
	}
	else if (pTIMx == TIM3)
	{
		TIM3_PCLK_EN();
	}
	else if (pTIMx == TIM4)
	{
		TIM4_PCLK_EN();
	}
	else
	{
		TIM5_PCLK_EN();
	}
}

TIM_StatusTypeDef TIM_BaseInit(TIM_HandleTypedef *pTIMHandle)
{
	uint32_t prescaler_divisor;
	uint32_t max_period;

	if ((pTIMHandle == NULL) || (TIM_IsSupported(pTIMHandle->pTIMx) == 0U) ||
		(pTIMHandle->Config.TimerClockHz == 0U) ||
		(pTIMHandle->Config.CounterFrequencyHz == 0U) ||
		(pTIMHandle->Config.Period == 0U))
	{
		return TIM_ERROR;
	}

	if ((TIM_Is32Bit(pTIMHandle->pTIMx) != 0U))
	{
		max_period = TIM2_TIM5_MAX_ARR;
	}
	else
	{
		max_period = TIM3_TIM4_MAX_ARR;
	}

	if (pTIMHandle->Config.Period > max_period)
	{
		return TIM_ERROR;
	}

	if ((pTIMHandle->Config.TimerClockHz %
		 pTIMHandle->Config.CounterFrequencyHz) != 0U)
	{
		return TIM_ERROR;
	}

	prescaler_divisor = pTIMHandle->Config.TimerClockHz /
						pTIMHandle->Config.CounterFrequencyHz;
	if ((prescaler_divisor == 0U) ||
		(prescaler_divisor > TIM_MAX_PRESCALER))
	{
		return TIM_ERROR;
	}

	TIM_EnableClock(pTIMHandle->pTIMx);

	pTIMHandle->pTIMx->CR1 = 0U;
	pTIMHandle->pTIMx->CR2 = 0U;
	pTIMHandle->pTIMx->SMCR = 0U;
	pTIMHandle->pTIMx->DIER = 0U;
	pTIMHandle->pTIMx->PSC = prescaler_divisor - 1U;
	pTIMHandle->pTIMx->ARR = pTIMHandle->Config.Period;
	pTIMHandle->pTIMx->CNT = 0U;
	pTIMHandle->pTIMx->EGR = TIM_EGR_UG;
	pTIMHandle->pTIMx->SR = 0U;
	pTIMHandle->pTIMx->CR1 = TIM_CR1_ARPE;
	pTIMHandle->IsInitialized = 1U;
	pTIMHandle->IsRunning = 0U;

	return TIM_OK;
}

TIM_StatusTypeDef TIM_Start(TIM_HandleTypedef *pTIMHandle)
{
	if ((pTIMHandle == NULL) || (TIM_IsSupported(pTIMHandle->pTIMx) == 0U) ||
		(pTIMHandle->IsInitialized == 0U))
	{
		return TIM_ERROR;
	}

	pTIMHandle->pTIMx->CR1 |= TIM_CR1_CEN;
	pTIMHandle->IsRunning = 1U;
	return TIM_OK;
}

TIM_StatusTypeDef TIM_Stop(TIM_HandleTypedef *pTIMHandle)
{
	if ((pTIMHandle == NULL) || (TIM_IsSupported(pTIMHandle->pTIMx) == 0U) ||
		(pTIMHandle->IsInitialized == 0U))
	{
		return TIM_ERROR;
	}

	pTIMHandle->pTIMx->CR1 &= ~TIM_CR1_CEN;
	pTIMHandle->IsRunning = 0U;
	return TIM_OK;
}

TIM_StatusTypeDef TIM_GetCounter(TIM_HandleTypedef *pTIMHandle,
								 uint32_t *counter)
{
	if ((pTIMHandle == NULL) || (counter == NULL) ||
		(TIM_IsSupported(pTIMHandle->pTIMx) == 0U) ||
		(pTIMHandle->IsInitialized == 0U) ||
		(pTIMHandle->IsRunning == 0U))
	{
		return TIM_ERROR;
	}

	*counter = pTIMHandle->pTIMx->CNT;
	return TIM_OK;
}
