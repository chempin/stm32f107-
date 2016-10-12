#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "NRF24L01.h"
#include "TFT.h"


int main(void)
{
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33];
	
	LED_Init();
	delay_init();
	uart_init(9600);	
	LCD_Init();	
	NRF24L01_Init();
	
	
	POINT_COLOR=RED;//设置字体为红色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"NRF24L01 TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");		
	
		while(NRF24L01_Check())//检测不到24L01
	{
		LCD_ShowString(60,130,"24L01 Check Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"Please Check!      ");
		delay_ms(500);
		LED_01();
	}
	
	LCD_ShowString(60,130,"24L01 Ready!");
	POINT_COLOR=BLUE;//设置字体为蓝色	 
	
	while(1)
	{
		/******************************************************************************************************/
//		LCD_ShowString(60,150,"NRF24L01 TX_Mode");	
//		NRF24L01_TX_Mode();
//		mode=' ';//从空格键开始  
//		while(1)
//		{	  		   				 
//			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//			{
//				LCD_ShowString(60,170,"Sended DATA:");	
//				LCD_ShowString(0,190,tmp_buf); 
//				key=mode;
//				for(t=0;t<32;t++)
//				{
//					key++;
//					if(key>('~'))key=' ';
//					tmp_buf[t]=key;	
//				}
//				mode++; 
//				if(mode>'~')mode=' ';  	  
//				tmp_buf[32]=0;//加入结束符		   
//			}else
//			{										   	
// 				LCD_ShowString(60,170,"Send Failed "); 
//				LCD_Fill(0,188,240,218,WHITE);//清空上面的显示			   
//			}
//		 LED_01();
//	  }
	/******************************************************************************************************/
	
   	LCD_ShowString(60,150,"NRF24L01 RX_Mode");	
		LCD_ShowString(60,170,"Received DATA:");	
		NRF24L01_RX_Mode();		  
		while(1)
		{	  		    		    				 
			if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
				tmp_buf[32]=0;//加入字符串结束符
				LCD_ShowString(0,190,tmp_buf);    
			}else delay_us(100);	   
			t++;
			if(t==10000)//大约1s钟改变一次状态
			{
				t=0;
				LED_01();
			} 				    
		}
	/******************************************************************************************************/
  }
}
