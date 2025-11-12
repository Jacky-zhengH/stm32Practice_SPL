#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void)
{
	//第一步通过RCC给GPIO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//设置为推挽输出形式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第三步写入
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0);// 输出低电平
//	GPIO_SetBits(GPIOA,GPIO_Pin_0);//输出高电平
	
	
	while(1)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
		Delay_ms(200);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(200);
	}	
}
