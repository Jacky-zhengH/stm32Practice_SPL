#include "stm32f10x.h"                  // Device header
//RCC->APB2ENR=0x00000010;
//GPIOC->CRH=0x00300000;
//GPIOC->ODR=0x00002000;
//以上代码直接对寄存器进行配置，但需要一遍遍的查找对应寄存器的功能
//和判断，而且无法简单的配置单一串口，所以需要用到库函数
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	while(1)
	{
		
	}
}
