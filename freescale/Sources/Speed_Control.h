#ifndef    __SPEED_H
#define    __SPEED_H


void SpeedControl(void);
void SpeedOutCal(void);


extern float Speed_P,Speed_I,nSpeed_Left,nSpeed_Right,nSpeed,nSpeed_Change;
extern float Speed_Control_Integral;  //�ٶȻ���
extern float Speed_Old,Speed_New; 
extern int Left_Speed_Cal,Right_Speed_Cal;//�������ٶȿ��Ƽ���ֵ
extern int Left_Speed,Right_Speed; //˫�ջ������������ٶȡ������ٶ�
extern int Speed_Set,Speed_Set_in;
extern float Speed_Control_P,  Speed_Control_I; 
#endif