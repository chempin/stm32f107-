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

	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	
	printf("\r\n�����͵���ϢΪ:%d\r\n\r\n",a);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	printf("\n");  
	
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%200==0)printf("123123123123\n");  
			delay_ms(10);   
		}
	}	 
}
