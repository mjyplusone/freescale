#include "ALL.h"


#define OPTICAL_ENCODE_CONSTANT			200     //光电编码盘刻槽数量
//#define SPEED_CONTROL_COUNT				20  	// 20 ms * 5 ms
#define SPEED_CONTROL_PERIOD			100   // 速度控制周期取100ms
#define SPEED_CONSTANT				1000.0/SPEED_CONTROL_PERIOD/OPTICAL_ENCODE_CONSTANT  //单位转化比例值
//定义速度单位是电机每秒转动圈数
                
int Speed_Set= -15 ;//-10;
int Speed_Set_in=0;  //负的为正

float Speed_Control_P=43,  Speed_Control_I=0.001;    //速度控制PI     //50
//速度参数 43 0.001
float Speed_P=0,Speed_I=0;
float nSpeed_Left=0,nSpeed_Right=0,nSpeed=0,nSpeed_Change=0;
float Speed_Control_Integral;  //速度积分                        
float Speed_Old=0,Speed_New=0; 
int Left_Speed_Cal=0,Right_Speed_Cal=0;//左右轮速度控制计算值
int Left_Speed,Right_Speed; //最终左轮速度、右轮速度
   

                                                           
void SpeedControl(void)     //速度控制周期100ms     
{
    nSpeed_Left=Speed_Left_Get;       
    nSpeed_Right=Speed_Right_Get;
       
    nSpeed=(nSpeed_Left+nSpeed_Right)/2;     //取左右轮平均速度为小车速度
    nSpeed *= SPEED_CONSTANT;
  //  nSpeed_Left=nSpeed_Right=0;
    
    nSpeed_Change=Speed_Set_in-nSpeed;
    
    Speed_P=nSpeed_Change*Speed_Control_P;
    Speed_I=nSpeed_Change*Speed_Control_I;
                                                       
    Speed_Control_Integral += Speed_I;
    
    Speed_Old=Speed_New;     
    Speed_New=Speed_P + Speed_Control_Integral;    
}        


void SpeedOutCal(void) //速度调整均分在20个5ms控制周期内完成~~
{
    float Speed_Out;
    Speed_Out=Speed_New-Speed_Old;
    Speed_Out=Speed_Out*(coder_finish_flag*1.0/20)+Speed_Old;
    Left_Speed_Cal=Right_Speed_Cal=Speed_Out;    
}





