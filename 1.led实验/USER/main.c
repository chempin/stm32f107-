#include<stm32f10x.h>
#define uint unsigned int 

int delay(int z)
{
	 uint x,y;
	 for(x=100;x<z;x++)
		for(y=100;y<1000;y++);
	 return 0;
}

int main(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;  //���ýṹ�����
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //��������
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�����ʽ
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //����ٶ�			
	 GPIO_Init(GPIOB,&GPIO_InitStructure);          //����ṹ���ַ
  while(1)
	{
	 
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0);              //����io��Ϊ�͵�ƽ
	 GPIO_SetBits(GPIOB,GPIO_Pin_1);
	 delay(10000);
   GPIO_SetBits(GPIOB,GPIO_Pin_0); 
	 GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	 delay(10000);
	} 
	
}
