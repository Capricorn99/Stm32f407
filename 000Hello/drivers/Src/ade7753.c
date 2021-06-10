/*
 * ade7753.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Admin
 */


#include "ade7753.h"

/*********************************************************************
 * @fn      		  - ADE_ReadData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

/*
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 -> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT function mode : 5
 */

void SPI2_GPIOInits(void)
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

	//RESET Pin GPIO
	SPIPins.pGPIOx = PORT_RST;
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = PIN_RST;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0;
	GPIO_Init(&SPIPins);

}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;			//full duplex
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;	//STM as master
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV16;		// clock 1MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;					// mỗi lần truyền 1 byte
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;					//CPOL 0
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_HIGH;					//CPHA 1
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; 						//Hardware slave management enabled for NSS pin

	SPI2->CR1 &= ~((uint16_t)0x0040);
	SPI_Init(&SPI2handle);
	SPI2->CR1 |= ((uint16_t)0x0040);
}

/*
 * PIN PD5 as input for interrupt
 */
void ZeroX_Inits(void)
{
	//Input pin trigger as falling edge
	GPIO_Handle_t GpioZX;
	GpioZX.pGPIOx = PORT_ZX_IT;
	GpioZX.GPIO_PinConfig.GPIO_PinNumber = PIN_ZX_IT;
	GpioZX.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioZX.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioZX.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GpioZX);

	//IRQ configuration
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRIO0);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
}

void SAG_Inits(void)
{
	//Input pin
	GPIO_Handle_t GpioSAG;
	GpioSAG.pGPIOx = PORT_SAG;
	GpioSAG.GPIO_PinConfig.GPIO_PinNumber = PIN_SAG;


//	GpioSAG.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
//	GpioSAG.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//	GpioSAG.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
//	GPIO_Init(&GpioSAG);
//
//	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRIO11);


	//Output led
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = PORT_SAG_LED;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = PIN_SAG_LED;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed);

	//ADE side
	ADE_WriteData(SPI2, MODE, 0x0004, 2);
	ADE_WriteData(SPI2, SAGCYC, 0x04, 1);
	ADE_WriteData(SPI2, SAGLVL, 0x17, 1);

}

void IRQ_Inits()
{
	//Input pin trigger as falling edge
	GPIO_Handle_t GpioIRQ;
	GpioIRQ.pGPIOx = PORT_IRQ_IT;
	GpioIRQ.GPIO_PinConfig.GPIO_PinNumber = PIN_IRQ_IT;
	GpioIRQ.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioIRQ.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioIRQ.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GpioIRQ);

	//IRQ configuration
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRIO0);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);

	//Output led
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = PORT_VP_LED;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = PIN_VP_LED;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed);

	GpioLed.pGPIOx = PORT_IP_LED;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = PIN_IP_LED;
	GPIO_Init(&GpioLed);

	//ADE side
	printf("IRQEN0 : %x \n", ADE_ReadData(SPI2, IRQEN, 2));
	ADE_WriteData(SPI2, IRQEN, 0x0340, 2);
	printf("IRQEN1 : %x \n", ADE_ReadData(SPI2, IRQEN, 2));
	ADE_WriteData(SPI2, VPKLVL, 0x29, 1);
	ADE_WriteData(SPI2, IPKLVL, 0x2D, 1);

}

void ADE_Inits(void)
{
	SPI2_GPIOInits();


	SPI2_Inits();

	/*
	* making SSOE 1 does NSS output enable.
	* The NSS pin is automatically managed by the hardware.
	* i.e when SPE=1 , NSS will be pulled to low
	* and NSS pin will be high when SPE=0
	*/

	SPI_SSOEConfig(SPI2, ENABLE);

	//Reset
	GPIO_WriteToOutputPin(PORT_RST, PIN_RST, 1);
	delay();
	GPIO_WriteToOutputPin(PORT_RST, PIN_RST, 0);
	delay();
	GPIO_WriteToOutputPin(PORT_RST, PIN_RST, 1);
	delay();

//	ZeroX_Inits();
//	delay();

//	SAG_Inits();
//	delay();

	IRQ_Inits();
	delay();

}


uint32_t ADE_ReadData( SPI_RegDef_t *pSPIx, uint8_t addr, uint32_t bytes_to_read)
{
	uint32_t data = 0;
	uint8_t dummy_write = 0xff;
//	uint8_t dummy_write2 = 0x00;
	SPI_PeripheralControl(pSPIx, ENABLE); //SS pin pull to low
	SPI_Transfer(pSPIx, addr);
	for(uint32_t i = 0; i < bytes_to_read; i++)
	{
		data <<= 8;
		data |= SPI_Transfer(pSPIx, dummy_write);
		//printf("%x\n", data);
	}

//	SPI_Transfer(pSPIx, dummy_write2);

	SPI_PeripheralControl(pSPIx, DISABLE); //SS pin pull to high
	return data;
}

/*********************************************************************
 * @fn      		  - ADE_WriteData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @ return            -
 *
 * @Note              -
 */

void ADE_WriteData(SPI_RegDef_t *pSPIx, uint8_t address, uint32_t write_buffer, uint32_t bytes_to_write)
{
	uint8_t data = 0;
	address |= 0x80;
//	uint8_t dummy_write2 = 0x00;
	SPI_PeripheralControl(pSPIx, ENABLE); //SS pin pull to low
	SPI_Transfer(pSPIx, address);
	for(uint32_t i = 0; i < bytes_to_write; i++)
	{
		data = (uint8_t)(write_buffer >> 8*(bytes_to_write - i - 1));
		SPI_Transfer(pSPIx, data);
	}
//	SPI_Transfer(pSPIx, dummy_write2);

	SPI_PeripheralControl(pSPIx, DISABLE);; //SS pin pull to high
}

void EXTI15_10_IRQHandler(void)
{

    uint32_t pending = EXTI->PR;
//    if(pending & (1 << PIN_SAG))
//    {
//        EXTI->PR |= 1 << PIN_SAG; // clear pending flag, otherwise we'd get endless interrupts
//        // handle pin ZX here
//    	printf("SAG \n");
//		if(GPIO_ReadFromInputPin(PORT_SAG, PIN_SAG) ==  0)
//		{
//			GPIO_WriteToOutputPin(PORT_SAG_LED, PIN_SAG_LED, 1);
//		}
//    }
    if(pending & (1 << PIN_ZX_IT))
    {
        EXTI->PR |= 1 << PIN_ZX_IT; // clear pending flag, otherwise we'd get endless interrupts
        // handle pin ZX here
    	printf("VRMS : %x \n", ADE_ReadData(SPI2, VRMS, 3));
    }

}


void EXTI9_5_IRQHandler(void)
{

    uint32_t pending = EXTI->PR;
    if(pending & (1 << PIN_IRQ_IT))
    {
        EXTI->PR |= 1 << PIN_IRQ_IT; // clear pending flag, otherwise we'd get endless interrupts
        // handle pin ZX here
        for(int i = 0; i < 5000; i++);
        printf("RSTSTATUS : %x \n", ADE_ReadData(SPI2, RSTSTATUS, 2));



    }

}



//uint32_t ADE_VRMS(SPI_RegDef_t *pSPIx)
//{
//	uint32_t vrms_stack = 0;
//	for (int i = 0; i < 50; i++ )
//	{
//		vrms_stack += ADE_ReadData(pSPIx);
//	}
//}
