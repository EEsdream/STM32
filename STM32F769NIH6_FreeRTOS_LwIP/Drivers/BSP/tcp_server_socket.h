/**
  ******************************************************************************
  * @file    tcp_server_socket.h
  * @author  Xuke XIA
  * @version V1.0
  * @date    2020-06-21
  * @brief   Tcp server socket head file.
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TCP_SERVER_SOCKET_H
#define __TCP_SERVER_SOCKET_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <lwip/sockets.h>
#include <lwip/err.h>
#include <lwip/sys.h>
#include <string.h>
#include "usart.h"
/* Exported define -----------------------------------------------------------*/
#define SERVER_PORT		50000
/* Exported typedef ----------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void TCP_Server_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __TCP_SERVER_SOCKET_H */

/******************************** END OF FILE *********************************/

/**
  * @brief
  */

/**
  * @brief  Function description.
  * @param  None
  * @retval None
  */

/**< Detailed description after the member */