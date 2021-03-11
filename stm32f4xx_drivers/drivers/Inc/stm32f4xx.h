/*
 * stm32f4xx.h
 *
 *  Created on: Feb 7, 2021
 *      Author: Admin
 */

#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_

#define __vo volatile
#include<stdint.h>

/*
 * ARM Cortex Mx Processor NVIC ISER register Addresses
 */
#define NVIC_ISER0					( (__vo uint32_t*)0xE000E100)
#define NVIC_ISER1					( (__vo uint32_t*)0xE000E104)
#define NVIC_ISER2					( (__vo uint32_t*)0xE000E108)
#define NVIC_ISER3					( (__vo uint32_t*)0xE000E10C)

/*
 * ARM Cortex Mx Processor NVIC ICER register Addresses
 */
#define NVIC_ICER0					((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1					((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2					((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3					((__vo uint32_t*)0xE000E18C)

/*
 * ARM Cortex Mx Processor Priority register Addresses
 */
#define NVIC_PR_BASE_ADDR					((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED				4

//Base addresses of memories
#define FLASH_BASEADDR				0X08000000U
#define SRAM1_BASEADDR				0X20000000U	//112KB
#define SRAM2_BASEADDR				0X20001C00U
#define ROM_BASEADDR				0X1FFF0000U
#define SRAM						SRAM1_BASEADDR

//Base addresses of BUS
#define PERIPH_BASEADDR					0X40000000U
#define APB1PERIPH_BASEADDR				PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR				0X40010000U
#define AHB1PERIPH_BASEADDR				0X40020000U
#define AHB2PERIPH_BASEADDR				0X50000000U

//Base addresses of PERIPHERALS hanging in AHB1
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0X0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0X1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0X1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0X1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0X1C00)
#define GPIOI_BASEADDR				(AHB1PERIPH_BASEADDR + 0X2000)
#define RCC_BASEADDR					(AHB1PERIPH_BASEADDR + 0X3800)

//Base addresses of PERIPHERALS hanging in APB1
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0X5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0X5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0X5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0X3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0X3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0X4400)
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0X4800)
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0X4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0X5000)

//Base addresses of PERIPHERALS hanging in APB2
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0X3C00)
#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0X3000)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0X3800)

#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0X1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0X1400)

/*--- Define Regs using C struture ---*/
// GPIO
typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;

	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
} GPIO_RegDef_t;

// RCC
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	uint32_t RESERVED2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t RESERVED6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
} RCC_RegDef_t;

/*
 * Peripheral register definition structure for EXTI
 */
typedef struct
{
	__vo uint32_t IMR; /* address offset :0x00 */
	__vo uint32_t EMR; /* address offset :0x04 */
	__vo uint32_t RTSR; /* address offset :0x08 */
	__vo uint32_t FTSR; /* address offset :0x0c */
	__vo uint32_t SWIER; /* address offset :0x10 */
	__vo uint32_t PR; /* address offset :0x14 */
} EXTI_RegDef_t;

/*
 * Peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP; 	/* address offset :0x00 */
	__vo uint32_t PMC;		/* address offset :0x04 */
	__vo uint32_t EXTICR[4];/* address offset :0x08-0x14 */
	uint32_t RESERVED1[2];	/* address offset :0x18-0x1C */
	__vo uint32_t CMPCR;	/* address offset :0x20 */
	uint32_t RESERVED2[2];	/* address offset :0x24-0x28 */
	__vo uint32_t CFGR;		/* address offset :0x2C */
} SYSCFG_RegDef_t;

// Peripherals definition
#define GPIOA 					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB 					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC 					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD 					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE 					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF 					((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG 					((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH 					((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI 					((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC 					((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI					((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG					((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)
/*
 * Clock Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()		(RCC->AHB1ENR |= (1<<8))

/*
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1<<23))

/*
 * Clock Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()		(RCC->APB2ENR |= (1<<14))
#define SPI3_PCLK_EN()		(RCC->APB2ENR |= (1<<15))
#define SPI4_PCLK_EN()		(RCC->APB2ENR |= (1<<13))


/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN()		(RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN()		(RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()		(RCC->APB1ENR |= (1<<18))
#define UART4_PCLK_EN()			(RCC->APB2ENR |= (1<<19))
#define UART5_PCLK_EN()			(RCC->APB1ENR |= (1<<20))
#define USART6_PCLK_EN()		(RCC->APB1ENR |= (1<<5))

/*
 * Clock Enable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1<<14))


////
/*
 * Clock Disable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()		(RCC->AHB1ENR &= ~(1<<8))

/*
 * Clock Disable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1<<23))

/*
 * Clock Disable Macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()		(RCC->APB2ENR &= ~(1<<14))
#define SPI3_PCLK_DI()		(RCC->APB2ENR &= ~(1<<15))
#define SPI4_PCLK_DI()		(RCC->APB2ENR &= ~(1<<13))


/*
 * Clock Disable Macros for USARTx peripherals
 */
#define USART1_PCLK_DI()		(RCC->APB2ENR &= ~(1<<4))
#define USART2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI()		(RCC->APB1ENR &= ~(1<<18))
#define UART4_PCLK_DI()			(RCC->APB2ENR &= ~(1<<19))
#define UART5_PCLK_DI()			(RCC->APB1ENR &= ~(1<<20))
#define USART6_PCLK_DI()		(RCC->APB1ENR &= ~(1<<5))

/*
 * Clock Disable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1<<14))

#define ENABLE 	1
#define DISABLE 0
#define SET 	ENABLE
#define RESET	DISABLE

/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~ (1<<0));} while(0)
#define GPIOB_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~ (1<<1));} while(0)
#define GPIOC_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~ (1<<2));} while(0)
#define GPIOD_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~ (1<<3));} while(0)
#define GPIOE_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~ (1<<4));} while(0)
#define GPIOF_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<5)); (RCC->AHB1RSTR &= ~ (1<<5));} while(0)
#define GPIOG_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<6)); (RCC->AHB1RSTR &= ~ (1<<6));} while(0)
#define GPIOH_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~ (1<<7));} while(0)
#define GPIOI_REG_RESET()		do {(RCC ->AHB1RSTR |= (1<<8)); (RCC->AHB1RSTR &= ~ (1<<8));} while(0)

#define GPIO_BASEADDR_TO_CODE(x)	(x == GPIOA) ? 0 :\
									(x == GPIOB) ? 1 :\
									(x == GPIOC) ? 2 :\
									(x == GPIOD) ? 3 :\
									(x == GPIOE) ? 4 :\
									(x == GPIOF) ? 5 :\
									(x == GPIOG) ? 6 :\
									(x == GPIOH) ? 7 :0

/*
 * IRQ (Interrupt Request) Numbers of STM32F407x MCU
 * NOTE : update the right macros according to MCU
 */
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40

/*
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRIO0		0
#define NVIC_IRQ_PRIO15		15

//some generic macros#define IRQ_NO_EXTI0	6
#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

#include "stm32f4xx_gpio_driver.h"


#endif /* INC_STM32F4XX_H_ */
