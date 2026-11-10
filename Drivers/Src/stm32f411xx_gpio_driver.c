/*
 * stm32f411xx_gpio_driver.c
 *
 *  Created on: Feb 18, 2026
 *      Author: joshi
 */

#include "stm32f411xx_gpio_driver.h"

/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void GPIO_PeriClkControl(GPIO_RegDefTypedef *pGPIOx, uint8_t EnorDi){
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
	}else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
	}
}


/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function initializes a GPIO port
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void GPIO_Init(GPIO_HandleTypedef *pGPIO_Handle){
	GPIO_PeriClkControl(pGPIO_Handle->pGPIOx, ENABLE);
	uint32_t temp=0;

	// configure mode of GPIO pin
	if(pGPIO_Handle->GPIO_PinConfig.PinMode <= GPIO_MODE_ANALOG)
	{
		//non interrupt mode
		temp = pGPIO_Handle->GPIO_PinConfig.PinMode << (2 * pGPIO_Handle->GPIO_PinConfig.PinNumber);
		pGPIO_Handle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIO_Handle->GPIO_PinConfig.PinNumber)); // Clear
		pGPIO_Handle->pGPIOx->MODER |= temp;
	}else	// EXTI configuration
	{
		if(pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_MODE_IT_FT)
		{
			// configure FTSR
			EXTI->FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.PinNumber);
			// clear corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIO_Handle->GPIO_PinConfig.PinNumber);

		}else if(pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_MODE_IT_RT)
		{
			// configure RTSR
			EXTI->RTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.PinNumber);
			// clear corresponding FTSR bit
			EXTI->FTSR &= ~(1 << pGPIO_Handle->GPIO_PinConfig.PinNumber);

		}else if(pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_MODE_IT_RFT)
		{
			// configure RTSR
			EXTI->RTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.PinNumber);
			// configure FTSR
			EXTI->FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.PinNumber);
		}

		// configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIO_Handle->GPIO_PinConfig.PinNumber / 4;
		uint8_t temp2 = pGPIO_Handle->GPIO_PinConfig.PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIO_Handle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

		// enable exti 	interrupt delivery system using IMR
		EXTI->IMR |= (1 << pGPIO_Handle->GPIO_PinConfig.PinNumber);
	}
	temp=0;

	// configure output type of GPIO pin
	temp = pGPIO_Handle->GPIO_PinConfig.PinOPType << (pGPIO_Handle->GPIO_PinConfig.PinNumber);
	pGPIO_Handle->pGPIOx->OTYPER &= ~(0x1 << pGPIO_Handle->GPIO_PinConfig.PinNumber); // Clear
	pGPIO_Handle->pGPIOx->OTYPER |= temp;
	temp=0;

	// configure output speed of GPIO pin
	temp = pGPIO_Handle->GPIO_PinConfig.PinSpeed << (2* pGPIO_Handle->GPIO_PinConfig.PinNumber);
	pGPIO_Handle->pGPIOx->OSPEEDR &= ~(0x3 << (2* pGPIO_Handle->GPIO_PinConfig.PinNumber)); // Clear
	pGPIO_Handle->pGPIOx->OSPEEDR |= temp;
	temp=0;

	// configure PUPD type of GPIO pin
	temp = pGPIO_Handle->GPIO_PinConfig.PinPuPdControl << (2 * pGPIO_Handle->GPIO_PinConfig.PinNumber);
	pGPIO_Handle->pGPIOx->PUPDR &= ~(0x3 << (2* pGPIO_Handle->GPIO_PinConfig.PinNumber)); // Clear
	pGPIO_Handle->pGPIOx->PUPDR |= temp;
	temp=0;

	// configure alt functionality of GPIO pin
	if(pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_MODE_ALTFN){
		// configure alt func register
		uint8_t temp1, temp2;
		temp1 = pGPIO_Handle->GPIO_PinConfig.PinNumber / 8;
		temp2 = pGPIO_Handle->GPIO_PinConfig.PinNumber % 8;
		pGPIO_Handle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); // Clear
		pGPIO_Handle->pGPIOx->AFR[temp1] |= (
				pGPIO_Handle->GPIO_PinConfig.PinAltFuncMode << (4 * temp2)
				);
	}
}



/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             - This function de-initializes a GPIO port
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void GPIO_DeInit(GPIO_RegDefTypedef *pGPIOx){
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}
}


/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             - This function reads data from input pin
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  0 or 1
 *
 * @Note              -  GPIOx_IDR is a read only register.

 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDefTypedef *pGPIOx, uint8_t PinNum){
	uint8_t value;
	value = (uint8_t) (pGPIOx->IDR >> PinNum) & 0x00000001;
	return value;
}


/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             - This function reads data from input port
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  16 bit value
 *
 * @Note              -  GPIOx_IDR is read only

 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDefTypedef *pGPIOx){
	uint8_t value;
	value = pGPIOx->IDR;
	return value;
}


/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             - This function writes data to output pin
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -

 */
void GPIO_WriteToOutputPin(GPIO_RegDefTypedef *pGPIOx, uint8_t PinNum, uint8_t Value)
{
	if(Value == SET){
		pGPIOx->ODR |= (1 << PinNum);
	}else{
		pGPIOx->ODR &= ~(1 << PinNum);
	}
}


/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             - This function writes data to output port
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -

 */
void GPIO_WriteToOutputPort(GPIO_RegDefTypedef *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}



/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             - This function toggles output pin
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -

 */
void GPIO_ToggleOutputPin(GPIO_RegDefTypedef *pGPIOx, uint8_t PinNum)
{
	pGPIOx->ODR ^= (1 << PinNum);	// EX-OR operation
}

/*
 * IRQ Configuration and ISR handling
 */

/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             - This function configures GPIO Interrupt Requests
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -

 */
void GPIO_IRQConfig(uint8_t IRQNum, uint8_t IRQPriority, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNum <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNum);

		}else if(IRQNum >=32 && IRQNum <=63) // 32 to 63
		{
			// program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNum%32));

		}else if(IRQNum >= 64 && IRQNum <= 95) // 64 to 95
		{
			// program ISER2 register
			*NVIC_ISER1 |= (1 << (IRQNum%64));

		}
	}else
	{
		if(IRQNum <= 31)
		{
			// program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNum);

		}else if(IRQNum >=32 && IRQNum <=63) // 32 to 63
		{
			// program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNum%32));

		}else if(IRQNum >= 64 && IRQNum <= 95) // 64 to 95
		{
			// program ICER2 register
			*NVIC_ICER1 |= (1 << (IRQNum%32));

		}
	}

	// set priority
	GPIO_IRQPriorityConfig(IRQNum, IRQPriority);
}


/*********************************************************************
 * @fn      		  - GPIOPriorityConfig
 *
 * @brief             - This function configures GPIO Interrupt Priority
 *
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -

 */
void GPIO_IRQPriorityConfig(uint8_t IRQNum, uint32_t IRQPriority)
{
	uint8_t iprx = IRQNum / 4;
	uint8_t iprx_section = IRQNum % 4;
	uint8_t shift_amt = ((8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED));
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amt);
}


void GPIO_IRQHandling(uint8_t PinNum)
{
	//clear the exti pr register corresponding to the pin number
	if(EXTI->PR & ( 1 << PinNum))
	{
		//clear
		EXTI->PR |= ( 1 << PinNum);
	}

}
