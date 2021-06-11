
#include "stm32f4xx.h"

void delay() {
	for(int i = 0; i < 500000; i++);
}

void SPI_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 14;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 12;
	GPIO_Init(&SPIPins);
}

void SPI_Inits(void)
{
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;			//full duplex
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;	//STM as master
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;		// clock 1MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;					// mỗi lần truyền 1 byte
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;					//CPOL 0
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_HIGH;					//CPHA 1
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; 						//Hardware slave management enabled for NSS pin

	SPI2->CR1 &= ~((uint16_t)0x0040);
	SPI_Init(&SPI2handle);
	SPI2->CR1 |= ((uint16_t)0x0040);
}

int main() {

	printf("hello world \n");
	return 0;
}
