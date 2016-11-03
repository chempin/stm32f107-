#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序参考自网友guanfu_wang代码。
//ALIENTEK战舰STM32开发板
//SCCB 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/14
//版本：V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////

#define SCCB_SDA_IN()  {GPIOD->CRH&=0XFFFFFFF0;GPIOD->CRH|=0X00000008;}
#define SCCB_SDA_OUT() {GPIOD->CRH&=0XFFFFFFF0;GPIOD->CRH|=0X00000003;}

//IO操作函数	 
#define SCCB_SCL    		PDout(9)	 	//SCL
#define SCCB_SDA    		PDout(8) 		//SDA	 

#define SCCB_READ_SDA    	PDin(8)  		//输入SDA    
#define SCCB_ID   			0X42  			//OV7670的ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif
