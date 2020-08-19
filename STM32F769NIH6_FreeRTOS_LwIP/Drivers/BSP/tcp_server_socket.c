/**
  ******************************************************************************
  * @file    tcp_server_socket.c
  * @author  Xuke XIA
  * @version V1.0
  * @date    2020-06-21
  * @brief   Tcp server socket source file.
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tcp_server_socket.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t DataBuffer[100];
/* Private function prototypes -----------------------------------------------*/
static void TCP_Server_Thread(void *arg);
/* Exported functions --------------------------------------------------------*/
/**
  * @brief  TCP Server Initialize.
  * @param  None
  * @retval None
  */
void TCP_Server_Init(void)
{
  sys_thread_new("TCP_Server", TCP_Server_Thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}

/**
  * @brief  TCP Server Thread.
  * @param  None
  * @retval None
  */
static void TCP_Server_Thread(void *arg)
{
  struct sockaddr_in server_addr;
  struct sockaddr_in conn_addr;
  int sock_fd;          // Server socked
  int sock_conn;        // Request socked
  socklen_t addr_len;
  int err;
  int length;
  
  sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock_fd == -1)
  {
    Console_Error("Failed to create sock_fd!\r\n");
  }
  
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(SERVER_PORT);
  
  err = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (err < 0)
  {
    closesocket(sock_fd);
    Console_Error("Failed to bind sock_fd!\r\n");
  }
  
  err = listen(sock_fd, 1);
  if (err < 0)
  {
    closesocket(sock_fd);
    Console_Error("Failed to listen sock_fd!\r\n");
  }
  
  addr_len = sizeof(struct sockaddr_in);
  
  sock_conn = accept(sock_fd, (struct sockaddr *)&conn_addr, &addr_len);
  if (sock_conn < 0)
  {
    closesocket(sock_fd);
    Console_Error("Failed to accept sock_fd!\r\n");
  }
  else
  {
    send(sock_conn, "Connect success!\r\n", 18 , 0);
    Console_Info("TCP Server Connect Success!\r\n");
  }
  
  while(1)
  {
    memset(DataBuffer, 0, sizeof(DataBuffer));
    (void)length;
    length = recv(sock_conn, (uint32_t *)DataBuffer, 100, 0);
    
    //Console_Info("Length received %d\r\n", length);
    //Console_Info("Received string: %s\r\n", DataBuffer);
    
    send(sock_conn, "OK", 2, 0);
    
    //osDelay(1000);
  }
}


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

/*
 ===============================================================================
                ##### Interrrupt Service Routine Functions #####
 ===============================================================================
*/