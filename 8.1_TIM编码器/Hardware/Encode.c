#include "stm32f10x.h"                  // Device header

void Encode_Init(void)
{
    //开启RCC时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //设置GPIO输入模式
    
    GPIO_InitTypeDef GPIOInitSturcture;
    GPIOInitSturcture.GPIO_Mode=GPIO_Mode_IPU;
    GPIOInitSturcture.GPIO_Pin=GPIO_Pin_6 |GPIO_Pin_7;
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
    
    TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);
   
    TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICFilter=0xF;
    
    TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);
    
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Falling);;

    TIM_Cmd(TIM3,ENABLE);
}

int16_t Encode_GetCNT(void)
{
    int16_t Temp;
    Temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return Temp;
}

