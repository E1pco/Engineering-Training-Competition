#include "Control.h"
#define led_debug_on  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET) // ����LED2
#define led_debug_off HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)   // Ϩ��LED2

uint8_t Task_Num0    = 0;
int16_t Task_Num1    = 0;
int16_t Task_Num2    = 0;
uint8_t Running_Flag = 0; // �������б�־λ

uint8_t Running_Mode          = 0; // �ٶ�ģʽ
uint16_t Car_Speed            = 250;
uint16_t Car_Acc              = 150;
uint16_t Car_Speed_Slow       = 150;
uint16_t Car_Acc_Slow         = 100;
uint16_t Car_Turn_Speed_Limit = 50;
uint16_t Motor_HuaGui_Speed   = 150;
uint16_t Motor_HuaGui_ACC     = 240;

uint8_t Task_Flag[100]  = {0};
int16_t Task_Data1[100] = {0};
int16_t Task_Data2[100] = {0};
extern uint8_t Car_Counter_Enable;
extern uint16_t Car_Counter_Times;
void Control_Proc(void)
{
    if (Running_Mode == 0) {
        Car_Speed            = 250;
        Car_Acc              = 150;
        Car_Speed_Slow       = 150;
        Car_Acc_Slow         = 100;
        Car_Turn_Speed_Limit = 50;
        Motor_HuaGui_Speed   = 250;
        Motor_HuaGui_ACC     = 230;
    } else if (Running_Mode == 1) {
        Car_Speed            = 280;
        Car_Acc              = 180;
        Car_Speed_Slow       = 150;
        Car_Acc_Slow         = 100;
        Car_Turn_Speed_Limit = 55;
        Motor_HuaGui_Speed   = 250;
        Motor_HuaGui_ACC     = 230;
    } else if (Running_Mode == 2) {
        Car_Speed            = 300;
        Car_Acc              = 210;
        Car_Speed_Slow       = 150;
        Car_Acc_Slow         = 100;
        Car_Turn_Speed_Limit = 60;
        Motor_HuaGui_Speed   = 250;
        Motor_HuaGui_ACC     = 230;
    } else if (Running_Mode == 3) {
        Car_Speed            = 320;
        Car_Acc              = 210;
        Car_Speed_Slow       = 180;
        Car_Acc_Slow         = 110;
        Car_Turn_Speed_Limit = 65;
        Motor_HuaGui_Speed   = 260;
        Motor_HuaGui_ACC     = 235;
    }
    if (PI_Data0 != 0) {
        Task_Flag[PI_Data0]  = 1;
        Task_Data1[PI_Data0] = PI_Data1;
        Task_Data2[PI_Data0] = PI_Data2;
        Task_Num0            = PI_Data0;
        Task_Num1            = PI_Data1;
        Task_Num2            = PI_Data2;

        PI_Data0     = 0;
        PI_Data1     = 0;
        PI_Data2     = 0;
        Running_Flag = 1;
    }
    if (Task_Flag[1]) // С���ƶ���x��y��
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        static uint8_t temp = 0;
        Car_Counter_Times   = 1000;

        if (temp == 0) {
            Car_Go_Target(Task_Data1[1] * 128, Task_Data2[1] * 128, Car_Speed, Car_Acc);
            Car_Counter_Enable = 1;
            temp               = 1;
        } else if (temp == 1) {
            if (Stop_Flag_Car == 1 || Car_Counter_Enable == 0) {
                Car_Counter_Enable = 0;
                temp               = 0;
                Task_Flag[1]       = 0;
                HAL_UART_Transmit_DMA(&huart4, "01", 2);

                printf("Task 1 End\r\n");

                // Delay_ms(20);
                // HAL_UART_Transmit(&huart4, "01", 2, 0xffff);

                Running_Flag = 0;
                led_debug_off; // Ϩ��LED2
            }
        }
    }
    if (Task_Flag[2]) // С��ת��
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        static uint8_t temp = 0;
        if (temp == 0) {
            if (Car_Turn(Task_Data1[2], Car_Turn_Speed_Limit, Car_Acc_Slow) == 1)
                temp = 1;
        } else if (temp == 1) {
            temp         = 0;
            Task_Flag[2] = 0;
            HAL_UART_Transmit_DMA(&huart4, "02", 2);
#if Serial_Debug == 1
            printf("Task 2 End\r\n");
#endif
            // Delay_ms(20);
            // HAL_UART_Transmit(&huart4, "02", 2, 0xffff);

            Running_Flag = 0;
            led_debug_off; // Ϩ��LED2
        }
    }
    if (Task_Flag[3]) // ���������ƶ�
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        static uint8_t temp       = 0;
        static uint8_t Last_Data1 = 0;
        if (temp == 0) {
            switch (Task_Data1[3]) {
                case 0:
                    HuaGui_UP(Motor_HuaGui_Speed, Motor_HuaGui_ACC);
                    break;
                case 1:
                    HuaGui_DOWN(Motor_HuaGui_Speed, Motor_HuaGui_ACC);
                    break;
                default:
                    break;
            }
            Last_Data1 = Task_Data1[3];
            temp       = 1;
        } else if (temp == 1) {
            if (Task_Data1[3] != Last_Data1) {
                switch (Task_Data1[3]) {
                    case 0:
                        HuaGui_UP(Motor_HuaGui_Speed, Motor_HuaGui_ACC);
                        break;
                    case 1:
                        HuaGui_DOWN(Motor_HuaGui_Speed, Motor_HuaGui_ACC);
                        break;
                    default:
                        break;
                }
                Last_Data1 = Task_Data1[3];
            }
            if (Stop_Flag_HuaGui == 1) {
                temp         = 0;
                Task_Flag[3] = 0;
                HAL_UART_Transmit_DMA(&huart4, "03", 2);
#if Serial_Debug == 1
                printf("Task 3 End\r\n");
#endif
                // Delay_ms(20);
                // HAL_UART_Transmit(&huart4, "03", 2, 0xffff);

                Running_Flag = 0;
                Last_Data1   = 0;
                led_debug_off; // Ϩ��LED2
            }
        }
    }
    if (Task_Flag[4]) // ����������ת
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        static uint8_t temp = 0;
        if (temp == 0) {
            if (Task_Data1[4] == 0) {
                if (HuaGui_Turn(HuaGui_IN) == 1) {
                    temp = 1;
                }
            } else if (Task_Data1[4] == 1) {
                if (HuaGui_Turn(HuaGui_OUT) == 1) {
                    temp = 1;
                }
            }
        } else if (temp == 1) {
            temp         = 0;
            Task_Flag[4] = 0;
            HAL_UART_Transmit_DMA(&huart4, "04", 2);
#if Serial_Debug == 1
            printf("Task 4 End\r\n");
#endif
            // Delay_ms(20);
            // HAL_UART_Transmit(&huart4, "04", 2, 0xffff);

            Running_Flag = 0;
            led_debug_off; // Ϩ��LED2
        }
    }
    if (Task_Flag[5]) // ȡ����
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        static uint8_t temp  = 0;
        static uint8_t temp1 = 0;
        static uint8_t temp2 = 0;
        temp1                = Task_Data1[5];
        temp2                = Task_Data2[5];
        if (temp == 0) {
            uint8_t temp_state = Get_Loads(temp1, temp2, Motor_HuaGui_Speed, Motor_HuaGui_ACC);
            if (temp_state == 1) {
                temp = 1;
            } else if (temp_state == 2) {
                HAL_UART_Transmit_DMA(&huart4, "95", 2);
            } else if (temp_state == 3) {
                HAL_UART_Transmit_DMA(&huart4, "85", 2);
            }
        } else if (temp == 1) {
            temp         = 0;
            temp1        = 0;
            temp2        = 0;
            Task_Flag[5] = 0;
            HAL_UART_Transmit_DMA(&huart4, "05", 2);
#if Serial_Debug == 1
            printf("Task 5 End\r\n");
#endif
            // Delay_ms(20);
            // HAL_UART_Transmit(&huart4, "05", 2, 0xffff);

            Running_Flag = 0;
            led_debug_off; // Ϩ��LED2
        }
    }
    if (Task_Flag[6]) // ��������
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        static uint8_t temp  = 0;
        static uint8_t temp1 = 0;
        static uint8_t temp2 = 0;
        temp1                = Task_Data1[6];
        temp2                = Task_Data2[6];
        if (temp == 0) {
            uint8_t temp_state = Put_Loads(temp1, temp2, Motor_HuaGui_Speed, Motor_HuaGui_ACC);
            if (temp_state == 1) {
                temp = 1;
            } else if (temp_state == 2) {
                HAL_UART_Transmit_DMA(&huart4, "96", 2);
            }
        } else if (temp == 1) {
            temp         = 0;
            temp1        = 0;
            temp2        = 0;
            Task_Flag[6] = 0;
            HAL_UART_Transmit_DMA(&huart4, "06", 2);
            led_debug_off;
#if Serial_Debug == 1
            printf("Task 6 End\r\n");
#endif
            // Delay_ms(20);
            // HAL_UART_Transmit(&huart4, "06", 2, 0xffff);

            Running_Flag = 0;
        }
    }
    if (Task_Flag[7]) // ����ǶȻ���
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        uint8_t temp = Car_Calibration(Car_Speed_Slow, Car_Acc_Slow);
        if (temp == 1) {
            Task_Flag[7] = 0;
            HAL_UART_Transmit_DMA(&huart4, "07", 2);
            led_debug_off;
#if Serial_Debug == 1
            printf("Task 7 End\r\n");
#endif
            // Delay_ms(20);
            // HAL_UART_Transmit(&huart4, "07", 2, 0xffff);

            Running_Flag = 0;
        }
    }
    if (Task_Flag[8]) // LCD���������
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        LCD_SendData(Task_Data1[8], Task_Data2[8]);
        Delay_ms(50);
        LCD_SendData(Task_Data1[8], Task_Data2[8]);

        Task_Flag[8] = 0;
        HAL_UART_Transmit_DMA(&huart4, "08", 2);
