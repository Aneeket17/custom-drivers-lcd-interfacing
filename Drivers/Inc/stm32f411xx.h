/*
 * stm32f411xx.h
 *
 *  Created on: Feb 14, 2026
 *      Author: joshi
 */

#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_

#include<stddef.h>
#include<stdint.h>

#define __vo volatile


/******************************************START: Processor specific details *********************************************/
/*
 *  ARM Cortex M4 Processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0		((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1		((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2		((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3		((__vo uint32_t*)0xE000E10C)


/*
 *  ARM Cortex M4 Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0		((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1		((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2		((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3		((__vo uint32_t*)0XE000E18C)


/*
 *  ARM Cortex M4 Processor NVIC Priority register Addresses
 */
#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE000E400)


/*
 * ARM Cortex M4 Processor NUmbe rf priority bits implemented in Priority register
 */
#define NO_PR_BITS_IMPLEMENTED			4

/*******************************************END: Processor specific details **********************************************/

/*
 * Some generic macros
 */
#define ENABLE 			1
#define DISABLE 		0
#define SET				ENABLE
#define	RESET			DISABLE


/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************
 */

/*
 * Bit position definition of CR1
 */
#define SPI_CR1_CPHA     				 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     				 2
#define SPI_CR1_BR   					 3
#define SPI_CR1_SPE     				 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     				 8
#define SPI_CR1_SSM      				 9
#define SPI_CR1_RXONLY      		 	10
#define SPI_CR1_DFF     			 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   			 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE      			15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE				 	2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE					7

/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8



/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 					8
#define I2C_CR1_STOP  				 	9
#define I2C_CR1_ACK 				 	10
#define I2C_CR1_SWRST  				 	15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ				 	0
#define I2C_CR2_ITERREN				 	8
#define I2C_CR2_ITEVTEN				 	9
#define I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			 	15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15


/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10
#define USART_CR3_ONEBIT   				11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9


/* 
The project leaves the STM32F411 on its 16 MHz HSI reset clock.
System tick timer flags and control bits for delay implementation.
*/
#define LCD_SYSCLK_HZ       16000000U
#define SYSTICK_BASEADDR    0xE000E010U
#define SYSTICK_CTRL_ENABLE (1U << 0)
#define SYSTICK_CTRL_CLKSOURCE (1U << 2)
#define SYSTICK_CTRL_COUNTFLAG (1U << 16)

/*
 * This macros returns a code between 0 and 5 for a given GPIO base address
 */
#define GPIO_BASEADDR_TO_CODE(x) 			((x == GPIOA) ?0:\
											 (x == GPIOB) ?1:\
											 (x == GPIOC) ?2:\
											 (x == GPIOD) ?3:\
											 (x == GPIOE) ?4:\
											 (x == GPIOH) ?5:0 )


/*
 * IRQ (Interrupt Request number) of STM32F411xx MCU
 */
#define IRQ_EXTI0				6
#define IRQ_EXTI1				7
#define IRQ_EXTI2				8
#define IRQ_EXTI3				9
#define IRQ_EXTI4				10
#define IRQ_EXTI9_5				23
#define IRQ_EXTI15_10			40
#define IRQ_SPI1				35
#define IRQ_SPI2    	     	36
#define IRQ_SPI3	         	51
#define IRQ_SPI4				84
#define IRQ_SPI5				85


/*
* Base addresses of Flash, SRAM, ROM
*/
#define FLASH_BASEADDR			0x08000000U // base address of Flash memory
#define SRAM1_BASEADDR			0x20000000U // base address of SRAM1
#define SRAM SRAM1_BASEADDR		SRAM1_BASEADDR // SRAM refers to SRAM1
#define ROM_BASEADDR			0x1FFF0000U // base address of system memory


/*
 * AHBx and APBx bus peripheral base addresses
 */
#define PERI_BASEADDR			0x40000000U
#define APB1PERI_BASEADDR		PERI_BASEADDR
#define APB2PERI_BASEADDR		0x40010000U
#define AHB1PERI_BASEADDR		0x40020000U
#define AHB2PERI_BASEADDR		0x50000000U


