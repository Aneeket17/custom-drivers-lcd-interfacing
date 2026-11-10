/*
 * stm32f411xx_gpio_driver.h
 *
 *  Created on: Feb 18, 2026
 *      Author: joshi
 */

#ifndef INC_STM32F411XX_GPIO_DRIVER_H_
#define INC_STM32F411XX_GPIO_DRIVER_H_

#include "stm32f411xx.h"

/*
 * Configuration structure for SPIx peripheral
 */
typedef struct{
	uint8_t PinNumber;			/*Possible values from @GPIO_PIN_NUM */
	uint8_t PinMode;			/*Possible values from @GPIO_PIN_MODES */
	uint8_t PinOPType;			/*Possible values from @GPIO_PIN_OUT_TYPES */
	uint8_t PinSpeed;			/*Possible values from @GPIO_PIN_SPEED */
	uint8_t PinPuPdControl;	/*Possible values from @GPIO_PIN_PUPD */
	uint8_t PinAltFuncMode;
}GPIO_PinConfigTypedef;


/*
 * Handle structure for GPIO pin
 */

typedef struct{
	GPIO_RegDefTypedef *pGPIOx;				/* This holds the base address of the GPIO port to which the pin belongs */
	GPIO_PinConfigTypedef GPIO_PinConfig;	/* Holds the GPIO configuration settings */
}GPIO_HandleTypedef;


/*
 * @GPIO_PIN_NUM
 * GPIO pin numbers
 */

#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_PIN_8		8
#define GPIO_PIN_9		9
#define GPIO_PIN_10 	10
#define GPIO_PIN_11		11
#define GPIO_PIN_12		12
#define GPIO_PIN_13		13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15



/* @GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4	/*GPIO Mode for Input Falling edge Trigger*/
#define GPIO_MODE_IT_RT		5	/*GPIO Mode for Input Rising edge Trigger*/
#define GPIO_MODE_IT_RFT	6	/*GPIO Mode for Input Rising and Falling edge Trigger*/


/* @GPIO_PIN_OUT_TYPES
 * GPIO pin output types
 */
#define GPIO_OUT_TYPE_PP	0	/*GPIO output type Push-Pull*/
#define GPIO_OUT_TYPE_OD	1	/*GPIO output type Open Drain*/


/* @GPIO_PIN_SPEED
 * GPIO pin possible speed modes
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3


/* @GPIO_PIN_PUPD
 * GPIO pin possible pull-up/pull-down macros
 */
#define GPIO_PIN_NO_PUPD 	0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2



/******************************************************************************************
 * 								APIs supported by this driver
 * 				For more information about the APIs, check the function description
 ******************************************************************************************/

/*
 * Peripheral clock setup
 */
void GPIO_PeriClkControl(GPIO_RegDefTypedef *pGPIOx, uint8_t EnorDi);

/*
 * Initialization and de-initialization
 */
void GPIO_Init(GPIO_HandleTypedef *pGPIO_Handle);
void GPIO_DeInit(GPIO_RegDefTypedef *pGPIOx);

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDefTypedef *pGPIOx, uint8_t PinNum);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDefTypedef *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDefTypedef *pGPIOx, uint8_t PinNum, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDefTypedef *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDefTypedef *pGPIOx, uint8_t PinNum);

/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNum, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNum, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNum);

#endif /* INC_STM32F411XX_GPIO_DRIVER_H_ */
