/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "AppMain.h"
#include "PowerStateMachine.h"
#include "Irqs.h"
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FORCE_RECOVERY__Pin GPIO_PIN_13
#define FORCE_RECOVERY__GPIO_Port GPIOC
#define BRD_RST__Pin GPIO_PIN_14
#define BRD_RST__GPIO_Port GPIOC
#define BRD_WAKE__Pin GPIO_PIN_15
#define BRD_WAKE__GPIO_Port GPIOC
#define SENSE_3V3_Pin GPIO_PIN_0
#define SENSE_3V3_GPIO_Port GPIOA
#define SENSE_VIN_Pin GPIO_PIN_1
#define SENSE_VIN_GPIO_Port GPIOA
#define SENSE_5V_Pin GPIO_PIN_2
#define SENSE_5V_GPIO_Port GPIOA
#define SENSE_1V8_Pin GPIO_PIN_3
#define SENSE_1V8_GPIO_Port GPIOA
#define SENSE_1V2_Pin GPIO_PIN_4
#define SENSE_1V2_GPIO_Port GPIOA
#define POWER_EN__Pin GPIO_PIN_6
#define POWER_EN__GPIO_Port GPIOA
#define SYS_RESET__Pin GPIO_PIN_7
#define SYS_RESET__GPIO_Port GPIOA
#define SYS_RESET_OUT_Pin GPIO_PIN_0
#define SYS_RESET_OUT_GPIO_Port GPIOB
#define STM32_SUSCLK_32KHZ_Pin GPIO_PIN_1
#define STM32_SUSCLK_32KHZ_GPIO_Port GPIOB
#define CARRIER_PWR_ENABLE_Pin GPIO_PIN_2
#define CARRIER_PWR_ENABLE_GPIO_Port GPIOB
#define MAIN_PWR_GOOD_Pin GPIO_PIN_10
#define MAIN_PWR_GOOD_GPIO_Port GPIOB
#define MOD_SLEEP__Pin GPIO_PIN_12
#define MOD_SLEEP__GPIO_Port GPIOB
#define ON_5V_MODULE_Pin GPIO_PIN_13
#define ON_5V_MODULE_GPIO_Port GPIOB
#define SLEEP_WAKE_Pin GPIO_PIN_14
#define SLEEP_WAKE_GPIO_Port GPIOB
#define SHUTDOWN_REQUEST__Pin GPIO_PIN_15
#define SHUTDOWN_REQUEST__GPIO_Port GPIOB
#define SEQUENCER_ACTIVE_Pin GPIO_PIN_15
#define SEQUENCER_ACTIVE_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
