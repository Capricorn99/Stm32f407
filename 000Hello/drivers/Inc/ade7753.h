/*
 * ade7753.h
 *
 *  Created on: Mar 22, 2021
 *      Author: Admin
 */

/*
 * File header 	+include các file header cần thiết (theo thứ tự)
 * 				+Các macros
 * 				+Khai báo biến, struct, hàm
 */

#ifndef INC_ADE7753_H_
#define INC_ADE7753_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio_driver.h"
#include "stm32f4xx_spi_driver.h"

/*
 * ADE REGISTERS
 */
#define WAVEFORM   	0x01	//24bits
#define AENERGY     0x02	//24bits
#define RAENERGY    0x03	//24bits
#define LAENERGY    0x04	//24bits
#define VAENERGY    0x05	//24bits
#define RVAENERGY   0x06	//24bits
#define LVAENERGY   0x07	//24bits
#define LVARENERGY  0x08	//24bits

#define MODE        0x09
#define IRQEN       0x0A
#define STATUS      0x0B
#define RSTSTATUS   0x0C

#define CH1OS       0x0D
#define CH2OS       0x0E
#define GAIN        0x0F
#define PHCAL       0x10

#define APOS        0x11
#define WGAIN       0x12	//12bits
#define WDIV        0x13
#define CFNUM       0x14 	//12bits
#define CFDEN       0x15
#define IRMS        0x16
#define VRMS        0x17
#define IRMSOS      0x18
#define VRMSOS      0x19
#define VAGAIN      0x1A
#define VADIV       0x1B
#define LINECYC     0x1C
#define ZXTOUT      0x1D
#define SAGCYC      0x1E
#define SAGLVL      0x1F
#define IPKLVL      0x20
#define VPKLVL      0x21
#define IPEAK       0x22
#define RSTIPEAK    0x23
#define VPEAK       0x24
#define RSTVPEAK    0x25
#define TEMP        0x26
#define PERIOD      0x27

#define TMODE       0x3D
#define CHKSUM      0x3E
#define DIEREV      0x3F

/*
 * Pin Mode
 */
#define SPI_PORT 		GPIOB
#define SPI_PIN_MOSI 	GPIO_PIN_NO_15
#define SPI_PIN_MISO	GPIO_PIN_NO_14
#define SPI_PIN_SCLK	GPIO_PIN_NO_13
#define SPI_PIN_NSS		GPIO_PIN_NO_12

#define IT_PORT			GPIOB
#define IT_PIN_ZX		GPIO_PIN_NO_11

SPI_Handle_t SPI2handle;

//this function is used to initialize the GPIO pins to behave as SPI2 pins
void SPI2_GPIOInits(void);

//This function is used to initialize the SPI2 peripheral parameters
void SPI2_Inits(void);

//This function is used to initialize the Zero_crossing  of ADE
void ZeroX_Inits(void);

//This function is used to initialize SPI2_GPIOInits & SPI2_Inits & some default configure for ADE eg: ZeroCrossing
void ADE_Inits(void);

uint32_t ADE_ReadData(SPI_RegDef_t *pSPIx, uint8_t addr, uint32_t bytes_to_read);
void ADE_WriteData(SPI_RegDef_t *pSPIx, uint8_t address, uint32_t write_buffer, uint32_t bytes_to_write);
//uint32_t ADE_VRMS(SPI_RegDef_t *pSPIx);


#endif /* INC_ADE7753_H_ */
