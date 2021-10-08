//#include "G_EC20.h"

////波特率EC20 115200
//#define EC20_BaudRate 115200
//USART_TypeDef *EC20_USARTx;
//char Ec20RxBuffer[EC20BufMaxSize];
//int  Ec20Rxcounter = 0; 
//char *strx = NULL;
//char *extstrx = NULL;
//void EC20_Init(GPIO_MEMBER Tx,GPIO_MEMBER Rx,USART_TypeDef *USARTx)
//{
//	delay_init(168);
//	delay_s(20);//延时20s等待EC20初始化完成
//	
//	USART_Config(Tx,Rx,EC20_BaudRate,USARTx);
//	NVIC_USART_Configuration(USART2,0,1);
//	EC20_USARTx = USARTx;

//	while(EC20_AT_Command("AT","OK",300)!=AT_ACK) {}
//	EC20_AT_Command("ATE0",NULL,300);
//	EC20_AT_Command("AT+CSQ",NULL,300);//检查CSQ
//	EC20_AT_Command("ATI",NULL,300);//检查模块的版本号
//	while(EC20_AT_Command("AT+CPIN?","+CPIN: READY",300)!=AT_ACK){}
//		
//	Clear_Buffer();	
//	strx = extstrx = NULL;
// while(strx==NULL&&extstrx==NULL)
//	{
//			Clear_Buffer();
//			EC20_AT_Command("AT+CREG?",0,500);//查看是否注册GSM网络
//			strx=strstr((const char*)Ec20RxBuffer,(const char*)"+CREG: 0,1");//返回正常
//			extstrx=strstr((const char*)Ec20RxBuffer,(const char*)"+CREG: 0,5");//返回正常，漫游
//	}
//	Clear_Buffer();
//	/////////////////////////////////////
//	strx = extstrx = NULL;
//	while(strx==NULL&&extstrx==NULL)
//		{
//				Clear_Buffer();
//				EC20_AT_Command("AT+CGREG?",0,500);//查看是否注册GPRS网络
//				strx=strstr((const char*)Ec20RxBuffer,(const char*)"+CGREG: 0,1");//，这里重要，只有注册成功，才可以进行GPRS数据传输。
//				extstrx=strstr((const char*)Ec20RxBuffer,(const char*)"+CGREG: 0,5");//返回正常，漫游
//		}
//		EC20_AT_Command("AT+COPS?",NULL,500);
//}


//void ConnectTCP(const char *addr)
//{
//		Clear_Buffer();
//    EC20_AT_Command("AT+QICLOSE=0",NULL,500);//关闭socket连接
//    delay_ms(500);
//    strx=strstr((const char*)Ec20RxBuffer,(const char*)"OK");//开启成功
//		while(EC20_AT_Command("AT+QICSGP=1,1,\"CMNET\",\"\",\"\",0","OK",500)!=AT_ACK){}//接入APN，无用户名和密码
//		while(EC20_AT_Command("AT+QIDEACT=1","OK",500)!=AT_ACK){}//去激活
//		while(EC20_AT_Command("AT+QIACT=1","OK",500)!=AT_ACK){}//激活
//    EC20_AT_Command("AT+QIACT?",NULL,500);//获取当前卡的IP地址
//		while(EC20_AT_Command("AT+QIOPEN=1,0,\"TCP\",\"39.105.23.243\",6002,0,1","+QIOPEN: 0,0",400)!=AT_ACK){}
//		//这里是需要登陆的IP号码，采用直接吐出模式
//    delay_ms(500);
//    Clear_Buffer();
//}

//void ConnectUDP(const char *addr)
//{
//		Clear_Buffer();
//    EC20_AT_Command("AT+QICLOSE=0",NULL,500);//关闭socket连接
//    delay_ms(500);
//    strx=strstr((const char*)Ec20RxBuffer,(const char*)"OK");//开启成功
//		while(EC20_AT_Command("AT+QICSGP=1,1,\"CMNET\",\"\",\"\",0","OK",500)!=AT_ACK){}//接入APN，无用户名和密码
//		while(EC20_AT_Command("AT+QIDEACT=1","OK",500)!=AT_ACK){}//去激活
//		while(EC20_AT_Command("AT+QIACT=1","OK",500)!=AT_ACK){}//激活
//    EC20_AT_Command("AT+QIACT?",NULL,500);//获取当前卡的IP地址
//		while(EC20_AT_Command("AT+QIOPEN=1,0,\"UDP\",\"39.105.23.243\",6002,0,1","+QIOPEN: 0,0",400)!=AT_ACK){}
//		//这里是需要登陆的IP号码，采用直接吐出模式
//    delay_ms(500);
//    Clear_Buffer();
//}



