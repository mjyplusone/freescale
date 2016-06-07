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


extern int CCD_L_trigger , CCD_H_trigger ; //上下CCD扫线阀值

//障碍
extern int CCD_obstacle_trigger ;    //障碍扫线 阀值 
extern int CCD_obstacle_pianyi  ;    //障碍     偏移距离
extern int CCD_obstacle_over_1  ;    //减缓转弯便宜 的 时间
extern int CCD_obstacle_over_2  ;    //结束障碍模式 的 时间

//十字弯
extern int cross_flag_trigger ;                 //产生十字弯进弯标志所需 平均像素大小
extern int cross_time_1;
extern int cross_time_2;

//直角弯
extern int Right_Angle_Left_juli , Right_Angle_Right_juli ;  //左右转直角弯滞后距离  越大离直角弯越近
extern int Right_Angle_Left_r    , Right_Angle_Right_r    ;  //左右转直角弯转弯半径  越大转弯半径越大



#endif