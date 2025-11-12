#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void)
{
	//第一步通过RCC给GPIO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//第二步初始化GPIO
	
	//1.定义结构体GPIO_InitTypeDef，来作为初始化的属性
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//2.设置为推挽输出形式：无论是低电平还是高电平都是有驱动能力的
	//3.选择需要初始化的端口地址，可以选择多个端口进行初始化，通过写" | "隔开
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	//4.设定GPIO口的输出频率
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	//5.用GPIO初始化函数，传入端口类型，初始化的属性
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//第三步写入
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0);输出低电平
//	GPIO_SetBits(GPIOA,GPIO_Pin_0);输出高电平
	
	
	while(1)
	{
		//GPIO_Write()函数：指定输出的端口类型，然后给寄存器直接写入数据
		//可以实现某一端口类型的整体信号输出
		//~：按位取反，因为是低电平驱动
		//端口有16个，但无法用二进制表示，所以需要转化成对应的16进制数据
		GPIO_Write(GPIOA,~0x0001);//0000 0000 0000 0001
		Delay_ms(200);
		GPIO_Write(GPIOA,~0x0002);//0000 0000 0000 0010
		Delay_ms(200);
		GPIO_Write(GPIOA,~0x0004);//0000 0000 0000 0100
		Delay_ms(200);
		GPIO_Write(GPIOA,~0x0008);//0000 0000 0000 1000
		Delay_ms(200);
		GPIO_Write(GPIOA,~0x0010);//0000 0000 0001 0000
		Delay_ms(200);

	}	
}
