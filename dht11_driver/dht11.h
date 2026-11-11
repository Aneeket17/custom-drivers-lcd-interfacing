#ifndef DHT11_H
#define DHT11_H

#include <stdint.h>
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_timer_driver.h"

typedef enum
{
    DHT11_OK,
    DHT11_ERROR,
    DHT11_TIMEOUT
} DHT11_StatusTypeDef;

DHT11_StatusTypeDef DHT11_Start(GPIO_HandleTypedef *dht11,
							   TIM_HandleTypedef *timer);

#endif
