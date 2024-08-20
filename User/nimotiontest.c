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
  * @details    : 对电机位置模式下的基本操作，请参照下面函数。
  * @param [in] : nAddr：  	 电机地址Node-ID   取值范围： 1~127 
  * @param [out]: 
  * @retval     : 100 成功，其他表示错误
	
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
	error = NiM_writeParam(nAddr,0x0380,(uint8_t *)&temp2,2);//脱机
	if (error !=0)
		{
			return error;
		}
	temp2=0;
	error = NiM_writeParam(nAddr,0x0402,(uint8_t *)&temp2,2);//线性
		if (error !=0)
		{
			return error;
		}
	temp2=33;
	error = NiM_writeParam(nAddr,0x0326,(uint8_t *)&temp2,2);//虚拟端子使能
		if (error !=0)
		{
			return error;
		}
	temp2=1;
	error = NiM_writeParam(nAddr,0x0373,(uint8_t *)&temp2,2);//通信给定虚拟端子电平
	//if (error !=0)return error;
	if (error !=0)
		{
			return error;
		}
	temp2=0;
	error = NiM_writeParam(nAddr,0x0373,(uint8_t *)&temp2,2);//当前位置清零
		if (error !=0)
		{
			return error;
		}
	if(temp1 == nAddr)//电机在线
		{

			NiM_powerOff(nAddr);                    //电机脱机
			NiM_changeWorkMode(nAddr,POSITION_MODE);////设置为位置模式
			NiM_clearErrorState(nAddr);            //故障状态清除
			NiM_powerOn(nAddr);                     //使能电机
//			tagpostion = 2500;      //电机一圈10000
//			NiM_moveRelative(nAddr,0,tagpostion);//电机正转1圈,立即更新
//			delay_ms(1000);
//			tagpostion = -2500;
//			NiM_moveRelative(nAddr,1,tagpostion);//电机反转1圈，非立即更新
//			delay_ms(10);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);

//			NiM_moveRelative(nAddr,1,tagpostion);//电机反转1圈，非立即更新
//			delay_ms(10);	
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);
//		
//			NiM_moveRelative(nAddr,1,tagpostion);//电机反转1圈，非立即更新
//			delay_ms(10);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);

//			NiM_moveRelative(nAddr,1,tagpostion);//电机反转1圈，非立即更新
//			delay_ms(10);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);

//			NiM_moveRelative(nAddr,1,tagpostion);//电机反转1圈，非立即更新
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
////			delay_ms(1000);
//			tagpostion = 0;
			NiM_moveAbsolute(nAddr,0,tagpostion);//电机走到绝对位置0，立即更新

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
  * @details    : 对电机速度模式下的基本操作，请参照下面函数。
  * @param [in] : nAddr：  	 电机地址Node-ID   取值范围： 1~127 
  * @param [out]: 
  * @retval     :110 成功，其他表示错误
	
  * History
  * @date       : 2020/12/01
  *	@author     : Nimotion
********************************************************/

uint8_t NiM_Velocity_Mode(uint8_t nAddr)
{
	uint16_t temp = 0;
	uint8_t error =0;
	int32_t tagvelocity = 0;
	
	error = NiM_isMotorOnline(nAddr,&temp);//判断电机是否在线
	if (error !=0)return error;
	if(temp == nAddr)//电机在线
		{

		
		  NiM_powerOff(nAddr);                    //电机脱机
			NiM_changeWorkMode(nAddr,VELOCITY_MODE);////设置为速度模式
			NiM_clearErrorState(nAddr);            //故障状态清除
			NiM_powerOn(nAddr);                     //使能电机
//			tagvelocity = 100000;//100000/10000*60=600rpm
//			NiM_moveVelocity(nAddr,tagvelocity);//电机以600rpm正转
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			tagvelocity = -100000;//-600rpm
//			NiM_moveVelocity(nAddr,tagvelocity);//电机以600rpm反转
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			delay_ms(1000);
//			tagvelocity = 200000;//1200rpm
//			NiM_moveVelocity(nAddr,tagvelocity);//电机正1200rpm正转

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
  * @details    : 对电机转矩模式下的基本操作，请参照下面函数。
  * @param [in] : nAddr：  	 电机地址Node-ID   取值范围： 1~127 
  * @param [out]: 
  * @retval     :120 成功，其他表示错误
	
  * History
  * @date       : 2020/12/01
  *	@author     : Nimotion
********************************************************/
uint8_t NiM_Torque_Mode(uint8_t nAddr)
{
	uint16_t temp = 0;
	uint8_t error =0;
	int16_t tagtorque = 0;
	error = NiM_isMotorOnline(nAddr,&temp);//判断电机是否在线
	if (error !=0)
	{
		return error;
	}
	if(temp == nAddr)//电机在线
		{
			//NiM_powerOff(nAddr);                    //电机脱机
			NiM_changeWorkMode(nAddr,TORQUE_MODE);////设置为转矩模式
			NiM_clearErrorState(nAddr);            //故障状态清除
			NiM_powerOn(nAddr);                     //使能电机
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


