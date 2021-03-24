#include "sys.h"
#include "RCC.h"
#include "delay.h"
#include "IO.h"
#include "TIM.h"
#include "USART.h"
void System_Init(void)
{
	SystemClock_Config();//HSI16/4 -> PLL*8/2->16M	
	delay_init(16);
	TIM_Init();
	Configure_USART_MAIN(USART_MAIN_BOUND);
	IO_Init();
}



void System_Task(void)
{
	if(F_TASK_QMC5883L)
	{
		F_TASK_QMC5883L=0;
		TASK_QMC5883L();
	}		
}

