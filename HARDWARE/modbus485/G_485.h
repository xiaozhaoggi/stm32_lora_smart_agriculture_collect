#ifndef _G_485_H
#define _G_485_H
#include "G_base_config.h"
#include "G_USART.h"
#include "G_Switch.h"
void USART_485_Init(GPIO_MEMBER Tx,GPIO_MEMBER Rx,u32 BaudRate,USART_TypeDef *USARTx,GPIO_MEMBER RE);
void USART_485_SendBytes(const u8 * pstr,u16 len ,u8 UARTx);
void USART_485_SendStatus(void);
void USART_485_ReceiveStatus(void);
#endif
