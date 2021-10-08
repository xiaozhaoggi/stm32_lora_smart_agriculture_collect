#ifndef _EC20_H_
#define _EC20_H_
#include "G_base_config.h"
#include "G_USART.h"
#include "string.h"
#include "stdio.h"
#include "delay.h"

typedef enum{
	AT_ACK = 0,
	AT_ACK_ERROR = 1,
	AT_ACK_TIMEOUT = 2
}AT_ACK_STATUS;

#define EC20BufMaxSize 512


extern char Ec20RxBuffer[EC20BufMaxSize];
extern int  Ec20Rxcounter; 
extern USART_TypeDef *EC20_USARTx;

void EC20_Init(GPIO_MEMBER Tx,GPIO_MEMBER Rx,USART_TypeDef *USARTx);
void EC20_USART_Irq(void);
void EC20_UsartSend(const char *Data);
void EC20_UsartSendByLen(const char *Data,u16 len);
void Clear_Buffer(void);//��ջ���
///�����ַ�������
void EC20Send_StrData(char *bufferdata); 
void ConnectTCP(const char *addr);
void ConnectUDP(const char *addr);
//sendBuf�������ַ�����resone�����ӵ���Ӧ��waitTime�ȴ�ʱ��
extern AT_ACK_STATUS EC20_AT_Command(const char *sendBuf,const char *resone,u16 waitTime);
void  EC20_GetRcvData(uint8_t *buf, uint32_t rcv_len);
void EC20_UsartSendByte(u8 data);
#endif
