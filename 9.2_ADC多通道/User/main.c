#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t AD0,AD1,AD2,AD5;


int main(void)
{	
    OLED_Init();
    AD_Init();
    OLED_ShowString(1,1,"AD0v:");
    OLED_ShowString(2,1,"AD1v:");
    OLED_ShowString(3,1,"AD2v:");
    OLED_ShowString(4,1,"AD5v:");
    while(1)
    {
        AD0 = AD_GetValue(ADC_Channel_0);
        AD1 = AD_GetValue(ADC_Channel_1);
        AD2 = AD_GetValue(ADC_Channel_2);
        AD5 = AD_GetValue(ADC_Channel_5);
        
        OLED_ShowNum(1,6,AD0,4);
        OLED_ShowNum(2,6,AD1,4);
        OLED_ShowNum(3,6,AD2,4);
        OLED_ShowNum(4,6,AD5,4);
        
        Delay_ms(100);
    }
}

