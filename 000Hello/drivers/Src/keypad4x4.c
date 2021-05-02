/*
 * keypad4x4.c
 *
 *  Created on: Apr 28, 2021
 *      Author: DELL7470
 */
#include "keypad4x4.h"

/* Pins configuration, columns are outputs */
#define KEYPAD_COLUMN_1_LOW			GPIO_WriteToOutputPin(KEYPAD_COLUMN_1_PORT, KEYPAD_COLUMN_1_PIN, GPIO_PIN_RESET)
#define KEYPAD_COLUMN_2_LOW			GPIO_WriteToOutputPin(KEYPAD_COLUMN_2_PORT, KEYPAD_COLUMN_2_PIN, GPIO_PIN_RESET)
#define KEYPAD_COLUMN_3_LOW			GPIO_WriteToOutputPin(KEYPAD_COLUMN_3_PORT, KEYPAD_COLUMN_3_PIN, GPIO_PIN_RESET)
#define KEYPAD_COLUMN_4_LOW			GPIO_WriteToOutputPin(KEYPAD_COLUMN_4_PORT, KEYPAD_COLUMN_4_PIN, GPIO_PIN_RESET)

#define KEYPAD_COLUMN_1_HIGH		GPIO_WriteToOutputPin(KEYPAD_COLUMN_1_PORT, KEYPAD_COLUMN_1_PIN, GPIO_PIN_SET)
#define KEYPAD_COLUMN_2_HIGH		GPIO_WriteToOutputPin(KEYPAD_COLUMN_2_PORT, KEYPAD_COLUMN_2_PIN, GPIO_PIN_SET)
#define KEYPAD_COLUMN_3_HIGH		GPIO_WriteToOutputPin(KEYPAD_COLUMN_3_PORT, KEYPAD_COLUMN_3_PIN, GPIO_PIN_SET)
#define KEYPAD_COLUMN_4_HIGH		GPIO_WriteToOutputPin(KEYPAD_COLUMN_4_PORT, KEYPAD_COLUMN_4_PIN, GPIO_PIN_SET)

/* Read input pins */
#define KEYPAD_ROW_1_CHECK			(!GPIO_ReadFromInputPin(KEYPAD_ROW_1_PORT, KEYPAD_ROW_1_PIN))
#define KEYPAD_ROW_2_CHECK			(!GPIO_ReadFromInputPin(KEYPAD_ROW_2_PORT, KEYPAD_ROW_2_PIN))
#define KEYPAD_ROW_3_CHECK			(!GPIO_ReadFromInputPin(KEYPAD_ROW_3_PORT, KEYPAD_ROW_3_PIN))
#define KEYPAD_ROW_4_CHECK			(!GPIO_ReadFromInputPin(KEYPAD_ROW_4_PORT, KEYPAD_ROW_4_PIN))

uint8_t KEYPAD_INT_Buttons[4][4] = {
	{0x01, 0x02, 0x03, 0x0C},
	{0x04, 0x05, 0x06, 0x0D},
	{0x07, 0x08, 0x09, 0x0E},
	{0x0A, 0x00, 0x0B, 0x0F},
};

/* Private functions */
void TM_KEYPAD_INT_SetColumn(uint8_t column);
uint8_t TM_KEYPAD_INT_CheckRow(uint8_t column);
uint8_t TM_KEYPAD_INT_Read(void);

/* Private variables */
TM_KEYPAD_Type_t TM_KEYPAD_INT_KeypadType;
static TM_KEYPAD_Button_t KeypadStatus = TM_KEYPAD_Button_NOPRESSED;

void TM_KEYPAD_Init(TM_KEYPAD_Type_t type) {
	/* Set keyboard type */
	TM_KEYPAD_INT_KeypadType = type;

	GPIO_Handle_t GpioC_Out, GpioR_In;

	/* Columns are output */
	/* Column 1 */
	GpioC_Out.pGPIOx = KEYPAD_COLUMN_1_PORT;
	GpioC_Out.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_COLUMN_1_PIN;
	GpioC_Out.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioC_Out.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	GpioC_Out.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	GpioC_Out.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioC_Out);

	/* Column 2 */
	GpioC_Out.pGPIOx = KEYPAD_COLUMN_2_PORT;
	GpioC_Out.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_COLUMN_2_PIN;
	GPIO_Init(&GpioC_Out);

	/* Column 3 */
	GpioC_Out.pGPIOx = KEYPAD_COLUMN_3_PORT;
	GpioC_Out.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_COLUMN_3_PIN;
	GPIO_Init(&GpioC_Out);

	/* Column 4 */
	if (TM_KEYPAD_INT_KeypadType == TM_KEYPAD_Type_Large) {
		GpioC_Out.pGPIOx = KEYPAD_COLUMN_4_PORT;
		GpioC_Out.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_COLUMN_4_PIN;
		GPIO_Init(&GpioC_Out);
	}


	/* Rows are inputs */
	/* Row 1 */
	GpioR_In.pGPIOx = KEYPAD_ROW_1_PORT;
	GpioR_In.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_ROW_1_PIN;
	GpioR_In.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioR_In.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	GpioR_In.GPIO_PinConfig.GPIO_PinoType = GPIO_OP_TYPE_PP;
	GpioR_In.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GpioR_In);

	/* Row 2 */
	GpioR_In.pGPIOx = KEYPAD_ROW_2_PORT;
	GpioR_In.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_ROW_2_PIN;
	GPIO_Init(&GpioR_In);

	/* Row 3 */
	GpioR_In.pGPIOx = KEYPAD_ROW_3_PORT;
	GpioR_In.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_ROW_3_PIN;
	GPIO_Init(&GpioR_In);

	/* Row 4 */
	GpioR_In.pGPIOx = KEYPAD_ROW_4_PORT;
	GpioR_In.GPIO_PinConfig.GPIO_PinNumber = KEYPAD_ROW_4_PIN;
	GPIO_Init(&GpioR_In);

	/* All columns high */
	TM_KEYPAD_INT_SetColumn(0);
}

