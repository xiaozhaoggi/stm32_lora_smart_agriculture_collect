/*
采集板V1.0
					RS_XX.c/h   modbus 主机从机配置 程序主体
					G_485.c/h   485芯片配置
					G_USART.c/h 串口及串口中断配置
					gpio.c/h		其他gpio配置
					
					目前工作方式：lora模块收到网关讯息后（modbus slave） 采集板把所有传感器轮询一遍之后（modbus poll），
												再通过lora模块发送给网关
						
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
文件名		: main.c
。

作者	  	: 张博钊
版本	   	: V1.0
描述	   	: 主函数
其他	   	: 无
网站 	   	: 无
日志	   	: 初版V1.0 2020/11/2张博钊创建
***************************************************************/

extern LORA_GET_BUFF get;
extern LORA_SEND_BUFF send;
extern u16 co2;                      //二氧化碳传感器变量  
extern u16 sd,wd,qy;                 //大气气压传感器变量  
extern u16 gzd; 										 //光照传感器数据变量                
extern u16 soil_sf,soil_wd,soil_ddl; //土壤传感器数据变量
extern u16 ytmp1,ytmp2;										 //叶面红外温度传感器变量

extern u16 base_num;
extern u16 lora_id;

extern u8 get_sent_flag;       			 //接收网关请求数据标志位

 int main(void)
{	
	u16 * pbase_num = &base_num;
	u16 * plora_id = &lora_id;
	u8 times = 0;
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	gpio_Init();		  	 //初始化与LED连接的硬件接口 
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



