#include "ALL.h"


#define OPTICAL_ENCODE_CONSTANT			200     //�������̲̿�����
//#define SPEED_CONTROL_COUNT				20  	// 20 ms * 5 ms
#define SPEED_CONTROL_PERIOD			100   // �ٶȿ�������ȡ100ms
#define SPEED_CONSTANT				1000.0/SPEED_CONTROL_PERIOD/OPTICAL_ENCODE_CONSTANT  //��λת������ֵ
//�����ٶȵ�λ�ǵ��ÿ��ת��Ȧ��
                
int Speed_Set= -15 ;//-10;
int Speed_Set_in=0;  //����Ϊ��

float Speed_Control_P=43,  Speed_Control_I=0.001;    //�ٶȿ���PI     //50
//�ٶȲ��� 43 0.001
float Speed_P=0,Speed_I=0;
float nSpeed_Left=0,nSpeed_Right=0,nSpeed=0,nSpeed_Change=0;
float Speed_Control_Integral;  //�ٶȻ���                        
float Speed_Old=0,Speed_New=0; 
int Left_Speed_Cal=0,Right_Speed_Cal=0;//�������ٶȿ��Ƽ���ֵ
int Left_Speed,Right_Speed; //���������ٶȡ������ٶ�
   

                                                           
void SpeedControl(void)     //�ٶȿ�������100ms     
{
    nSpeed_Left=Speed_Left_Get;       
    nSpeed_Right=Speed_Right_Get;
       
    nSpeed=(nSpeed_Left+nSpeed_Right)/2;     //ȡ������ƽ���ٶ�ΪС���ٶ�
    nSpeed *= SPEED_CONSTANT;
  //  nSpeed_Left=nSpeed_Right=0;
    
    nSpeed_Change=Speed_Set_in-nSpeed;
    
    Speed_P=nSpeed_Change*Speed_Control_P;
    Speed_I=nSpeed_Change*Speed_Control_I;
                                                       
    Speed_Control_Integral += Speed_I;
    
    Speed_Old=Speed_New;     
    Speed_New=Speed_P + Speed_Control_Integral;    
}        


void SpeedOutCal(void) //�ٶȵ���������20��5ms�������������~~
{
    float Speed_Out;
    Speed_Out=Speed_New-Speed_Old;
    Speed_Out=Speed_Out*(coder_finish_flag*1.0/20)+Speed_Old;
    Left_Speed_Cal=Right_Speed_Cal=Speed_Out;    
}





