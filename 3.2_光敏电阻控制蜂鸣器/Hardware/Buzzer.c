#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	//第一步通过RCC给GPIO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//第二步初始化GPIO
	
	//1.定义结构体GPIO_InitTypeDef，来作为初始化的属性
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//2.设置为推挽输出形式：无论是低电平还是高电平都是有驱动能力的
	//3.选择需要初始化的端口地址，可以选择多个端口进行初始化，通过写" | "隔开
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	//4.设定GPIO口的输出频率
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	//5.用GPIO初始化函数，传入端口类型，初始化的属性
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	//第三步写入
//	GPIO_ResetBits(GPIOB,GPIO_Pin_12);输出低电平
//	GPIO_SetBits(GPIOB,GPIO_Pin_12);输出高电平

}

void Buzzer_On(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_Off(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
}
