#include "RCC.h"





void SystemClock_Config(void)  //选择HSI16时钟先四分频，到PLLCLK进行8倍频2分频，作为sysclk,
{
	RCC->APBENR1 |= 1<<28;//使能电源接口时钟           																								
  PWR->CR1 = 1<<9;//选择1.8V范围		
  while((PWR->SR2 & 1<<10) != 0)//等待调压器输出电压更改为所需 VOS 电平
	{
		
	}
	
  RCC->CR |= 1<<8 ;//使能HSI   																								
  while ((RCC->CR & (1<<10)) != (1<<10)) //等待HSI振荡就绪
  {
		
  } 
	
  RCC->CFGR &= ~(1<<0); //设置HSI16作为系统时钟
  while ((RCC->CFGR & 7<<3)  != 0) //等待HSI16作为系统时钟
  {

  }	
}

