#include "sys.h"


int  main(void)
{
	System_Init();
	wifi_protocol_init();//wifiЭ���ʼ��
	while(1)
	{
		wifi_uart_service();//wifi�������ݴ������
		System_Task();
	}
}
