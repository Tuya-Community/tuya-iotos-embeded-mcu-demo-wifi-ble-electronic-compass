#ifndef __USART_H
#define __USART_H 		
#include "MY_ST_config.h"
#include "stdio.h"
#include "string.h"








#define USART_MAIN  USART1
#define USART_MAIN_BOUND 115200



void Configure_USART_MAIN(uint32_t bound);//TX PC4, RX PC5 USART1


#endif

