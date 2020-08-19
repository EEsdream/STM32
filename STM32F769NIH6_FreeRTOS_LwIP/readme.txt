/**
  ******************************************************************************
  * @file    readme.txt
  * @author  Xuke XIA
  * @version V1.01
  * @date    2020-08-02
  * @brief   Project Description and Debug logger file.
  ******************************************************************************
  * @attention
  *
  * Hardware Platform : STM32F769NIH6
  * Software Platform : STM32CubeMX Version 5.2.1
  *                     STM32Cube_FW_F7_V1.15.0
  *                     IAR Embedded Workbench for ARM Version 8.32.1.18361
  *
  *
  ******************************************************************************
  */

I、描述：
1. STM32F769NIH6 FreeRTOS工程模版；
2. 通过USART1(PA9->Console_TX，PA10->Console_RX)进行调试；115200bps,8N1；
3. 使能CPU ICache、CPU DCache；
4. Timebase Source使用TIM6；
5. Heap Size：0x1000；Stack Size：0x400；
6. 使用LwIP，socket方式创建TCP Server，IP：169.254.16.100，Port：50000；
7. 设置LwIP使能LWIP_NETIF_LINK_CALLBACK,实现网线热插拔;

II、记录：
1. IAR开发环境中，使用scanf会导致第一个字节无法正常接收，更改为调用自己写的getInputString函数来获取；Keil开发环境不存在该问题；
2. 使用IAR开发环境中的FreeRTOS调试插件，Project->Options->Debugger->Plugins->FreeRTOS(with task local context)；
3. 相同优先级的任务，后创建的先运行；
