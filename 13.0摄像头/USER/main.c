#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "TFT.h"
#include "LED.h"
#include "ov7670.h"
#include "string.h"
#include "exti.h"

extern u8 ov_sta;	//��exit.c���涨��

void camera_refresh(void)
{
	u32 j;
 	u16 color;	 
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������ 
		LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1;  
		for(j=0;j<76800;j++)
		{
			OV7670_RCK=0;
			color=GPIOC->IDR&0XFF;	//������
			OV7670_RCK=1; 
			color<<=8;  
			OV7670_RCK=0;
			color|=GPIOC->IDR&0XFF;	//������
			OV7670_RCK=1; 
			LCD_WR_DATA(color);	   
		}   							 
		EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE8�ϵ��жϱ�־λ
		ov_sta=0;					//��ʼ��һ�βɼ�
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 
	} 
}	


int main(void)
{
	uart_init(9600);
	delay_init();
	LED_Init();
	LCD_Init();
	if(lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X5510)	//ǿ��������Ļ�ֱ���Ϊ320*240.��֧��3.5/4.3�����
	{
		lcddev.width=240;
		lcddev.height=320; 
	}

  POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,"WarShip STM32");	
	LCD_ShowString(60,70,"OV7670 TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2012/9/14");  
  LCD_ShowString(60,130,"OV7670 Init...");	
	while(OV7670_Init())//��ʼ��OV7670
	{
		LCD_ShowString(60,130,"OV7670 Error!!");
		delay_ms(200);
	  LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
		LED_01();
	}
	
	LCD_ShowString(60,130,"OV7670 Init OK");
	delay_ms(1500);	 
	
	EXTI3_Init();						//ʹ�ܶ�ʱ������
	OV7670_Window_Set(10,174,240,320);	//���ô���	  
  OV7670_CS=0;			
	
	while(1)
	{
		camera_refresh();//������ʾ
		LED_01();
	}
	
}
