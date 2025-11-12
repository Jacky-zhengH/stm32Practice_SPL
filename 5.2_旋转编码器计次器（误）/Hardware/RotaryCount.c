#include "stm32f10x.h"                  // Device header

int16_t CountNum;

void RotaryCount_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitTypeDef GPIOInstructer;
    GPIOInstructer.GPIO_Mode=GPIO_Mode_IPU;
    GPIOInstructer.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;
    GPIOInstructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIOInstructer);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
    
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line=EXTI_Line0 | EXTI_Line1;
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStruct;
    
    NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStruct);
    
     NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
    NVIC_Init(&NVIC_InitStruct);
}
int16_t Rotary_CountGet(void)
{
    int16_t Temp;
    Temp = CountNum;
    CountNum = 0;
    return Temp;

}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1) == 0)
        {
            CountNum++;
            
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }

}



void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0) == 0)
        {
            CountNum++;
            
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }

}
