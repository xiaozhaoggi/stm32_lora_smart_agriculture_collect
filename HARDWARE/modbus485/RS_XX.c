#include "RS_XX.h"

/***************************************************************
Copyright  Information and electrical engineering of HUE All rights reserved.
文件名		: RS_XX.c
作者	  	: 张博钊
版本	   	: V1.0
描述	   	: 设备采集及数据处理、中断
其他	   	: 无
网站 	   	: 无
日志	   	: 初版V1.0 2019/11/2 张博钊创建
***************************************************************/

//RS485端口初始化
//串口Tx,Rx,串口波特率,串口号,485控制端口
RS_XX_BUFF RS_CO2_Buff;                                       
RS_XX_BUFF RS_QY_Buff;                                        
RS_XX_BUFF RS_GWS_Buff;                
RS_XX_BUFF RS_SOIL_Buff;
RS_XX_BUFF RS_YTMP_Buff;
u8 readAddrNow;//当前读取的设备地址码
u8 checkCrcBuff[260];
u16 co2;                         // 二氧化碳传感器  
u16 sd,wd,qy;                   //  气象百叶窗传感器
u16 gzd;                 				//光照传感器
u16 soil_sf,soil_wd,soil_ddl; //土壤传感器
u16 ytmp1,ytmp2; 										//叶面红外传感器
LORA_SEND_BUFF send;
LORA_GET_BUFF get;
u8 get_sent_flag;       //接收网关请求数据标志位
u8 set_mode = 0;			//配置模式

extern u16 base_num;
extern u16 lora_id;

/*
*主机问询帧发送
*/
//addr:设备地址码 regAddr寄存器地址
////////////////////////////////////////////* modbus poll*////////////////////////////////////////////
	
void RS_XX_Send(u8 addr,u8 func,u16 regAddr,u16 length)  // Uart 2 
{
	u16 crc;
	u8 buf[8] ;
	buf[0] = addr;
	buf[1] = func;
	buf[2] = regAddr>>8;
	buf[3] = regAddr&0xff;
	buf[4] = length>>8;
	buf[5] = length&0xff;
	crc    = CRC_Check(buf,6);
	buf[6] = crc>>8;
	buf[7] = crc&0xff;
	USART_485_SendBytes(buf,8,2);
//	memset(buf, 0, sizeof(u8)*8);
}

//获取大气气压数据的问询帧
void RS_QY_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_QY_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//大气气压变送器获取气压
u16 RS_QY_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_QY_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_QY_Buff);
	delay_ms(200);
	return ret;
}



//获取二氧化碳数据的问询帧
void RS_CO2_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_CO2_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//二氧化碳送变器获取二氧化碳浓度
u16 RS_CO2_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_CO2_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_CO2_Buff);
	delay_ms(200);
	return ret;
}

//获取光照数据问询帧
void RS_GWS_M_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_GWS_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//光照传感器获取光照数据
u16 RS_GWS_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_GWS_M_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_GWS_Buff);
	delay_ms(200);
	return ret;
}

//获取土壤数据的问询帧
void RS_SOIL_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_SOIL_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//土壤传感器获取温度 水分 电导率
u16 RS_SOIL_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_SOIL_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_SOIL_Buff);
	
	delay_ms(200);
	return ret;
}

//获取叶面温度的闻讯帧
void RS_YTMP_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_YTMP_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0002);
}

//红外测温传感器获取叶面温度
u16 RS_YTMP_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_YTMP_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_YTMP_Buff);
	
	delay_ms(200);
	return ret;
}

