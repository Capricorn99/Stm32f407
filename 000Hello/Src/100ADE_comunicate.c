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


//#define MAX_LEN 500


//char RcvBuff[MAX_LEN];

//volatile char ReadByte;

//volatile uint8_t rcvStop = 0;

/*This flag will be set in the interrupt handler of the Arduino interrupt GPIO */
//volatile uint8_t dataAvailable = 0;

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}





int main (void)
{
//	GPIO_Handle_t GpioLed;
//
//	GpioLed.pGPIOx = GPIOA;
//	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
//	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
//	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//	GpioLed.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_OD;
//	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
//
//	//GPIO_PeriClockControl(GPIOD, ENABLE);
//
//	GPIO_Init(&GpioLed);




	//ADE_Inits();



	//Initialize LCD with 0x38 software contrast
	LCD5110_Init(0x38);
	printf("init \n");

	//Go to x=14, y=3 position
	LCD5110_GotoXY(14, 3);

	//Print data with Pixel Set mode and Fontsize of 5x7px
	LCD5110_Puts("STM32F429", LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
	LCD5110_GotoXY(15, 13);
	LCD5110_Puts("Discovery", LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
	LCD5110_GotoXY(30, 26);
	LCD5110_Puts("2014", LCD5110_Pixel_Set, LCD5110_FontSize_5x7);

	LCD5110_GotoXY(45, 42);
	//Put string with Pixel set mode and Fontsize of 3x5
	LCD5110_Puts("majerle.eu", LCD5110_Pixel_Set, LCD5110_FontSize_3x5);

	//Display data on LCD
	LCD5110_Refresh();
//
//
//	uint32_t data = 0x000C;
//	ADE_WriteData(SPI2, MODE, data, 2);
//	data1 = ADE_ReadData(SPI2, MODE, 2);
//	printf("DATA1 : %x \n", data1);
//	while(1){
////		delay();
////		printf("MODE : %x \n", ADE_ReadData(SPI2, MODE, 2));
////		delay();
////		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_3, 0);
////		delay();
////		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_3, 1);
//	}



//	while (1)
//	{
//		data1 = ADE_ReadData(SPI2, VRMS, 3);
//		printf("DATA1 : %d \n", data1);
//		data2 = ADE_ReadData(SPI2, MODE, 2);
//		printf("DATA2 : %d \n", data2);
//
//	}
}

void EXTI9_5_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_5);// clear the pending event

	printf("VRMS : %x \n", ADE_ReadData(SPI2, VRMS, 3));
	printf("VRMS : %x \n", ADE_ReadData(SPI2, MODE, 2));

}
