#include "RCC.h"





void SystemClock_Config(void)  //ѡ��HSI16ʱ�����ķ�Ƶ����PLLCLK����8��Ƶ2��Ƶ����Ϊsysclk,
{
	RCC->APBENR1 |= 1<<28;//ʹ�ܵ�Դ�ӿ�ʱ��           																								
  PWR->CR1 = 1<<9;//ѡ��1.8V��Χ		
  while((PWR->SR2 & 1<<10) != 0)//�ȴ���ѹ�������ѹ����Ϊ���� VOS ��ƽ
	{
		
	}
	
  RCC->CR |= 1<<8 ;//ʹ��HSI   																								
  while ((RCC->CR & (1<<10)) != (1<<10)) //�ȴ�HSI�񵴾���
  {
		
  } 
	
  RCC->CFGR &= ~(1<<0); //����HSI16��Ϊϵͳʱ��
  while ((RCC->CFGR & 7<<3)  != 0) //�ȴ�HSI16��Ϊϵͳʱ��
  {

  }	
}

