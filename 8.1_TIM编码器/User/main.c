#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
#include "Encode.h"


int main(void)
{
    OLED_Init();
    Encode_Init();
    
    OLED_ShowString(1,1,"Speed:");

    while(1)
    {
        OLED_ShowSignedNum(1,7,Encode_GetCNT(),5);
        Delay_ms(500);
    }
}

