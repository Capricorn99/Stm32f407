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

	SPIPins.pGPIOx = SPI_PORT;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_SCLK;
	GPIO_Init(&SPIPins);

	//MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_MOSI;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_MISO;
	GPIO_Init(&SPIPins);


	//NSS
 	SPIPins.GPIO_PinConfig.GPIO_PinNumber = SPI_PIN_NSS;
	GPIO_Init(&SPIPins);

}

void SPI2_Inits(void)
{
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;			//full duplex
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;	//STM as master
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;		// clock 2MHz
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;					// mỗi lần truyền 1 byte
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;					//CPOL 0
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_HIGH;					//CPHA 1
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; 						//Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2handle);
}

/*
 * PIN PD5 as input for interrupt
 */
void ZeroX_Inits(void)
{
	//Input pin trigger as falling edge
	GPIO_Handle_t GpioBtn;
	GpioBtn.pGPIOx = IT_PORT;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = IT_PIN_ZX;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GpioBtn);

	//IRQ configuration
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRIO11);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
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
	ZeroX_Inits();
}


uint32_t ADE_ReadData( SPI_RegDef_t *pSPIx, uint8_t addr, uint32_t bytes_to_read)
{
	uint32_t data = 0;
	uint8_t dummy_write = 0xff;
	uint8_t dummy_write2 = 0x00;
	SPI_PeripheralControl(pSPIx, ENABLE); //SS pin pull to low
//	while( ( (pSPIx->SR & 0x0003) == 0) || (pSPIx->SR & 0x0080) );

	SPI_Transfer(pSPIx, addr);
	for(uint32_t i = 0; i < bytes_to_read; i++)
	{
		data <<= 8;
		data |= SPI_Transfer(pSPIx, dummy_write);
		//printf("%x\n", data);
	}

	SPI_Transfer(pSPIx, dummy_write2);

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
	uint8_t dummy_write = 0xff;
	uint8_t dummy_write2 = 0x00;
	SPI_PeripheralControl(pSPIx, ENABLE); //SS pin pull to low
//	while( ( (pSPIx->SR & 0x0003) == 0) || (pSPIx->SR & 0x0080) );

	SPI_Transfer(pSPIx, address);
	for(uint32_t i = 0; i < bytes_to_write; i++)
	{
		data = (uint8_t)(write_buffer >> 8*(bytes_to_write - i - 1));
		SPI_Transfer(pSPIx, data);
	}
	SPI_Transfer(pSPIx, dummy_write2);


	SPI_PeripheralControl(pSPIx, DISABLE);; //SS pin pull to high
}

//uint32_t ADE_VRMS(SPI_RegDef_t *pSPIx)
//{
//	uint32_t vrms_stack = 0;
//	for (int i = 0; i < 50; i++ )
//	{
//		vrms_stack += ADE_ReadData(pSPIx);
//	}
//}
