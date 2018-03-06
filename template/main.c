#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_gpio.h"
void systickInit (uint32_t frequency)
{
   RCC_ClocksTypeDef RCC_Clocks;
   RCC_GetClocksFreq (&RCC_Clocks);
   (void) SysTick_Config (RCC_Clocks.HCLK_Frequency / frequency);
}


volatile uint32_t ticks ,now,last,interval;
void SysTick_Handler (void)
 {
   ticks++;
 }
 
uint32_t micros(void)
{
   return ticks;
}
void delay_micros(uint16_t delaytime){
	uint32_t startnum=micros();
	uint32_t now=micros();
while(now<startnum+delaytime){
	now=micros();
}
}
void delay_millis(uint16_t delaytime){
	uint32_t startnum=micros();
	uint32_t now=micros();
  uint32_t num;
  for(uint32_t i=0;i<delaytime;i++){
		delay_micros(1000);
	}
}
void setup_Periph(){
	
systickInit (1000000);
	

GPIO_InitTypeDef GPIO_InitStructure;
	 //sysclock();
//Enable the preiph clock for USART2

//Enable the GPIO clock
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);	
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
GPIO_Init(GPIOD,&GPIO_InitStructure);



}
int main()
{

int state;	
setup_Periph();

	
	
while(1){
	//now=millis();
//interval=now-last;
//	if(interval>=100){
//		
//		state=!state;	
//		last=now;
//	}
	delay_millis(1000);
	state=!state;	
	GPIO_WriteBit(GPIOD,GPIO_Pin_13,state);
	delay_millis(1000);
	state=!state;	
	GPIO_WriteBit(GPIOD,GPIO_Pin_13,state);

}

//return 0;

}
