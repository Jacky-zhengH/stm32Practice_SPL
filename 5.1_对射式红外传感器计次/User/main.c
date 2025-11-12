#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

uint8_t Keynum;

int main(void)
{
	OLED_Init();
    CountSensor_Init();
	OLED_ShowString(2,1,"Count:");
    OLED_ShowString(1,1,"ON");
    while(1)
    {
        OLED_ShowNum(3,1,CountSensor_countGet(),5);
    }
}

