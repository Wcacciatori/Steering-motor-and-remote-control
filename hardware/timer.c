#include "timer.h"
#include "misc.h"

//(72M/7200)*10=1ms
ITStatus FLAG;

void TIM2_Int_Init(u16 arr,u16 psc) //1ms
{
	TIM_TimeBaseInitTypeDef  _TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	_TIM_TimeBaseStructure.TIM_Prescaler=psc;
	_TIM_TimeBaseStructure.TIM_Period=arr;
	_TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	_TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &_TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;

	NVIC_Init(&NVIC_InitStructure);
	
	//Serial_Printf("test_tim2");
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	TIM_Cmd(TIM2, ENABLE); 
	FLAG = TIM_GetITStatus(TIM2, TIM_IT_Update);
	Serial_Printf("FLAG2 = %d\r\n",FLAG);
}

void TIM3_Int_Init(u16 arr,u16 psc)//2ms
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;
	TIM_TimeBaseStructure.TIM_Period=arr;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	
	TIM_Cmd(TIM3, ENABLE); 
		FLAG = TIM_GetITStatus(TIM3, TIM_IT_Update);
	Serial_Printf("FLAG3 = %d\r\n",FLAG);

}
extern volatile int timer2_cnt;
extern uint16_t RTU_FLAG;
void TIM2_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
		{
			//RTU_FLAG=1;
		  timer2_cnt++;
		}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  
}
void TIM3_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) 
		{
			  RTU_FLAG=1;
		}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  
}	
	
	
