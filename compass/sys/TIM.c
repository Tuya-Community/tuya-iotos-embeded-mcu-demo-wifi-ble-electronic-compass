#include "TIM.h"
#include "IO.h"
#include "USART.h"




void TIM6_Init(uint16_t arr,uint16_t psc)//TASK����
{
	RCC->APBENR1 |= 1<<4;
	TIM6->ARR = arr;
	TIM6->PSC = psc;
	TIM6->DIER |= 1<<0;//ʹ�ܸ����ж�
	TIM6->CR1 |= 1<<0;//ʹ�ܼ�����
	NVIC_SetPriority(TIM6_DAC_LPTIM1_IRQn, 1); 
	NVIC_EnableIRQ(TIM6_DAC_LPTIM1_IRQn);
}
void TIM6_Start(void)
{
	TIM6->CR1 |=1<<0;//ʹ�ܼ�����
}
void TIM6_Stop(void)
{
	TIM6->CR1 &=~(1<<0);	//��ֹ������
	TIM6->CNT =0;//��������
}
uint8_t F_TASK_TIM6=0;
void TIM6_DAC_LPTIM1_IRQHandler(void)
{
	if ((TIM6->SR & 1) == 1) /* Check ARR match */ 
	{	
		TIM6->SR &= ~(1<<0);//����жϱ�־λ
		F_TASK_QMC5883L=1;
	}
}

void TIM_Init(void)
{	
	TIM6_Init(500,15999);//1s,����TASK_TIM6
}

