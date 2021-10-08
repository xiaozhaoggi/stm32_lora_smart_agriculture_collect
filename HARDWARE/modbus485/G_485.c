#include "G_485.h"
#include "delay.h"

/***************************************************************
Copyright  Information and electrical engineering of HUE All rights reserved.
�ļ���		: G_485.c
����	  	: �Ų���
�汾	   	: V1.0
����	   	: 485��������
����	   	: ��
��վ 	   	: ��
��־	   	: ����V1.0 2019/11/2 �Ų��ȴ���
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
{ GPIO_SetBits(GPIOA,GPIO_Pin_1);	  //����ʱ max485 RE����	
	 delay_ms(1); 
		for(i=0;i<len;i++)
	{ 
		
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART2,pstr[i]);
	}
	delay_ms(1);
  GPIO_ResetBits(GPIOA,GPIO_Pin_1);	//����ʱ max485 RE����

}
}
