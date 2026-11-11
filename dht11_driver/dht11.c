#include <stdint.h>

#include "dht11.h"

static DHT11_StatusTypeDef DHT11_WaitForLevel(GPIO_HandleTypedef *dht11,
											  TIM_HandleTypedef *timer,
											  uint32_t level,
											  uint32_t timeout_us);
static DHT11_StatusTypeDef DHT11_DelayUs(TIM_HandleTypedef *timer,
										 uint32_t microseconds);
static DHT11_StatusTypeDef DHT11_DelayMs(TIM_HandleTypedef *timer,
										 uint32_t milliseconds);
static uint32_t DHT11_ReadPin(GPIO_HandleTypedef *dht11);
static DHT11_StatusTypeDef DHT11_DriveLow(GPIO_HandleTypedef *dht11);
static DHT11_StatusTypeDef DHT11_Release(GPIO_HandleTypedef *dht11);
static uint8_t DHT11_IsHandleValid(const GPIO_HandleTypedef *dht11);

static uint8_t DHT11_IsHandleValid(const GPIO_HandleTypedef *dht11)
{
    if ((dht11 == NULL) || (dht11->GPIO_PinConfig.PinNumber > GPIO_PIN_15))
    {
        return 0U;
    }

    return (uint8_t)((dht11->pGPIOx == GPIOA) ||
                     (dht11->pGPIOx == GPIOB) ||
                     (dht11->pGPIOx == GPIOC) ||
                     (dht11->pGPIOx == GPIOD) ||
                     (dht11->pGPIOx == GPIOE) ||
                     (dht11->pGPIOx == GPIOH));
}

static DHT11_StatusTypeDef DHT11_WaitForLevel(GPIO_HandleTypedef *dht11,
											  TIM_HandleTypedef *timer,
											  uint32_t level,
											  uint32_t timeout_us)
{
    uint32_t start;
    uint32_t now;

    if ((level > 1U) || (TIM_GetCounter(timer, &start) != TIM_OK))
    {
        return DHT11_ERROR;
    }

    while (DHT11_ReadPin(dht11) != level)
    {
        if (TIM_GetCounter(timer, &now) != TIM_OK)
        {
            return DHT11_ERROR;
        }

        if ((uint32_t)(now - start) >= timeout_us)
        {
            return DHT11_TIMEOUT;
        }
    }

    return DHT11_OK;
}

DHT11_StatusTypeDef DHT11_Start(GPIO_HandleTypedef *dht11,
								TIM_HandleTypedef *timer)
{
    DHT11_StatusTypeDef status;

    if ((DHT11_IsHandleValid(dht11) == 0U) || (timer == NULL) ||
        (timer->Config.CounterFrequencyHz != 1000000U) ||
        (timer->Config.Period != 0xFFFFFFFFU))
    {
        return DHT11_ERROR;
    }

    // 1. Request a reading from the sensor.
    status = DHT11_DriveLow(dht11);
    if (status != DHT11_OK)
    {
        return status;
    }
    status = DHT11_DelayMs(timer, 20U);
    if (status != DHT11_OK)
    {
        return status;
    }

    // 2. Release the data line.
    status = DHT11_Release(dht11);
    if (status != DHT11_OK)
    {
        return status;
    }

    // 3. Wait for the sensor to pull the line LOW.
    status = DHT11_WaitForLevel(dht11, timer, 0U, 120U);
    if (status != DHT11_OK)
    {
        return status;
    }

    // 4. Wait for the sensor to pull the line HIGH.
    status = DHT11_WaitForLevel(dht11, timer, 1U, 120U);
    if (status != DHT11_OK)
    {
        return status;
    }

    // 5. Wait for the HIGH response to end.
    //    The line goes LOW for the first data bit.
    status = DHT11_WaitForLevel(dht11, timer, 0U, 120U);
    if (status != DHT11_OK)
    {
        return status;
    }

    return DHT11_OK;
}

static DHT11_StatusTypeDef DHT11_DriveLow(GPIO_HandleTypedef *dht11)
{
    uint32_t pin;

    if (DHT11_IsHandleValid(dht11) == 0U)
    {
        return DHT11_ERROR;
    }

    pin = dht11->GPIO_PinConfig.PinNumber;
    dht11->pGPIOx->BSRR = 1U << (pin + 16U); // Set the pin LOW using bits 16-31 of the BSRR register
    dht11->pGPIOx->MODER &= ~(0x3U << (2U * pin));
    dht11->pGPIOx->MODER |= 0x1U << (2U * pin);

    return DHT11_OK;
}

static DHT11_StatusTypeDef DHT11_Release(GPIO_HandleTypedef *dht11)
{
    uint32_t pin;

    if (DHT11_IsHandleValid(dht11) == 0U)
    {
        return DHT11_ERROR;
    }

    pin = dht11->GPIO_PinConfig.PinNumber;
    dht11->pGPIOx->PUPDR &= ~(0x3U << (2U * pin));
    dht11->pGPIOx->PUPDR |= (uint32_t)GPIO_PIN_PU << (2U * pin);
    dht11->pGPIOx->MODER &= ~(0x3U << (2U * pin));

    return DHT11_OK;
}

static uint32_t DHT11_ReadPin(GPIO_HandleTypedef *dht11)
{
    return (uint32_t)((dht11->pGPIOx->IDR & (1U << dht11->GPIO_PinConfig.PinNumber)) != 0U);
}

static DHT11_StatusTypeDef DHT11_DelayUs(TIM_HandleTypedef *timer,
										 uint32_t microseconds)
{
    uint32_t start;
    uint32_t now;

    if (TIM_GetCounter(timer, &start) != TIM_OK)
    {
        return DHT11_ERROR;
    }
    now = start;

    while ((uint32_t)(now - start) < microseconds)
    {
        if (TIM_GetCounter(timer, &now) != TIM_OK)
        {
            return DHT11_ERROR;
        }
    }

    return DHT11_OK;
}

static DHT11_StatusTypeDef DHT11_DelayMs(TIM_HandleTypedef *timer,
										 uint32_t milliseconds)
{
    while (milliseconds > 0U)
    {
        DHT11_StatusTypeDef status = DHT11_DelayUs(timer, 1000U);
        if (status != DHT11_OK)
        {
            return status;
        }
        --milliseconds;
    }

    return DHT11_OK;
}