#if Serial_Debug == 1
        printf("Task 8 End\r\n");
#endif
        // Delay_ms(20);
        // HAL_UART_Transmit(&huart4, "08", 2, 0xffff);

        Running_Flag = 0;
        led_debug_off; // Ϩ��LED2
    }
    if (Task_Flag[9]) // С���ƶ����ף�x��y��
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        static uint8_t temp = 0;
        if (Task_Data1[9] <= 5 && Task_Data2[9] <= 5) {
            Car_Counter_Times = 150;
        } else {
            Car_Counter_Times = 400;
        }
        if (temp == 0) {
            Car_Go_Target(Task_Data1[9] * 13, Task_Data2[9] * 13, Car_Speed_Slow, Car_Acc_Slow);
            temp               = 1;
            Car_Counter_Enable = 1;
        } else if (temp == 1) {
            if (Stop_Flag_Car == 1 || Car_Counter_Enable == 0) {
                Car_Counter_Enable = 0;
                temp               = 0;
                Task_Flag[9]       = 0;
                HAL_UART_Transmit_DMA(&huart4, "09", 2);
#if Serial_Debug == 1
                printf("Task 9 End\r\n");
#endif
                // Delay_ms(20);
                // HAL_UART_Transmit(&huart4, "09", 2, 0xffff);

                Running_Flag = 0;
                led_debug_off; // Ϩ��LED2
            }
        }
    }
    if (Task_Flag[10]) // ������10
    {
        Servo_Init();                                        // ��ʼ�����
        Delay_ms(1000);                                      // ��ʱ1��
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 10000); // ����TIM3ͨ��1��CCRֵΪ1
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 10000); // ����TIM3ͨ��1��CCRֵΪ1
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 10000); // ����TIM3ͨ��1��CCRֵΪ1

        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        HAL_UART_Transmit_DMA(&huart4, "10", 2);                     // ͨ��UART������������Ϣ

        Task_Flag[10] = 0; // ִ�к����������־
