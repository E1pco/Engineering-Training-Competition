#ifndef __PID_H__
#define __PID_H__
#include "main.h"
typedef struct
{
      uint8_t Enable;
      float Target_value;  // Ŀ��ֵ
      float Current_value; // ��ǰֵ
      float Err;           // Ŀǰ���
      float Last_Err;      // ��һ�����
      float Kp, Ki, Kd;    // �������������ֳ�����΢�ֳ���
      float Output;        // PID�����ͨ����Ϊ����ִ�����ı���
      float integral;      // ����ֵ
      float OutPut_Limit;
} PID_TypeDef;
void PID_Init(PID_TypeDef *PID);
float PID_Speed_Cal(float Current, PID_TypeDef *PID);
float PID_Position_Cal(float Current, PID_TypeDef *PID);
float PID_Xunji_Cal(float Current, PID_TypeDef *PID); // PID����

void Set_PID(PID_TypeDef *PID, float Kp, float Ki, float Kd);
void Set_PID_Target(PID_TypeDef *PID, float Target);
float Get_PID_Target(PID_TypeDef *PID);
void PID_Turn(PID_TypeDef *PID, uint8_t STATE);

#endif
