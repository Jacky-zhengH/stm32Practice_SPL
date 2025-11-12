#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
    //RCC时钟开启，ADCCLK开启
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    /*设置ADC时钟*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    
    //初始化GPIOA
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //初始化ADC规则组通道
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
    
    
    //ADC初始化
    ADC_InitTypeDef ADC_InitStruct;                                   //定义ADC_InitTypeDef，运用结构体初始化
    ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;                     //ADC模式，此处选独立模式，因为用的是单ADC
    ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;                 //数字对齐模式，可选择向左或向右对齐，此处选择向右对齐，方便后续获取数据无需进行位数转换
    ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;    //选择外部触发模式，由于此程序没有任何外设，选择用软件出发，所以选择无
    ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;                    //选择连续或单次
    ADC_InitStruct.ADC_NbrOfChannel=1;                                //选择使用的通道数量
    ADC_InitStruct.ADC_ScanConvMode=DISABLE;                          //选择是否为扫描模式
    
    ADC_Init(ADC1,&ADC_InitStruct);                                   //填入结构体，初始化ADC配置
    
    //由于本次无需设置看门狗，所以跳过此步骤
    
    //ADC使能，上电
    ADC_Cmd(ADC1,ENABLE);
    
    //ADC校准过程
    ADC_ResetCalibration(ADC1);                         //准许复位校准
    while (ADC_GetResetCalibrationStatus(ADC1) == SET); //检查是否准备好复位校准，若返回值不对，一直循环
    ADC_StartCalibration(ADC1);                         //开始校准
    while (ADC_GetCalibrationStatus(ADC1) == SET);      //检查是否校准完毕
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

//测量峰峰值，软件方法
uint16_t AD_GetTTvalue(void)
{




}




//开关控制并获取转换值函数，属于软件触发，不是外部触发
uint16_t AD_GetValue(void)
{
    
    //while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);  //获取ADC标志位，检查规则组是否转换完成，如果未完成则继续等待
    return ADC_GetConversionValue(ADC1);
}



