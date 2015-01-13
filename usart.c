/**
 *	\file
 *
 *	\brief USART management
 *
 *  Created on: 09.06.2011
 *      Author: Anton Glukhov
 */

#include "Bootloader.h"

#include "usart.h"

void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;

	/* Configure the USART3 for DEBUG */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART_DBG_PORT, &USART_InitStructure);

	USART_Cmd(USART_DBG_PORT, ENABLE);
}


uint8_t USART_STR_TX(uint8_t *data, USART_TypeDef* USARTx)
{
	while(*data != '\0')
	{
	    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); /* Waitwhile TX full */
	    USART_SendData(USARTx, *(uint8_t *)data);
		data++;
	}
	return 0;
}


void USART_BUF_TX(uint8_t *data, size_t len, USART_TypeDef* USARTx)
{
	while(len > 0)
	{
	    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); /* Waitwhile TX full */
	    USART_SendData(USARTx, *(uint8_t *)data);
	    data++;
	    len--;
	}
}