#if Serial_Debug == 1
        printf("Task 10 End\r\n");
#endif
        // Delay_ms(20);
        // HAL_UART_Transmit(&huart4, "10", 2, 0xffff);

        Running_Flag = 0; // �������б�־
        led_debug_off;    // Ϩ��LED2
    }

    if (Task_Flag[11]) // ������11
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED2
        HAL_UART_Transmit_DMA(&huart4, "11", 2);                     // ͨ��UART���������
        HuaGui_JiaoZhun();
        HAL_Delay(1000);
        // �������죬������ָ��λ��
        // HuaGui_UP(Motor_HuaGui_Speed, Motor_HuaGui_ACC);

        Task_Flag[11] = 0; // ִ�к����������־

#if Serial_Debug == 1
        printf("Task 11 End\r\n");
#endif

        Running_Flag = 0; // �������б�־
        led_debug_off;    // Ϩ��LED2
    }

    if (Task_Flag[12]) // ������12
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED3
        HAL_UART_Transmit_DMA(&huart4, "12", 2);                     // ͨ��UART���������

        // ���������½������¶�ȡ��λ��
        HuaGui_DOWN(Task_Data1[12], Task_Data2[12]);
        Task_Data1[12] = 0;
        Task_Data2[12] = 0;
        Task_Flag[12]  = 0; // ִ�к����������־

#if Serial_Debug == 1
        printf("Task 12 End\r\n");
#endif

        Running_Flag = 0; // �������б�־
        led_debug_off;    // Ϩ��LED3
    }

    if (Task_Flag[13]) // ������13
    {
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); // ����LED4
        HAL_UART_Transmit_DMA(&huart4, "13", 2);                     // ͨ��UART���������

        // ���������ƶ�������̨�ķ���λ��
        HuaGui_Fang(Task_Data1[13], Task_Data2[13]);

        Task_Flag[13] = 0; // ִ�к����������־

#if Serial_Debug == 1
        printf("Task 13 End\r\n");
#endif

        Running_Flag = 0; // �������б�־
        led_debug_off;    // Ϩ��LED4
    }
    if (Task_Flag[14]) // ������14
    {
        led_debug_on;
        HAL_UART_Transmit_DMA(&huart4, "14", 2); // ͨ��UART���������

        // ���������½������¶�ȡ��λ��
        HuaGui_Fang(Task_Data1[14], Task_Data2[14]);
        Task_Data1[14] = 0;
        Task_Data2[14] = 0;
        Task_Flag[14]  = 0; // ִ�к����������־

#if Serial_Debug == 1
        printf("Task 14 End\r\n");
#endif

        Running_Flag = 0; // �������б�־
        led_debug_off;
    }
    if (Task_Flag[15]) // ������15
    {
        led_debug_on;
        HAL_UART_Transmit_DMA(&huart4, "15", 2); // ͨ��UART���������

        HuaGui_Qu(Task_Data1[15], Task_Data2[15]);
        Task_Data1[15] = 0;
        Task_Data2[15] = 0;
        Task_Flag[15]  = 0; // ִ�к����������־

#if Serial_Debug == 1
        printf("Task 15 End\r\n");
#endif

        Running_Flag = 0; // �������б�־
        led_debug_off;
    }
}