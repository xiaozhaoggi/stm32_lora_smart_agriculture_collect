#ifndef __G_BASE_CONFIG_H
#define __G_BASE_CONFIG_H
#include "stm32f10x.h"
#include "stdio.h"
/**************************************************************************************************************
*@fliename:stm3f24xx系列基础配置头文件
*@author:葛硕童
*@notes:
**************************************************************************************************************/
#define TrueOrFalse(x)  ((x)>0)?(1):(0)
typedef enum
{
	ON = 0,
	OFF = !ON
}SWITCH_STATE;		//开关状态

typedef enum
{
	START = 1,
	NO_START = !START
}SRART_FLAG;

typedef enum
{
	False = 0,
	True = !False
}Bool;

typedef enum
{
	Null = 0x00000000,
	
	PA0  = 0x00010001,
	PA1  = 0x00010002,
	PA2  = 0x00010004,
	PA3  = 0x00010008,
	PA4  = 0x00010010,
	PA5  = 0x00010020,
	PA6  = 0x00010040,
	PA7  = 0x00010080,
	PA8  = 0x00010100,
	PA9  = 0x00010200,
	PA10 = 0x00010400,
	PA11 = 0x00010800,
	PA12 = 0x00011000,
	PA13 = 0x00012000,
	PA14 = 0x00014000,
	PA15 = 0x00018000,
	
	PB0  = 0x00020001,
	PB1  = 0x00020002,
	PB2  = 0x00020004,
	PB3  = 0x00020008,
	PB4  = 0x00020010,
	PB5  = 0x00020020,
	PB6  = 0x00020040,
	PB7  = 0x00020080,
	PB8  = 0x00020100,
	PB9  = 0x00020200,
	PB10 = 0x00020400,
	PB11 = 0x00020800,
	PB12 = 0x00021000,
	PB13 = 0x00022000,
	PB14 = 0x00024000,
	PB15 = 0x00028000,
	
	PC0  = 0x00040001,
	PC1  = 0x00040002,
	PC2  = 0x00040004,
	PC3  = 0x00040008,
	PC4  = 0x00040010,
	PC5  = 0x00040020,
	PC6  = 0x00040040,
	PC7  = 0x00040080,
	PC8  = 0x00040100,
	PC9  = 0x00040200,
	PC10 = 0x00040400,
	PC11 = 0x00040800,
	PC12 = 0x00041000,
	PC13 = 0x00042000,
	PC14 = 0x00044000,
	PC15 = 0x00048000,
	
	PD0  = 0x00080001,
	PD1  = 0x00080002,
	PD2  = 0x00080004,
	PD3  = 0x00080008,
	PD4  = 0x00080010,
	PD5  = 0x00080020,
	PD6  = 0x00080040,
	PD7  = 0x00080080,
	PD8  = 0x00080100,
	PD9  = 0x00080200,
	PD10 = 0x00080400,
	PD11 = 0x00080800,
	PD12 = 0x00081000,
	PD13 = 0x00082000,
	PD14 = 0x00084000,
	PD15 = 0x00088000,
	
	PE0  = 0x00100001,
	PE1  = 0x00100002,
	PE2  = 0x00100004,
	PE3  = 0x00100008,
	PE4  = 0x00100010,
	PE5  = 0x00100020,
	PE6  = 0x00100040,
	PE7  = 0x00100080,
	PE8  = 0x00100100,
	PE9  = 0x00100200,
	PE10 = 0x00100400,
	PE11 = 0x00100800,
	PE12 = 0x00101000,
	PE13 = 0x00102000,
	PE14 = 0x00104000,
	PE15 = 0x00108000,
	
	PF0  = 0x00200001,
	PF1  = 0x00200002,
	PF2  = 0x00200004,
	PF3  = 0x00200008,
	PF4  = 0x00200010,
	PF5  = 0x00200020,
	PF6  = 0x00200040,
	PF7  = 0x00200080,
	PF8  = 0x00200100,
	PF9  = 0x00200200,
	PF10 = 0x00200400,
	PF11 = 0x00200800,
	PF12 = 0x00201000,
	PF13 = 0x00202000,
	PF14 = 0x00204000,
	PF15 = 0x00208000,
	
	PG0  = 0x00400001,
	PG1  = 0x00400002,
	PG2  = 0x00400004,
	PG3  = 0x00400008,
	PG4  = 0x00400010,
	PG5  = 0x00400020,
	PG6  = 0x00400040,
	PG7  = 0x00400080,
	PG8  = 0x00400100,
	PG9  = 0x00400200,
	PG10 = 0x00400400,
	PG11 = 0x00400800,
	PG12 = 0x00401000,
	PG13 = 0x00402000,
	PG14 = 0x00404000,
	PG15 = 0x00408000
}GPIO_MEMBER;

typedef enum
{
	TIM_Null = 0x0000,
	
	TIM1_1 = 0x0101,
	TIM1_2 = 0x0102,
	TIM1_3 = 0x0104,
	TIM1_4 = 0x0108,
         
	TIM2_1 = 0x0201,
	TIM2_2 = 0x0202,
	TIM2_3 = 0x0204,
	TIM2_4 = 0x0208,
	       
	TIM3_1 = 0x0401,
	TIM3_2 = 0x0402,
	TIM3_3 = 0x0404,
	TIM3_4 = 0x0408,
	       
	TIM4_1 = 0x0801,
	TIM4_2 = 0x0802,
	TIM4_3 = 0x0804,
	TIM4_4 = 0x0808,
	       
	TIM5_1 = 0x1001,
	TIM5_2 = 0x1002,
	TIM5_3 = 0x1004,
	TIM5_4 = 0x1008,
	       
	TIM8_1 = 0x2001,
	TIM8_2 = 0x2002,
	TIM8_3 = 0x2004,
	TIM8_4 = 0x2008
	               
}TIM_MEMBER; 

typedef enum
{
	CHANNEL1 = 1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4
}TIM_CHANNEL;

typedef u8 DEVICE_ID;
typedef u8 DEVICE_NUM;
#define HAVE_PERCENT
typedef u8 PERCENT;
typedef struct
{
	GPIO_TypeDef* GPIOx;
	u16 GPIO_Pin;
}GPIO_STRUCT;			//GPIO接口结构体

typedef struct
{
	TIM_TypeDef* TIMx;
	TIM_CHANNEL channel;
}TIM_STRUCT;			//TIM结构体


extern void GPIO_Operating(GPIO_MEMBER IOPort,FlagStatus pinState);
extern GPIO_STRUCT GPIO_Convert(GPIO_MEMBER IO_PORT);
extern u8 pin2PinSource(u16 GPIO_Pin);
extern void toggle(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
extern void RCC_GPIO_Init(GPIO_TypeDef* GPIOx);
extern TIM_STRUCT TIM_Convert(TIM_MEMBER TIM_N);

#endif
