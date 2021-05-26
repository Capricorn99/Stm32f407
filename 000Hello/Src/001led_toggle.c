#include "stm32f4xx.h"


void delay(void)
{
	for(uint32_t i = 0 ; i < 500000 ; i ++);
}


int main(void)
{

	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOE;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioLed);

	GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_15, 1);
	while(1)
	{
		GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_15, 1);
		delay();
//		GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_15, 0);
		delay();
	}
	return 0;
}
