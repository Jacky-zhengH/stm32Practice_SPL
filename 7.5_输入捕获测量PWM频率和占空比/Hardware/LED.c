#include "stm32f10x.h"                  // Device header
//驱动LED模块函数

//1、Led模块初始化函数

void LED_Init(void)
{
	//第一步通过RCC给GPIO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步初始化GPIO
	
	//1.定义结构体GPIO_InitTypeDef，来作为初始化的属性
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//2.设置为推挽输出形式：无论是低电平还是高电平都是有驱动能力的
	//3.选择需要初始化的端口地址，可以选择多个端口进行初始化，通过写" | "隔开
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_2;
	//4.设定GPIO口的输出频率
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	//5.用GPIO初始化函数，传入端口类型，初始化的属性
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_2);
	
	//6.默认是高电平驱动所以初始化后LED保持亮，所以要
	//再加个设置低电平函数使初始化后灯为熄灭状态
	
}

void LED0_SET(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}
void LED0_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

void LED0_Turn(void)//根据端口输出情况更新输出的状态
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);//如果读到为高电平就状态取反
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//反之，则可实现状态取反
	}
}
void LED2_SET(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
}
