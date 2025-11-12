#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t Array[3] = {0x41,0x42,0x43};

int main(void)
{
	OLED_Init();
    Serial_Init();
	OLED_ShowString(1,1,"ON");
    Serial_SendByte(0x51);
    Serial_Array(Array,3);
    while(1)
    {
    
    }
}

