#include "gpio.h"

/***************************************************************
Copyright  Information and electrical engineering of HUE All rights reserved.
文件名		: gpio.c
作者	  	: 张博钊
版本	   	: V1.0
描述	   	: GPIO初始化
其他	   	: 无
网站 	   	: 无
日志	   	: 初版V1.0 2019/11/2 张博钊创建
***************************************************************/

void gpio_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA PB端口时钟
	

 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz

	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // 蜂鸣器  端口配置
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.4
 GPIO_ResetBits(GPIOA,GPIO_Pin_4);						 //PB.5 输出低
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LoRa EN  端口配置
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_ResetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出低
	
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //指示灯  端口配置
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.15
 GPIO_ResetBits(GPIOA,GPIO_Pin_15);						 //PA.15 输出低
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //485 RE 端口配置
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.1
 GPIO_ResetBits(GPIOA,GPIO_Pin_1);						 //PA.1 输出低
}
 
