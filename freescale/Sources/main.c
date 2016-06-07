#include "ALL.h"


#define Left_Dir   PTH_PTH6       //Left:正转1，反转0
#define Right_Dir  PTH_PTH7       //Right:正转0，反转1


int  coder_right_cnt  = 0  ,  coder_left_cnt  = 0;
int  coder_finish_flag = 0 ;
int timer5ms;
int Speed_Left_Get, Speed_Right_Get;

int Start_time_count = 0 , Direction_piece_flag = 0;//,time_flag2;

char ee[2];
int S_flag = 0;

int boma_1,boma_2,boma_3,boma_4;

int Stop_enable_flag = 1 , Start_delay_flag = 0;           

void Boma_Change(void);
                

void main(void) 
{                               
    //unsigned char temp[4],tem;

     DisableInterrupts;   

     INIT_PLL();                   
                         
     INIT_SCI();    
     
     INIT_PWM();
     
     ECT_Init();
     
     LCD_Init();
         
     InitMPU6050(); //初始化MPU6050 
     
     INIT_PIT();
     
     AD_Init();

     INIT_CCD();//包含起跑检测初始化
     
     INIT_Key();//包含拨码开关设置的模式 检测
     
     
     LCD_WrCmd(0xc0); //OLED图像上下反转
     
     
     Get_Gyro_Zero() ;
  // Get_Gravity_Zero();
  
 //    if(Boma_1==0){PIEJ_PIEJ0 = 0 ;PIEJ_PIEJ1 = 0;} //默认打开起跑检测模式，如果拨码开关1在右侧，则关闭起跑检测
     
     Boma_Change();//根据拨码开关改变速度控制
   
     EnableInterrupts;
                                             
  //   SCI_Send("Car Starts\n");  
  
  //   Get_MMA7361();          
  
     while(1) 
     {
          
          Angle_Calcu(); 
      //  SCI_Control(); 
          
          Key_Oled();
          
      /*  if(Boma_1==1)boma_1++;
          if(Boma_2==1)boma_2++;
          if(Boma_3==1)boma_3++;
          if(Boma_4==1)boma_4++; 
       */
       
     }
                       
}
void Boma_Change() 
{
  
     if(Boma_1==1)// 12
     {
        Speed_Set = -12;  //速度设定
        Direction_P=49;  //方向控制参数
        Direction_D=36; 
        
        //障碍
        CCD_obstacle_pianyi  = 4 ;    //障碍     偏移距离        4
        CCD_obstacle_over_1  = 4 ;    //减缓转弯便宜 的 时间     3
        CCD_obstacle_over_2  = 11 ;    //结束障碍模式 的 时间     7

        //十字弯
     //   cross_flag_trigger = 70;                 //产生十字弯进弯标志所需 平均像素大小

        //直角弯                 //9
        Right_Angle_Left_juli = 14 , Right_Angle_Right_juli = 14;  //左右转直角弯滞后距离  越大离直角弯越近
        Right_Angle_Left_r    = 23 , Right_Angle_Right_r   = 23;  //左右转直角弯转弯半径  越大转弯半径越大

     }
     
     if(Boma_2==1)// 15     7.86V
     {
        Speed_Set = -15;   
        Direction_P=50;  //方向控制参数
        Direction_D=42;
        
        //障碍 
        CCD_obstacle_pianyi  = 5 ;    //障碍     偏移距离       4    5
        CCD_obstacle_over_1  = 7 ;    //减缓转弯便宜 的 时间    4    6
        CCD_obstacle_over_2  = 11 ;    //结束障碍模式 的 时间   8    10

        //十字弯
        // cross_flag_trigger = 70; //产生十字弯进弯标志所需 平均像素大小

        //直角弯
        Right_Angle_Left_juli = 9 , Right_Angle_Right_juli = 9 ;  //左右转直角弯滞后距离  越大离直角弯越近
        Right_Angle_Left_r    = 20 , Right_Angle_Right_r   = 18;  //左右转直角弯转弯半径  越大转弯半径越大

     }
     

     if(Boma_3==1)//起跑和停车检测都不进行   延迟 4 S 发车
     {
        /* PIEJ_PIEJ0 = 0 ;PIEJ_PIEJ1 = 0; //关闭 红外接收 
         
         Start_delay_flag = 1; //延迟发车标志位         */
         
          // 17 内容


        Speed_Set = -17;
        Direction_P=52;  //方向控制参数
        Direction_D=44; 
        
        //障碍
        CCD_obstacle_pianyi  = 5 ;    //障碍     偏移距离
        CCD_obstacle_over_1  = 6 ;    //减缓转弯便宜 的 时间
        CCD_obstacle_over_2  = 10 ;    //结束障碍模式 的 时间

        //十字弯
     //   cross_flag_trigger = 70;                 //产生十字弯进弯标志所需 平均像素大小

        //直角弯
        Right_Angle_Left_juli = 9, Right_Angle_Right_juli = 9 ;  //左右转直角弯滞后距离  越大离直角弯越近
        Right_Angle_Left_r    = 15 , Right_Angle_Right_r   = 17;  //左右转直角弯转弯半径  越大转弯半径越大


         
     }
     
     else if(Boma_4==1)//不进行停车检测  只进行起跑检测
     {
         Stop_enable_flag = 0;
     }
     
     
     
}   


          
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 67 Timer_5ms() 
{
    DisableInterrupts;
    
    timer5ms++;
    
    
    Kalman_Filter(Angle_ax,Gyro_y);
    
   // Angle_Control();

   
 // { 编码器测速
    if( PTH_PTH4 == 0)   {coder_right_cnt += PACNT; PTH_PTH4  = 1;} 
    else                 {coder_left_cnt  += PACNT; PTH_PTH4  = 0;}
    //切换编码器             
    PACNT = 0;  
    coder_finish_flag++;
  //}
  
  
    if(coder_finish_flag==20) 
    {
        //Left:正转1，反转0  Right:正转0，反转1
        if(Left_Dir==0)  Speed_Left_Get=-coder_left_cnt;
        else             Speed_Left_Get=coder_left_cnt;
        if(Right_Dir==1) Speed_Right_Get=-coder_right_cnt;
        else             Speed_Right_Get=coder_right_cnt;
        
      
        
        if(Speed_Control_Integral>=100)
            Speed_Control_Integral=100;      //积分限幅
        
        coder_left_cnt=0;
        coder_right_cnt=0;
                                     
        Start();  
        SpeedControl();
         
        coder_finish_flag=0; 
        
        if(S_flag >= 4)
         {
             if(Speed_Set_in ==0)Start_time_count = 0;//若实际设定速度较小，则认为处于发车状态中
             else if(Speed_Set_in == Speed_Set && Stop_enable_flag == 1)Start_time_count = - 15000;//若实际设定速度已达到最大，则认为处于停车状态中
          }
        
        if(Start_delay_flag == 1 ){while(1){if(key_press()==5)break;}}
        if(Start_delay_flag > 0) //用来延时起跑
        {
            Start_time_count = 0;
            Start_delay_flag ++;
            if(Start_delay_flag >= 40 ){Start_delay_flag = 0;} //延时时间 ：flag * 100ms
        }
        
        
        S_flag = 0;//起跑计数清零
        Delay_Right_Angle++;//100ms +1
        
    }
    
      
    SpeedOutCal();
    if(timer5ms == 2){Start_time_count++;timer5ms = 0;}          
    //每10ms加一 
    

    if(CCD_finsh_flag == 1)
    {
      Check_Line_H();
      Check_Line_L();
      CCD_finsh_flag = 0;//每次采线后只分析一次
      DirectionControl();   
    } 
    
    Direction_piece_flag++;
    
    
    DirectionOutCal();      
    
    
 //   MidFilterint();
   
    Angle_Control();
    
    Speed_Adjust(Left_Speed,Right_Speed); 
      
    PITTF_PTF1 = 1;
    
    EnableInterrupts;    
}


  
void interrupt 8 Timer0_ECT(void) //8 为定时器通道 0 的中断标号
{  
    static unsigned char TimerCnt20ms = 0;
                                    //控制 程序
    unsigned int m;
    TFLG1_C0F=1;   //清中断标志位
    DisableInterrupts;
    m=TCNT;
    TC0=m+625;    //391*1.6us=1ms 定时时间
        
    TimerCnt20ms+=1;
      // 根据曝光时间计算20ms周期内的曝光点 
   
   if(integration_piont >= 2)
   {     // 曝光点小于2(曝光时间大于18ms)则不进行再曝光 
        if(integration_piont >= TimerCnt20ms)
        StartIntegration();           // 曝光开始
   }
   
    if(TimerCnt20ms >= 20) 
    {
       TimerCnt20ms = 0;
       // Sampling CCD data 
       ImageCapture(Pixel_L,Pixel_H);

       // Calculate Integration Time 
       CalculateIntegrationTime(); 
    }  

     EnableInterrupts;
}
  
void interrupt 24 Start_Stop()//起跑检测中断程序 
{
   PIFJ_PIFJ0 = 1;//清除标志位
   PIFJ_PIFJ1 = 1;
   S_flag++;
 //  while(1){if(key_press()==5)break;}
 /*
   if(Speed_Set_in ==0)time_flag1 = 0;//若实际设定速度较小，则认为处于发车状态中
   else if(Speed_Set_in == Speed_Set)time_flag1 = - 15000;//若实际设定速度已达到最大，则认为处于停车状态中
   */
}



