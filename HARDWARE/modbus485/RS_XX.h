#ifndef RS_XX_H_
#define RS_XX_H_
#include "G_485.h"
#include "delay.h"

#define  MULOR  0xA001       //CRC异或多项式


//设备的地址
#define RS_GWS_ADDR  0x01  //光照传感器
#define RS_SOIL_ADDR  0x02 //土壤 温度 湿度 电导率传感器
#define RS_CO2_ADDR 0x03  // 二氧化碳传感器
#define RS_QY_ADDR  0x04 //  气象百叶窗传感器
#define RS_YTMP_ADDR  0x06 //  叶面红外温度传感器

 

//RX系列 485 通信接收缓冲区
typedef struct
{
	u8  Addr; 		//地址码
#define READ_REGISTER_FUNC_CODE 0x03 //都只用到了功能码0x03
	u8  length;		//有效字节数
	u8  data[4];//数据区
	u16 crc_check;//crc校验
	u8  flag;     //表示数据包是否就绪
}RS_XX_BUFF;



// Lora 接收缓冲区
typedef struct
{
//#define  ADDR  0x01	;	//本采集板节点地址
#define  FUNC  0x03  ; //读取寄存器的功能码  查询功能码
	u8  reg_start;	  //用于指定寄存器读取 	
	u8  reg_end;      //目前为全部轮询 故未用到
	u8  regl_start;   //未用到
	u8  regl_end;     //未用到
	u16 crc_check;//crc校验
	u8  flag;     //表示数据包是否就绪
}LORA_GET_BUFF;

// Lora 发送缓冲区
typedef struct
{
//#define NODE_ADDR  0x01		//本采集板节点地址
#define FUNC 0x03 //读取寄存器的功能码  查询功能码
//#define BASE_NUM  0x00
	u8  length;		//有效字节数
	u8  data[20];//数据区
	u16 crc_check;//crc校验
}LORA_SEND_BUFF;



extern RS_XX_BUFF RS_CO2_Buff;                                       
extern RS_XX_BUFF RS_QY_Buff;                                        
extern RS_XX_BUFF RS_GWS_Buff;                
extern RS_XX_BUFF RS_SOIL_Buff;
extern RS_XX_BUFF RS_YTMP_Buff;


u16 RS_GWS_N01GetData(u16 regAddr);
u16 RS_QY_N01GetData(u16 regAddr);
u16 RS_CO2_N01GetData(u16 regAddr);
u16 RS_SOIL_N01GetData(u16 regAddr);
u16 RS_YTMP_N01GetData(u16 regAddr);


void RS_GWS_N01_SendGet(u16 regAddr);
void RS_QY_N01_SendGet(u16 regAddr);
void RS_CO2_N01_SendGet(u16 regAddr);
void RS_SOIL_N01_SendGet(u16 regAddr);
void RS_YTMP_N01_SendGet(u16 regAddr);



static void RS_XX_Send(u8 addr,u8 func,u16 regAddr,u16 length); 
static u16 RS_XX_GetData(RS_XX_BUFF * rs_xx_buff);//问询设备数据
static u16  CRC_Check(const u8 *buff,u16 length);
void RS_XX_Irq(void);
void lora_get(void);
void lora_send(void);

#endif
