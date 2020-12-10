
/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#include "platform.h"
#include "system_stm32g4xx.h"

#include "led.h"
#include "console.h"

#include "FreeRTOS.h"
#include "task.h"

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void vTask1_handler(void *params);

TaskHandle_t xTaskHandle1 = NULL;

int main(void)
{  
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  SystemInit();
  SystemClock_Config();
  SystemCoreClockUpdate();

  leds_init();
  console_init();

  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  xTaskCreate(vTask1_handler, "Task1", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandle1);

  vTaskStartScheduler();
  

  while (1)
  {

  }
}

void vTask1_handler(void *params)
{
  while(1)
  {
    leds_greenLedSetState(LEDS_STATE_TOGGLE);
    
    vTaskDelay(500/portTICK_RATE_MS );
  }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_8);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_8)
  {
    // Error_Handler();  
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSE_Enable();
  LL_RCC_HSE_EnableCSS();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {
    
  }

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_6, 85, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  LL_Init1msTick(170000000);
  LL_SetSystemCoreClock(170000000);

  LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_SYSCLK, LL_RCC_MCO1_DIV_16);
}