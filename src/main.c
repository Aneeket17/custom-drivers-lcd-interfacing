#include <stdint.h>
#include <string.h>
#include "stm32f411xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define button_pressed 0

void delay(){

	for(uint32_t i = 0; i<500000; i++);
}

int main(void){

	//	LED configuration
	GPIO_HandleTypedef gpio_led, gpio_button;
	memset(&gpio_led, 0, sizeof(gpio_led));
	memset(&gpio_button, 0, sizeof(gpio_button));

	gpio_led.pGPIOx = GPIOA;
	gpio_led.GPIO_PinConfig.PinNumber = GPIO_PIN_5;
	gpio_led.GPIO_PinConfig.PinMode = GPIO_MODE_OUT;
	gpio_led.GPIO_PinConfig.PinSpeed = GPIO_SPEED_FAST;
	gpio_led.GPIO_PinConfig.PinOPType = GPIO_OUT_TYPE_PP;
	gpio_led.GPIO_PinConfig.PinPuPdControl = GPIO_PIN_NO_PUPD;

	GPIO_PeriClkControl(GPIOA, ENABLE);
	GPIO_Init(&gpio_led);

	// user button configuration
	gpio_button.pGPIOx = GPIOC;
	gpio_button.GPIO_PinConfig.PinNumber = GPIO_PIN_13;
	gpio_button.GPIO_PinConfig.PinMode = GPIO_MODE_IT_FT;
	gpio_button.GPIO_PinConfig.PinSpeed = GPIO_SPEED_FAST;
	gpio_button.GPIO_PinConfig.PinPuPdControl = GPIO_PIN_NO_PUPD;

	GPIO_PeriClkControl(GPIOC, ENABLE);
	GPIO_Init(&gpio_button);

	//IRQ configuration
	GPIO_IRQConfig(IRQ_EXTI15_10, 15, ENABLE);

	return 0;
}

void EXTI15_10_IRQHandler(){
	GPIO_IRQHandling(GPIO_PIN_13);
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
}

