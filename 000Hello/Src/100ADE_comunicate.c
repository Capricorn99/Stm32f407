/*
 * 100ADE_comunicate.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Admin
 */

#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "ade7753.h"
#include "LCD5110.h"



void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}





int main (void)
{
	ADE_Inits();
}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_11);// clear the pending event

	//printf("VRMS : %x \n", ADE_ReadData(SPI2, VRMS, 3));
	//printf("VRMS : %x \n", ADE_ReadData(SPI2, MODE, 2));

}
