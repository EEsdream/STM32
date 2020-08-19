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

I��������
1. STM32F769NIH6 FreeRTOS����ģ�棻
2. ͨ��USART1(PA9->Console_TX��PA10->Console_RX)���е��ԣ�115200bps,8N1��
3. ʹ��CPU ICache��CPU DCache��
4. Timebase Sourceʹ��TIM6��
5. Heap Size��0x1000��Stack Size��0x400��
6. ʹ��LwIP��socket��ʽ����TCP Server��IP��169.254.16.100��Port��50000��
7. ����LwIPʹ��LWIP_NETIF_LINK_CALLBACK,ʵ�������Ȳ��;

II����¼��
1. IAR���������У�ʹ��scanf�ᵼ�µ�һ���ֽ��޷��������գ�����Ϊ�����Լ�д��getInputString��������ȡ��Keil�������������ڸ����⣻
2. ʹ��IAR���������е�FreeRTOS���Բ����Project->Options->Debugger->Plugins->FreeRTOS(with task local context)��
3. ��ͬ���ȼ������񣬺󴴽��������У�
