#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //开启RCC_APB1时钟，由于是选择的是基本定时器
    //开启RCC_APB2时钟，用于外设的时钟使能
    
    //GPIOA口配置
    GPIO_InitTypeDef GPIOInitSturcture;
    GPIOInitSturcture.GPIO_Mode=GPIO_Mode_IPU;
    GPIOInitSturcture.GPIO_Pin=GPIO_Pin_6;
    GPIOInitSturcture.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIOInitSturcture);
    
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//结构体
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1; //指定时钟分频
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period= 65536 - 1;//ARR
    TIM_TimeBaseInitStruct.TIM_Prescaler= 1 - 1;//PSC
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
    //当时写了TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//结构体初始化
    //结果功夫全白费，重新初始化了一次IimeBaseSturct,就等于没有做任何配置，哈哈
    
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//时基单元初始化
    
    //初始化输入捕获单元
    TIM_ICInitTypeDef TIM_ICInitStruct;
    TIM_ICStructInit(&TIM_ICInitStruct);
    TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICFilter=0xF;
    TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);

    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    
    TIM_Cmd(TIM3,ENABLE);
    

}

uint32_t IC_GetFreq(void)
{
    return 1000000/(TIM_GetCapture1(TIM3)+1);
}

uint32_t IC_GetDuty(void)
{
    return (TIM_GetCapture2(TIM3)+1)*100/TIM_GetCapture1(TIM3);
}

