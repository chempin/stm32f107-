#include"stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"

int main(void)
{
	u8 t;
	u8 len;	
	u16 times=0;
	int a=22;

	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 //串口初始化为9600
	
	printf("\r\n您发送的消息为:%d\r\n\r\n",a);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
	printf("\n");  
	
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%200==0)printf("123123123123\n");  
			delay_ms(10);   
		}
	}	 
}
