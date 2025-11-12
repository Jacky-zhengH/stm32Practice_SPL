#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

/*USART发送模式初始化*/
void Serial_Init(void)
{
    /*RCC开启时钟，USART1时钟在APB2，2、3在APB1*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    /*GPIO部分*/
    GPIO_InitTypeDef GPIO_Instructer;
	GPIO_Instructer.GPIO_Mode=GPIO_Mode_AF_PP;      //复用功能，低电平触发，推挽输出
	GPIO_Instructer.GPIO_Pin=GPIO_Pin_9;
	GPIO_Instructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Instructer);
    
    /*USART部分*/
    /*1.结构体定义+初始化函数*/
    USART_InitTypeDef USART_InitStructure;                                          
    
    USART_InitStructure.USART_Mode=USART_Mode_Tx;                                   //选择发送或接受模式，可用|同时触发
    USART_InitStructure.USART_Parity=USART_Parity_No;                               //校验模式（无，奇，偶）
    USART_InitStructure.USART_StopBits=USART_StopBits_1;                            //停止位占的字节位数（0.5,1,1.5,2）
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;                       //发送或接受的字节长度（8/9）
    USART_InitStructure.USART_BaudRate= 9600;                                       //波特率，直接写数值即可
    USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;  //选择硬件控流模式
    USART_Init(USART1,&USART_InitStructure);                
    
    USART_Cmd(USART1,ENABLE);//USART开关控制
   
}

/*数据发送字节函数*/
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1,Byte);
    /*防止数据覆盖，需要TXE标志位判断为完成，在此之前选择等待*/
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
    /*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}

/*发送数组*/
void Serial_Array(uint8_t* Array,uint16_t Length)
{
    uint16_t i;
    
    for(i = 0 ; i < Length ; i++ )
    {
        Serial_SendByte(Array[i]);
    }
}


/**
  * 函    数：串口发送一个字符串
  * 参    数：String 要发送字符串的首地址
  * 返 回 值：无
  */
void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
	{
		Serial_SendByte(String[i]);		//依次调用Serial_SendByte发送每个字节数据
	}
}

/**
  * 函    数：次方函数（内部使用）
  * 返 回 值：返回值等于X的Y次方
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//设置结果初值为1
	while (Y --)			//执行Y次
	{
		Result *= X;		//将X累乘到结果
	}
	return Result;
}

/**
  * 函    数：串口发送数字
  * 参    数：Number 要发送的数字，范围：0~4294967295
  * 参    数：Length 要发送数字的长度，范围：0~10
  * 返 回 值：无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)		//根据数字长度遍历数字的每一位
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');	//依次调用Serial_SendByte发送每位数字
	}
}

/**
  * 函    数：使用printf需要重定向的底层函数
  * 参    数：保持原始格式即可，无需变动
  * 返 回 值：保持原始格式即可，无需变动
  */
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);			//将printf的底层重定向到自己的发送字节函数
	return ch;
}

/**
  * 函    数：自己封装的prinf函数
  * 参    数：format 格式化字符串
  * 参    数：... 可变的参数列表
  * 返 回 值：无
  */
void Serial_Printf(char *format, ...)
{
	char String[100];				//定义字符数组
	va_list arg;					//定义可变参数列表数据类型的变量arg
	va_start(arg, format);			//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);	//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);					//结束变量arg
	Serial_SendString(String);		//串口发送字符数组（字符串）
}

