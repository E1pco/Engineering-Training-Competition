#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "Delay.h"
#include "LCD.h"
#include "Motor.h"
#include "Move.h"
#include "main.h"
#include "usart.h"
#define Car_Turn_Use_IMU 1
void Control_Proc(void);
extern uint8_t Task_Num0;
extern int16_t Task_Num1;
extern int16_t Task_Num2;
extern uint8_t Running_Flag;

#endif
