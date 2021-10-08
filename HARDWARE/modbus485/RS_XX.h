#ifndef RS_XX_H_
#define RS_XX_H_
#include "G_485.h"
#include "delay.h"

#define  MULOR  0xA001       //CRC������ʽ


//�豸�ĵ�ַ
#define RS_GWS_ADDR  0x01  //���մ�����
#define RS_SOIL_ADDR  0x02 //���� �¶� ʪ�� �絼�ʴ�����
#define RS_CO2_ADDR 0x03  // ������̼������
#define RS_QY_ADDR  0x04 //  �����Ҷ��������
#define RS_YTMP_ADDR  0x06 //  Ҷ������¶ȴ�����

 

//RXϵ�� 485 ͨ�Ž��ջ�����
typedef struct
{
	u8  Addr; 		//��ַ��
#define READ_REGISTER_FUNC_CODE 0x03 //��ֻ�õ��˹�����0x03
	u8  length;		//��Ч�ֽ���
	u8  data[4];//������
	u16 crc_check;//crcУ��
	u8  flag;     //��ʾ���ݰ��Ƿ����
}RS_XX_BUFF;



// Lora ���ջ�����
typedef struct
{
//#define  ADDR  0x01	;	//���ɼ���ڵ��ַ
#define  FUNC  0x03  ; //��ȡ�Ĵ����Ĺ�����  ��ѯ������
	u8  reg_start;	  //����ָ���Ĵ�����ȡ 	
	u8  reg_end;      //ĿǰΪȫ����ѯ ��δ�õ�
	u8  regl_start;   //δ�õ�
	u8  regl_end;     //δ�õ�
	u16 crc_check;//crcУ��
	u8  flag;     //��ʾ���ݰ��Ƿ����
}LORA_GET_BUFF;

// Lora ���ͻ�����
typedef struct
{
//#define NODE_ADDR  0x01		//���ɼ���ڵ��ַ
#define FUNC 0x03 //��ȡ�Ĵ����Ĺ�����  ��ѯ������
//#define BASE_NUM  0x00
	u8  length;		//��Ч�ֽ���
	u8  data[20];//������
	u16 crc_check;//crcУ��
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
static u16 RS_XX_GetData(RS_XX_BUFF * rs_xx_buff);//��ѯ�豸����
static u16  CRC_Check(const u8 *buff,u16 length);
void RS_XX_Irq(void);
void lora_get(void);
void lora_send(void);

#endif
