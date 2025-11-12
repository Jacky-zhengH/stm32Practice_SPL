#ifndef __SERIAl_H
#define __SERIAl_H

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_Array(uint8_t* Array,uint16_t Length);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);
#endif
