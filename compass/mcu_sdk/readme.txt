
此MCU_SDK是根据涂鸦开发平台上定义的产品功能，自动生成的MCU代码。在此基础上进行修改、补充，可快速完成MCU程序。

MCU_SDK使用指导文档链接：
https://docs.tuya.com/zh/iot/device-development/access-mode-mcu/wifi-general-solution/software-reference-wifi/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9


开发步骤：

1：需要根据产品实际情况（重置wifi按钮和wifi状态指示灯处理方式、是否支持MCU升级等）进行配置，请在protocol.h内修改此配置；

2：移植此MCU_SDK，请查看protocol.c文件内的移植步骤,并正确完成移植。移植后，请完成数据下发处理、数据上报部分的代码，即可完成全部wifi功能。

文件概览：
此MCU_SDK包括7个文件：
	
（1）system.c和system.h 是wifi通用协议解析实现代码，无特殊情况，用户不需要修改。
	
（2）mcu_api.c和mcu_api.h ，用户需要主动调用的函数都在该文件内。
	
（3）protocol.h和protocol.c ，接收到模块数据后对数据的处理函数，可在此文件内找到，需要用户修改完善相关功能。protocol.h 和protocol.c文件内有详细修改说明，请仔细阅读。
	
（4）wifi.h文件包含了以上所有的.h文件，并定义了以上所有文件中的函数里用到的宏定义，使用此SDK相关函数，请#include "wifi.h"。

