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

}

/*************************
 *
 */

void SPI_DeInit(SPI_RegDef_t *pSPIx);

/**************************
 *
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);

/**************************
 *
 */
void SPI_ReceiData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);
