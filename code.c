printf("--------------------------------------------------\r\n");
printf("  XXX Test...\r\n");
printf("--------------------------------------------------\r\n");

/*
--------------------------------------------------------------------------------
*/
/* 串口相关 */
// Add in "usart.c"
/* USER CODE BEGIN 1 */
#if defined (__GNUC__)
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
  #define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
  #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART2 and Loop until the end of transmission */
  if (HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 0xFFFF) != HAL_OK)
  {
    Error_Handler();
  }

  return ch;
}

/**
  * @brief  Retargets the C library scanf function to the USART.
  * @param  None
  * @retval None
  */
GETCHAR_PROTOTYPE
{
  /* Place your implementation of fgetc here */
  /* e.g. read a character on USART2 and loop until the end of reception */
  uint8_t ch = 0;
  if (HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 0xFFFF) != HAL_OK)
  {
    Error_Handler();
  }

  return ch;
}

#if defined (__ICCARM__)
/**
  * @brief  Get a line from the console (user input).
  * @param  Out:  inputString   Pointer to buffer for input line.
  * @param  In:   len           Max length for line.
  * @retval Number of bytes read from the terminal.
  */
uint32_t getInputString(char *inputString, uint32_t len)
{
  uint32_t currLen = 0;
  int c = 0;
  
  c = getchar();
  
  while ((c != EOF) && ((currLen + 1) < len) && (c != '\r') && (c != '\n') && (c != ' '))
  {
    if (c == '\b')
    {
      if (currLen != 0)
      {
        --currLen;
        inputString[currLen] = 0;
        printf("\b");
      }
    }
    else
    {
      if (currLen < (len-1))
      {
        inputString[currLen] = c;
      }
      
      ++currLen;
    }
    c = getchar();
  }
  if (currLen != 0)
  { /* Close the string in the input buffer... only if a string was written to it. */
    inputString[currLen] = '\0';
  }
  if (c == '\r')
  {
    c = getchar(); /* assume there is '\n' after '\r'. Just discard it. */
  }
  
  return currLen;
}
#endif
/* USER CODE END 1 */

// Add in "usart.h"
/* USER CODE BEGIN Private defines */
#define USE_CONSOLE

#ifdef USE_CONSOLE
  #define Console_Info(...)    \
          {\
            printf("[Info]: "); \
            printf(__VA_ARGS__); \
          }
  #define Console_Warning(...)    \
          {\
            printf("[Warn]: %s L#%d - ", __func__, __LINE__); \
            printf(__VA_ARGS__); \
          }
  #define Console_Error(...)    \
          {\
            printf("[Error]: %s L#%d - ", __func__, __LINE__); \
            printf(__VA_ARGS__); \
          }
#else
  #define Console_Info(...)
  #define Console_Warning(...)
  #define Console_Error(...)
#endif
/* USER CODE END Private defines */


/*
--------------------------------------------------------------------------------
*/
/* 采样周期设定 */
// Add in "main.h"
#define NUM_TASK        1
extern uint32_t Task_Delay[NUM_TASK];
// Add in "main.c"
uint32_t Task_Delay[NUM_TASK]={0};
// Add in "stm32xxx_it.c"
/* USER CODE BEGIN SysTick_IRQn 1 */
// Task Delay
{
  uint8_t i;

  for(i = 0; i < NUM_TASK; i++)
  {
    if(Task_Delay[i])
    {
      Task_Delay[i]--;
    }
  }
}
/* USER CODE END SysTick_IRQn 1 */


/*
--------------------------------------------------------------------------------
*/
/* 编译器相关 */
#if defined (__CC_ARM)                  /* ARM Compiler */
	printf("__CC_ARM\r\n");
#elif defined (__ICCARM__)              /* IAR Compiler */
	printf("__ICCARM__\r\n");
#elif defined (__GNUC__)                /* GNU Compiler */
	printf("__GNUC__\r\n");
#endif


/*
--------------------------------------------------------------------------------
*/
/* 指定变量存储位置（方法一） */
// Add in "main.c"
/* Define variables in fixed flash address */
#if defined (__CC_ARM)
    user_config_t lUserConfig __attribute__((section("UNINIT_FIXED_LOC"), zero_init));
#elif defined (__ICCARM__)
    __no_init const user_config_t lUserConfig @"UNINIT_FIXED_LOC";
#elif defined (__GNUC__)
    user_config_t lUserConfig __attribute__((section("UNINIT_FIXED_LOC")));
#endif
/* Must Add in .sct file */
UNINIT_FIXED_LOC 0x0800F000 0x00000080 {    ; UNINIT_FIXED_LOC
.ANY (UNINIT_FIXED_LOC)
}
/* Must Add in .icf file */
define symbol __ICFEDIT_region_FIXED_LOC_start__ = 0x080FF800;
define region uninit_fixed_loc = mem:[from __ICFEDIT_region_FIXED_LOC_start__ size 2K];
place in uninit_fixed_loc { readonly section UNINIT_FIXED_LOC };
// or
place at address mem:0x080FF800 { readonly section UNINIT_FIXED_LOC };

