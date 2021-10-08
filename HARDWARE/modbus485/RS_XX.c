#include "RS_XX.h"

/***************************************************************
Copyright  Information and electrical engineering of HUE All rights reserved.
�ļ���		: RS_XX.c
����	  	: �Ų���
�汾	   	: V1.0
����	   	: �豸�ɼ������ݴ����ж�
����	   	: ��
��վ 	   	: ��
��־	   	: ����V1.0 2019/11/2 �Ų��ȴ���
***************************************************************/

//RS485�˿ڳ�ʼ��
//����Tx,Rx,���ڲ�����,���ں�,485���ƶ˿�
RS_XX_BUFF RS_CO2_Buff;                                       
RS_XX_BUFF RS_QY_Buff;                                        
RS_XX_BUFF RS_GWS_Buff;                
RS_XX_BUFF RS_SOIL_Buff;
RS_XX_BUFF RS_YTMP_Buff;
u8 readAddrNow;//��ǰ��ȡ���豸��ַ��
u8 checkCrcBuff[260];
u16 co2;                         // ������̼������  
u16 sd,wd,qy;                   //  �����Ҷ��������
u16 gzd;                 				//���մ�����
u16 soil_sf,soil_wd,soil_ddl; //����������
u16 ytmp1,ytmp2; 										//Ҷ����⴫����
LORA_SEND_BUFF send;
LORA_GET_BUFF get;
u8 get_sent_flag;       //���������������ݱ�־λ
u8 set_mode = 0;			//����ģʽ

extern u16 base_num;
extern u16 lora_id;

/*
*������ѯ֡����
*/
//addr:�豸��ַ�� regAddr�Ĵ�����ַ
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

//��ȡ������ѹ���ݵ���ѯ֡
void RS_QY_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_QY_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//������ѹ��������ȡ��ѹ
u16 RS_QY_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_QY_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_QY_Buff);
	delay_ms(200);
	return ret;
}



//��ȡ������̼���ݵ���ѯ֡
void RS_CO2_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_CO2_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//������̼�ͱ�����ȡ������̼Ũ��
u16 RS_CO2_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_CO2_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_CO2_Buff);
	delay_ms(200);
	return ret;
}

//��ȡ����������ѯ֡
void RS_GWS_M_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_GWS_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//���մ�������ȡ��������
u16 RS_GWS_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_GWS_M_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_GWS_Buff);
	delay_ms(200);
	return ret;
}

//��ȡ�������ݵ���ѯ֡
void RS_SOIL_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_SOIL_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0001);
}

//������������ȡ�¶� ˮ�� �絼��
u16 RS_SOIL_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_SOIL_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_SOIL_Buff);
	
	delay_ms(200);
	return ret;
}

//��ȡҶ���¶ȵ���Ѷ֡
void RS_YTMP_N01_SendGet(u16 regAddr)
{
	RS_XX_Send(RS_YTMP_ADDR,READ_REGISTER_FUNC_CODE,regAddr,0x0002);
}

//������´�������ȡҶ���¶�
u16 RS_YTMP_N01GetData(u16 regAddr)
{
	u16 ret;
	RS_YTMP_N01_SendGet(regAddr);
	delay_ms(200);
	ret = RS_XX_GetData(&RS_YTMP_Buff);
	
	delay_ms(200);
	return ret;
}

