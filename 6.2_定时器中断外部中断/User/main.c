#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint8_t Num;//用于执行加减

int main(void)
{
	TimerInit();
	OLED_Init();
	OLED_ShowString(1,1,"ON");
    while(1)
    {
        OLED_ShowString(2,1,"Num:");
        OLED_ShowNum(2,5,Num-1,5);
        OLED_ShowString(3,1,"CNT:");
        OLED_ShowNum(3,5,Timer_GetCounter(),5);

    }
}

