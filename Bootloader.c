

#include "Bootloader.h"
#include "usart.h"

//#define RESET_VECTOR_TABLE_OFFSET           	4
#define ST_BOOTLOADER_ADDRESS					0x08000000
//#define APPLICATION_RESET_VECTOR_ADDRESS		(ST_BOOTLOADER_ADDRESS + RESET_VECTOR_TABLE_OFFSET)
#define APPLICATION_ADDRESS		0x08004000

typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;

int main(void)
{
	uint8_t i = 0;

	RCC_Configuration();

	GPIO_Configuration();

	USART_Configuration();

	NVIC_Configuration();

	for (i = 0; i < 2; ++i)
	{
		USART_STR_TX("Bootloader\r\n", USART3);
		Delay_ms(1000);
	}

    JumpAddress = *(__IO uint32_t*)(APPLICATION_ADDRESS + 4);
    Jump_To_Application = (pFunction) JumpAddress;
    __disable_irq();
    __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
	Jump_To_Application();

	return 0;
}


#ifdef DISCOVERY
void RCC_Configuration(void)
{

	/* Enable HSI Clock */
	RCC_HSICmd(ENABLE);

	/*!< Wait till HSI is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	/* Set HSI as sys clock*/
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

	/* Set MSI clock range to ~4.194MHz*/
	RCC_MSIRangeConfig(RCC_MSIRange_6);

	/* Enable the GPIOs clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC , ENABLE);

	/* Enable comparator, LCD and PWR mngt clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP | RCC_APB1Periph_PWR | RCC_APB1Periph_I2C1 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2 ,ENABLE);

	/* Enable ADC & SYSCFG clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_SYSCFG , ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* Allow access to the RTC */
	PWR_RTCAccessCmd(ENABLE);

	/* Reset RTC Backup Domain */
	RCC_RTCResetCmd(ENABLE);
	RCC_RTCResetCmd(DISABLE);

	/* LSE Enable */
	RCC_LSEConfig(RCC_LSE_ON);

	/* Wait until LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

	/* RTC Clock Source Selection */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* Enable the RTC */
	RCC_RTCCLKCmd(ENABLE);

	/*Disable HSE*/
	RCC_HSEConfig(RCC_HSE_OFF);
	if(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET )
	{
		/* Stay in infinite loop if HSE is not disabled*/
		while(1);
	}
}
#else
void RCC_Configuration(void)
{

	RCC_HSEConfig(ENABLE);

	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

	/* Enable the GPIOs clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC| RCC_AHBPeriph_GPIOD, ENABLE);

	/* Enable comparator, LCD and PWR mngt clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_I2C1 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2 ,ENABLE);

	/* Enable ADC & SYSCFG clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG , ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* RTC configuration in rtc.c file */
}
#endif


void NVIC_Configuration(void)
{
}


void SysTickConfig(void)
{
}


void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure the LED_pin as output push-pull usage*/
	GPIO_InitStructure.GPIO_Pin = GPIO_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);

	memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitTypeDef));

	/* Configure the USART3 as alternative usage*/
	GPIO_InitStructure.GPIO_Pin =  USART_DBG_TX | USART_DBG_RX;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
}

void Delay_ms(uint32_t ms)
{
        volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
        for (; nCount!=0; nCount--);
}
