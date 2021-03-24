#include "sys.h"


int  main(void)
{
	System_Init();
	wifi_protocol_init();//wifi协议初始化
	while(1)
	{
		wifi_uart_service();//wifi串口数据处理服务
		System_Task();
	}
}
