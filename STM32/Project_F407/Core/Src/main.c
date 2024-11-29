/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Control.h"
#include "Delay.h"
#include "IMU.h"
#include "LCD.h"
#include "Motor.h"
#include "Move.h"
#include "OLED.h"
#include "PI.h"
#include "Servo.h"
#include "usart.h"
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
int fputc(int ch, FILE *f)
{
      uint8_t temp[1] = {ch};
      HAL_UART_Transmit(&huart5, temp, 1, 1000);
      return ch;
}
 void Uart_Debug_Init(void)
 {
      
 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t HuaGui_Init_State = 0;
void HuaGui_Init_Proc(void)
{
      // Motor_Read_Current(5);
      if (HuaGui_Init_State == 1)
      {
            Motor_SetPosition(5, 3200, -50, 0);
            //Motor_Run();
            HuaGui_Init_State = 2;
      }
      else if (HuaGui_Init_State == 2)
      {
            Motor_Read_Current(5);
#if Serial_Debug == 1
            printf("%d\r\n", Motor_HuaGui_Current); // 200
#endif
            if (Motor_HuaGui_Current >= 520)
            {
                  HuaGui_Init_State = 3;
                  Motor_Reset(5);
                  HuaGui_JiaoZhun();
                  Servo_Init();
            }
      }
      else if (HuaGui_Init_State == 3)
      {
            if (HuaGui_Turn(HuaGui_IN) == 1)
            {
                  HuaGui_Init_State = 0;
            }
      }
}
// uint16_t Temp_Val = 90;
uint8_t Motor_State = 1;
extern uint8_t Running_Mode; // �ٶ�ģʽ
uint8_t temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
void Key_Proc(void)
{
      if (temp1 == 1)
      {
            // uint8_t temp = ZaiWu_Turn(ZaiWu_Mid);
            // if (temp == 1)
            // {
            //       temp1 = 0;
            //       temp2 = 0;
            //       temp3 = 0;
            //       temp4 = 0;
            // }
      }
      if (temp2 == 1)
      {
            // uint8_t temp = ZaiWu_Turn(ZaiWu_Left);
            // if (temp == 1)
            // {
            //       temp1 = 0;
            //       temp2 = 0;
            //       temp3 = 0;
            //       temp4 = 0;
            // }
      }
      if (temp3 == 1)
      {
            // uint8_t temp = Put_Loads(0, 0);
            // if (temp == 1)
            // {
            //       temp1 = 0;
            //       temp2 = 0;
            //       temp3 = 0;
            //       temp4 = 0;
            // }
      }
      if (temp4 == 1)
      {
            // uint8_t temp = Car_Calibration(150, 100);
            // if (temp == 1)
            // {
            //       temp1 = 0;
            //       temp2 = 0;
            //       temp3 = 0;
            //       temp4 = 0;
            // }
      }
      if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET) // �������ʹ��ʧ��
      {
            while (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET)
                  ;
            Motor_State = !Motor_State;
            if (Motor_State == 1)
            {
                  Motor_Enable_All();
            }
            else
            {
                  Motor_Disable_All();
            }
            temp1 = 1;
            temp2 = 0;
            temp3 = 0;
            temp4 = 0;
      }
      if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET) // ����������ת��
      {
            while (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET)
                  ;
            // HuaGui_Init_State = 1;
            temp1 = 0;
            temp2 = 1;
            temp3 = 0;
            temp4 = 0;
      }
      if (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET)
      {
            while (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET)
                  ;
            // Temp_Val += 5;
            Running_Mode++;
            if (Running_Mode > 3)
                  Running_Mode = 0;
            temp1 = 0;
            temp2 = 0;
            temp3 = 1;
            temp4 = 0;
      }
      if (HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin) == GPIO_PIN_RESET) // ����λ�����Ϳ�ʼ����
      {
            while (HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin) == GPIO_PIN_RESET)
                  ;
            HAL_UART_Transmit(&huart4, "99", 2, 0xffff);
#if Serial_Debug == 1
            printf("GO!!!!!\r\n");
#endif

            temp1 = 0;
            temp2 = 0;
            temp3 = 0;
            temp4 = 1;
      }
}
void OLED_Proc(void)
{
      OLED_ShowString(1, 1, "H ");
      OLED_ShowNum(1, 3, Stop_Flag_HuaGui, 1);
      OLED_ShowString(1, 5, "C ");
      OLED_ShowNum(1, 7, Stop_Flag_Car, 1);
      OLED_ShowString(1, 9, "Y ");
      OLED_ShowSignedNum(1, 11, Yaw, 3);

      OLED_ShowString(2, 1, "Task:");
      OLED_ShowNum(2, 6, Task_Num0, 2);
      OLED_ShowNum(2, 9, Running_Flag, 1);

      OLED_ShowString(3, 1, "Data:");
      OLED_ShowSignedNum(3, 6, Task_Num1, 3);
      OLED_ShowSignedNum(3, 11, Task_Num2, 3);

      OLED_ShowNum(4, 15, Running_Mode, 1);
      // OLED_ShowNum(4, 10, Temp_Val, 3);
      // Servo_SetAngle(SERVO_ZaiWu, Temp_Val);
      if (Motor_State == 1)
      {
            OLED_ShowString(4, 1, "Motor ON ");
      }
      else
      {
            OLED_ShowString(4, 1, "Motor OFF");
      }
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
      Delay_Init(168);
      OLED_Init();
      Motor_Init();
      HAL_TIM_Base_Start_IT(&htim6);
      // #if Car_Turn_Use_IMU
      IMU_Init();
// #endif
#if Serial_Debug == 1
      Uart_Debug_Init();
#endif
      PI_Init();
      LCD_Init();
      Delay_ms(1000);
      HuaGui_Init_State = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
      while (1)
      {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
            PI_Data_Receive_Proc();
            OLED_Proc();
            Key_Proc();
            Control_Proc();
            IMU_Proc();
            HuaGui_Init_Proc();
      }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
      /* User can add his own implementation to report the HAL error return state */
      __disable_irq();
      while (1)
      {
      }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
      /* User can add his own implementation to report the file name and line number,
         ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