/*
 * Base addresses of all peripherals connected to AHB1 bus
 */
#define GPIOA_BASEADDR		(AHB1PERI_BASEADDR + 0x0000)
#define GPIOB_BASEADDR		(AHB1PERI_BASEADDR + 0x0400)
#define GPIOC_BASEADDR		(AHB1PERI_BASEADDR + 0x0800)
#define GPIOD_BASEADDR		(AHB1PERI_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR		(AHB1PERI_BASEADDR + 0x1000)
#define GPIOH_BASEADDR		(AHB1PERI_BASEADDR + 0x1C00)
#define RCC_BASEADDR		(AHB1PERI_BASEADDR + 0x3800)


/*
 * Base addresses of all peripherals connected to APB1 bus
 */
#define TIM2_BASEADDR		(APB1PERI_BASEADDR + 0x0000)
#define TIM3_BASEADDR		(APB1PERI_BASEADDR + 0x0400)
#define TIM4_BASEADDR		(APB1PERI_BASEADDR + 0x0800)
#define TIM5_BASEADDR		(APB1PERI_BASEADDR + 0x0C00)
#define SPI2_BASEADDR		(APB1PERI_BASEADDR + 0x3800)
#define SPI3_BASEADDR		(APB1PERI_BASEADDR + 0x3C00)
#define I2C1_BASEADDR		(APB1PERI_BASEADDR + 0x5400)
#define I2C2_BASEADDR		(APB1PERI_BASEADDR + 0x5800)
#define I2C3_BASEADDR		(APB1PERI_BASEADDR + 0x5C00)
#define USART2_BASEADDR		(APB1PERI_BASEADDR + 0x4400)
#define USART3_BASEADDR		(APB1PERI_BASEADDR + 0x4800)
#define UART4_BASEADDR		(APB1PERI_BASEADDR + 0x4C00)
#define UART5_BASEADDR		(APB1PERI_BASEADDR + 0x5000)

/*
 * Base addresses of all peripherals connected to APB2 bus
 */
#define TIM1_BASEADDR		(APB2PERI_BASEADDR + 0x0000)
#define USART1_BASEADDR		(APB2PERI_BASEADDR + 0x1000)
#define USART6_BASEADDR		(APB2PERI_BASEADDR + 0x1400)
#define ADC1_BASEADDR		(APB2PERI_BASEADDR + 0x2000)
#define SPI1_BASEADDR		(APB2PERI_BASEADDR + 0x3000)
#define SPI4_BASEADDR		(APB2PERI_BASEADDR + 0x3400)
#define EXTI_BASEADDR		(APB2PERI_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR		(APB2PERI_BASEADDR + 0x3800)


/*
 * GPIOx register definition structures
 */
typedef struct{
	__vo uint32_t MODER;	/*GPIO port mode register, 					offset: 0x00*/
	__vo uint32_t OTYPER;	/*GPIO port output type register, 	 		offset: 0x04*/
	__vo uint32_t OSPEEDR;	/*GPIO port output speed register, 			offset: 0x08*/
	__vo uint32_t PUPDR;	/*GPIO port pull-up/pull-down register, 	offset: 0x0C*/
	__vo uint32_t IDR;		/*GPIO port input data register, 			offset: 0x10*/
	__vo uint32_t ODR;		/*GPIO port output data register, 			offset: 0x14*/
	__vo uint32_t BSRR;		/*GPIO port bit set/reset register, 		offset: 0x18*/
	__vo uint32_t LCKR;		/*GPIO port configuration lock register, 	offset: 0x1C*/
	__vo uint32_t AFR[2];	/*GPIO alternate function low and high register,
							* AFR[0]: AFRL, AFR[1]: AFRH,				offset: 0x20*/
}GPIO_RegDefTypedef;


/*
 * Peripheral register definition structure for EXTI
 */
