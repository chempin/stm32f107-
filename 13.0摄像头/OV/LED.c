#include "LED.h"



void LED_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;  //���ýṹ�����
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //��������
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�����ʽ
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //����ٶ�			
	 GPIO_Init(GPIOB,&GPIO_InitStructure);          //����ṹ���ַ
}
 
void LED_01(void)	
{
	 
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0);              //����io��Ϊ�͵�ƽ
	 GPIO_SetBits(GPIOB,GPIO_Pin_1);
	 delay_ms(500);
   GPIO_SetBits(GPIOB,GPIO_Pin_0); 
	 GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	 delay_ms(500);
	} 

void LED_0(void)	
{
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
  delay_ms(500);
}	

void LED_1(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
  delay_ms(500);
}
