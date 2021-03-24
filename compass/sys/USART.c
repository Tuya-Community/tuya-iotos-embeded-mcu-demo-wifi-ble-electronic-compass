#include "USART.h"
#include "TIM.h"



void Configure_USART_MAIN(uint32_t bound) //TX PC4, RX PC5 USART1
{
	RCC->APBRSTR2 &=~(1<<14);//�ָ�����1
	RCC->IOPENR |= 1<<2;//ʹ��GPIOCʱ��
	GPIOC->MODER &=~(3<<8|3<<10);
	GPIOC->MODER |=2<<8|2<<10;//����ģʽ
	GPIOC->AFR[0] &=~(0xf<<16|0xf<<20);
	GPIOC->AFR[0] |=1<<16|1<<20;//ѡ���ù���AF1
	RCC->APBENR2 |=1<<14;//ʹ�ܴ���1ʱ��	
	USART_MAIN->BRR = 16000000 / bound; 
	USART_MAIN->CR1 |= 1<<0|1<<2|1<<3|1<<5;//����ʹ�ܣ�ʹ�ܽ��գ�ʹ�ܷ���,
	while((USART_MAIN->ISR & 1<<6) != 1<<6)//������ɱ�־λ
	{ 
		break;/* add time out here for a robust application */
	}	
	NVIC_SetPriority(USART1_IRQn, 1);
	NVIC_EnableIRQ(USART1_IRQn);

}
void USART1_IRQHandler(void)
{
	if((USART_MAIN->ISR & 1<<5) == 1<<5)//���ռĴ������ݲ�Ϊ��
	{
		uart_receive_input((unsigned char)(USART_MAIN->RDR));
	}
	else
	{
		//NVIC_DisableIRQ(USART1_IRQn); /* Disable USART1_IRQn */
	}	
	if((USART_MAIN->ISR & (1<<3)) == (1<<3))//ORE
	{
		USART_MAIN->ICR =1<<3;
	}
}




#if 1
#pragma import(__use_no_semihosting)  
//���HAL��ʹ��ʱ,ĳЩ������ܱ����bug
int _ttywrch(int ch)    
{
    ch=ch;
	return ch;
}
//��׼����Ҫ��֧�ֺ���       

struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 

/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
#define USART_fput USART_MAIN
int fputc(int ch, FILE *f)
{      
	while((USART_fput->ISR&0X40)==0);//ѭ������,ֱ���������   
	USART_fput->TDR = (uint8_t) ch;          	
	return ch;
}
#endif