//void Clear_Buffer(void)//清空缓存
//{
//	int i;
//	for(i=0;i<EC20BufMaxSize;i++)
//	Ec20RxBuffer[i]=0;//缓存
//	Ec20Rxcounter=0;
//	strx = NULL;
//}


///*******************************************************************************
//* 函数名 : Find
//* 描述   : 判断缓存中是否含有指定的字符串
//* 返回   : unsigned char:1 找到指定字符，0 未找到指定字符 
//*******************************************************************************/

//u8 findStr(const char *a)
//{
//  if(strstr(Ec20RxBuffer,a)!=NULL)
//	    return 1;
//	else
//			return 0;
//}


///*
//*EC20发送
//*/
//void EC20_UsartSend(const char *Data)
//{
//	USART_printf(EC20_USARTx,Data);
//}

//void EC20_UsartSendByte(u8 data)
//{
//	USART_SendByte(data,EC20_USARTx);
//}

///*
//*EC20发送
//*/
//void EC20_UsartSendByLen(const char *Data,u16 len)
//{
//  u16 i=0;
//	for(i=0;i<len;i++)
//		USART_SendByte(Data[i],EC20_USARTx);
//}

////sendBuf：命令字符串，resone期望接到的应答，waitTime等待时间
//AT_ACK_STATUS EC20_AT_Command(const char *sendBuf,const char *resone,u16 waitTime)
//{
//	AT_ACK_STATUS err = AT_ACK;
//	Clear_Buffer();
//	EC20_UsartSend(sendBuf);
//	USART_SendByte('\r',EC20_USARTx);
//	USART_SendByte('\n',EC20_USARTx);
//	delay_ms(waitTime);
//	if(resone == NULL)
//	{
//		return AT_ACK;
//	}
//	if(findStr(resone)==NULL)
//	{
//		err = AT_ACK_TIMEOUT;
//	}
//	if(findStr("ERROR"))
//	{
//		err = AT_ACK_ERROR;
//	}
//	return err;
//}

////sendBuf：命令字符串，resone期望接到的应答，waitTime等待时间
//AT_ACK_STATUS EC20_aaa()
//{
//	return AT_ACK;
//}

/////发送字符型数据
//void EC20Send_StrData(char *bufferdata)
//{
//	
//	strx = NULL;
//	EC20_AT_Command("AT+QISEND=0",NULL,30);
//	strx=strstr((char*)Ec20RxBuffer,(char*)">");//是否正确发送
//	if(strx==NULL)//没有正确发送，请求重连
//	{
//		ConnectTCP(NULL);
//		EC20_AT_Command("AT+QISEND=0",NULL,30);
//	}
//	EC20_UsartSend(bufferdata);
//  delay_ms(100);	
//  USART_SendByte(0x1a,EC20_USARTx);//发送完成函数
//	delay_ms(100);
//  strx=NULL;
//  while(strx==NULL)
//  {
//			delay_ms(100);
//      strx=strstr((char*)Ec20RxBuffer,(char*)"SEND OK");//是否正确发送  
//  }
//  Clear_Buffer();
//}




////USARTx_IRQHandler(void)
//void EC20_USART_Irq(void)
//{
//	u8 Res;
//	if(USART_GetITStatus(EC20_USARTx, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//		USART_ClearITPendingBit(EC20_USARTx,USART_IT_RXNE);
//		Res =USART_ReceiveData(EC20_USARTx);//(USART1->DR);	//读取接收到的数据
//		Ec20RxBuffer[Ec20Rxcounter++]=Res;//
//		if(Ec20Rxcounter>=500)
//			Ec20Rxcounter=0;
//		//
//  } 
//}

///*
// *  @brief 返回USART2已接收的数据到buf，长度为rcv_len
// */
//void  EC20_GetRcvData(uint8_t *buf, uint32_t rcv_len)
//{
//	u8 len;
//	char *p;
//	len=Ec20Rxcounter;
//	p=Ec20RxBuffer;
//    if(buf)
//    {
//        memcpy(buf, p, len);//直接复制数据到数据里面去
//    }
//}