typedef struct{
	__vo uint32_t IMR;		/*Interrupt mask register (EXTI_IMR)*/
	__vo uint32_t EMR;		/*Event mask register (EXTI_EMR)*/
	__vo uint32_t RTSR;		/*Rising trigger selection register (EXTI_RTSR)*/
	__vo uint32_t FTSR;		/*Falling trigger selection register (EXTI_FTSR)*/
	__vo uint32_t SWIER;	/*Software interrupt event register (EXTI_SWIER)*/
	__vo uint32_t PR;		/*Pending register (EXTI_PR)*/
}EXTI_RegDefTypedef;


/*
 * SYSYCFG register definition structure
 */
typedef struct{
	__vo uint32_t MEMRMP;		/*SYSCFG memory remap register (SYSCFG_MEMRMP)*/
	__vo uint32_t PMC;			/*SYSCFG peripheral mode configuration register (SYSCFG_PMC)*/
	__vo uint32_t EXTICR[4];	/*SYSCFG external interrupt configuration register 1-4 (SYSCFG_EXTICR1-4)*/
	__vo uint32_t CMPCR;		/*Compensation cell control register (SYSCFG_CMPCR)*/
}SYSCFG_RegDefTypedef;


/*
 * RCC register definition structure
 */
typedef struct{
	__vo uint32_t CR;			/*RCC clock control register, 					offset: 0x00*/
	__vo uint32_t PLLCFGR;		/*RCC PLL configuration register, 				offset: 0x04*/
	__vo uint32_t CFGR;			/*RCC clock configuration register, 			offset: 0x08*/
	__vo uint32_t CIR;			/*RCC clock interrupt register, 				offset: 0x0C*/
	__vo uint32_t AHB1RSTR;		/*RCC AHB1 peripheral reset register, 			offset: 0x10*/
	__vo uint32_t AHB2RSTR;		/*RCC AHB2 peripheral reset register, 			offset: 0x14*/
	__vo uint32_t RESERVED0[2];	/*0x18-0x1C*/
	__vo uint32_t APB1RSTR;		/*RCC APB1 peripheral reset register, 			offset: 0x20*/
	__vo uint32_t APB2RSTR;		/*RCC APB2 peripheral reset register, 			offset: 0x24*/
	__vo uint32_t RESERVED1[2];	/*0x28-0x2C*/
	__vo uint32_t AHB1ENR;		/*RCC AHB1 peripheral clock enable register,	offset: 0x30*/
	__vo uint32_t AHB2ENR;		/*RCC AHB2 peripheral clock enable register,	offset: 0x34*/
	__vo uint32_t RESERVED2[2];	/*0x38-0x3C*/
	__vo uint32_t APB1ENR;		/*RCC APB1 peripheral clock enable register,	offset: 0x40*/
	__vo uint32_t APB2ENR;		/*RCC APB2 peripheral clock enable register,	offset: 0x44*/
	__vo uint32_t RESERVED3[2];	/*0x48 - 0x4C*/
	__vo uint32_t AHB1LPENR;	/*RCC AHB1 peripheral clock enable in low power
									mode register,								offset: 0x50*/
	__vo uint32_t AHB2LPENR;	/*RCC AHB2 peripheral clock enable in low power
									mode register,								offset: 0x54*/
	__vo uint32_t RESERVED4[2];	/*0x58 - 0x5C*/
	__vo uint32_t APB1LPENR;	/*RCC APB1 peripheral clock enable in low power
									mode register,								offset: 0x60*/
	__vo uint32_t APB2LPENR;	/*RCC APB1 peripheral clock enable in low power
									mode register,								offset: 0x64*/
	__vo uint32_t RESERVED5[2];	/*0x68 - 0x6C*/
	__vo uint32_t BDCR;			/*RCC Backup domain control register,			offset: 0x70*/
	__vo uint32_t CSR;			/*RCC clock control & status register,			offset: 0x74*/
	__vo uint32_t RESERVED6[2];	/*0x78 - 0x7C*/
	__vo uint32_t SSCGR;		/*RCC spread spectrum clock generation register,offset: 0x80*/
	__vo uint32_t PLLI2SCFGR;	/*RCC PLLI2S configuration register,			offset: 0x84*/
	__vo uint32_t DCKCFGR;		/*RCC Dedicated Clocks Configuration register,	offset: 0x8C*/
}RCC_RegDefTypedef;


