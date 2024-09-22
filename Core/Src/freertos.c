/* USER CODE BEGIN Header */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "lcd.h"
#include "camera.h"
#include "delay.h"
#include "supersonic.h"
#include "utils.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */
/* Definitions for os_demorun */
osThreadId_t         os_demorunHandle;
const osThreadAttr_t os_demorun_attributes = {
    .name       = "os_demorun",
    .stack_size = 128 * 4,
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for os_supersonicTa */
osThreadId_t         os_supersonicTaHandle;
const osThreadAttr_t os_supersonicTa_attributes = {
    .name       = "os_supersonicTa",
    .stack_size = 128 * 4,
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for os_image_receiv */
osThreadId_t         os_image_receivHandle;
const osThreadAttr_t os_image_receiv_attributes = {
    .name       = "os_image_receiv",
    .stack_size = 128 * 4,
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for dma_semaphore */
osSemaphoreId_t         dma_semaphoreHandle;
const osSemaphoreAttr_t dma_semaphore_attributes = {.name = "dma_semaphore"};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void supersonicTask(void *argument);
void image_receive_start(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */
    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* USER CODE END RTOS_MUTEX */

    /* Create the semaphores(s) */
    /* creation of dma_semaphore */
    dma_semaphoreHandle = osSemaphoreNew(1, 1, &dma_semaphore_attributes);

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of os_demorun */
    //os_demorunHandle = osThreadNew(demorunTask, NULL, &os_demorun_attributes);

    /* creation of os_supersonicTa */
    os_supersonicTaHandle = osThreadNew(supersonicTask, NULL, &os_supersonicTa_attributes);

    /* creation of os_image_receiv */
    os_image_receivHandle = osThreadNew(image_receive_start, NULL, &os_image_receiv_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_demorunTask */
/* USER CODE END Header_demorunTask */


/* USER CODE BEGIN Header_supersonicTask */

/* USER CODE END Header_supersonicTask */
void supersonicTask(void *argument)
{
    /* USER CODE BEGIN supersonicTask */
    /* Infinite loop */
    for(;;)
    {
        printf("measurement distancde is %d mm\r\n", supersonic_run());
        tim6_delay_ms(500);
        osDelay(1);
    }
    /* USER CODE END supersonicTask */
}

/* USER CODE BEGIN Header_image_receive_start */
/**
 * @brief Function implementing the os_image_receiv thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_image_receive_start */
void image_receive_start(void *argument)
{
    /* USER CODE BEGIN image_receive_start */
    image_receive_init(line_mode);

    /* Infinite loop */
    for(;;)
    {
        image_receive_run();
        osDelay(1);
    }
    /* USER CODE END image_receive_start */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
