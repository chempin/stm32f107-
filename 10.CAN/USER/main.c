#include "stm32f10x.h"
#include "LED.h"
#include "sys.h"
#include "delay.h"
int main(void)
{
	delay_init();
	LED_Init();
	
	
	while(1)
	{
		LED_01();
		delay_init();
	}
}
