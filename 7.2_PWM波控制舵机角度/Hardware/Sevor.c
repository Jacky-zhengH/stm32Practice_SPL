#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Sevor_Init(void)
{
    PWM_Init();
}

void Sevor_SetAngle(float angle)
{
    
    PWM_SETcompare(angle / 180 * 2000 + 500);

}





