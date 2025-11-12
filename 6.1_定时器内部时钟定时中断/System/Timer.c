#include "stm32f10x.h"    // Device header
//1.打开RCC内部时钟
//2.选择内部时钟模式
//3.配置时基单元
//4.配置中断模块
//5.计数器使能

extern uint8_t Num;

void TimerInit(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    //开启RCC_APB1时钟，由于是选择的是基本定时器
    TIM_InternalClockConfig(TIM2);
    //选择时钟TIM2
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    //指定时钟分频
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period= 10000 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler= 7200 - 1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
    
    //使能中断
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//TIM_IT_Update是指中断模式为更新中断
    
    //配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2,ENABLE);

}

//写中断函数
void TIM2_IRQHandler(void)
{
    //先获取中断标志位,
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)== SET)
    {
        Num++;
        //清除标志位
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }


}




