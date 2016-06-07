#ifndef    __SPEED_H
#define    __SPEED_H


void SpeedControl(void);
void SpeedOutCal(void);


extern float Speed_P,Speed_I,nSpeed_Left,nSpeed_Right,nSpeed,nSpeed_Change;
extern float Speed_Control_Integral;  //速度积分
extern float Speed_Old,Speed_New; 
extern int Left_Speed_Cal,Right_Speed_Cal;//左右轮速度控制计算值
extern int Left_Speed,Right_Speed; //双闭环后最终左轮速度、右轮速度
extern int Speed_Set,Speed_Set_in;
extern float Speed_Control_P,  Speed_Control_I; 
#endif