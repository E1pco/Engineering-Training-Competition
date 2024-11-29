#include "IMU.h"
float Yaw;
float Last_Yaw;

uint8_t Usart2_Rx_Buffer[RXBUFFERSIZE];
uint8_t Usart2_Rx_Flag;
uint8_t Usart2_aRxBuffer[RXBUFFERSIZE];

void IMU_Init(void)
{
      // 开启串口DMA接收和IDLE空闲中断
      HAL_UART_Receive_DMA(&huart2, (uint8_t *)Usart2_aRxBuffer, RXBUFFERSIZE);
      __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
      uint8_t temp[5] = {0xFF, 0xAA, 0x76, 0x00, 0x00};
      HAL_UART_Transmit(&huart2, temp, 5, 0xffff);
}
void IMU_Proc(void)
{
      if (Usart2_Rx_Flag == 1)
      {
            Yaw = (float)(Usart2_Rx_Buffer[18] << 8 | Usart2_Rx_Buffer[17]) / 32768 * 180;
            if (Yaw - Last_Yaw > 180)
            {
                  Yaw -= 360;
            }
            else if (Yaw - Last_Yaw < -180)
            {
                  Yaw += 360;
            }
            Last_Yaw = Yaw;
            Yaw += Yaw_Compensate;
            Usart2_Rx_Flag = 0;
      }
}
