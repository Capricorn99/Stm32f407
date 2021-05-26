#include "stm32f4xx.h"
#include "stm32f4xx_gpio_driver.h"
#include "stm32f4xx_spi_driver.h"

#include "lcd5110.h"
#include "keypad4x4.h"
#include "ade7753.h"

void delay(void) {
	for(uint32_t i = 0; i < 500000; i++);
}

#define SYSTICK_TIM_CLK	16000000UL
void init_systick_timer(uint32_t tick_hz)
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

int main(void) {
	char* buf;

	LCD5110_Init(0x37);
	ADE_Inits();


	//ADE_WriteData(SPI2, MODE, 0x000C, 2);

	printf("MODE : %x \n", ADE_ReadData(SPI2, MODE, 2));
	while(1)
	{
		uint32_t vrms = ADE_ReadData(SPI2, VRMS, 3);
		int_to_string(vrms, buf);

//		printf("VRMS : %x \n", vrms);
		LCD5110_Clear();
		LCD5110_Puts("Vrms: ", LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
		LCD5110_Puts(buf, LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
		LCD5110_Refresh();

		if(GPIO_ReadFromInputPin(PORT_SAG, PIN_SAG) ==  0)
		{
			GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_11, 1);
		}
		else
		{
			GPIO_WriteToOutputPin(GPIOE, GPIO_PIN_NO_11, 0);
		}
		delay();
	}
//    TM_KEYPAD_Button_t Keypad_Button, last_key;
//    last_key = TM_KEYPAD_Button_NOPRESSED;
//    TM_KEYPAD_Init(TM_KEYPAD_Type_Large);
//    init_systick_timer(1000);

//	char* buf;
//	int_to_string(ADE_ReadData(SPI2, VRMS, 3), buf);
//    LCD5110_Puts(buf, LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
//    LCD5110_Refresh();

//    while (1) {
//        Keypad_Button = TM_KEYPAD_Read();
//        if (Keypad_Button != TM_KEYPAD_Button_NOPRESSED && last_key == TM_KEYPAD_Button_NOPRESSED ) {
////            printf("%u\n", (uint8_t) Keypad_Button);
//        	static char buf[3];
//        	buf[2] = '\0';
//        	number_to_string((uint8_t) Keypad_Button, buf);
//        	LCD5110_Puts(buf, LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
//        	LCD5110_Refresh();
//		}
//        last_key = Keypad_Button;
//    }
}



void SysTick_Handler(void) {
    TM_KEYPAD_Update();
}

