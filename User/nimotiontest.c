/******************************************************************************
  *
  *   Copyright (C), 2022-2023, Beijing NiMotion Control Technology Co., Ltd.
  *
  *****************************************************************************
  *@file       : nimotiontest.c
  *@version    : Initial Draft
  *@author     : liuping
  *@date       : 2022/8/16
  *@brief      :
  *****************************************************************************
  **function   :
  *History     :
  *@date       : 2022/8/16
  *@author     : liupinga
  *@note       : Created file

  ****************************************************************************/
#include "nimotiontest.h"
#include "delay.h"




/********************************************************
  * @brief      : NiM_Position_Mode
  * @details    : �Ե��λ��ģʽ�µĻ�����������������溯����
  * @param [in] : nAddr��  	 �����ַNode-ID   ȡֵ��Χ�� 1~127 
  * @param [out]: 
  * @retval     : 100 �ɹ���������ʾ����
	
  * History
  * @date       : 2020/12/01
  *	@author     : Nimotion
********************************************************/

uint8_t NiM_Position_Mode(uint8_t nAddr)
{
	uint16_t temp1 = 0;
	uint8_t error =0;
	uint8_t temp2;
	int32_t tagpostion = 0;
//	uint16_t temprr = 0;
	error = NiM_isMotorOnline(nAddr,&temp1);
	if (error !=0)
	{
		return error;
	}
	temp2=0;
	error = NiM_writeParam(nAddr,0x0380,(uint8_t *)&temp2,2);//�ѻ�
	if (error !=0)
		{
			return error;
		}
	temp2=0;
	error = NiM_writeParam(nAddr,0x0402,(uint8_t *)&temp2,2);//����
		if (error !=0)
		{
			return error;
		}
	temp2=33;
	error = NiM_writeParam(nAddr,0x0326,(uint8_t *)&temp2,2);//�������ʹ��
		if (error !=0)
		{
			return error;
		}
	temp2=1;
	error = NiM_writeParam(nAddr,0x0373,(uint8_t *)&temp2,2);//ͨ�Ÿ���������ӵ�ƽ
	//if (error !=0)return error;
	if (error !=0)
		{
			return error;
		}
	temp2=0;
	error = NiM_writeParam(nAddr,0x0373,(uint8_t *)&temp2,2);//��ǰλ������
		if (error !=0)
		{
			return error;
		}
	if(temp1 == nAddr)//�������
		{

			NiM_powerOff(nAddr);                    //����ѻ�
			NiM_changeWorkMode(nAddr,POSITION_MODE);////����Ϊλ��ģʽ
			NiM_clearErrorState(nAddr);            //����״̬���
			NiM_powerOn(nAddr);                     //ʹ�ܵ��
//			tagpostion = 2500;      //���һȦ10000
//			NiM_moveRelative(nAddr,0,tagpostion);//�����ת1Ȧ,��������
//			delay_ms(1000);
//			tagpostion = -2500;
//			NiM_moveRelative(nAddr,1,tagpostion);//�����ת1Ȧ������������
//			delay_ms(10);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);

//			NiM_moveRelative(nAddr,1,tagpostion);//�����ת1Ȧ������������
//			delay_ms(10);	
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);
//		
//			NiM_moveRelative(nAddr,1,tagpostion);//�����ת1Ȧ������������
//			delay_ms(10);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);

//			NiM_moveRelative(nAddr,1,tagpostion);//�����ת1Ȧ������������
//			delay_ms(10);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);

//			NiM_moveRelative(nAddr,1,tagpostion);//�����ת1Ȧ������������
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);
//			tagpostion = 0;
			NiM_moveAbsolute(nAddr,0,tagpostion);//����ߵ�����λ��0����������

		}
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
		
		return 0;
}


/********************************************************
  * @brief      : NiM_Velocity_Mode
  * @details    : �Ե���ٶ�ģʽ�µĻ�����������������溯����
  * @param [in] : nAddr��  	 �����ַNode-ID   ȡֵ��Χ�� 1~127 
  * @param [out]: 
  * @retval     :110 �ɹ���������ʾ����
	
  * History
  * @date       : 2020/12/01
  *	@author     : Nimotion
********************************************************/

uint8_t NiM_Velocity_Mode(uint8_t nAddr)
{
	uint16_t temp = 0;
	uint8_t error =0;
	int32_t tagvelocity = 0;
	
	error = NiM_isMotorOnline(nAddr,&temp);//�жϵ���Ƿ�����
	if (error !=0)return error;
	if(temp == nAddr)//�������
		{

		
		  NiM_powerOff(nAddr);                    //����ѻ�
			NiM_changeWorkMode(nAddr,VELOCITY_MODE);////����Ϊ�ٶ�ģʽ
			NiM_clearErrorState(nAddr);            //����״̬���
			NiM_powerOn(nAddr);                     //ʹ�ܵ��
//			tagvelocity = 100000;//100000/10000*60=600rpm
//			NiM_moveVelocity(nAddr,tagvelocity);//�����600rpm��ת
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			tagvelocity = -100000;//-600rpm
//			NiM_moveVelocity(nAddr,tagvelocity);//�����600rpm��ת
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			tagvelocity = 200000;//1200rpm
//			NiM_moveVelocity(nAddr,tagvelocity);//�����1200rpm��ת

		}	
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1000);
//		delay_ms(1500);
//		
		return 0;
}
		

/********************************************************
  * @brief      : NiM_Torque_Mode
  * @details    : �Ե��ת��ģʽ�µĻ�����������������溯����
  * @param [in] : nAddr��  	 �����ַNode-ID   ȡֵ��Χ�� 1~127 
  * @param [out]: 
  * @retval     :120 �ɹ���������ʾ����
	
  * History
  * @date       : 2020/12/01
  *	@author     : Nimotion
********************************************************/
uint8_t NiM_Torque_Mode(uint8_t nAddr)
{
	uint16_t temp = 0;
	uint8_t error =0;
	int16_t tagtorque = 0;
	error = NiM_isMotorOnline(nAddr,&temp);//�жϵ���Ƿ�����
	if (error !=0)
	{
		return error;
	}
	if(temp == nAddr)//�������
		{
			//NiM_powerOff(nAddr);                    //����ѻ�
			NiM_changeWorkMode(nAddr,TORQUE_MODE);////����Ϊת��ģʽ
			NiM_clearErrorState(nAddr);            //����״̬���
			NiM_powerOn(nAddr);                     //ʹ�ܵ��
//			tagtorque = -100;
//			error=NiM_moveTorque(nAddr,tagtorque);
//			if (error !=0)
//				{
//					return error;
//	  		}
//			delay_ms(10000);
//			delay_ms(10000);
//			delay_ms(10000);
//			tagtorque = 100;
//			error=NiM_moveTorque(nAddr,tagtorque);
//			
//			if (error !=0) 
//				{
//					return error;
//				}
		}
//		delay_ms(10000);
//		delay_ms(10000);
//		delay_ms(10000);
		return 0;
}


