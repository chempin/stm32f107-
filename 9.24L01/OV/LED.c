#include "LED.h"



void LED_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;  //设置结构体变量
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //设置引脚
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//输出方式
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //输出速度			
	 GPIO_Init(GPIOB,&GPIO_InitStructure);          //赋予结构体地址
}
 
void LED_01(void)	
{
	 
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0);              //设置io口为低电平
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
