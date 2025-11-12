#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint16_t i;

int main(void)
{
    OLED_Init();
    PWM_Init();
    IC_Init();
    
    OLED_ShowString(1,1,"Freq:00000Hz");
    
    PWM_SETPrescaler(720-1);    //Freq = 72M/PCR+1/ARR+1
    PWM_SETcompare(50);         //Duty = CCR /ARR+1
    
    while(1)
    {
        OLED_ShowNum(1,6,IC_GetFreq(),5);
    }
}

