#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "TFT.h"
#include "LED.h"
#include "RS485.h"	 

int main(void)
{
	
	u8 i=0,t=1;
	u8 key=0;
	u8 cnt=0;
	u8 rs485buf[5];
	
	uart_init(9600);
	delay_init();
	LED_Init();
	LCD_Init();
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	RS485_Init(9600);	//��ʼ��RS485
	
	
	POINT_COLOR=RED;
	LCD_ShowString(30,50,"stm32 TEST");	
	LCD_ShowString(30,70,"RS485 TEST");	
	LCD_ShowString(30,90,"2016/10/13");	 
	LCD_ShowString(30,170,"Count:");
	LCD_ShowString(30,190,"send data:");	
	LCD_ShowString(30,250,"receive data:");
	
	while(1)
	{
		key=0;
		while(t)
		{	
			for(i=0;i<5;i++)
			{
				rs485buf[i]=cnt+i;//��䷢�ͻ�����
				LCD_ShowxNum(60+i*32,210,rs485buf[i],3,16,0X80);	//��ʾ����
 			}
			RS485_Send_Data(rs485buf,5);//����5���ֽ� 
			t=0;
		}
		
		RS485_Receive_Data(rs485buf,&key);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		if(key)//���յ�������
		{
			if(key>5)key=5;//�����5������.
 			for(i=0;i<key;i++)LCD_ShowxNum(60+i*32,270,rs485buf[i],3,16,0X80);	//��ʾ����
			t=1;
 		}
		
		LED_01();
		cnt++;
		LCD_ShowxNum(80,170,cnt,3,16,0X80);	
	}
	
}
