#include "gpio.h"

/***************************************************************
Copyright  Information and electrical engineering of HUE All rights reserved.
�ļ���		: gpio.c
����	  	: �Ų���
�汾	   	: V1.0
����	   	: GPIO��ʼ��
����	   	: ��
��վ 	   	: ��
��־	   	: ����V1.0 2019/11/2 �Ų��ȴ���
***************************************************************/

void gpio_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA PB�˿�ʱ��
	

 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // ������  �˿�����
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.4
 GPIO_ResetBits(GPIOA,GPIO_Pin_4);						 //PB.5 �����
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LoRa EN  �˿�����
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����
	
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //ָʾ��  �˿�����
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.15
 GPIO_ResetBits(GPIOA,GPIO_Pin_15);						 //PA.15 �����
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //485 RE �˿�����
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.1
 GPIO_ResetBits(GPIOA,GPIO_Pin_1);						 //PA.1 �����
}
 
