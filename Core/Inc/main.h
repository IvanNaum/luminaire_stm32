/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_utils.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_Pin LL_GPIO_PIN_8
#define BUTTON_GPIO_Port GPIOB
#define BUTTON_EXTI_IRQn EXTI4_15_IRQn
#define SEG_P_Pin LL_GPIO_PIN_0
#define SEG_P_GPIO_Port GPIOA
#define LED_RED_Pin LL_GPIO_PIN_1
#define LED_RED_GPIO_Port GPIOA
#define LED_GREEN_Pin LL_GPIO_PIN_2
#define LED_GREEN_GPIO_Port GPIOA
#define LED_BLUE_Pin LL_GPIO_PIN_3
#define LED_BLUE_GPIO_Port GPIOA
#define SEG_C_Pin LL_GPIO_PIN_4
#define SEG_C_GPIO_Port GPIOA
#define SEG_E_Pin LL_GPIO_PIN_5
#define SEG_E_GPIO_Port GPIOA
#define SEG_D_Pin LL_GPIO_PIN_6
#define SEG_D_GPIO_Port GPIOA
#define SEG_F_Pin LL_GPIO_PIN_7
#define SEG_F_GPIO_Port GPIOA
#define SEG_G_Pin LL_GPIO_PIN_2
#define SEG_G_GPIO_Port GPIOB
#define SEG_A_Pin LL_GPIO_PIN_11
#define SEG_A_GPIO_Port GPIOA
#define SEG_B_Pin LL_GPIO_PIN_12
#define SEG_B_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define SEG_GPIO_Port GPIOA
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
