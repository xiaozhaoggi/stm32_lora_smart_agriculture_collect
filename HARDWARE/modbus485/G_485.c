#include "G_485.h"
#include "delay.h"

/***************************************************************
Copyright  Information and electrical engineering of HUE All rights reserved.
文件名		: G_485.c
作者	  	: 张博钊
版本	   	: V1.0
描述	   	: 485发送数据
其他	   	: 无
网站 	   	: 无
日志	   	: 初版V1.0 2019/11/2 张博钊创建
***************************************************************/

void USART_485_SendBytes(const u8 * pstr,u16 len ,u8 UARTx)
{
	int i=0;

	if(UARTx == 1)
 {
	for(i=0;i<len;i++)
	{ while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART1,pstr[i]);
	}
 }
  if(UARTx == 2)	
{ GPIO_SetBits(GPIOA,GPIO_Pin_1);	  //发送时 max485 RE拉高	
	 delay_ms(1); 
		for(i=0;i<len;i++)
	{ 
		
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART2,pstr[i]);
	}
	delay_ms(1);
  GPIO_ResetBits(GPIOA,GPIO_Pin_1);	//接收时 max485 RE拉低

}
}
