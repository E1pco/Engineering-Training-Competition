#ifndef __SERVO_H__
#define __SERVO_H__

#include "Motor.h"
#include "main.h"
#include "tim.h"
typedef enum
{
      SERVO_ZaiWu = 0,
      SERVO_HuaGui,
      SERVO_JiaZhua
} Servo_t;
typedef enum
{
      ZaiWu_Mid = 0,
      ZaiWu_Left,
      ZaiWu_Right
} ZaiWu_State;
typedef enum
{
      HuaGui_IN = 0,
      HuaGui_OUT
} HuaGui_Servo_States;
typedef enum
{
      JiaZhua_Close = 0,
      JiaZhua_Open
} JiaZhua_State;
void Servo_Init(void);
void Servo_SetAngle(uint8_t servo, float angle);
uint8_t JiaZhua_Turn(JiaZhua_State state);
uint8_t HuaGui_Turn(HuaGui_Servo_States state);
uint8_t ZaiWu_Turn(ZaiWu_State state);
void Servo_CallBack(void);

#endif
