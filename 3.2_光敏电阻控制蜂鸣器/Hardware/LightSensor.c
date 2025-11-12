#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_Instructer;
	GPIO_Instructer.GPIO_Mode=GPIO_Mode_IPU;//采用上拉模式
	GPIO_Instructer.GPIO_Pin=GPIO_Pin_13;
	GPIO_Instructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Instructer);
}

uint8_t LightSensor_GetData(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
