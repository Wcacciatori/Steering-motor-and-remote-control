/*
	使用时首先选择需要的模式进行初始化
		1.电机位置模式初始化：NiM_Position_Mode(Motor1);
		2.电机速度模式初始化：NiM_Velocity_Mode(Motor1);
		3.电机转矩模式初始化：NiM_Torque_Mode(Motor1);
		
	1)当使用位置模式时，调用NiM_moveRelative(uint8_t nAddr, uint8_t nType,int32_t nDistance);
		设置位置,其中nDistance=10000时电机正转一圈。
	2)当使用速度模式时，调用NiM_moveVelocity(nAddr,tagvelocity);
		设置速度,其中tagvelocity=100000时电机以600rpm正转。
	3)当使用模式时，调用NiM_moveTorque(nAddr,tagtorque);
		设置转矩,其中tagtorque=100时电机力矩为0.127Nm
	
*/
#include "delay.h"
#include "timer.h"
#include "nimotion.h"
#include "nimotiontest.h"
#include "modbus.h"
#include "main.h"

extern uint16_t TURN_DATA;
extern volatile int timer2_cnt;
extern uint16_t received_data;
uint8_t err;

uint16_t baud;

int map_value(unsigned int input) {  
    if (input <= 32767) {  
        // 0~32767到0~10000  
        return (10000 * input) / 32767;  
    } else {  
        // 32768~65535到-10000~0  
        return (10000 * (input - 65535)) / 32767;  
    }  
} 

int main()
 {	

	  uint32_t date = 0;
	  delay_init();//滴答时钟初始化
	  Modbus_Mode_Init();//Modbus初始化
		Serial_Init();
		Turn_Init();
		TIM2_Int_Init(9,16799);//TIM2 用作通信超时检测,1ms
		TIM3_Int_Init(19,16799);//TIM3 定时更新Motor1电机当前位置和Motor2电机当前速度，2ms
	 

		err = NiM_readParam (1,0x0380,(uint16_t *)&date,2);
	 Serial_Printf("err:%d\r\n",err);//没有错误，返回成功
	 

	 	NiM_Position_Mode(Motor1);//Motor1电机位置模式运行
	 
//	 while(1)
//	{
		//Serial_Printf("start");
		//NiM_powerOff(Motor1);

//	  delay_ms(1000);
//	 Serial_Printf("test");
//		delay_ms(2000);
//		NiM_moveRelative(Motor1,1,2000);
//		delay_ms(2000);
//		NiM_moveAbsolute(Motor1,1,0);
//		delay_ms(2000);
		while(1){
			received_data = map_value(received_data);
			//TURN_DATA = 10000;
			//NiM_moveAbsolute(Motor1, 1, received_data*0);
			delay_ms(2000);
			NiM_moveAbsolute(Motor1, 1, received_data/0xA);
			delay_ms(2000);
			NiM_moveAbsolute(Motor1, 1, 0);

			
		}

		//NiM_Velocity_Mode(Motor1); //Motor1电机速度模式运行
		//NiM_Torque_Mode(Motor1); //Motor1电机转矩模式运行
		

//  }
	
}