//从机返回数据中读取数据位
u16 RS_XX_GetData(RS_XX_BUFF * rs_xx_buff)
{
	u16 result = 0;
	if(rs_xx_buff->flag)
	{
		rs_xx_buff->flag = 0;
		result = rs_xx_buff->data[0];
		result = (result<<8)|rs_xx_buff->data[1];
	}
	return result;
}
//传感器接收中断函数
void RS_XX_Irq()
{
	static u8  					receiveIndex= 0;
	static u8  					dataCount   = 0;
	static u8  					datalength  = 0;//有效字节数
	static u16 					hight8_crc  = 0;//crc校验高8位
	static RS_XX_BUFF * pRS_XX_Buff = 0;
	u8 Res;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //
	{
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		Res =USART_ReceiveData(USART2);//(USART_RS_XX->DR);	//读取接收到的数据
		//USART_SendByte(Res,USART1);
//		if(Res == 0xaa && receiveIndex == 0)
//			set_mode = 1;
//		if(set_mode == 1)
//		flash_485_write(Res);
		
//		if(set_mode == 0)
//		{
		switch(receiveIndex)
		{
			case 0://地址码
				switch(Res)
				{
					case RS_QY_ADDR:
						pRS_XX_Buff = &RS_QY_Buff;//获取对应的缓冲区地址
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
						break;
					case RS_CO2_ADDR:
						pRS_XX_Buff = &RS_CO2_Buff;//获取对应的缓冲区地址
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
						break;
					case RS_GWS_ADDR:
						pRS_XX_Buff = &RS_GWS_Buff;//获取对应的缓冲区地址
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
						break;
					case RS_SOIL_ADDR:
						pRS_XX_Buff = &RS_SOIL_Buff;//获取对应的缓冲区地址
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
					  break;
					case RS_YTMP_ADDR:
						pRS_XX_Buff = &RS_YTMP_Buff ;//获取对应的缓冲区地址
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
					  break;					
					default:
						receiveIndex= 0;
						dataCount   = 0;
						datalength  = 0;
						hight8_crc  = 0;
						pRS_XX_Buff = 0;
						break;
				}
				break;
			 case 1://功能码
				 if(Res == READ_REGISTER_FUNC_CODE)
				 {
					 pRS_XX_Buff->Addr = readAddrNow;
					 checkCrcBuff[0]   = readAddrNow;
					 checkCrcBuff[1]   = Res;
					 receiveIndex++;
				 }else
				 {
					 receiveIndex= 0;
					 dataCount   = 0;
					 datalength  = 0;
					 hight8_crc  = 0;
					 pRS_XX_Buff = 0;	 
				 }
					break;
			 case 2://有效字节数
				 datalength = Res;
			   pRS_XX_Buff->length = datalength;
			   checkCrcBuff[2] = datalength;
				 receiveIndex++;
				 if(datalength == 0)//如果数据长度为0则跳过接收有效字节
				 {
					 receiveIndex++;
				 }
				 break;
			 case 3:
				 if(dataCount<datalength)//接收有效返回字节
				 {
					 checkCrcBuff[dataCount+3] = Res;
					 pRS_XX_Buff->data[dataCount++] = Res;
				 }
				 if(dataCount == datalength)
				 {
					 receiveIndex++;
				 }
				 break;
			 case 4:
				  hight8_crc = Res;
					checkCrcBuff[3+datalength] = Res;
			    receiveIndex++;
				 break;
			 case 5:
				  pRS_XX_Buff->crc_check = (hight8_crc<<8) | Res;
			    checkCrcBuff[4+datalength] = Res;
			 
			    if(pRS_XX_Buff->crc_check == CRC_Check(checkCrcBuff,datalength+3))
					{
						pRS_XX_Buff->flag = 1;

					}
						receiveIndex= 0;
						dataCount   = 0;
						datalength  = 0;
						hight8_crc  = 0;
						pRS_XX_Buff = 0;	 
				 break;
			 default:
				 break;
		}
//	}
	
}
		
	
	
}   