/*
 * SPI register definition structure
 */
typedef struct{
	__vo uint32_t CR1;		/*SPI control register 1 (SPI_CR1)*/
	__vo uint32_t CR2;		/*SPI control register 2 (SPI_CR2)*/
	__vo uint32_t SR;		/*SPI status register (SPI_SR)*/
	__vo uint32_t DR;		/*SPI data register (SPI_DR)*/
	__vo uint32_t CRCPR;	/*SPI CRC polynomial register (SPI_CRCPR)(*/
	__vo uint32_t RXCRCR;	/*SPI RX CRC register (SPI_RXCRCR)(*/
	__vo uint32_t TXCRCR;	/*SPI TX CRC register (SPI_TXCRCR)*/
	__vo uint32_t I2SCFGR;	/*SPI_I2S configuration register (SPI_I2SCFGR)*/
	__vo uint32_t I2SPR;	/*SPI_I2S prescaler register (SPI_I2SPR)*/
}SPI_RegDefTypedef;


/*
 * peripheral register definition structure for I2C
 */
typedef struct
{
  __vo uint32_t CR1;        /*!< TODO,     										Address offset: 0x00 */
  __vo uint32_t CR2;        /*!< TODO,     										Address offset: 0x04 */
  __vo uint32_t OAR1;       /*!< TODO,     										Address offset: 0x08 */
  __vo uint32_t OAR2;       /*!< TODO,     										Address offset: 0x0C */
  __vo uint32_t DR;         /*!< TODO,     										Address offset: 0x10 */
  __vo uint32_t SR1;        /*!< TODO,     										Address offset: 0x14 */
  __vo uint32_t SR2;        /*!< TODO,     										Address offset: 0x18 */
  __vo uint32_t CCR;        /*!< TODO,     										Address offset: 0x1C */
  __vo uint32_t TRISE;      /*!< TODO,     										Address offset: 0x20 */
  __vo uint32_t FLTR;       /*!< TODO,     										Address offset: 0x24 */
}I2C_RegDefTypedef;

/*
 * peripheral register definition structure for USART
 */
typedef struct
{
	__vo uint32_t SR;         /*!< TODO,     										Address offset: 0x00 */
	__vo uint32_t DR;         /*!< TODO,     										Address offset: 0x04 */
	__vo uint32_t BRR;        /*!< TODO,     										Address offset: 0x08 */
	__vo uint32_t CR1;        /*!< TODO,     										Address offset: 0x0C */
	__vo uint32_t CR2;        /*!< TODO,     										Address offset: 0x10 */
	__vo uint32_t CR3;        /*!< TODO,     										Address offset: 0x14 */
	__vo uint32_t GTPR;       /*!< TODO,     										Address offset: 0x18 */
}USART_RegDefTypedef;

/*
 * peripheral register definition structure for systick timer
 */
typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} LCD_SysTickRegDef;

/*
 * Peripheral definitions (Peripheral definitions type-casted to xx_RegDefTypedef)
 */
#define GPIOA		((GPIO_RegDefTypedef*)GPIOA_BASEADDR)
#define GPIOB		((GPIO_RegDefTypedef*)GPIOB_BASEADDR)
#define GPIOC		((GPIO_RegDefTypedef*)GPIOC_BASEADDR)
#define GPIOD		((GPIO_RegDefTypedef*)GPIOD_BASEADDR)
#define GPIOE		((GPIO_RegDefTypedef*)GPIOE_BASEADDR)
#define GPIOH		((GPIO_RegDefTypedef*)GPIOH_BASEADDR)

#define RCC			((RCC_RegDefTypedef*)RCC_BASEADDR)
#define EXTI		((EXTI_RegDefTypedef*)EXTI_BASEADDR)
#define SYSCFG		((SYSCFG_RegDefTypedef*)SYSCFG_BASEADDR)
#define SPI1		((SPI_RegDefTypedef*)SPI1_BASEADDR)
#define SPI2		((SPI_RegDefTypedef*)SPI2_BASEADDR)
#define SPI3		((SPI_RegDefTypedef*)SPI3_BASEADDR)
#define SPI4		((SPI_RegDefTypedef*)SPI4_BASEADDR)

