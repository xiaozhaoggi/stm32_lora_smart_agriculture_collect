#ifndef __G_LED_H
#define __G_LED_H
#include "stm32f10x.h"
#include "G_base_config.h"
#define LED_MAX_NUM 15
typedef GPIO_STRUCT LED_STRUCT;

//LED��ʼ�������պ������õ�˳�����ID��
void LED_Init(GPIO_MEMBER IO_Port);
//LED���ƺ��� ����ΪID��LED״̬
extern void LED(DEVICE_ID ID,SWITCH_STATE state);
//��תLED״̬
extern void LED_TOGGLE(DEVICE_ID ID);
#endif