/* 指定变量存储位置（方法二） */
// // Add in "main.c"
/* Define variables in fixed flash address or fixed sram address */
#if defined (__CC_ARM)
  __attribute__((at(0x0800F000))) const uint32_t aSRC_Buffer[BUFFER_SIZE] = {
                              0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
                              0x11121314, 0x15161728, 0x191A1B1C, 0x1D1E1F20,
                              0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                              0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                              0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                              0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                              0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                              0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

  __attribute__((at(0x24000000))) uint32_t aDST_Buffer[BUFFER_SIZE] = {0x0AABBCCDD};
#elif defined (__ICCARM__)
  const uint32_t aSRC_Buffer[BUFFER_SIZE] @0x0800F000= {
                              0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
                              0x11121314, 0x15161728, 0x191A1B1C, 0x1D1E1F20,
                              0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                              0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                              0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                              0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                              0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                              0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};
  
  uint32_t aDST_Buffer[BUFFER_SIZE] @0x24000000 = {0x0AABBCCDD};
#endif


/*
--------------------------------------------------------------------------------
*/
/* 多功能按键 */
#define USE_PRESS_DOUBLE

// Add in "main.h"
typedef enum
{
  PRESS_RELEASE = 0x00,
  PRESS_LONG    = 0x01,
  PRESS_SHORT   = 0x02,
#ifdef USE_PRESS_DOUBLE
  PRESS_DOUBLE  = 0x03
#endif
} KEY_Status_t;

// Add in "stm32xxx_it.c"
#define PRESS_LEVEL                     1       // High level
#define PRESS_LONG_TIME                 2000    // 2s
#define PRESS_SHORT_TIME                50      // 50ms
#ifdef USE_PRESS_DOUBLE
#define PRESS_DOUBLE_INTERVAL_TIME_MAX  800     // 800ms
#define PRESS_DOUBLE_INTERVAL_TIME_MIN  50      // 50ms
#endif

extern __IO uint8_t flag_key_press;
extern __IO uint8_t flag_key_status;
__IO uint32_t key_holdon_ms;
#ifdef USE_PRESS_DOUBLE
__IO uint8_t flag_key_release;
__IO uint32_t key_release_ms;
#endif

  // KEY Check
  {
    if (flag_key_press)
    {
      if (HAL_GPIO_ReadPin(B_USER_GPIO_Port, B_USER_Pin) == PRESS_LEVEL)       // Key is still press
      {
        if (key_holdon_ms <= PRESS_LONG_TIME)
        {
          key_holdon_ms++;
        }
        else    // Long Press
        {
          key_holdon_ms = 0;
          flag_key_press = 0;
          flag_key_status = PRESS_LONG;
        }
      }
      else      // Key is release
      {
        // Short Press
        if (key_holdon_ms >= PRESS_SHORT_TIME)
        {
          key_holdon_ms = 0;
          flag_key_press = 0;
          flag_key_status = PRESS_SHORT;
          
#ifdef USE_PRESS_DOUBLE
           flag_key_release = 1;
           
          // Double Press
          if ((key_release_ms > PRESS_DOUBLE_INTERVAL_TIME_MIN) && (key_release_ms < PRESS_DOUBLE_INTERVAL_TIME_MAX))
          {
            key_release_ms = 0;
            flag_key_release = 0;
            flag_key_status = PRESS_DOUBLE;
          }
#endif
        }
        else    // Key is jitter
        {
          key_holdon_ms = 0;
          flag_key_press = 0;
          flag_key_status = PRESS_RELEASE;
        }
      }
    }
    
#ifdef USE_PRESS_DOUBLE
    // Key release time increase
    if (flag_key_release)
    {
      key_release_ms++;
      
      // Key release time more than Double Press time interval
      if (key_release_ms > PRESS_DOUBLE_INTERVAL_TIME_MAX)
      {
        key_release_ms = 0;
        flag_key_release = 0;
      }
    }
#endif
  }


/*
--------------------------------------------------------------------------------
*/
/* 8位CheckSum */
/**
  * @brief  Calculate 8 bit checksum function.
  * @param  *pData: The data to calculate.
  * @param  dataSize: The data length.
  * @retval checksum.
  */
uint8_t CheckSum8_Calculate(uint8_t *pData, uint32_t dataSize)
{
  uint8_t ckSum = 0;
  
  while (dataSize > 0)
  {
    ckSum += *pData;
	pData++;
	dataSize--;
  }
  
  return ((~ckSum) + 1);
}

/**
  * @brief  Verify 8 bit checksum function.
  * @param  *pData: The data to calculate.
  * @param  dataSize: The data length.
  * @param  ckSum: The data checksum.
  * @retval 0 -> Success, 1 -> Failed.
  */
uint8_t CheckSum8_Verify(uint8_t *pData, uint32_t dataSize, uint8_t ckSum)
{
  uint8_t pCkSum = ckSum;
  
  for (uint8_t i = 0; i < dataSize; i++)
  {
    pCkSum += *pData;
	pData++;
  }
  
  if (pCkSum == 0)
  {
    return 0;
  }
  else
  {
    return 1;  
  }
}