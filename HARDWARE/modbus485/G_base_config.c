#include "G_base_config.h"

//GPIO²Ù×÷
GPIO_STRUCT GPIO_Convert(GPIO_MEMBER IO_PORT)
{
	u8 i = 0;
	u32 cnt = 0;
	GPIO_STRUCT GPIO;
	GPIO.GPIO_Pin = IO_PORT & 0x0000ffff;
	for(i=16; i<32 && cnt!=1; i++)
	{
		cnt = (IO_PORT >> i) & 0x00000001;
	}
	GPIO.GPIOx = (GPIO_TypeDef *)(APB1PERIPH_BASE + (i-17)*0x0400);
	return GPIO;
}

u8 pin2PinSource(u16 GPIO_Pin)
{
	u8 i = 0;
	u16 GPIO_PinSource;
	u16 cnt = 0;
	for(i=0; i<16 && cnt!=1; i++)
	{
		cnt = (GPIO_Pin >> i) & 0x0001;
	}
	GPIO_PinSource = i-1;
	return GPIO_PinSource;
}

void toggle(GPIO_TypeDef* GPIOx,u16 GPIO_Pin) 
{
	GPIOx->ODR ^= GPIO_Pin;
}

//RCC²Ù×÷
void RCC_GPIO_Init(GPIO_TypeDef* GPIOx)
{
	RCC->APB2ENR |= (RCC_APB2Periph_GPIOA << (((u32)(GPIOx)-APB2PERIPH_BASE)/0x400));
}

//TIM²Ù×÷
TIM_STRUCT TIM_Convert(TIM_MEMBER TIM_N)
{
	u8 i = 0,t = 0;
	TIM_STRUCT TIM = {(TIM_TypeDef *)0,CHANNEL1}; 
	if(TIM_N != TIM_Null)
	{
		for(i = 0; i < 4 && t != 1; i++)
		{
			t = (TIM_N >> i) & 0x01;
		}
		TIM.channel = (TIM_CHANNEL)(i);
		for(i = 8,t = 0; i < 16 && t != 1; i++)
		{
			t = (TIM_N >> i) & 0x01;
		}
		if(i != 9 && i != 14)
			TIM.TIMx = (TIM_TypeDef *)(APB1PERIPH_BASE + 0x0400*(i-10));
		else if(i == 9)
			TIM.TIMx = TIM1;
		else if(i == 14)
			TIM.TIMx = TIM8;
}
	return TIM;
}

void GPIO_Operating(GPIO_MEMBER IOPort,FlagStatus pinState)
{
	GPIO_STRUCT gpio = GPIO_Convert(IOPort);
	if(pinState == SET)
	{
		GPIO_SetBits(gpio.GPIOx,gpio.GPIO_Pin);
	}else
	{
		GPIO_ResetBits(gpio.GPIOx,gpio.GPIO_Pin);
	}
}























