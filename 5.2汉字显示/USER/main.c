#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "TFT.h"
#include "LED.h"

int main(void)
{
	
	uart_init(9600);
	delay_init();
	LED_Init();
	LCD_Init();
	
	POINT_COLOR=RED;
	LCD_ShowString(30,50,"stm32 TEST");	
	LCD_ShowString(30,70,"2016/10/13");	 
	
	while(1)
	{
		LED_01();
	}
	
}
