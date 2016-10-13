#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "TFT.h"
#include "LED.h"
#include "CAN.h"


int main(void)
{
	u8 i,t=1;
	u8 cnt=0;
	u8 res;
	u8 data=0;
	u8 canbuf[8];
	
	uart_init(9600);
	delay_init();
	LED_Init();
	LCD_Init();
	
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_7tq,5,CAN_Mode_LoopBack);   //初始化can为回环模式
	
	POINT_COLOR=BLUE;
	LCD_ShowString(30,50,"stm32");	
	LCD_ShowString(30,70,"CAN TEST");	
	LCD_ShowString(30,90,"2016/10/13");	   
	LCD_ShowString(30,110,"looopback Mode");
	LCD_ShowString(30,170,"Count:");			//显示当前计数值	
  LCD_ShowString(30,190,"send data:");	
	LCD_ShowString(30,250,"receive data:");
	while(1)
	{	
		while(t)
		{
		for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//填充发送缓冲区
				if(i<4)LCD_ShowxNum(60+i*32,210,canbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(60+(i-4)*32,230,canbuf[i],3,16,0X80);	//显示数据
 			}
		res=Can_Send_Msg(canbuf,8);//发送8个字节 
			t=0;
		}	
		if(res)LCD_ShowString(110,190,"Failed");		//提示发送失败
			else LCD_ShowString(110,190,"OK    ");	 		//提示发送成功		

    	
		data=Can_Receive_Msg(canbuf);
		data=8;	
		if(data)//接收到有数据
		{			
			LCD_Fill(60,270,130,310,WHITE);//清除之前的显示
 			for(i=0;i<data;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,canbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(60+(i-4)*32,290,canbuf[i],3,16,0X80);	//显示数据
 			}
			t=1;
		}
		
		LED_01();
		cnt++;
		LCD_ShowxNum(80,170,cnt,3,16,0X80);	//显示数据
	}	
	
}
