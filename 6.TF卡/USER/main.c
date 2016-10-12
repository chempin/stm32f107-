#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "TFT.h"
#include "TF_Card.h"


u8 buf[512];//SD卡数据缓存区

int main(void)
{
	u32 sector_size;
	u8 t=0;	
	
	SystemInit();
	delay_init();	     //延时初始化
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
	LCD_Init();
	
	POINT_COLOR=RED;//设置字体为红色
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"SD Card TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");	
	
		while(SD_Initialize()!=0)//检测不到SD卡
	{
		LCD_ShowString(60,130,"SD Card Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"Please Check!      ");
		delay_ms(500);
		LED_01(); //DS0闪烁
	}
	//检测SD卡成功 											    
	LCD_ShowString(60,130,"SD Card Checked OK ");
	sector_size=SD_GetSectorCount();
	printf(" SD Sector Size:%x\n",sector_size);
	LCD_ShowString(60,150,"SD Card Size:    Mb");
	LCD_ShowNum(164,150,sector_size>>12,4,16);
	while(1)
	{
		if(t==30)//每6s钟执行一次
		{
			if(SD_ReadDisk(buf,0,1)==0)//读取MBR扇区
			{	
				LCD_ShowString(60,170,"USART1 Sending Data...");
				printf("SECTOR 0 DATA:\n");
				for(sector_size=0;sector_size<512;sector_size++)printf("%x ",buf[sector_size]);//打印MBR扇区数据    	   
				printf("\nDATA ENDED\n");
				LCD_ShowString(60,170,"USART1 Send Data Over!");
			}
			t=0;
		}   
	while(SD_Initialize()!=0)//检测不到SD卡
	{
		LCD_ShowString(60,130,"SD Card Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"Please Check!      ");
		delay_ms(500);
		LED_01();
	}
	//检测SD卡成功 											    
	LCD_ShowString(60,130,"SD Card Checked OK ");
	sector_size=SD_GetSectorCount();
	printf(" SD Sector Size:%x\n",sector_size);
	LCD_ShowString(60,150,"SD Card Size:    Mb");
	LCD_ShowNum(164,150,sector_size>>12,4,16);
	while(1)
	{
		if(t==30)//每6s钟执行一次
		{
			if(SD_ReadDisk(buf,0,1)==0)//读取MBR扇区
			{	
				LCD_ShowString(60,170,"USART1 Sending Data...");
				printf("SECTOR 0 DATA:\n");
				for(sector_size=0;sector_size<512;sector_size++)printf("%x ",buf[sector_size]);//打印MBR扇区数据    	   
				printf("\nDATA ENDED\n");
				LCD_ShowString(60,170,"USART1 Send Data Over!");
			}
			t=0;
		}   
		t++;
		delay_ms(200);
		LED_01();
	}
	}
	
}
