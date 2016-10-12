#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "TFT.h"
#include "touch.h"


void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(216,0,"RST");//显示清屏区域
  POINT_COLOR=RED;//设置画笔蓝色 
}



int main(void)
{
  u8 key;	
	
	delay_init();
	NVIC_Configuration();
	uart_init(9600);
	LED_Init();
	LCD_Init();
  
	
	POINT_COLOR=RED;//设置字体为蓝色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"TOUCH TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");		
	delay_ms(10000);
	Touch_Init(); 
	
	
	while(1)
	{	
		if(key==0)
		{
			LED_1();
			LCD_Clear(WHITE);//清屏
		  Touch_Adjust();  //屏幕校准 
			Save_Adjdata();	 
			Load_Drow_Dialog();
			LED_0();
			key=3;
		}
		if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
		{
			Pen_Int_Set(0);//关闭中断
			do
			{
				Convert_Pos();
				Pen_Point.Key_Sta=Key_Up;
				if(Pen_Point.X0>216&&Pen_Point.Y0<16)Load_Drow_Dialog();//清除
				else 
				{
					Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);//画图	    
					GPIOB->ODR|=1<<4;    //PC1 上拉	   
				}
			}while(PEN==0);//如果PEN一直有效,则一直执行
			Pen_Int_Set(1);//开启中断
		}else delay_ms(10);
//			LED_01();
	}	 
}
