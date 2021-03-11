/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: Mar 11, 2021
 *      Author: Admin
 */


/***********************
 *
 */
#include "stm32f4xx_spi_driver.h"

void SPI_PeriClockControl(SPI_RegDef_t*pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if (pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if (pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}else if (pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}

}

/************************
 *
 */

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//first lets configure the SPI_CR1 register

	uint32_t tempreg = 0;

	//1. configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

	//2. configure the bus config
	if(pSPIHandle -> SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		tempreg &=~ (1<<15);
	}else if (pSPIHandle ->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//BIDI mode should be set
		tempreg |= ~ (1<<15);
	}else if (pSPIHandle ->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//BIDI mode should be cleared
		tempreg &= ~ (1<<15);
		//RXONLY bit must be set
		tempreg |= (1<<10);
	}
	//3. configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;
	//4. configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << 11;
	//5. configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;
	//6. configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << 0;

	pSPIHandle->pSPIx->CR1 =tempreg;

}

/*************************
 *
 */

void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*************************
 *
 */

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;

}


/**************************
 *
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len >0)
	{
		//1. wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		//2. check the DFF bit in CR1
		if (pSPIx->CR1 & (1<<SPI_CR1_DFF))
		{
			//16 bit DFF
			//1. load the data in to the DR
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else
		{
			//8 bit DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
		}
	}
}

/**************************
 *
 */
void SPI_ReceiData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
