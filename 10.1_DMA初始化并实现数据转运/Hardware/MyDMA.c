#include "stm32f10x.h"                  // Device header

uint16_t MySize;
/*DMA初始化*/
//第一步RCC开启DMA时钟
//第二步定义初始化结构体配置DMA各参数
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)//传入一个目标地址作为形参
{
    MySize = Size;
    
    /*RCC开启DMA时钟*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //DMA连在AHB总线上，所以用RCC_AHBPeriphClockCmd()
    
    DMA_InitTypeDef DMA_InitStructure; //定义初始化结构体
    
    DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;                             //传输模式
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;                        //传输方向
    DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;                               //选择是否存储器到存储器，即是软件触发还是硬件触发
    DMA_InitStructure.DMA_BufferSize=Size;                                  //缓存区大小，即设置传输计数器的大小
    DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;                     //设置优先级                     
    DMA_InitStructure.DMA_MemoryBaseAddr=AddrB;                             //存储器起始地址，数据大小，地址是否自增
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;                  
    DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;                       
    DMA_InitStructure.DMA_PeripheralBaseAddr=AddrA;                         //外设寄存器起始地址，数据大小，地址是否自增
    DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;              
    DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;                   
    
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);                             //第一个参数DMAy_Channelx指定DMA1或2的x通道，如果是硬件触发则需要选择特定的通道

    DMA_Cmd(DMA1_Channel1,DISABLE);                                          //DMA开控制
}

void MyDMA_Transf(void)
{
    DMA_Cmd(DMA1_Channel1,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1,MySize);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
