#ifndef __G_LED_H
#define __G_LED_H
#include "stm32f10x.h"
#include "G_base_config.h"
#define LED_MAX_NUM 15
typedef GPIO_STRUCT LED_STRUCT;

//LED初始化，按照函数调用的顺序分配ID号
void LED_Init(GPIO_MEMBER IO_Port);
//LED控制函数 参数为ID和LED状态
extern void LED(DEVICE_ID ID,SWITCH_STATE state);
//翻转LED状态
extern void LED_TOGGLE(DEVICE_ID ID);
#endif
