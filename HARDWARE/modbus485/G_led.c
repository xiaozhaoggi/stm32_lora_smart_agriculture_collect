//#include "G_led.h"

//LED_STRUCT GPIO_LED[LED_MAX_NUM];
//DEVICE_NUM LED_Num = 0;

//void LED_Init(GPIO_MEMBER IO_Port)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_STRUCT gpio = GPIO_Convert(IO_Port);
//	if(IO_Port != Null)
//	{
//		RCC_GPIO_Init(gpio.GPIOx);
//		
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//		GPIO_InitStructure.GPIO_Pin = gpio.GPIO_Pin;
//		GPIO_Init(gpio.GPIOx, &GPIO_InitStructure);
//		
//		GPIO_LED[LED_Num].GPIOx = gpio.GPIOx;
//		GPIO_LED[LED_Num++].GPIO_Pin = gpio.GPIO_Pin;
//		
//		gpio.GPIOx->BSRRH = gpio.GPIO_Pin;
//	}
//}

//void LED(DEVICE_ID ID , SWITCH_STATE state)
//{
//	if(ID-1 < LED_Num)
//	{
//		if(state == OFF)
//			GPIO_ResetBits(GPIO_LED[ID-1].GPIOx,GPIO_LED[ID-1].GPIO_Pin);
//		else
//			GPIO_SetBits(GPIO_LED[ID-1].GPIOx,GPIO_LED[ID-1].GPIO_Pin);
//	}
//}

//void LED_TOGGLE(DEVICE_ID ID)
//{
//	if(ID-1 < LED_Num)
//		toggle(GPIO_LED[ID-1].GPIOx,GPIO_LED[ID-1].GPIO_Pin);
//}

