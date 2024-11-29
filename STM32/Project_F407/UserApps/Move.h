#ifndef __MOVE_H__
#define __MOVE_H__

#include "Delay.h"
#include "Motor.h"
#include "PI.h"
#include "Servo.h"
#include "main.h"
#include "tim.h"
uint8_t Get_Loads(uint8_t Dir, uint8_t From, uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);
uint8_t Put_Loads(uint8_t Dir, uint8_t Tar, uint16_t Motor_HuaGui_Speed, uint16_t Motor_HuaGui_Acc);
extern double Yaw_Compensate;

#endif
