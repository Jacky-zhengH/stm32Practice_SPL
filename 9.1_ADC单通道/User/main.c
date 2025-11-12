#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADvalue;
float Vorage;

int main(void)
{	
    OLED_Init();
    AD_Init();
	OLED_ShowString(1,1,"ON");
    OLED_ShowString(2,1,"ADValue:");
    OLED_ShowString(3,1,"Volatge:0.00V");
    while(1)
    {
        ADvalue = AD_GetValue();
        Vorage = (float)ADvalue / 4095 * 3.3;
        OLED_ShowNum(2,9,ADvalue,4);
        OLED_ShowNum(3,9,Vorage,1);
        OLED_ShowNum(3,11,(uint16_t)(Vorage*100)%100,2);
        Delay_ms(100);
    }
}

