#ifndef    __LINE_H
#define    __LINE_H

void Check_Line_L(void);
void Check_Line_H(void);
unsigned char abs_mi(unsigned char mi_a,unsigned char mi_b); 
void Start(void); 

extern int Center_Line;
extern int Left_Line_new,Right_Line_new;
extern float Center_Line_transform,Center_Line_transform_old,Center_Line_transform_new;

extern int Left_Line_H,Right_Line_H,Center_Line_H;

extern int cross_flag,obstacle_flag,Right_Angle_flag;
extern int Center_Line_obstacle;
//extern int change_P;

extern int Delay_Right_Angle;
extern int delay1;
extern int CCD_obstacle_over_2;
//extern int Zhangai_flag;
//extern int Delay_Zhangai;


extern int CCD_L_trigger , CCD_H_trigger ; //����CCDɨ�߷�ֵ

//�ϰ�
extern int CCD_obstacle_trigger ;    //�ϰ�ɨ�� ��ֵ 
extern int CCD_obstacle_pianyi  ;    //�ϰ�     ƫ�ƾ���
extern int CCD_obstacle_over_1  ;    //����ת����� �� ʱ��
extern int CCD_obstacle_over_2  ;    //�����ϰ�ģʽ �� ʱ��

//ʮ����
extern int cross_flag_trigger ;                 //����ʮ��������־���� ƽ�����ش�С
extern int cross_time_1;
extern int cross_time_2;

//ֱ����
extern int Right_Angle_Left_juli , Right_Angle_Right_juli ;  //����תֱ�����ͺ����  Խ����ֱ����Խ��
extern int Right_Angle_Left_r    , Right_Angle_Right_r    ;  //����תֱ����ת��뾶  Խ��ת��뾶Խ��



#endif