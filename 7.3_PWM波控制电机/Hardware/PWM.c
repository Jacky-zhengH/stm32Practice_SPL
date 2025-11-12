#include "stm32f10x.h"                  // Device header
//1.开启RCC时钟，打开定时器内部时钟和给外设使能
//2.配置时基单元
//3.配置输出比较单元，设置捕获/比较器
//4.配置GPIO输出
//5.配置运行控制函数
void PWM_Init(void)
{
    
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //开启RCC_APB1时钟，由于是选择的是基本定时器
    //开启RCC_APB2时钟，用于外设的时钟使能
    
    //GPIOA口配置
    GPIO_InitTypeDef GPIOInitSturcture;
    GPIOInitSturcture.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIOInitSturcture.GPIO_Pin=GPIO_Pin_2;
    GPIOInitSturcture.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIOInitSturcture);
    
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//结构体
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1; //指定时钟分频
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period= 100 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler= 36 - 1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
    //当时写了TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//结构体初始化
    //结果功夫全白费，重新初始化了一次IimeBaseSturct,就等于没有做任何配置，哈哈
    
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//时基单元初始化
    
    
    //此部分为输出比较单元初始化
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    //OC初始化函数，给定一个初始值，以便防止高级定时器的使用相同配置的结构体时发生错误
    //带Idle和N字眼的是高级定时器所需要的参数
    //通用定时器可以不用
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;                             //设置模式
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;                     //极性
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;                 //设置输出使能
    TIM_OCInitStructure.TIM_Pulse=0;                                            //设置ccr（占空比）
    TIM_OC3Init(TIM2,&TIM_OCInitStructure);
    
    TIM_Cmd(TIM2,ENABLE);//启动时钟
}

void PWM_SETcompare(uint16_t Compare)
{
    TIM_SetCompare3(TIM2,Compare);//设置crr的值而非直接设置占空比，这个值是需要实际运算的
}
