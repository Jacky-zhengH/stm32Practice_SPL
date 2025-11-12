#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Motor.h"
#include "Key.h"
uint8_t Keynum;
int8_t Speed;

int main(void)
{
    Key_Init();
    OLED_Init();
    OLED_ShowString(1,1,"On");
    OLED_ShowString(2,1,"Speed:");
    Motor_Init();
    while(1)
    {
        Keynum = Key_GetNum();
        if(Keynum == 1)
        {
            Speed += 20;
            if(Speed > 100)
            {
                Speed = -100;
            }
        }
        Motor_SetSpeed(Speed);
        OLED_ShowSignedNum(2,7,Speed,3);
    }
}

