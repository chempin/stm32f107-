#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "24cxx.h" 
#include "myiic.h"
#include "TFT.h"
#include "sys.h"
#include "usart.h"



const u8 TEXT_Buffer[]={"MiniSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)

int main(void)
{
	
	u8 datatemp[SIZE];
	
	
	LED_Init();
	delay_init();
	uart_init(9600);	
	LCD_Init();
	AT24CXX_Init();	
	
	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"IIC TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");		
	
	while(AT24CXX_Check())//��ⲻ��24c02
	{
		LCD_ShowString(60,130,"24C02 Check Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"Please Check!      ");
		delay_ms(500);
		LED_01();
	}
	LCD_ShowString(60,130,"24C02 Ready!");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ	
	delay_ms(1000);
	while(1)
	{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(60,170,"Start Write 24C02....");
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			LCD_ShowString(60,170,"24C02 Write Finished!");//��ʾ�������
		
		  delay_ms(5000);  LED_0();
		
			LCD_ShowString(60,170,"Start Read 24C02.... ");
			AT24CXX_Read(0,datatemp,SIZE);
			LCD_ShowString(60,170,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(60,190,datatemp);//��ʾ�������ַ���
		
		  delay_ms(5000); LED_1();
	}
}
