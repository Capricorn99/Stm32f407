#include "lcd5110.h"
#include "keypad4x4.h"

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

void number_to_string(uint8_t num , char* buf)
{
	if(num < 10){
		buf[0] = '0';
		buf[1] = num+48;
	}else if(num >= 10 && num < 99)
	{
		buf[0] = (num/10) + 48;
		buf[1]= (num % 10) + 48;
	}
}

int main(void) {
	LCD5110_Init(0x37);


    TM_KEYPAD_Button_t Keypad_Button, last_key;
    last_key = TM_KEYPAD_Button_NOPRESSED;
    TM_KEYPAD_Init(TM_KEYPAD_Type_Large);
    init_systick_timer(1000);

    while (1) {
        Keypad_Button = TM_KEYPAD_Read();
        if (Keypad_Button != TM_KEYPAD_Button_NOPRESSED && last_key == TM_KEYPAD_Button_NOPRESSED ) {
//            printf("%u\n", (uint8_t) Keypad_Button);
        	static char buf[3];
        	buf[2] = '\0';
        	number_to_string((uint8_t) Keypad_Button, buf);
        	LCD5110_Puts(buf, LCD5110_Pixel_Set, LCD5110_FontSize_5x7);
            LCD5110_Refresh();
		}
        last_key = Keypad_Button;
    }
}

void SysTick_Handler(void) {
    TM_KEYPAD_Update();
}
