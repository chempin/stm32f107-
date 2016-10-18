#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h" 
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"	
#include "common.h" 
#include "touch.h"	
#include "usart2.h"	

 
 int main(void)
 { 
	u8 key,fontok=0; 	  
	delay_init();	    	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	uart_init(115200);	 	
	USART2_Init(115200); 
	LCD_Init();				
	LED_Init();         	 
	KEY_Init();																	    
 
	tp_dev.init();			//��������ʼ��
 	mem_init();				//��ʼ���ڴ��	    
 	exfuns_init();			//Ϊfatfs��������ڴ�  
  f_mount(fs[0],"0:",1); 	//����SD�� 
	  	f_mount(fs[1],"1:",1); 	//����FLASH.
	key=KEY_Scan(0);  
	if(key==KEY0_PRES)		//ǿ��У׼
	{
		LCD_Clear(WHITE);	//����
		tp_dev.adjust();  	//��ĻУ׼  
		LCD_Clear(WHITE);	//����
	}
	fontok=font_init();		//����ֿ��Ƿ�OK
	if(fontok||key==KEY1_PRES)//��Ҫ�����ֿ⣨�ֿⲻ����/key1���£�			 
	{
		LCD_Clear(WHITE);		   	
 		POINT_COLOR=RED;				   	   	  
		LCD_ShowString(60,50,200,16,16,"ALIENTEK STM32");
		while(SD_Initialize())		//���SD��
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16);//�����ֿ�
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);	       
	}  
	atk_8266_test();		//����ATKESP8266����
}
 



