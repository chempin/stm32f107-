#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"


#define LED0 PBout(0)// PB0
#define LED1 PBout(1)// PB1


void LED_Init(void);
void LED_01(void);
void LED_0(void);	
void LED_1(void);

	

#endif
