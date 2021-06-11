/*
 * keypad4x4.h
 *
 *  Created on: Apr 28, 2021
 *      Author: DELL7470
 */

#ifndef KEYPAD4X4_H_
#define KEYPAD4X4_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio_driver.h"


/**
 * @defgroup TM_KEYPAD_Macros
 * @brief    Library defines
 * @{
 */

/* Rows */
/* Row 1 default */
#ifndef KEYPAD_ROW_1_PIN
#define KEYPAD_ROW_1_PORT			GPIOB
#define KEYPAD_ROW_1_PIN			GPIO_PIN_NO_7
#endif
/* Row 2 default */
#ifndef KEYPAD_ROW_2_PIN
#define KEYPAD_ROW_2_PORT			GPIOB
#define KEYPAD_ROW_2_PIN			GPIO_PIN_NO_5
#endif
/* Row 3 default */
#ifndef KEYPAD_ROW_3_PIN
#define KEYPAD_ROW_3_PORT			GPIOB
#define KEYPAD_ROW_3_PIN			GPIO_PIN_NO_3
#endif
/* Row 4 default */
#ifndef KEYPAD_ROW_4_PIN
#define KEYPAD_ROW_4_PORT			GPIOD
#define KEYPAD_ROW_4_PIN			GPIO_PIN_NO_6
#endif

/* Columns */
/* Column 1 default */
#ifndef KEYPAD_COLUMN_1_PIN
#define KEYPAD_COLUMN_1_PORT		GPIOD
#define KEYPAD_COLUMN_1_PIN			GPIO_PIN_NO_4
#endif
/* Column 2 default */
#ifndef KEYPAD_COLUMN_2_PIN
#define KEYPAD_COLUMN_2_PORT		GPIOD
#define KEYPAD_COLUMN_2_PIN			GPIO_PIN_NO_2
#endif
/* Column 3 default */
#ifndef KEYPAD_COLUMN_3_PIN
#define KEYPAD_COLUMN_3_PORT		GPIOD
#define KEYPAD_COLUMN_3_PIN			GPIO_PIN_NO_0
#endif
/* Column 4 default */
#ifndef KEYPAD_COLUMN_4_PIN
#define KEYPAD_COLUMN_4_PORT		GPIOC
#define KEYPAD_COLUMN_4_PIN			GPIO_PIN_NO_11
#endif

/* Number of milliseconds between 2 reads */
#ifndef KEYPAD_READ_INTERVAL
#define KEYPAD_READ_INTERVAL        50
#endif

/* Keypad no pressed */
#define KEYPAD_NO_PRESSED			(uint8_t)0xFF


/**
 * @brief  Keypad button enumeration
 */
typedef enum {
	TM_KEYPAD_Button_0 = 0x00,                     /*!< Button 0 code */
	TM_KEYPAD_Button_1 = 0x01,                     /*!< Button 1 code */
	TM_KEYPAD_Button_2 = 0x02,                     /*!< Button 2 code */
	TM_KEYPAD_Button_3 = 0x03,                     /*!< Button 3 code */
	TM_KEYPAD_Button_4 = 0x04,                     /*!< Button 4 code */
	TM_KEYPAD_Button_5 = 0x05,                     /*!< Button 5 code */
	TM_KEYPAD_Button_6 = 0x06,                     /*!< Button 6 code */
	TM_KEYPAD_Button_7 = 0x07,                     /*!< Button 7 code */
	TM_KEYPAD_Button_8 = 0x08,                     /*!< Button 8 code */
	TM_KEYPAD_Button_9 = 0x09,                     /*!< Button 9 code */
	TM_KEYPAD_Button_STAR = 0x0A,                  /*!< Button START code */
	TM_KEYPAD_Button_HASH = 0x0B,                  /*!< Button HASH code */
	TM_KEYPAD_Button_A = 0x0C,	                   /*!< Button A code. Only on large size */
	TM_KEYPAD_Button_B = 0x0D,	                   /*!< Button B code. Only on large size */
	TM_KEYPAD_Button_C = 0x0E,	                   /*!< Button C code. Only on large size */
	TM_KEYPAD_Button_D = 0x0F,	                   /*!< Button D code. Only on large size */
	TM_KEYPAD_Button_NOPRESSED = KEYPAD_NO_PRESSED /*!< No button pressed */
} TM_KEYPAD_Button_t;

/**
 * @brief  Keypad size enumeration
 */
typedef enum {
	TM_KEYPAD_Type_Large = 0x00, /*!< Keypad 4x4 size */
	TM_KEYPAD_Type_Small         /*!< Keypad 3x4 size */
} TM_KEYPAD_Type_t;

/**
 * @defgroup TM_KEYPAD_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes keypad functionality
 * @param  type: Keypad type you will use. This parameter can be a value of @ref TM_KEYPAD_Type_t enumeration
 * @retval None
 */
void TM_KEYPAD_Init(TM_KEYPAD_Type_t type);

/**
 * @brief  Reads keypad data
 * @param  None
 * @retval Button status. This parameter will be a value of @ref TM_KEYPAD_Button_t enumeration
 */
TM_KEYPAD_Button_t TM_KEYPAD_Read(void);

/**
 * @brief  Updates keypad
 * @note   This function must be called from interrupt routine every 1ms
 * @param  None
 * @retval None
 */
void TM_KEYPAD_Update(void);



#endif /* KEYPAD4X4_H_ */
