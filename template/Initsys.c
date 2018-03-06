#include "stm32f4xx.h"
#include "Initsys.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_flash.h"
int pinMode(GPIO_TypeDef  *GPIO_GROUPx,uint16_t GPIO_PIN_x, uint8_t inorout)
{
	GPIO_InitTypeDef LED_Init;
	//(1)enable prot D clock
		if(GPIO_GROUPx==GPIOA)
		{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//__HAL_RCC_GPIOA_CLK_ENABLE();
		}
		else if(GPIO_GROUPx==GPIOB)
		{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		
	//__HAL_RCC_GPIOB_CLK_ENABLE();
		}
		else if(GPIO_GROUPx==GPIOC)
		{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		
	//__HAL_RCC_GPIOC_CLK_ENABLE();
		}
	  else if(GPIO_GROUPx==GPIOD)
		{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//__HAL_RCC_GPIOD_CLK_ENABLE();
		}
	  else if(GPIO_GROUPx==GPIOE)
		{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//__HAL_RCC_GPIOE_CLK_ENABLE();	
		}
	  else
		{
		return 0;
		}
	//(2):Initialisation LEDS
	  LED_Init.GPIO_Pin=GPIO_PIN_x;
		if(inorout==INPUT)
		{
		LED_Init.GPIO_Mode=GPIO_Mode_IN;
		LED_Init.GPIO_OType=GPIO_OType_PP;
		}			
		else
		{
	    LED_Init.GPIO_Mode=GPIO_Mode_OUT;
	    LED_Init.GPIO_OType=GPIO_OType_PP;
		}
		LED_Init.GPIO_Speed=GPIO_Speed_100MHz;
        LED_Init.GPIO_PuPd=GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIO_GROUPx,&LED_Init);
		return 1;
}
uint8_t sysclock(){
RCC_DeInit();
uint8_t state;
ErrorStatus Errsts;
RCC_HSEConfig(RCC_HSE_ON);
Errsts = RCC_WaitForHSEStartUp();
if(Errsts==SUCCESS)
{
	RCC_PLLConfig(RCC_PLLSource_HSE,8,336,2,7);
	RCC_PLLCmd(ENABLE);
	RCC_GetFlagStatus(RCC_FLAG_PLLRDY==RESET);
	FLASH_SetLatency(FLASH_Latency_5);
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PCLK2Config(RCC_HCLK_Div2);
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  return 1;
}
else
{
	return 0;
}
return 3;	
}

