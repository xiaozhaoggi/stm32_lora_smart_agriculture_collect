//#include "G_Switch.h"
////��ſ���������Ľṹ������
//SWITCH_STRUCT cylinder[20] 			= {0};
//SWITCH_STRUCT optical[20] 			= {0};
//SWITCH_STRUCT infaredSwitch[20]	= {0};
//SWITCH_STRUCT limitSwitch[20]  	= {0};


////��Ÿ��ֿ��������������
//DEVICE_NUM cylinder_ID_Num 				= 0;
//DEVICE_NUM optical_ID_Num 					= 0;
//DEVICE_NUM infaredSwitch_ID_Num  = 0;
//DEVICE_NUM limitSwitch_ID_Num  	= 0;
//    
////�����������ʼ���ӿ�
//SWITCH_STRUCT Switch_Init(GPIO_MEMBER IO_Port,SWITCH_MODE mode,GPIOPuPd_TypeDef pupd)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_STRUCT gpio = GPIO_Convert(IO_Port);
//	if(IO_Port != Null)
//	{
//		RCC_GPIO_Init(gpio.GPIOx);
//		if(mode == OUTPUT)
//		{
//			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//			GPIO_InitStructure.GPIO_PuPd = pupd;
//			GPIO_InitStructure.GPIO_Pin = gpio.GPIO_Pin;
//		}
//		if(mode == INPUT)
//		{
//			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//			GPIO_InitStructure.GPIO_PuPd = pupd;
//			GPIO_InitStructure.GPIO_Pin = gpio.GPIO_Pin;
//		}	
//		GPIO_Init(gpio.GPIOx, &GPIO_InitStructure);
//	}
//	return gpio;
//}

////���׳�ʼ��
//void Cylinder_Init(GPIO_MEMBER IO_Port)
//{
//	cylinder[cylinder_ID_Num++] = Switch_Init(IO_Port,OUTPUT,GPIO_PuPd_UP);
//}

////���˳�ʼ��
//void Optical_Init(GPIO_MEMBER IO_Port)
//{
//	optical[optical_ID_Num++] = Switch_Init(IO_Port,INPUT,GPIO_PuPd_DOWN);
//}

////�����ʼ��   wozhushide
//void Infared_Switch_Init(GPIO_MEMBER IO_Port)
//{
//	infaredSwitch[infaredSwitch_ID_Num++] = Switch_Init(IO_Port,INPUT,GPIO_PuPd_UP);
//}

////��λ���س�ʼ��
//void Limit_Switch_Init(GPIO_MEMBER IO_Port)
//{
//	limitSwitch[limitSwitch_ID_Num++] = Switch_Init(IO_Port,INPUT,GPIO_PuPd_NOPULL);

//}

////���׿���
//void Cylinder(SWITCH_STATE State,DEVICE_ID ID)
//{
//	if(ID-1 < cylinder_ID_Num)
//	{
//		if(State == OFF)
//			GPIO_ResetBits(cylinder[ID-1].GPIOx,cylinder[ID-1].GPIO_Pin);
//		else
//			GPIO_SetBits(cylinder[ID-1].GPIOx,cylinder[ID-1].GPIO_Pin);
//	}
//}

////���˶�ȡ
//SWITCH_STATE Optical(DEVICE_ID ID)
//{
//	if(ID-1 < optical_ID_Num)
//	{
//		return (SWITCH_STATE)GPIO_ReadInputDataBit(optical[ID-1].GPIOx,optical[ID-1].GPIO_Pin);
//	}
//	return ON;
//}

////�����ȡ
//SWITCH_STATE InfaredSwitch(DEVICE_ID ID)
//{
//	if(ID-1 < infaredSwitch_ID_Num)
//	{
//		u8 dat = GPIO_ReadInputDataBit(infaredSwitch[ID-1].GPIOx,infaredSwitch[ID-1].GPIO_Pin);
//		if(dat != 0)
//			return OFF;
//		else 
//			return ON;
//	}
//	return OFF;
//}

////��λ���ض�ȡ
//SWITCH_STATE LimitSwitch(DEVICE_ID ID)
//{
//	if(ID-1 < limitSwitch_ID_Num)
//	{
//		u8 dat = GPIO_ReadInputDataBit(limitSwitch[ID-1].GPIOx,limitSwitch[ID-1].GPIO_Pin);
//		if(dat != 0)
//			return OFF;
//		else 
//			return ON;
//	}
//	return OFF;
//}








