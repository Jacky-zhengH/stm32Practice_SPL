#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];

void AD_Init(void)
{
    //RCC时钟开启，ADCCLK开启，DMA开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    /*设置ADC时钟*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    /*RCC开启DMA时钟*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //DMA连在AHB总线上，所以用RCC_AHBPeriphClockCmd()
    
    //初始化GPIOA
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //初始化ADC规则组通道,四个外设信号对应ADC四个通道
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
    
    //ADC初始化
    ADC_InitTypeDef ADC_InitStruct;                                   //定义ADC_InitTypeDef，运用结构体初始化
    ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;                     //ADC模式，此处选独立模式，因为用的是单ADC
    ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;                 //数字对齐模式，可选择向左或向右对齐，此处选择向右对齐，方便后续获取数据无需进行位数转换
    ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;    //选择外部触发模式，由于此程序没有任何外设，选择用软件出发，所以选择无
    ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;                    //选择连续或单次
    ADC_InitStruct.ADC_NbrOfChannel=4;                                //选择使用的通道数量
    ADC_InitStruct.ADC_ScanConvMode=ENABLE;                          //选择是否为扫描模式
    //这里因为同时要进行四个ADC通道，所以要用扫描模式
    ADC_Init(ADC1,&ADC_InitStruct);                                   //填入结构体，初始化ADC配置
    
    //由于本次无需设置看门狗，所以跳过此步骤
    
    
    DMA_InitTypeDef DMA_InitStructure; //定义初始化结构体
    
    DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;                             //传输模式
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;                        //传输方向
    DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;                               //选择是否存储器到存储器，即是软件触发还是硬件触发
    DMA_InitStructure.DMA_BufferSize=4;                                     //缓存区大小，即设置传输计数器的大小
    DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;                     //设置优先级                     
    DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)AD_Value;                          //存储器起始地址，数据大小，地址是否自增
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;                  
    DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;                       
    DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;                      //外设寄存器起始地址，数据大小，地址是否自增
    DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;   //外设寄存器在这里是ADC1->DR        
    DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;                   
    
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);                             //第一个参数DMAy_Channelx指定DMA1或2的x通道，如果是硬件触发则需要选择特定的通道

    DMA_Cmd(DMA1_Channel1,ENABLE);                                         //DMA开控制
    //这里可以将DMA开关控制函数赋ENABLE
    //DMA工作三个要素：1. 2. 3.触发信号源（在这里ADC还没工作）
    
    ADC_DMACmd(ADC1,ENABLE);
    
    //ADC使能，上电
    ADC_Cmd(ADC1,ENABLE);   
    
    //ADC校准过程
    ADC_ResetCalibration(ADC1);                         //准许复位校准
    while (ADC_GetResetCalibrationStatus(ADC1) == SET); //检查是否准备好复位校准，若返回值不对，一直循环
    ADC_StartCalibration(ADC1);                         //开始校准
    while (ADC_GetCalibrationStatus(ADC1) == SET);      //检查是否校准完毕
    
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}