TM_KEYPAD_Button_t TM_KEYPAD_Read(void) {
	TM_KEYPAD_Button_t temp;

	/* Get keypad status */
	temp = KeypadStatus;

	/* Reset keypad status */
	//KeypadStatus = TM_KEYPAD_Button_NOPRESSED;

	return temp;
}

/* Private */
void TM_KEYPAD_INT_SetColumn(uint8_t column) {
	/* Set rows high */
	KEYPAD_COLUMN_1_HIGH;
	KEYPAD_COLUMN_2_HIGH;
	KEYPAD_COLUMN_3_HIGH;
	if (TM_KEYPAD_INT_KeypadType == TM_KEYPAD_Type_Large) {
		KEYPAD_COLUMN_4_HIGH;
	}

	/* Set column low */
	if (column == 1) {
		KEYPAD_COLUMN_1_LOW;
	}
	if (column == 2) {
		KEYPAD_COLUMN_2_LOW;
	}
	if (column == 3) {
		KEYPAD_COLUMN_3_LOW;
	}
	if (column == 4) {
		KEYPAD_COLUMN_4_LOW;
	}
}

uint8_t TM_KEYPAD_INT_CheckRow(uint8_t column) {
	/* Read rows */

	/* Scan row 1 */
	if (KEYPAD_ROW_1_CHECK) {
		return KEYPAD_INT_Buttons[0][column - 1];
	}
	/* Scan row 2 */
	if (KEYPAD_ROW_2_CHECK) {
		return KEYPAD_INT_Buttons[1][column - 1];
	}
	/* Scan row 3 */
	if (KEYPAD_ROW_3_CHECK) {
		return KEYPAD_INT_Buttons[2][column - 1];
	}
	/* Scan row 4 */
	if (TM_KEYPAD_INT_KeypadType == TM_KEYPAD_Type_Large && KEYPAD_ROW_4_CHECK) {
		return KEYPAD_INT_Buttons[3][column - 1];
	}

	/* Not pressed */
	return KEYPAD_NO_PRESSED;
}

uint8_t TM_KEYPAD_INT_Read(void) {
	uint8_t check;
	/* Set row 1 to LOW */
	TM_KEYPAD_INT_SetColumn(1);
	/* Check rows */
	check = TM_KEYPAD_INT_CheckRow(1);
	if (check != KEYPAD_NO_PRESSED) {
		return check;
	}

	/* Set row 2 to LOW */
	TM_KEYPAD_INT_SetColumn(2);
	/* Check columns */
	check = TM_KEYPAD_INT_CheckRow(2);
	if (check != KEYPAD_NO_PRESSED) {
		return check;
	}

	/* Set row 3 to LOW */
	TM_KEYPAD_INT_SetColumn(3);
	/* Check columns */
	check = TM_KEYPAD_INT_CheckRow(3);
	if (check != KEYPAD_NO_PRESSED) {
		return check;
	}

	if (TM_KEYPAD_INT_KeypadType == TM_KEYPAD_Type_Large) {
		/* Set column 4 to LOW */
		TM_KEYPAD_INT_SetColumn(4);
		/* Check rows */
		check = TM_KEYPAD_INT_CheckRow(4);
		if (check != KEYPAD_NO_PRESSED) {
			return check;
		}
	}

	/* Not pressed */
	return KEYPAD_NO_PRESSED;
}

void TM_KEYPAD_Update(void) {
	static uint16_t millis = 0;

	/* Every X ms read */
	if (++millis >= KEYPAD_READ_INTERVAL) {// && KeypadStatus == TM_KEYPAD_Button_NOPRESSED) {
		/* Reset */
		millis = 0;

		/* Read keyboard */
		KeypadStatus = (TM_KEYPAD_Button_t) TM_KEYPAD_INT_Read();
	}
}
