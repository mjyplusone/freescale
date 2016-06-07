#ifndef    __PWM_H
#define    __PWM_H


void INIT_PWM(void);
void motor(int choose,int dir,int rate) ;

                  
#endif
#define Left  0
#define Front 0
//
/*
choose   =0 控制左轮  =1 控制右轮
dir      =0 为向前转  =1  为向后转
rate     占空比
*/