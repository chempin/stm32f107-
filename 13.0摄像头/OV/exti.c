#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "ov7670.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//�ⲿ�ж� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/01  
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved	  
////////////////////////////////////////////////////////////////////////////////// 	  
 


 //ov_sta:0,��ʼһ֡���ݲɼ�
u8 ov_sta;
 //�ⲿ�ж�5~9�������
void EXTI3_IRQHandler(void)
{		 		
 
	if(EXTI_GetITStatus(EXTI_Line3)==SET)//��8�ߵ��ж�
	{     
		if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				OV7670_WRST=0;	 	//��λдָ��		  		 
				OV7670_WRST=1;	
				OV7670_WREN=1;		//����д��FIFO
			}else 
			{
				OV7670_WREN=0;		//��ֹд��FIFO 
				OV7670_WRST=0;	 	//��λдָ��		  		 
				OV7670_WRST=1;	
			}
			ov_sta++;
		}
	}
 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���EXTI8��·����λ						  
} 
//�ⲿ�ж�8��ʼ��
void EXTI3_Init(void)
{   
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);//PA8���ж���8
 	   	 
	  EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
   
}


