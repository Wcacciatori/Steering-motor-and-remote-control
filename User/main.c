/*
	ʹ��ʱ����ѡ����Ҫ��ģʽ���г�ʼ��
		1.���λ��ģʽ��ʼ����NiM_Position_Mode(Motor1);
		2.����ٶ�ģʽ��ʼ����NiM_Velocity_Mode(Motor1);
		3.���ת��ģʽ��ʼ����NiM_Torque_Mode(Motor1);
		
	1)��ʹ��λ��ģʽʱ������NiM_moveRelative(uint8_t nAddr, uint8_t nType,int32_t nDistance);
		����λ��,����nDistance=10000ʱ�����תһȦ��
	2)��ʹ���ٶ�ģʽʱ������NiM_moveVelocity(nAddr,tagvelocity);
		�����ٶ�,����tagvelocity=100000ʱ�����600rpm��ת��
	3)��ʹ��ģʽʱ������NiM_moveTorque(nAddr,tagtorque);
		����ת��,����tagtorque=100ʱ�������Ϊ0.127Nm
	
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
        // 0~32767��0~10000  
        return (10000 * input) / 32767;  
    } else {  
        // 32768~65535��-10000~0  
        return (10000 * (input - 65535)) / 32767;  
    }  
} 

int main()
 {	

	  uint32_t date = 0;
	  delay_init();//�δ�ʱ�ӳ�ʼ��
	  Modbus_Mode_Init();//Modbus��ʼ��
		Serial_Init();
		Turn_Init();
		TIM2_Int_Init(9,16799);//TIM2 ����ͨ�ų�ʱ���,1ms
		TIM3_Int_Init(19,16799);//TIM3 ��ʱ����Motor1�����ǰλ�ú�Motor2�����ǰ�ٶȣ�2ms
	 

		err = NiM_readParam (1,0x0380,(uint16_t *)&date,2);
	 Serial_Printf("err:%d\r\n",err);//û�д��󣬷��سɹ�
	 

	 	NiM_Position_Mode(Motor1);//Motor1���λ��ģʽ����
	 
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

		//NiM_Velocity_Mode(Motor1); //Motor1����ٶ�ģʽ����
		//NiM_Torque_Mode(Motor1); //Motor1���ת��ģʽ����
		

//  }
	
}
