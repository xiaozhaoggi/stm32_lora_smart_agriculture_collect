/*
�ɼ���V1.0
					RS_XX.c/h   modbus �����ӻ����� ��������
					G_485.c/h   485оƬ����
					G_USART.c/h ���ڼ������ж�����
					gpio.c/h		����gpio����
					
					Ŀǰ������ʽ��loraģ���յ�����ѶϢ��modbus slave�� �ɼ�������д�������ѯһ��֮��modbus poll����
												��ͨ��loraģ�鷢�͸�����
						
*/
#include "gpio.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "RS_XX.h"
#include "G_485.h"
#include "string.h"
#include "stmflash.h"
/***************************************************************
Copyright  Information and electrical engineering of HUE All rights reserved.
�ļ���		: main.c
��

����	  	: �Ų���
�汾	   	: V1.0
����	   	: ������
����	   	: ��
��վ 	   	: ��
��־	   	: ����V1.0 2020/11/2�Ų��ȴ���
***************************************************************/

extern LORA_GET_BUFF get;
extern LORA_SEND_BUFF send;
extern u16 co2;                      //������̼����������  
extern u16 sd,wd,qy;                 //������ѹ����������  
extern u16 gzd; 										 //���մ��������ݱ���                
extern u16 soil_sf,soil_wd,soil_ddl; //�������������ݱ���
extern u16 ytmp1,ytmp2;										 //Ҷ������¶ȴ���������

extern u16 base_num;
extern u16 lora_id;

extern u8 get_sent_flag;       			 //���������������ݱ�־λ

 int main(void)
{	
	u16 * pbase_num = &base_num;
	u16 * plora_id = &lora_id;
	u8 times = 0;
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	gpio_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
	uart_init(9600);
	flash_init();
	
	while(1)
	{ 
		
		soil_wd = RS_SOIL_N01GetData(0x01);
				send.data[0] = RS_SOIL_Buff.data[0];
				send.data[1] = RS_SOIL_Buff.data[1];
		    //memset(RS_SOIL_Buff.data, 0, sizeof(u8)*2);
			
		soil_sf = RS_SOIL_N01GetData(0x00);
				send.data[2] = RS_SOIL_Buff.data[0];
		    send.data[3] = RS_SOIL_Buff.data[1];
		    //memset(RS_SOIL_Buff.data, 0, sizeof(u8)*2);
			
		soil_ddl = RS_SOIL_N01GetData(0x02);
				send.data[4] = RS_SOIL_Buff.data[0];
		    send.data[5] = RS_SOIL_Buff.data[1];
				//memset(RS_SOIL_Buff.data, 0, sizeof(u8)*2);
			
		wd = RS_QY_N01GetData(0x01F5);
				send.data[6] = RS_QY_Buff.data[0];
				send.data[7] = RS_QY_Buff.data[1];
		    //memset(RS_QY_Buff.data, 0, sizeof(u8)*2);
			
		sd =RS_QY_N01GetData(0x01F4);
				send.data[8] = RS_QY_Buff.data[0];
				send.data[9] = RS_QY_Buff.data[1];
        //memset(RS_QY_Buff.data, 0, sizeof(u8)*2);	
				
  	qy = RS_QY_N01GetData(0x01F9);
				send.data[10] = RS_QY_Buff.data[0];
				send.data[11] = RS_QY_Buff.data[1];		
				//memset(RS_QY_Buff.data, 0, sizeof(u8)*2);
				
		co2 = RS_CO2_N01GetData(0x02);
				send.data[12] = RS_CO2_Buff.data[0];
		    send.data[13] = RS_CO2_Buff.data[1];
				//memset(RS_CO2_Buff.data, 0, sizeof(u8)*2);	
				
    gzd = RS_GWS_N01GetData(0x03);
				send.data[14] = RS_GWS_Buff.data[0];
		    send.data[15] = RS_GWS_Buff.data[1];
				//memset(RS_GWS_Buff.data, 0, sizeof(u8)*2);
				
		do 
		{
			ytmp1 = RS_YTMP_N01GetData(0x00);
			times++;
		}
		while((ytmp1 == 0) && (times < 3));
		
		times = 0;
		send.data[16] = RS_YTMP_Buff.data[0];
		send.data[17] = RS_YTMP_Buff.data[1];
		send.data[18] = RS_YTMP_Buff.data[2];
		send.data[19] = RS_YTMP_Buff.data[3];	

		send.length = 20;

		
		//memset(RS_YTMP_Buff.data, 0, sizeof(u8)*4);				



		
	}	 

 
}



