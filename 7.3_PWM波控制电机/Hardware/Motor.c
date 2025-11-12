#include "stm32f10x.h"                  // Device header
#include "PWM.h"
//没有速度编码器
void Motor_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5;//电机正负引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    PWM_Init();//需要PWM波驱动，所以要先初始化PWM生成
    
    
}

void Motor_SetSpeed(int8_t Speed)//接受正负值
{
    if(Speed > 0)//正转
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4);//正引脚置SET
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);//引脚置SET
        PWM_SETcompare(Speed);
    }
    if(Speed < 0)//反转
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        PWM_SETcompare(-Speed);
    }


}

/*----------------有编码器功能------------------*/
/* 加速，减速，降速增加扭矩等其他功能函数*/
