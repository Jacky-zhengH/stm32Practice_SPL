#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Sevor.h"
#include "Key.h"
#include "PWM.h"

uint16_t Keynum;
float angle;

int main(void)
{
    Key_Init();
    OLED_Init();
    PWM_Init();
    Sevor_Init();
    OLED_ShowString(1,1,"ON");
    OLED_ShowString(2,1,"angle:");
    Sevor_SetAngle(180);
    while(1)
    {
        Keynum = Key_GetNum();
        if(Keynum == 1)
        {
            angle += 30;
            if(angle > 180)
            {
                angle = 0;
            }
        }
        Sevor_SetAngle(angle);
        OLED_ShowNum(2,7,angle,3);
        OLED_ShowNum(3,1,Keynum,1);

    }
}

