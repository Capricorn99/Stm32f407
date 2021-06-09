/*
 * test.c
 *
 *  Created on: Jun 8, 2021
 *      Author: Admin
 */


#include "stm32f4xx.h"

void delay() {
	for(int i = 0; i < 50000; i++);
}
void SPI_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOA;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIPins);

}

void SPI_Inits(void)
{
	SPI_Handle_t SPI1handle;
	SPI1handle.pSPIx = SPI1;
	SPI1handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;			//full duplex
	SPI1handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;	//STM as master
	SPI1handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;		// clock 2MHz
	SPI1handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;					// mỗi lần truyền 1 byte
	SPI1handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;					//CPOL 0
	SPI1handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;					//CPHA 0
	SPI1handle.SPIConfig.SPI_SSM = SPI_SSM_DI; 						//Hardware slave management enabled for NSS pin

	SPI_Init(&SPI1handle);
}

int main() {
	GPIO_Handle_t Gpio;

	Gpio.pGPIOx = GPIOA;
	Gpio.GPIO_PinConfig.GPIO_PinNumber = 3;
	Gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpio.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpio.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	Gpio.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&Gpio);

	Gpio.pGPIOx = GPIOC;
	Gpio.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&Gpio);

	Gpio.pGPIOx = GPIOB;
	Gpio.GPIO_PinConfig.GPIO_PinNumber = 1;
	GPIO_Init(&Gpio);

	SPI_GPIOInits();
	SPI_Inits();


	GPIO_WriteToOutputPin(GPIOB, 1, 1);
	delay();
	GPIO_WriteToOutputPin(GPIOB, 1, 0);
	SPI_Transfer(SPI1, 0x69);
	GPIO_WriteToOutputPin(GPIOB, 1, 1);

	return 0;
}
