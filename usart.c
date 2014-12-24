/**
 *	\file
 *
 *	\brief USART management
 *
 *	\page License
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
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