//�ӻ����������ж�ȡ����λ
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
//�����������жϺ���
void RS_XX_Irq()
{
	static u8  					receiveIndex= 0;
	static u8  					dataCount   = 0;
	static u8  					datalength  = 0;//��Ч�ֽ���
	static u16 					hight8_crc  = 0;//crcУ���8λ
	static RS_XX_BUFF * pRS_XX_Buff = 0;
	u8 Res;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //
	{
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		Res =USART_ReceiveData(USART2);//(USART_RS_XX->DR);	//��ȡ���յ�������
		//USART_SendByte(Res,USART1);
//		if(Res == 0xaa && receiveIndex == 0)
//			set_mode = 1;
//		if(set_mode == 1)
//		flash_485_write(Res);
		
//		if(set_mode == 0)
//		{
		switch(receiveIndex)
		{
			case 0://��ַ��
				switch(Res)
				{
					case RS_QY_ADDR:
						pRS_XX_Buff = &RS_QY_Buff;//��ȡ��Ӧ�Ļ�������ַ
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
						break;
					case RS_CO2_ADDR:
						pRS_XX_Buff = &RS_CO2_Buff;//��ȡ��Ӧ�Ļ�������ַ
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
						break;
					case RS_GWS_ADDR:
						pRS_XX_Buff = &RS_GWS_Buff;//��ȡ��Ӧ�Ļ�������ַ
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
						break;
					case RS_SOIL_ADDR:
						pRS_XX_Buff = &RS_SOIL_Buff;//��ȡ��Ӧ�Ļ�������ַ
						readAddrNow = Res;
						receiveIndex++;
					  pRS_XX_Buff->Addr = Res;
					  break;
					case RS_YTMP_ADDR:
						pRS_XX_Buff = &RS_YTMP_Buff ;//��ȡ��Ӧ�Ļ�������ַ
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
			 case 1://������
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
			 case 2://��Ч�ֽ���
				 datalength = Res;
			   pRS_XX_Buff->length = datalength;
			   checkCrcBuff[2] = datalength;
				 receiveIndex++;
				 if(datalength == 0)//������ݳ���Ϊ0������������Ч�ֽ�
				 {
					 receiveIndex++;
				 }
				 break;
			 case 3:
				 if(dataCount<datalength)//������Ч�����ֽ�
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
//lora�����жϺ���
void lora_get(void)
{
	static u8  					receiveIndex= 0;
	static u8  					reg_start  = 0;//
	static u8  					reg_end   = 0;
  static u8    	      regl_start = 0;
	static u8    	      regl_end  = 0;
	static u16 					hight8_crc  = 0;//crcУ���8λ
	static LORA_GET_BUFF * pget = 0;
	u8 Res;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //
	{
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);//(USART_RS_XX->DR);	//��ȡ���յ�������
		//USART_SendByte(Res,USART1);
		if(Res == 0xaa && receiveIndex == 0)
			set_mode = 1;
		if(set_mode == 1)
			flash_485_write(Res);
		
		if(set_mode == 0)
		{
		switch(receiveIndex)
		{
			case 0://��ַ��
					 if(Res == lora_id)
					 {
						pget = &get;//��ȡ��Ӧ�Ļ�������ַ
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
			 case 1://������
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
			 case 6: // crc�߰�λ��ȡ
				 	hight8_crc = Res;
			    receiveIndex++;
			   break;
			 case 7: //crc�ж�
				 	pget->crc_check = (hight8_crc<<8) | Res;
			 
			    if(pget->crc_check == CRC_Check(checkCrcBuff,6))
					{
						pget->flag = 1;
						//get_sent_flag = 1;    //���У��ɹ������ͱ�־λ��1
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



//lora�������ݺ���   Uart 1 
 u8 buf1[100]={0};
void lora_send(void)
{
	 LORA_SEND_BUFF * psend ;
	 u8 dataCount=0;
   u16 crc;
	 psend=&send;  
	buf1[0] = lora_id;  //���ɼ����ַ
	buf1[1] = 0x03;				//������
	buf1[2] = psend->length; //���ݳ���
//	buf1[3] = base_num; //
    	 while(dataCount<psend->length)//������Ч�����ֽ�
				 {  
 				 	 buf1[3+dataCount] = psend->data[dataCount];
					 dataCount++;
				 }
	crc    = CRC_Check(buf1,3+psend->length);
	buf1[3+psend->length] = crc>>8;
	buf1[4+psend->length] = crc&0xff;
	USART_485_SendBytes(buf1,5+psend->length,1); 


}

//CRCУ�����
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
