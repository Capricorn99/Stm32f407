/*
 * 102Keypad_communicate.c
 *
 *  Created on: Apr 28, 2021
 *      Author: DELL7470
 */
#include "keypad4x4.h"
#include "lcd5110.h"

void int_to_string(uint32_t num , char* buf)
{
	int buf_len;
	if (num == 0) {
		buf[0] = 48;
		buf_len = 1;
	}
	else {
		for (buf_len = 0; num > 0; buf_len++) {
			buf[buf_len] = (num % 10) + 48;
			num /= 10;
		}

		for (int low = 0, high = buf_len - 1; low < high; low++, high--)
		{
			int temp = buf[low];
			buf[low] = buf[high];
			buf[high] = temp;
		}
	}
	buf[buf_len] = '\0';
}

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

#define SYSTICK_TIM_CLK 16000000UL
void init_systick_timer(uint32_t tick_hz) //tan so nhay vào ngắt trong 1 giây
{
	uint32_t *pSRVR = (uint32_t*)0xE000E014;
	uint32_t *pSCSR = (uint32_t*)0xE000E010;

    /* calculation of reload value */
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz)-1;

    //Clear the value of SVR
    *pSRVR &= ~(0x00FFFFFFFF);

    //load the value in to SVR
    *pSRVR |= count_value;

    //do some settings
    *pSCSR |= ( 1 << 1); //Enables SysTick exception request:
    *pSCSR |= ( 1 << 2);  //Indicates the clock source, processor clock source

    //enable the systick
    *pSCSR |= ( 1 << 0); //enables the counter

}

int main(void)
{
	char* buf;
	LCD5110_Init(0x37);

    /* Create keypad instance */
    TM_KEYPAD_Button_t Keypad_Button, temp;
    temp = TM_KEYPAD_Button_NOPRESSED;

    /* Initialize matrix keyboard */
    TM_KEYPAD_Init(TM_KEYPAD_Type_Large);
    init_systick_timer(10000);

    while (1) {
        /* Read keyboard data */
        Keypad_Button = TM_KEYPAD_Read();

        /* Keypad was pressed */
        if (Keypad_Button != TM_KEYPAD_Button_NOPRESSED && temp == TM_KEYPAD_Button_NOPRESSED ) /* Keypad is pressed */
		{
        	/* Print to user */
//			printf("%u \n", (uint8_t) Keypad_Button);
        	int_to_string((uint32_t) Keypad_Button, buf);
//        	LCD5110_Clear();
        	LCD5110_Puts(buf, LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
        	LCD5110_Refresh();
		}
        temp = Keypad_Button;
    }
}

/* 1ms handler */
void SysTick_Handler(void)
{
    /* Process keypad */
    TM_KEYPAD_Update();
}

