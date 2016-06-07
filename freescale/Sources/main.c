#include "ALL.h"


#define Left_Dir   PTH_PTH6       //Left:��ת1����ת0
#define Right_Dir  PTH_PTH7       //Right:��ת0����ת1


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
         
     InitMPU6050(); //��ʼ��MPU6050 
     
     INIT_PIT();
     
     AD_Init();

     INIT_CCD();//�������ܼ���ʼ��
     
     INIT_Key();//�������뿪�����õ�ģʽ ���
     
     
     LCD_WrCmd(0xc0); //OLEDͼ�����·�ת
     
     
     Get_Gyro_Zero() ;
  // Get_Gravity_Zero();
  
 //    if(Boma_1==0){PIEJ_PIEJ0 = 0 ;PIEJ_PIEJ1 = 0;} //Ĭ�ϴ����ܼ��ģʽ��������뿪��1���Ҳ࣬��ر����ܼ��
     
     Boma_Change();//���ݲ��뿪�ظı��ٶȿ���
   
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
        Speed_Set = -12;  //�ٶ��趨
        Direction_P=49;  //������Ʋ���
        Direction_D=36; 
        
        //�ϰ�
        CCD_obstacle_pianyi  = 4 ;    //�ϰ�     ƫ�ƾ���        4
        CCD_obstacle_over_1  = 4 ;    //����ת����� �� ʱ��     3
        CCD_obstacle_over_2  = 11 ;    //�����ϰ�ģʽ �� ʱ��     7

        //ʮ����
     //   cross_flag_trigger = 70;                 //����ʮ��������־���� ƽ�����ش�С

        //ֱ����                 //9
        Right_Angle_Left_juli = 14 , Right_Angle_Right_juli = 14;  //����תֱ�����ͺ����  Խ����ֱ����Խ��
        Right_Angle_Left_r    = 23 , Right_Angle_Right_r   = 23;  //����תֱ����ת��뾶  Խ��ת��뾶Խ��

     }
     
     if(Boma_2==1)// 15     7.86V
     {
        Speed_Set = -15;   
        Direction_P=50;  //������Ʋ���
        Direction_D=42;
        
        //�ϰ� 
        CCD_obstacle_pianyi  = 5 ;    //�ϰ�     ƫ�ƾ���       4    5
        CCD_obstacle_over_1  = 7 ;    //����ת����� �� ʱ��    4    6
        CCD_obstacle_over_2  = 11 ;    //�����ϰ�ģʽ �� ʱ��   8    10

        //ʮ����
        // cross_flag_trigger = 70; //����ʮ��������־���� ƽ�����ش�С

        //ֱ����
        Right_Angle_Left_juli = 9 , Right_Angle_Right_juli = 9 ;  //����תֱ�����ͺ����  Խ����ֱ����Խ��
        Right_Angle_Left_r    = 20 , Right_Angle_Right_r   = 18;  //����תֱ����ת��뾶  Խ��ת��뾶Խ��

     }
     

     if(Boma_3==1)//���ܺ�ͣ����ⶼ������   �ӳ� 4 S ����
     {
        /* PIEJ_PIEJ0 = 0 ;PIEJ_PIEJ1 = 0; //�ر� ������� 
         
         Start_delay_flag = 1; //�ӳٷ�����־λ         */
         
          // 17 ����


        Speed_Set = -17;
        Direction_P=52;  //������Ʋ���
        Direction_D=44; 
        
        //�ϰ�
        CCD_obstacle_pianyi  = 5 ;    //�ϰ�     ƫ�ƾ���
        CCD_obstacle_over_1  = 6 ;    //����ת����� �� ʱ��
        CCD_obstacle_over_2  = 10 ;    //�����ϰ�ģʽ �� ʱ��

        //ʮ����
     //   cross_flag_trigger = 70;                 //����ʮ��������־���� ƽ�����ش�С

        //ֱ����
        Right_Angle_Left_juli = 9, Right_Angle_Right_juli = 9 ;  //����תֱ�����ͺ����  Խ����ֱ����Խ��
        Right_Angle_Left_r    = 15 , Right_Angle_Right_r   = 17;  //����תֱ����ת��뾶  Խ��ת��뾶Խ��


         
     }
     
     else if(Boma_4==1)//������ͣ�����  ֻ�������ܼ��
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

   
 // { ����������
    if( PTH_PTH4 == 0)   {coder_right_cnt += PACNT; PTH_PTH4  = 1;} 
    else                 {coder_left_cnt  += PACNT; PTH_PTH4  = 0;}
    //�л�������             
    PACNT = 0;  
    coder_finish_flag++;
  //}
  
  
    if(coder_finish_flag==20) 
    {
        //Left:��ת1����ת0  Right:��ת0����ת1
        if(Left_Dir==0)  Speed_Left_Get=-coder_left_cnt;
        else             Speed_Left_Get=coder_left_cnt;
        if(Right_Dir==1) Speed_Right_Get=-coder_right_cnt;
        else             Speed_Right_Get=coder_right_cnt;
        
      
        
        if(Speed_Control_Integral>=100)
            Speed_Control_Integral=100;      //�����޷�
        
        coder_left_cnt=0;
        coder_right_cnt=0;
                                     
        Start();  
        SpeedControl();
         
        coder_finish_flag=0; 
        
        if(S_flag >= 4)
         {
             if(Speed_Set_in ==0)Start_time_count = 0;//��ʵ���趨�ٶȽ�С������Ϊ���ڷ���״̬��
             else if(Speed_Set_in == Speed_Set && Stop_enable_flag == 1)Start_time_count = - 15000;//��ʵ���趨�ٶ��Ѵﵽ�������Ϊ����ͣ��״̬��
          }
        
        if(Start_delay_flag == 1 ){while(1){if(key_press()==5)break;}}
        if(Start_delay_flag > 0) //������ʱ����
        {
            Start_time_count = 0;
            Start_delay_flag ++;
            if(Start_delay_flag >= 40 ){Start_delay_flag = 0;} //��ʱʱ�� ��flag * 100ms
        }
        
        
        S_flag = 0;//���ܼ�������
        Delay_Right_Angle++;//100ms +1
        
    }
    
      
    SpeedOutCal();
    if(timer5ms == 2){Start_time_count++;timer5ms = 0;}          
    //ÿ10ms��һ 
    

    if(CCD_finsh_flag == 1)
    {
      Check_Line_H();
      Check_Line_L();
      CCD_finsh_flag = 0;//ÿ�β��ߺ�ֻ����һ��
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


  
void interrupt 8 Timer0_ECT(void) //8 Ϊ��ʱ��ͨ�� 0 ���жϱ��
{  
    static unsigned char TimerCnt20ms = 0;
                                    //���� ����
    unsigned int m;
    TFLG1_C0F=1;   //���жϱ�־λ
    DisableInterrupts;
    m=TCNT;
    TC0=m+625;    //391*1.6us=1ms ��ʱʱ��
        
    TimerCnt20ms+=1;
      // �����ع�ʱ�����20ms�����ڵ��ع�� 
   
   if(integration_piont >= 2)
   {     // �ع��С��2(�ع�ʱ�����18ms)�򲻽������ع� 
        if(integration_piont >= TimerCnt20ms)
        StartIntegration();           // �ع⿪ʼ
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
  
void interrupt 24 Start_Stop()//���ܼ���жϳ��� 
{
   PIFJ_PIFJ0 = 1;//�����־λ
   PIFJ_PIFJ1 = 1;
   S_flag++;
 //  while(1){if(key_press()==5)break;}
 /*
   if(Speed_Set_in ==0)time_flag1 = 0;//��ʵ���趨�ٶȽ�С������Ϊ���ڷ���״̬��
   else if(Speed_Set_in == Speed_Set)time_flag1 = - 15000;//��ʵ���趨�ٶ��Ѵﵽ�������Ϊ����ͣ��״̬��
   */
}



