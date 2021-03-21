/*
 * 004HSI_measurement.c
 *
 *  Created on: Mar 21, 2021
 *      Author: Admin
 */




#include<stdint.h>

#define RCC_BASE_ADDR              0x40023800UL

#define RCC_CFGR_REG_OFFSET        0x08UL

#define RCC_CFGR_REG_ADDR          (RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET )

#define GPIOA_BASE_ADDR            0x40020000UL

int main(void)
{
	uint32_t *pRccCfgrReg =  (uint32_t*) RCC_CFGR_REG_ADDR;


	//1. Configure the RCC_CFGR MCO1 bit fields to select HSI as clock source
	*pRccCfgrReg &= ~(0x3 << 21); //clear 21 and 22 bit positions

	//Configure MCO1 prescaler
	//*pRccCfgrReg |= ( 1 << 25);
	*pRccCfgrReg |= ( 1 << 26);

	//2. Configure PA8 to AF0 mode to behave as MCO1 signal
/*
 * You are not expected to understand the below codes for the time being
 * because these codes are related to GPIO configurations,
 * which will be covered in later sections of this course.
 */

	//a ) Enable the peripheral clock for GPIOA peripheral

	 uint32_t *pRCCAhb1Enr = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*pRCCAhb1Enr |= ( 1 << 0); //Enable GPIOA peripheral clock

	//b ) Configure the mode of GPIOA pin 8 as alternate function mode

	uint32_t *pGPIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR + 00);
	*pGPIOAModeReg &= ~( 0x3 << 16); //clear
	*pGPIOAModeReg |= ( 0x2 << 16);  //set

	//c ) Configure the alternation function register to set the mode 0 for PA8

	uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
	*pGPIOAAltFunHighReg &= ~( 0xf << 0);

	for(;;);
}
