#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t Keynum;

int main(void)
{
	Key_Init();
	OLED_Init();
	OLED_ShowString(1,1,"ON");
    OLED_ShowSignedNum(2,1,-100,3);
    OLED_ShowString(3,1,"This is OLED");

}

