#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "Control.h"
#include "Delay.h"
#include "IMU.h"
#include "OLED.h"
#include "PI.h"
#include "main.h"
#include "usart.h"
#include <math.h>
extern uint8_t uart1_rxbuff;
extern uint8_t Stop_Flag_Car;
extern uint16_t RxBuffer1[10];
extern uint8_t Stop_Flag_HuaGui;
extern uint16_t Motor_HuaGui_Current;

void Motor_Init(void);
void Motor_Reset(uint8_t Motor_Num);
void Motor_Enable(uint8_t Motor_Num);
void Motor_Disable(uint8_t Motor_Num);
void Motor_Enable_All(void);
void Motor_Disable_All(void);
void Motor_Set_PID(uint8_t Motor_Num, uint32_t KP, uint32_t KI, uint32_t KD);
void Motor_Read_Current(uint8_t Motor_Num);

void Motor_SetSpeed(uint8_t Motor_Num, int16_t Speed, uint8_t Acc);
void Motor_SetPosition(uint8_t Motor_Num, uint32_t Pulse, int16_t Speed, uint8_t Acc);
void Motor_SetPosition_A(uint8_t Motor_Num, uint32_t Pulse, int16_t Speed, uint8_t Acc);

void Motor_Receive_Data(uint8_t com_data);
void Motor_Run(void);
void Car_Go(int16_t Angle, int16_t Speed, int32_t Distance, uint16_t Car_ACC);
void Car_Go_Target(int32_t Tar_X, int32_t Tar_Y, int16_t Speed, uint16_t Car_ACC);
void Car_Go_Target_A(int32_t Tar_X, int32_t Tar_Y, int16_t Speed, uint16_t Car_ACC);
void Car_Clear(void);
uint8_t Car_Turn(int16_t Tar_Yaw, uint16_t Speed_Limit, uint16_t Car_ACC);
uint8_t Car_Calibration(uint16_t Speed_Limit, uint16_t Car_ACC);

void HuaGui_UP(uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);
void HuaGui_DOWN(uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);
void HuaGui_Fang(uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);
void HuaGui_Qu(uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);
void HuaGui_DOWN2(uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);
void HuaGui_ZhuanPan(uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);

extern uint8_t HuaGui_Motor_State;
void HuaGui_JiaoZhun(void);

typedef enum
{
      HuaGui_Motor_State_UP = 0, // 最高零点位置
      HuaGui_Motor_State_Fang,   // 向载物台放置物块位置
      HuaGui_Motor_State_Qu,     // 从载物台取物块位置
      HuaGui_Motor_State_DOWN2,  // 第二层取物位置
      HuaGui_Motor_State_DOWN,   // 最低取放物位置
      HuaGui_Motor_State_ZhuanPan
} Motor_HuaGui_States;

#endif
