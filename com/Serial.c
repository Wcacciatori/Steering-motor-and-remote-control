#include "Serial.h"
#include "main.h"

#define RX_BUFFER_SIZE 2  // 半字需要两个字节

uint16_t Serial_RxData;
uint16_t TURN_DATA;
uint8_t Serial_RxFlag;
volatile uint8_t RxBuffer[RX_BUFFER_SIZE];
volatile uint16_t RxCounter = 0;
uint16_t received_data = 0;
//extern	OS_EVENT *Sem_Task_UR;
//extern	OS_ERR err;

int turn_flag=0;

void Turn_Init()//串口初始化--接收407的未映射过的转向数据，再发送给转向电机	
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

//PC7-接受  PC6-发送
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOC , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOC , &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART6, &USART_InitStructure);
	
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART6, ENABLE);
}

void Serial_Init()//串口初始化--self
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

//PA10-接受  PA9-发送
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig (USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}
	
void Serial_SendByte(uint8_t Byte)//发送单个字节
{
	//self
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	
//	//zhou!
//	USART_SendData(USART6, Byte);
//	while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(int16_t *Array, uint16_t Length)//发送数组
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)//发送字符串
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)//返回x的y次方
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(int32_t Number, uint8_t Length)//发送十进制数字
{
	uint8_t i;
	//uint32_t Number1;
	if (Number >= 0)
	{
		Serial_SendString("+");
		Number = Number;
	}
	else
	{
		Serial_SendString("-");
		Number = -Number;
	}
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)//重定向所需函数
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)//printf的重定向
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void)//获取接受中断信号
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)//获取数据
{
	return Serial_RxData;
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//判断是否接收到数据
	{
		Serial_RxData = USART_ReceiveData(USART1);//读取接收到的数据
		//Serial_GetRxFlag();//设置接受标志位，表示是否接到数据。
		//OSSemPost(Sem_Task_UR);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清除接收中断标志位
	}

}

void USART6_IRQHandler(void)
{
	uint16_t low=0,high=0;
    // 检查是否发生溢出错误
    if (USART_GetITStatus(USART6, USART_IT_ORE_RX) != RESET)
    {
        // 读取数据寄存器以清除溢出错误标志
        (void)USART_ReceiveData(USART6);

        // 清除溢出错误标志
        USART_ClearITPendingBit(USART6, USART_IT_ORE_RX);

        // 您可以在这里添加错误处理代码，例如记录错误状态或通知上层应用
    }

    // 检查是否有数据接收
    if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
    {
        // 读取接收到的数据
        uint8_t data = USART_ReceiveData(USART6);

        // 将数据存入缓冲区
        if (RxCounter < RX_BUFFER_SIZE)
        {
            RxBuffer[RxCounter++] = data;
        }

        // 当接收到两个字节后，组合成16位数据
        if (RxCounter >= 2)
        {
            received_data = (RxBuffer[0] << 8) | RxBuffer[1];
            RxCounter = 0;  // 重置接收计数器
        }

        // 清除接收中断标志
        USART_ClearITPendingBit(USART6, USART_IT_RXNE);
    }
}

