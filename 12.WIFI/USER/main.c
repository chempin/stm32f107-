#include "stm32f10x.h"
#include "LED.h"
#include "sys.h"
#include "delay.h"
#include "TFT.h"

int main(void)
{
	LED_Init();
	delay_init();
	LCD_Init();				
	
	while(1)
	{
		LED_01();
	}
}
