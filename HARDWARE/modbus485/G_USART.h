#ifndef __G_USART_H
#define __G_USART_H
#include "stm32f10x.h"
#include "stdarg.h"
#include "G_base_config.h"
#include "stdio.h"
typedef struct
{
	GPIO_STRUCT Tx;
	GPIO_STRUCT Rx;
	GPIO_STRUCT Ck;
	USART_TypeDef *USARTx;
	u32 BaudRate;
}USART_STRUCT;

typedef enum 
{
	GPIO_AF_USART1_3 = 0x07,
	GPIO_AF_USART4_6 = 0x08,
}GPIO_AF_USART;

typedef enum
{
	WRITE = 0x00,
	READ	= 0x01
}CMD;

typedef struct 
{
	u8 ID;
	u8 length;
	CMD cmd;
	u8 data[255];
	s32 sum;
}BoChuang_Protocol;


extern u8 g_HaveUSARTConfigured[6];
extern u8 g_USART1_ReceivedBuf;




void uart_init(u32 bound);
void Usart_Init(GPIO_MEMBER Tx,GPIO_MEMBER Rx,u32 BaudRate,USART_TypeDef *USARTx);
void USART_printf(USART_TypeDef *USARTx,const char *Data,...);
void protocolSend_BoChuang(USART_TypeDef *USARTx,BoChuang_Protocol* protocol);
void USART_PrintfInit(USART_TypeDef* USARTx);
#endif