#define I2C1		((I2C_RegDefTypedef*)I2C1_BASEADDR)
#define I2C2		((I2C_RegDefTypedef*)I2C2_BASEADDR)
#define I2C3		((I2C_RegDefTypedef*)I2C3_BASEADDR)

#define USART1  	((USART_RegDefTypedef*)USART1_BASEADDR)
#define USART2  	((USART_RegDefTypedef*)USART2_BASEADDR)
#define USART3  	((USART_RegDefTypedef*)USART3_BASEADDR)
#define UART4  		((USART_RegDefTypedef*)UART4_BASEADDR)
#define UART5  		((USART_RegDefTypedef*)UART5_BASEADDR)
#define USART6  	((USART_RegDefTypedef*)USART6_BASEADDR)

/*
 * IRQ(Interrupt Request) Numbers of STM32F411x MCU
 */

#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI9_5 		23
#define IRQ_NO_EXTI15_10 	40
#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2         36
#define IRQ_NO_SPI3         51
#define IRQ_NO_SPI4
#define IRQ_NO_I2C1_EV     31
#define IRQ_NO_I2C1_ER     32
#define IRQ_NO_USART1	    37
#define IRQ_NO_USART2	    38
#define IRQ_NO_USART3	    39
#define IRQ_NO_UART4	    52
#define IRQ_NO_UART5	    53
#define IRQ_NO_USART6	    71



/*
 * clock enable macros for GPIOx peripherals
 *
 */
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1 << 7))

/*
 * clock enable macros for I2Cx peripherals
 *
 */
#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 << 23))

/*
 * clock enable macros for SPIx peripherals
 *
 */
#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI4_PCLK_EN()		(RCC->APB2ENR |= (1 << 13))
#define SPI5_PCLK_EN()		(RCC->APB2ENR |= (1 << 20))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))


/*
 * clock enable macros for USARTx peripherals
 *
 */
#define USART1_PCCK_EN() (RCC->APB2ENR |= (1 << 4))
#define USART2_PCCK_EN() (RCC->APB1ENR |= (1 << 17))
#define USART3_PCCK_EN() (RCC->APB1ENR |= (1 << 18))
#define UART4_PCCK_EN()  (RCC->APB1ENR |= (1 << 19))
#define UART5_PCCK_EN()  (RCC->APB1ENR |= (1 << 20))
#define USART6_PCCK_EN() (RCC->APB1ENR |= (1 << 5))


/*
 * clock enable macros for SYSCFG peripheral
 *
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))


/*
 * clock disable macros for GPIOx peripherals
 *
 */
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 7))


/*
 * clock disable macros for I2Cx peripherals
 *
 */
#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 23))

/*
 * clock disable macros for SPIx peripherals
 *
 */
#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 12))
#define SPI4_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 13))
#define SPI5_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 20))
#define SPI2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 15))


/*
 * clock disable macros for USARTx peripherals
 *
 */
#define USART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define USART6_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 5))
#define USART2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 17))


/*
 * clock disable macros for SYSCFG peripheral
 *
 */
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))


/*
 * GPIO port reset macros
 */
#define GPIOA_REG_RESET() 	do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET() 	do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET() 	do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET() 	do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET() 	do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOH_REG_RESET() 	do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)

#define SPI1_REG_RESET()	do{(RCC->APB2RSTR |= (1<<12)); (RCC->APB2RSTR &= ~(1<<12));}while(0)
#define SPI2_REG_RESET()	do{(RCC->APB1RSTR |= (1<<14)); (RCC->APB1RSTR &= ~(1<<14));}while(0)
#define SPI3_REG_RESET()	do{(RCC->APB1RSTR |= (1<<15)); (RCC->APB1RSTR &= ~(1<<15));}while(0)
#define SPI4_REG_RESET()	do{(RCC->APB2RSTR |= (1<<13)); (RCC->APB2RSTR &= ~(1<<13));}while(0)

#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_i2c_driver.h"

#endif /* INC_STM32F411XX_H_ */
