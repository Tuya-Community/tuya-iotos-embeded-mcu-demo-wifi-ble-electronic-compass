
��MCU_SDK�Ǹ���Ϳѻ����ƽ̨�϶���Ĳ�Ʒ���ܣ��Զ����ɵ�MCU���롣�ڴ˻����Ͻ����޸ġ����䣬�ɿ������MCU����

MCU_SDKʹ��ָ���ĵ����ӣ�
https://docs.tuya.com/zh/iot/device-development/access-mode-mcu/wifi-general-solution/software-reference-wifi/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9


�������裺

1����Ҫ���ݲ�Ʒʵ�����������wifi��ť��wifi״ָ̬ʾ�ƴ���ʽ���Ƿ�֧��MCU�����ȣ��������ã�����protocol.h���޸Ĵ����ã�

2����ֲ��MCU_SDK����鿴protocol.c�ļ��ڵ���ֲ����,����ȷ�����ֲ����ֲ������������·����������ϱ����ֵĴ��룬�������ȫ��wifi���ܡ�

�ļ�������
��MCU_SDK����7���ļ���
	
��1��system.c��system.h ��wifiͨ��Э�����ʵ�ִ��룬������������û�����Ҫ�޸ġ�
	
��2��mcu_api.c��mcu_api.h ���û���Ҫ�������õĺ������ڸ��ļ��ڡ�
	
��3��protocol.h��protocol.c �����յ�ģ�����ݺ�����ݵĴ����������ڴ��ļ����ҵ�����Ҫ�û��޸�������ع��ܡ�protocol.h ��protocol.c�ļ�������ϸ�޸�˵��������ϸ�Ķ���
	
��4��wifi.h�ļ��������������е�.h�ļ��������������������ļ��еĺ������õ��ĺ궨�壬ʹ�ô�SDK��غ�������#include "wifi.h"��

