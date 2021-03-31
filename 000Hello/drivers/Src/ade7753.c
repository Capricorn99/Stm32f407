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




uint32_t ADE_ReadData( SPI_RegDef_t *pSPIx, uint8_t addr, uint32_t bytes_to_read)
{
	uint32_t data = 0;
	uint8_t dummy_write = 0xff;

	SPI_PeripheralControl(pSPIx,ENABLE); //SS pin pull to low

	SPI_Transfer(pSPIx, &addr);
	for(uint32_t i = 0; i < bytes_to_read; i++)
	{
		data <<= 8;
		data |= SPI_Transfer(pSPIx, &dummy_write);
		printf("%x\n", data);
	}
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

uint32_t ADE_WriteData(SPI_RegDef_t *pSPIx, uint8_t address, uint32_t write_buffer, uint32_t bytes_to_write)
{
	uint8_t data = 0;
	uint8_t write_cmd = 0x80;
	address |= write_cmd;
	uint8_t dummy_write = 0xff;
	SPI_PeripheralControl(pSPIx, ENABLE); //SS pin pull to low
	SPI_Transfer(pSPIx, &address);
	for(uint32_t i = 0; i < bytes_to_write; i++)
	{
		data = (uint8_t)(write_buffer >> 8*(bytes_to_write - i - 1));
		SPI_Transfer(pSPIx, &data);
	}
	SPI_PeripheralControl(pSPIx, DISABLE);; //SS pin pull to high

	return ADE_ReadData(pSPIx, &address, bytes_to_write);
}
