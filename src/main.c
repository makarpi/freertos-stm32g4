
/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#include "platform.h"
#include "system_stm32g4xx.h"

#include "led.h"

#include "FreeRTOS.h"
#include "task.h"

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void vTask1_handler(void *params);

TaskHandle_t xTaskHandle1 = NULL;

int main(void)
{
  SystemInit();
  SystemClock_Config();
  SystemCoreClockUpdate();

  leds_init();

  xTaskCreate(vTask1_handler, "Task1", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandle1);

  vTaskStartScheduler();
  // usart_init();
  // console_init();

  while (1)
  {

  }
}

void vTask1_handler(void *params)
{
  while(1)
  {
    leds_greenLedSetState(LEDS_STATE_TOGGLE);
    
    vTaskDelay(500);
  }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
    // Error_Handler();  
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(64);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(16000000);
  LL_SetSystemCoreClock(16000000);
}