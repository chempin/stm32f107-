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
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	RS485_Init(9600);	//初始化RS485
	
	
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
				rs485buf[i]=cnt+i;//填充发送缓冲区
				LCD_ShowxNum(60+i*32,210,rs485buf[i],3,16,0X80);	//显示数据
 			}
			RS485_Send_Data(rs485buf,5);//发送5个字节 
			t=0;
		}
		
		RS485_Receive_Data(rs485buf,&key);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		if(key)//接收到有数据
		{
			if(key>5)key=5;//最大是5个数据.
 			for(i=0;i<key;i++)LCD_ShowxNum(60+i*32,270,rs485buf[i],3,16,0X80);	//显示数据
			t=1;
 		}
		
		LED_01();
		cnt++;
		LCD_ShowxNum(80,170,cnt,3,16,0X80);	
	}
	
}