////////////////////////////////////////////* modbus slave*////////////////////////////////////////////
//lora接收中断函数
void lora_get(void)
{
	static u8  					receiveIndex= 0;
	static u8  					reg_start  = 0;//
	static u8  					reg_end   = 0;
  static u8    	      regl_start = 0;
	static u8    	      regl_end  = 0;
	static u16 					hight8_crc  = 0;//crc校验高8位
	static LORA_GET_BUFF * pget = 0;
	u8 Res;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //
	{
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);//(USART_RS_XX->DR);	//读取接收到的数据
		//USART_SendByte(Res,USART1);
		if(Res == 0xaa && receiveIndex == 0)
			set_mode = 1;
		if(set_mode == 1)
			flash_485_write(Res);
		
		if(set_mode == 0)
		{
		switch(receiveIndex)
		{
			case 0://地址码
					 if(Res == lora_id)
					 {
						pget = &get;//获取对应的缓冲区地址
						readAddrNow = Res;
						receiveIndex++;
					 }else
						{
						receiveIndex= 0;
						reg_end   = 0;
				  	reg_start = 0;
					  regl_start = 0;
					  regl_end   = 0;
						hight8_crc = 0;
						pget = 0;
						}
					break;
			 case 1://功能码
				 if(Res == 0x03)
				 {
					 checkCrcBuff[0]   = lora_id;
					 checkCrcBuff[1]   = Res;
					 receiveIndex++;
				 }else
				 {
						receiveIndex= 0;
						reg_end   = 0;
				  	reg_start = 0;
					  regl_start = 0;
					  regl_end   = 0;
						hight8_crc = 0;
						pget = 0;
				 }
					break;
			 case 2://reg_start
				 reg_start = Res;
			   pget->reg_start = reg_start;
			   checkCrcBuff[2] = reg_start;
				 receiveIndex++;
				 break;
			 case 3: //reg_end
				 reg_end = Res;
			   pget->reg_end = reg_end;
			   checkCrcBuff[3] = reg_end;
				 receiveIndex++;
				 break;
			 case 4: //regl_start
				 regl_start = Res;
			   pget->regl_start = regl_start;
			   checkCrcBuff[4] = regl_start;
				 receiveIndex++;
				 break;
			 case 5: // regl_end
				 regl_end = Res;
			   pget->regl_end = regl_end;
			   checkCrcBuff[5] = regl_end;
				 receiveIndex++;
				 break;
			 case 6: // crc高八位获取
				 	hight8_crc = Res;
			    receiveIndex++;
			   break;
			 case 7: //crc判断
				 	pget->crc_check = (hight8_crc<<8) | Res;
			 
			    if(pget->crc_check == CRC_Check(checkCrcBuff,6))
					{
						pget->flag = 1;
						//get_sent_flag = 1;    //如果校验成功，发送标志位置1
						lora_send();
						//get_sent_flag = 0 ;
					}
						receiveIndex= 0;
						reg_end   = 0;
				  	reg_start = 0;
					  regl_start = 0;
					  regl_end   = 0;
						hight8_crc = 0;
						pget = 0;
			 default:
				 break;
			}

		}
	}
}



//lora发送数据函数   Uart 1 
 u8 buf1[100]={0};
void lora_send(void)
{
	 LORA_SEND_BUFF * psend ;
	 u8 dataCount=0;
   u16 crc;
	 psend=&send;  
	buf1[0] = lora_id;  //本采集板地址
	buf1[1] = 0x03;				//功能码
	buf1[2] = psend->length; //数据长度
//	buf1[3] = base_num; //
    	 while(dataCount<psend->length)//接收有效返回字节
				 {  
 				 	 buf1[3+dataCount] = psend->data[dataCount];
					 dataCount++;
				 }
	crc    = CRC_Check(buf1,3+psend->length);
	buf1[3+psend->length] = crc>>8;
	buf1[4+psend->length] = crc&0xff;
	USART_485_SendBytes(buf1,5+psend->length,1); 


}

//CRC校验计算
u16 CRC_Check(const u8 *buff,u16 length)
{
	u16 n;
	u16 tmp=0xffff;
	u16 ret;
	u8 i;
	for(n = 0; n < length; n++)
	{
        tmp = buff[n] ^ tmp;
        for(i = 0;i < 8;i++)
				{
            if(tmp & 0x01){
                tmp = tmp >> 1;
                tmp = tmp ^ MULOR;
            }   
            else{
                tmp = tmp >> 1;
            }   
        }   
    }   
    ret = tmp >> 8;
    ret = ret | (tmp << 8);
		return ret;
}
