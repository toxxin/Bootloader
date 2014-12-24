/*
 * Bootloader.h
 *
 *  Created on: Nov 16, 2014
 *      Author: anton
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include <string.h>		/* for _DEBUG macro */
#include <stdio.h>		/* for _DEBUG macro */

#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"

#define HW_VERSION	0x01
#define SW_VERSION	0x13
#define SN "EW-1409010001-T"

#define BIT(x) (1 << (x))

#define GPIO_HIGH(a,b) 		a->BSRRL = b
#define GPIO_LOW(a,b)		a->BSRRH = b
#define GPIO_TOGGLE(a,b) 	a->ODR ^= b

#define SETBIT(a,b) ((a) |= b)
#define CLEARBIT(a,b) ((a) &= ~(b))

/* return 0 - if bit is clear */
#define CHKBIT_REG(reg, BIT)  (reg & BIT)


void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTickConfig(void);
void GPIO_Configuration(void);
void USART_Configuration(void);


/**
 * 	\brief	Delay
 *
 * 	This function implements delay function.
 *
 * 	\param ms		- milliseconds
 */
void Delay_ms(uint32_t ms);


#ifdef DEBUG
//    #define _DEBUG(fmt, args...) fprintf(stderr, "\r\n%s:%s:%d: "fmt, __FILE__, __FUNCTION__, __LINE__, ##args)
	#define _DEBUG(fmt, args...) fprintf(stderr, "\r\n"fmt, ##args)
#else
    #define _DEBUG(fmt, args...)
#endif


#ifdef DISCOVERY
	#define	GPIO_LED_PORT	GPIOB
	#define	GPIO_LED_PIN	GPIO_Pin_7

	#define USART_DBG_PORT	USART3
#else
	#define	GPIO_LED_PORT	GPIOA
	#define	GPIO_LED_PIN	GPIO_Pin_5

	#define USART_DBG_PORT	USART3
#endif

#define USART_DBG_TX	GPIO_Pin_10
#define USART_DBG_RX	GPIO_Pin_11



#endif /* BOOTLOADER_H_ */
