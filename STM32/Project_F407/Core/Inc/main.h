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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define Serial_Debug 1
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M2_EN_Pin GPIO_PIN_2
#define M2_EN_GPIO_Port GPIOE
#define M2_DIR_Pin GPIO_PIN_3
#define M2_DIR_GPIO_Port GPIOE
#define M3_EN_Pin GPIO_PIN_4
#define M3_EN_GPIO_Port GPIOE
#define M3_DIR_Pin GPIO_PIN_5
#define M3_DIR_GPIO_Port GPIOE
#define M4_EN_Pin GPIO_PIN_6
#define M4_EN_GPIO_Port GPIOE
#define BUZ_Pin GPIO_PIN_0
#define BUZ_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOF
#define KEY4_Pin GPIO_PIN_3
#define KEY4_GPIO_Port GPIOF
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOF
#define KEY2_Pin GPIO_PIN_5
#define KEY2_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_6
#define KEY1_GPIO_Port GPIOF
#define PI1_Pin GPIO_PIN_7
#define PI1_GPIO_Port GPIOF
#define PI2_Pin GPIO_PIN_8
#define PI2_GPIO_Port GPIOF
#define PI3_Pin GPIO_PIN_9
#define PI3_GPIO_Port GPIOF
#define M4_DIR_Pin GPIO_PIN_7
#define M4_DIR_GPIO_Port GPIOE
#define M1_STP_Pin GPIO_PIN_9
#define M1_STP_GPIO_Port GPIOE
#define M2_STP_Pin GPIO_PIN_11
#define M2_STP_GPIO_Port GPIOE
#define M3_STP_Pin GPIO_PIN_13
#define M3_STP_GPIO_Port GPIOE
#define M4_STP_Pin GPIO_PIN_14
#define M4_STP_GPIO_Port GPIOE
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB
#define M1_EN_Pin GPIO_PIN_0
#define M1_EN_GPIO_Port GPIOE
#define M1_DIR_Pin GPIO_PIN_1
#define M1_DIR_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
