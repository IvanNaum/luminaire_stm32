/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>

#include "leds.h"
#include "seven_segment.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

leds_t leds_state;

bool button_clicked = false;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    /* SysTick_IRQn interrupt configuration */
    NVIC_SetPriority(SysTick_IRQn, 3);

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    /* USER CODE BEGIN 2 */
    leds_pin_port_t leds_arr[LEDS_NUMS] = {
        {.port = LED_RED_GPIO_Port, .pin = LED_RED_Pin},
        {.port = LED_GREEN_GPIO_Port, .pin = LED_GREEN_Pin},
        {.port = LED_BLUE_GPIO_Port, .pin = LED_BLUE_Pin},
    };

    leds_init(&leds_state, leds_arr);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    // uint8_t counter = 0;

    seg_dot_disable();
    for (int i = 0; i < 2; i++) {
        LL_mDelay(500);
        seg_dot_toggle(SEG_DOT);
    }

    seg_set_digit(leds_get_current_mode(&leds_state));

    while (1) {
        if (button_clicked) {
            LL_mDelay(20);
            leds_next_mode(&leds_state);
            seg_set_digit(leds_get_current_mode(&leds_state));
            button_clicked = false;
        }
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    /* HSI configuration and activation */
    LL_RCC_HSI_Enable();
    while (LL_RCC_HSI_IsReady() != 1) {}

    /* Set AHB prescaler*/
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

    /* Sysclk activation on the HSI */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI) {}

    /* Set APB1 prescaler*/
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

    LL_Init1msTick(16000000);

    /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
    LL_SetSystemCoreClock(16000000);
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
    LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

    /**/
    LL_GPIO_ResetOutputPin(SEG_P_GPIO_Port, SEG_P_Pin);

    /**/
    LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);

    /**/
    LL_GPIO_ResetOutputPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);

    /**/
    LL_GPIO_ResetOutputPin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);

    /**/
    LL_GPIO_ResetOutputPin(SEG_C_GPIO_Port, SEG_C_Pin);

    /**/
    LL_GPIO_ResetOutputPin(SEG_E_GPIO_Port, SEG_E_Pin);

    /**/
    LL_GPIO_ResetOutputPin(SEG_D_GPIO_Port, SEG_D_Pin);

    /**/
    LL_GPIO_ResetOutputPin(SEG_F_GPIO_Port, SEG_F_Pin);

    /**/
    LL_GPIO_ResetOutputPin(SEG_G_GPIO_Port, SEG_G_Pin);

    /**/
    LL_GPIO_ResetOutputPin(SEG_A_GPIO_Port, SEG_A_Pin);

    /**/
    LL_GPIO_ResetOutputPin(SEG_B_GPIO_Port, SEG_B_Pin);

    /**/
    LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTB, LL_EXTI_CONFIG_LINE8);

    /**/
    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_8;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
    LL_EXTI_Init(&EXTI_InitStruct);

    /**/
    LL_GPIO_SetPinPull(BUTTON_GPIO_Port, BUTTON_Pin, LL_GPIO_PULL_UP);

    /**/
    LL_GPIO_SetPinMode(BUTTON_GPIO_Port, BUTTON_Pin, LL_GPIO_MODE_INPUT);

    /**/
    GPIO_InitStruct.Pin = SEG_P_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_P_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = LED_RED_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(LED_RED_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = LED_GREEN_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = LED_BLUE_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = SEG_C_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_C_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = SEG_E_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_E_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = SEG_D_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_D_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = SEG_F_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_F_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = SEG_G_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_G_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = SEG_A_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_A_GPIO_Port, &GPIO_InitStruct);

    /**/
    GPIO_InitStruct.Pin = SEG_B_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    LL_GPIO_Init(SEG_B_GPIO_Port, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    NVIC_SetPriority(EXTI4_15_IRQn, 0);
    NVIC_EnableIRQ(EXTI4_15_IRQn);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    // NVIC_DisableIRQ(EXTI4_15_IRQn);

    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {}
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
