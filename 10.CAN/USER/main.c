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
	
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_7tq,5,CAN_Mode_LoopBack);   //��ʼ��canΪ�ػ�ģʽ
	
	POINT_COLOR=BLUE;
	LCD_ShowString(30,50,"stm32");	
	LCD_ShowString(30,70,"CAN TEST");	
	LCD_ShowString(30,90,"2016/10/13");	   
	LCD_ShowString(30,110,"looopback Mode");
	LCD_ShowString(30,170,"Count:");			//��ʾ��ǰ����ֵ	
  LCD_ShowString(30,190,"send data:");	
	LCD_ShowString(30,250,"receive data:");
	while(1)
	{	
		while(t)
		{
		for(i=0;i<8;i++)
			{
				canbuf[i]=cnt+i;//��䷢�ͻ�����
				if(i<4)LCD_ShowxNum(60+i*32,210,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(60+(i-4)*32,230,canbuf[i],3,16,0X80);	//��ʾ����
 			}
		res=Can_Send_Msg(canbuf,8);//����8���ֽ� 
			t=0;
		}	
		if(res)LCD_ShowString(110,190,"Failed");		//��ʾ����ʧ��
			else LCD_ShowString(110,190,"OK    ");	 		//��ʾ���ͳɹ�		

    	
		data=Can_Receive_Msg(canbuf);
		data=8;	
		if(data)//���յ�������
		{			
			LCD_Fill(60,270,130,310,WHITE);//���֮ǰ����ʾ
 			for(i=0;i<data;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(60+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
 			}
			t=1;
		}
		
		LED_01();
		cnt++;
		LCD_ShowxNum(80,170,cnt,3,16,0X80);	//��ʾ����
	}	
	
}
