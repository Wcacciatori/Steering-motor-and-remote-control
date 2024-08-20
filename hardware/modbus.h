/******************************************************************************
  *
  *   Copyright (C), 2010-2018, Beijing NiMotion Control Technology Co., Ltd.
  *
  *****************************************************************************
  *@file       : modbus.h
  *@version    : Initial Draft
  *@author     : Nimotion
  *@date       : 2019/7/12
  *@brief      :
  *****************************************************************************
  **function   :
								本程序为北京立迈胜控制技术有限公司控制MODBUS通信电机程序模板


								本程序版权为北京立迈胜控制技术有限公司所有
								未经本公司允许，不可转作其他商业用途
								如因非法转载造成一切意外事故，均与本公司无任何责任关系
  *History     :
  *@date       : 2019/7/12
  *@author     : Nimotion
  *@note       : Created file

  ****************************************************************************/
#include "misc.h"
#ifndef _BSP_USART_H_
#define _BSP_USART_H_


#define _485_USART                             USART2
#define _485_USART_CLK                         RCC_APB1Periph_USART2
#define _485_USART_BAUDRATE                    115200

#define _485_USART_RX_GPIO_PORT                GPIOD
#define _485_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define _485_USART_RX_PIN                      GPIO_Pin_5
#define _485_USART_RX_AF                       GPIO_AF_USART2
#define _485_USART_RX_SOURCE                   GPIO_PinSource5

#define _485_USART_TX_GPIO_PORT                GPIOD
#define _485_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define _485_USART_TX_PIN                      GPIO_Pin_6
#define _485_USART_TX_AF                       GPIO_AF_USART2
#define _485_USART_TX_SOURCE                   GPIO_PinSource6


#define _485_RE_GPIO_PORT												GPIOC
#define _485_RE_GPIO_CLK												RCC_AHB1Periph_GPIOC
#define _485_RE_PIN															GPIO_Pin_0

#define _485_INT_IRQ                 						USART2_IRQn
#define _485_IRQHandler                         USART2_IRQHandler



void Modbus_Mode_Init(void);
void USART_Send_Buffer(uint8_t *buf,uint8_t size);
uint16_t usMBCRC16( uint8_t * pucFrame, uint16_t usLen );
void set_data(uint8_t addr,uint8_t reg,uint8_t volue);

#endif


