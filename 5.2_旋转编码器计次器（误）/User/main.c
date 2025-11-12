#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "RotaryCount.h"

int16_t Num;

int main(void)
{

	OLED_Init();
    RotaryCount_Init();
	OLED_ShowString(1,1,"ON");
    OLED_ShowString(2,1,"Num:");
    while(1)
    {
        Num += Rotary_CountGet();
        OLED_ShowSignedNum(2,5,Num,5);
    }
}

