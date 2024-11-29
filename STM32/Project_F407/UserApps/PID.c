#include "PID.h"
#include "OLED.h"
/**************************PID******************************/
// λ��ʽPID
//  ��ʼ��PID�������
void PID_Init(PID_TypeDef *PID)
{
      PID->Enable = 0;
      PID->Target_value = 0.0;
      PID->Current_value = 0.0;
      PID->Err = 0.0;
      PID->Last_Err = 0.0;
      PID->Output = 0.0;
      PID->integral = 0.0;
      PID->Kp = 0.0;
      PID->Ki = 0.0;
      PID->Kd = 0.0;
      PID->OutPut_Limit = 7200;
}
void Set_PID(PID_TypeDef *PID, float Kp, float Ki, float Kd)
{
      PID->Kp = Kp;
      PID->Ki = Ki;
      PID->Kd = Kd;
}
void Set_PID_Target(PID_TypeDef *PID, float Target)
{
      PID->Target_value = Target;
}
float Get_PID_Target(PID_TypeDef *PID)
{
      return PID->Target_value;
}
void PID_Turn(PID_TypeDef *PID, uint8_t STATE)
{
      if (STATE)
            PID->Enable = 1;
      else
            PID->Enable = 0;
}
/*
float PID_Operation(float Current, PID_TypeDef *PID)// PID����
{
      if (PID->Enable == 1)
      {
            PID->Current_value = Current;
            PID->Err = PID->Target_value - PID->Current_value; // ����ƫ����

            if ((PID->Err >= -1) && (PID->Err <= 1)) // ���ñջ�����
                  PID->Err = 0;

            if ((PID->Err <= -1) || (PID->Err >= 1)) // ���û��ַ���
                  PID->integral += PID->Err;

            if (PID->integral >= 1000) // ���û����޷�
            {
                  PID->integral = 1000;
            }
            else if (PID->integral < -1000)
            {
                  PID->integral = -1000;
            }
            // PID����
            PID->Output = PID->Kp * PID->Err + PID->Ki * PID->integral + PID->Kd * (PID->Err - PID->Last_Err);

            PID->Last_Err = PID->Err;     // �������

            if (PID->Output > PID->OutPut_Limit) // ��������޷�
                  PID->Output = PID->OutPut_Limit;
            if (PID->Output < -PID->OutPut_Limit)
                  PID->Output = -PID->OutPut_Limit;

            return PID->Output; // ���ص�ǰֵ
      }
      else
      {
            PID->Err = 0;
            PID->Last_Err = 0;
            PID->integral = 0;
            PID->Output = 0;
            return 0;
      }
}
*/
float PID_Speed_Cal(float Current, PID_TypeDef *PID)
{
      if (PID->Enable == 1)
      {
            PID->Current_value = Current;
            PID->Err = PID->Target_value - PID->Current_value; // ����ƫ����

            if ((PID->Err >= -1) && (PID->Err <= 1)) // ���ñջ�����
                  PID->Err = 0;
            if ((PID->Err <= -1) || (PID->Err >= 1)) // ���û��ַ���
                  PID->integral += PID->Err;

            if (PID->integral >= 3000) // ���û����޷�
            {
                  PID->integral = 3000;
            }
            else if (PID->integral < -3000)
            {
                  PID->integral = -3000;
            }
            // PID����
            PID->Output = PID->Kp * PID->Err + PID->Ki * PID->integral;

            PID->Last_Err = PID->Err; // �������

            if (PID->Output > PID->OutPut_Limit) // ��������޷�
                  PID->Output = PID->OutPut_Limit;
            if (PID->Output < -PID->OutPut_Limit)
                  PID->Output = -PID->OutPut_Limit;

            return PID->Output; // ���ص�ǰֵ
      }
      else
      {
            PID->Err = 0;
            PID->Last_Err = 0;
            PID->Output = 0;
            return 0;
      }
}

float PID_Xunji_Cal(float Current, PID_TypeDef *PID) // PID����
{
      if (PID->Enable == 1)
      {
            PID->Current_value = Current;
            PID->Err = PID->Current_value - PID->Target_value; // ����ƫ����

            if ((PID->Err >= -3) && (PID->Err <= 3)) // ���ñջ�����
                  PID->Err = 0;

            // if ((PID->Err <= -1) || (PID->Err >= 1)) // ���û��ַ���
            //       PID->integral += PID->Err;

            // if (PID->integral >= 1000) // ���û����޷�
            // {
            //       PID->integral = 1000;
            // }
            // else if (PID->integral < -1000)
            // {
            //       PID->integral = -1000;
            // }
            // PID����
            PID->Output = PID->Kp * PID->Err + PID->Ki * PID->integral + PID->Kd * (PID->Err - PID->Last_Err);

            PID->Last_Err = PID->Err; // �������

            if (PID->Output > PID->OutPut_Limit) // ��������޷�
                  PID->Output = PID->OutPut_Limit;
            if (PID->Output < -PID->OutPut_Limit)
                  PID->Output = -PID->OutPut_Limit;

            return PID->Output; // ���ص�ǰֵ
      }
      else
      {
            PID->Err = 0;
            PID->Last_Err = 0;
            PID->integral = 0;
            PID->Output = 0;
            return 0;
      }
}

// λ�û�PIDʵ��
float PID_Position_Cal(float Current, PID_TypeDef *PID)
{
      if (PID->Enable == 1)
      {
            PID->Current_value = Current;
            PID->Err = PID->Target_value - PID->Current_value; // ����ƫ����

            if ((PID->Err >= -10) && (PID->Err <= 10)) // ���ñջ�����
                  PID->Err = 0;

            PID->Output = PID->Kp * PID->Err + PID->Kd * (PID->Err - PID->Last_Err);

            PID->Last_Err = PID->Err; // �������

            if (PID->Output > PID->OutPut_Limit) // ��������޷�
                  PID->Output = PID->OutPut_Limit;
            if (PID->Output < -PID->OutPut_Limit)
                  PID->Output = -PID->OutPut_Limit;

            return PID->Output; // ���ص�ǰֵ
      }
      else
      {
            PID->Err = 0;
            PID->Output = 0;
            return 0;
      }
}
