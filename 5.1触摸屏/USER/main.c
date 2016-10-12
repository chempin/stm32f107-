#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "TFT.h"
#include "touch.h"


void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(216,0,"RST");//��ʾ��������
  POINT_COLOR=RED;//���û�����ɫ 
}



int main(void)
{
  u8 key;	
	
	delay_init();
	NVIC_Configuration();
	uart_init(9600);
	LED_Init();
	LCD_Init();
  
	
	POINT_COLOR=RED;//��������Ϊ��ɫ	   
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
			LCD_Clear(WHITE);//����
		  Touch_Adjust();  //��ĻУ׼ 
			Save_Adjdata();	 
			Load_Drow_Dialog();
			LED_0();
			key=3;
		}
		if(Pen_Point.Key_Sta==Key_Down)//������������
		{
			Pen_Int_Set(0);//�ر��ж�
			do
			{
				Convert_Pos();
				Pen_Point.Key_Sta=Key_Up;
				if(Pen_Point.X0>216&&Pen_Point.Y0<16)Load_Drow_Dialog();//���
				else 
				{
					Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);//��ͼ	    
					GPIOB->ODR|=1<<4;    //PC1 ����	   
				}
			}while(PEN==0);//���PENһֱ��Ч,��һֱִ��
			Pen_Int_Set(1);//�����ж�
		}else delay_ms(10);
//			LED_01();
	}	 
}
