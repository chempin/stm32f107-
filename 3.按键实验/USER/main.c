#include "stm32f10x.h"
#include "LED.h"
#include "ADC.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"	

int key(void);

int main(void)
{
   unsigned int key1=0;
	
	Adc_Init();
	delay_init();
  uart_init(9600);	
	LED_Init();
	
	while(1)
	{ 
		key1=key();
		if(key1)
		{
			switch (key1)
			{
			  case 1: LED_0();  break;
				case 2: LED_1();  break;
			  case 3: LED_01(); break;
			  case 4: LED_0(); LED_1();break;
			}
			
		}
   
	}
	
}

int key(void)
{
	 unsigned int a=0;
	
		a=Get_Adc_Average(ADC_Channel_0,10);
	
		if(a>1000&a<1200)
			return 1;
		else if(a>1300&a<1400)
			return 2;
		else if(a>2000&a<2100)
			return 3;
		else if(a<1000)
			return 0;
		else 
			return 4;
}
