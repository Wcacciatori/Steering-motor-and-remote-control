/******************************************************************************
  *@file       : NiMotionMotorSDK.h
  *@version    : Initial Draft
  *@author     : nimotion
  *@date       : 2020/12/1
  *@brief      : 
  *****************************************************************************
  **function   :
								本程序为南京立迈胜机器人有限公司控制CAN通信伺服电机程序模板
								
								
								本程序版权为南京立迈胜机器人有限公司所有
								未经本公司允许，不可转作其他商业用途
								如因非法转载造成一切意外事故，均与本公司无任何责任关系
  *History     :
  *@date       : 2020/12/1
  *@author     : nimotion
  *@note       : Created file

  ****************************************************************************/
#ifndef __NIMOTIONTEST_H__
#define __NIMOTIONTEST_H__
#include "stm32f4xx.h"
#include "nimotion.h"
#include "main.h"


#define Motor1 0x01     //1号电机地址为0x01
#define Motor2 0x02     //2号电机地址为0x02
#define MOVE_POSITION_SUCCESS 100
#define MOVE_POSITION_FALSE 101
#define MOVE_VELOCITY_SUCCESS 110
#define MOVE_VELOCITY_FALSE 111
#define MOVE_TORQUE_SUCCESS 120
#define MOVE_TORQUE_FALSE 121



extern CanRxMsg tpdo2;
extern CanRxMsg tpdo3;
extern CanRxMsg tpdo4;


//单台电机位置模式测试
uint8_t NiM_Position_Mode(uint8_t nAddr);

//单台电机速度模式测试
uint8_t NiM_Velocity_Mode(uint8_t nAddr); 

//单台电机转矩模式测试
uint8_t NiM_Torque_Mode(uint8_t nAddr);



#endif

