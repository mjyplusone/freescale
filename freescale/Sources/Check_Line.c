#include "ALL.h"

int L,H;

//int ONELINE_F_R=0,ONELINE_F_L=0,ONELINE_F=0,RightAngle_F=0;
//int FF1,FF2,FF3,FF4,FF5,FF6;


//�ɵ����� ���������ٶȵ���
//CCD
int CCD_L_trigger = 45 , CCD_H_trigger = 28; //����CCDɨ�߷�ֵ
                 //40
//�ϰ�
int CCD_obstacle_trigger = 20;    //�ϰ�ɨ�� ��ֵ 
int CCD_obstacle_pianyi  = 6 ;    //�ϰ�     ƫ�ƾ���
int CCD_obstacle_over_1  = 4 ;    //����ת����� �� ʱ��
int CCD_obstacle_over_2  = 9 ;    //�����ϰ�ģʽ �� ʱ��

//ʮ����                
int cross_flag_trigger = 100;                 //����ʮ��������־���� ƽ�����ش�С
int cross_time_1 = 8;
int cross_time_2 = 14;

//ֱ����
int Right_Angle_Left_juli = 9 , Right_Angle_Right_juli = 9 ;  //����תֱ�����ͺ����  Խ����ֱ����Խ��
int Right_Angle_Left_r    = 18 , Right_Angle_Right_r   = 18;  //����תֱ����ת��뾶  Խ��ת��뾶Խ��




//СǰհCCD
int L_F,R_F,L_F1,R_F1,L_F2,R_F2;
int Center_Line=64,Center_Line_old[2]={0};
int Left_Line,Right_Line;
int Left_Line1,Right_Line1,Left_Line2,Right_Line2;
int Left_Line_new,Left_Line_old,Right_Line_new,Right_Line_old;
float Center_Line_transform,Center_Line_transform_old,Center_Line_transform_new;
float black_transform_save[12];
int ccd_average[2] = {0}; 
int cross_flag = 0,obstacle_flag_L=0,obstacle_flag_R=0;;
int scan_width=30;
int width;

//ֱ�����־λ���
unsigned char Left_Led_trigger =150 ,Right_Led_trigger = 150,test_L =0,test_R =0,test_all = 0;
int Right_Angle_flag = 0;
int Delay_Right_Angle = 0;


//�ϰ���־
//int Zhangai_flag = 0;
//int Delay_Zhangai = 0;


//��ǰհCCD
int Center_Line_H,Right_Line_H,Left_Line_H;
int width_H;


unsigned char  obstacle_left,obstacle_right;
int Center_Line_obstacle;
int delay1;
int Turn_L,Turn_R;



unsigned char average_Left(int Center_Line);
unsigned char average_Right(int Center_Line);

//��������
void Start(void) 
{
    if(key_press()==5)
    {
        Speed_Set_in = 0; 
        Start_time_count = 0; 
        Speed_Control_Integral=0;
        test_all = 0;
        test_L = 0;test_R = 0;
        obstacle_flag_L = 0;
        obstacle_flag_R = 0;
        Center_Line = 64;
        width = 100;
    }
    
    if(Speed_Set_in<=Speed_Set)Speed_Set_in=Speed_Set; 
    else if(Start_time_count>=51 && Speed_Set_in>-5) 
    {
      Speed_Set_in=-1;
      Start_time_count=0; 
    } 
    else if(Start_time_count>=10 && Speed_Set_in<=-1)
    {
      Speed_Set_in -= 1;
      Start_time_count=0;  
    }
    //if(Speed_Set_in<=Speed_Set)Speed_Set_in=Speed_Set;
    if(Start_time_count >14000 )Start_time_count = 500; 
    
    //����flag��ʱ�ο������ܺ�ֹͣ  
    if(Start_time_count < 0 && Start_time_count >= -14989 && Speed_Set_in < 0)//����ֹͣģʽ 
    {                               //��110ms��ʱ��� �ӵ���Ϩ��С����ʼֹͣ
      Speed_Set_in++;
      Start_time_count = -15000;
    }
    else if(Start_time_count < 0 && Start_time_count >= -14999 && Speed_Set_in >= Speed_Set + 1 && Speed_Set_in <= -1)//����ֹͣģʽ 
    {
      Speed_Set_in += 2;//= Speed_Set_in +2;
      if(Speed_Set_in > 0)Speed_Set_in = 0;
      Start_time_count = -15000;//ÿ10ms�ٶȼ�12
    }
}



void Check_Line_H(void) 
{
    Right_Line_H=127;   
    for(H=Center_Line_H;H<128-5;H++) 
    {  
        if(Pixel_H[H]-Pixel_H[H+3]>= CCD_H_trigger && Pixel_H[H+1]-Pixel_H[H+4]>= CCD_H_trigger && Pixel_H[H+2]-Pixel_H[H+5]>= CCD_H_trigger) 
        {
            Right_Line_H=H+3;
            break;             
        }
     } 
     Left_Line_H=0;    
     for(H=Center_Line_H;H>0+5;H--) 
     {   
        
         if(Pixel_H[H]-Pixel_H[H-3]>= CCD_H_trigger && Pixel_H[H-1]-Pixel_H[H-4]>= CCD_H_trigger && Pixel_H[H-2]-Pixel_H[H-5]>= CCD_H_trigger ) 
         {
             Left_Line_H=H-3;
             break;    
         }
     } 
     
     
     //
     if(Left_Line_H > Right_Line_H)
     {
        Left_Line_H  = Left_Line_H + Right_Line_H;
        Right_Line_H = Left_Line_H - Right_Line_H;
        Left_Line_H  = Left_Line_H - Right_Line_H;
     }
     //
     
     
     
     if(Left_Line_H<5 && Right_Line_H>122)
     {
         Center_Line_H=64;
     } 
     else if(Left_Line_H<5)
     { 
         Center_Line_H=Right_Line_H-width_H;
     } 
     else if(Right_Line_H>122) 
     {
         Center_Line_H=Left_Line_H+width_H;
     } 
     else  if(Left_Line_H>=5 && Right_Line_H<=122)
     {
         Center_Line_H=(Left_Line_H+Right_Line_H)>>1;
         width_H=(Right_Line_H-Left_Line_H)>>1;
 //        Right_Angle_flag = 0;
     }
     
     if(Center_Line_H<0)Center_Line_H=0;
     else if(Center_Line_H>127)Center_Line_H=127;    //��ֹ��������� 
         
}



//���Բ���2015.6.23
void Check_Line_L(void)      
{ 

      L_F=0;   R_F=0;
      L_F1=0;  R_F1=0;
      L_F2=0;  R_F2=0;
    
      Right_Line=127;  
      L = Center_Line-scan_width;
      if(L<0)  L=0;
      for(;L<127-5;L++) //δ��ƫ��Ƭ �� 30
      {  
          if(Pixel_L[L]-Pixel_L[L+3]>= CCD_L_trigger && Pixel_L[L+1]-Pixel_L[L+4]>= CCD_L_trigger && Pixel_L[L+2]-Pixel_L[L+5]>= CCD_L_trigger ) 
          {
              R_F++;
              if(R_F==1) 
              {
                 Right_Line=L+3;
                 break;    
              }             
          }
      } 
        
       Left_Line=0;
       L = Center_Line+scan_width;
       if(L>127)  L=127;
       for(;L>0+5;L--) 
       {   
          
           if(Pixel_L[L]-Pixel_L[L-3]>= CCD_L_trigger && Pixel_L[L-1]-Pixel_L[L-4]>= CCD_L_trigger && Pixel_L[L-2]-Pixel_L[L-5]>= CCD_L_trigger ) 
           {
                L_F++;
                if(L_F==1) 
                {
                    Left_Line=L-3;
                    break;    
                }
           }
        }
        
       /* 
        if(Right_Line - Left_Line < 0  && ) 
        {
            Left_Line  = Left_Line_old;
            Right_Line = Right_Line_old;
        }*/
          
         
       //ֱ������                               
      // if(Left_Led  > Left_Led_trigger ) test_L = 1;
      // if(Right_Led > Right_Led_trigger) test_R = 1;
       if(Left_Led  > Left_Led_trigger && Right_Led > Right_Led_trigger && Delay_Right_Angle > 10)
       {
            if(Right_Angle_flag == -1)//PixelAverage(128,Pixel_H) <45
            {
              
              test_all = 0;
              Right_Angle_flag = 0;
              Delay_Right_Angle = 0;
         /*    PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
              while(1);   */             
            }
            else
            {
                test_all = 1;Delay_Right_Angle = 0;
           /*     PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
                while(1){if(key_press()==5)break; } */    
            }
       }
      


        //�����ж��� ��߽绹���ұ߽�
        if((L_F<1)&&(R_F<1))
        {
            Left_Line_new  = Left_Line_old;    //�޸��ˣ�������û��ɨ�赽�ܵ�ʱ����ֱ���ߣ������䣬��ʮ����������кô�
            Right_Line_new = Right_Line_old;
            
           
            if(Right_Angle_flag == 0 && PixelAverageValue> cross_flag_trigger )   cross_flag = 1;    //������ʮ�����־(ע����ֱ�����־����)
            
       /*      if(Right_Angle_flag == 1 ) 
            {
                 PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
                while(1){;}        
            }    */
            
        } 
        else if((L_F==1)&&(R_F<1))//�Ҷ���    ��
        {
            Left_Line_new  = Left_Line;
            Right_Line_new = Right_Line_old;//B_Right_old
            
            Turn_R=1;  Turn_L=0;
            //��תֱ����
            if(test_all == 1 && (Left_Line_H<5 || Right_Line_H>122) && Right_Angle_flag != -1)
            { 
              
                Right_Angle_flag ++ ;
                if(Right_Angle_flag > Right_Angle_Right_juli) //��ʼת��ľ���  Խ����ֱ����Խ��   ���� �� 5
                {
                  Left_Line_new  = Right_Line_new - Right_Angle_Right_r; //ת��뾶  Խ��뾶Խ��  ���� �� 26
             /*     PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
                  while(1){;}     */
                }
                 //Left_Line +35;//while(1){;}
                
            /*  PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
                while(1){;} */
             
            }    
        } 
        else if((L_F<1)&&(R_F==1))//����
        {
            Left_Line_new  = Left_Line_old;//B_Left_old ;
            Right_Line_new = Right_Line;
            
            Turn_R=0;  Turn_L=1;
            //��תֱ����
            if(test_all == 1 && (Left_Line_H<5 || Right_Line_H>122) && Right_Angle_flag != -1)
            {
              
                Right_Angle_flag ++ ;
                if(Right_Angle_flag > Right_Angle_Left_juli) //��ʼת��ľ���  5
                {
                  Right_Line_new  = Left_Line_new +Right_Angle_Left_r; //ת��뾶   26
                /*PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
                  while(1){;}    */
                }
                 //Right_Line -35;//while(1){;} 
                
           /*  
                PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
                while(1){;}     */
            }
        }
        else if((L_F==1)&&(R_F==1)) //δ����
        {
            Left_Line_new  = Left_Line;
            Right_Line_new = Right_Line; 
            
            if(Right_Angle_flag ==0 && Right_Line > Left_Line){width = Right_Line - Left_Line  ;}
           
           
       /*   
           if(width <= 70  &&  Zhangai_flag == 0) 
            {
              if      (  (  (Left_Line+Right_Line)>>1  )  >  64  )Zhangai_flag =  1;//�ϰ������ Left_Line_new  += 30;
              else  if(  (  (Left_Line+Right_Line)>>1  )  <  64  )Zhangai_flag = -1;//�ϰ����ұ� Right_Line_new -= 30;
              else  Zhangai_flag = 0;
         
            }
         
        */  
        
         
         
            if(Right_Angle_flag >  Right_Angle_Left_juli || Right_Angle_flag >  Right_Angle_Right_juli)
            {
              Right_Angle_flag = -1;
             //  PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0; while(1){;}
            } 
      
           
        }
      
       
       
         
      Center_Line = (Left_Line_new+Right_Line_new)>>1;
      
         
                                                     
      if(Center_Line<0)Center_Line=0;
      else if(Center_Line>127)Center_Line=127;    //��ֹ���������
 
   
  //    Center_Line_transform = 64 - Center_Line;
        
 
   
    //�ϰ���������   
 
       Right_Line1=Left_Line_new;
       for(L=0;L<Left_Line_new-10;L++) //������� �������-10 ɨ�½���  ����� ���� (������)�½���
       {
           if(Pixel_L[L]-Pixel_L[L+3]>= CCD_obstacle_trigger && Pixel_L[L+1]-Pixel_L[L+4]>= CCD_obstacle_trigger && Pixel_L[L+2]-Pixel_L[L+5]>= CCD_obstacle_trigger ) 
           {
              R_F1++;
              if(R_F1==1) 
              {
                 Right_Line1=L+3;
                 break;    
              }             
           }            
       }
       Left_Line1=0;
       for(L=Left_Line_new-10;L>0+5;L--) //�������-10���ұ�ɨ�½���  ��������� ������
       {   
          
           if(Pixel_L[L]-Pixel_L[L-3]>= CCD_obstacle_trigger && Pixel_L[L-1]-Pixel_L[L-4]>= CCD_obstacle_trigger && Pixel_L[L-2]-Pixel_L[L-5]>= CCD_obstacle_trigger ) 
           {
                L_F1++;
                if(L_F1==1) 
                {
                    Left_Line1=L-3;
                    break;    
                }
           }
        }
        
        
        
       Right_Line2=127;
       for(L=Right_Line_new+10;L<127;L++) //�ұ��� �Ҳ��  �½���
       {
           if(Pixel_L[L]-Pixel_L[L+3]>= CCD_obstacle_trigger  && Pixel_L[L+1]-Pixel_L[L+4]>= CCD_obstacle_trigger && Pixel_L[L+2]-Pixel_L[L+5]>= CCD_obstacle_trigger ) 
           {
              R_F2++;
              if(R_F2==1) 
              {
                 Right_Line2=L+3;
                 break;    
              }             
           }
       }
       Left_Line2=Right_Line_new;
       for(L=127;L>Right_Line_new+10;L--) //�ұ��� �Ҳ��  ������
       {   
          
           if(Pixel_L[L]-Pixel_L[L-3]>= CCD_obstacle_trigger  && Pixel_L[L-1]-Pixel_L[L-4]>= CCD_obstacle_trigger && Pixel_L[L-2]-Pixel_L[L-5]>= CCD_obstacle_trigger ) 
           {
                L_F2++;
                if(L_F2==1) 
                {
                    Left_Line2=L-3;
                    break;    
                }
           }
        }
        
        
        if(R_F1==1&&L_F1==1&&Right_Line1-Left_Line1>4 && Right_Line1-Left_Line1<10 && Left_Line-Right_Line1 < 35)
        {
           obstacle_flag_L=1;  Center_Line_obstacle=Center_Line + CCD_obstacle_pianyi;//15  5
           
     //       PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
      //        while(1){if(key_press()==5)break;}         
        } 
        if(R_F2==1&&L_F2==1&&Right_Line2-Left_Line2>4 && Right_Line2-Left_Line2<10 && Left_Line2-Right_Line < 35)
        {
           obstacle_flag_R=1;  Center_Line_obstacle=Center_Line - CCD_obstacle_pianyi;
           
      //      PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
       //       while(1){if(key_press()==5)break;}   
        } 
       
     
     
     
     
       
 
      if(obstacle_flag_L==1) 
      {
          obstacle_flag_L=2;//0; 
           
          Center_Line_transform = 64 - Center_Line_obstacle;
          
          delay1=0;
          
      /*    PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
         while(1)if(key_press()==5)break;  */ 
      } 
      else if(obstacle_flag_R==1) 
      {
          obstacle_flag_R=2;//0; 
           
          Center_Line_transform = 64 - Center_Line_obstacle;
          
          delay1=0;
          
       /*   PWMDTY01  = 0;PWMDTY23  = 0;PWMDTY45  = 0;PWMDTY67  = 0;
         while(1)if(key_press()==5)break;    */
      }
     
          delay1++;
   /*       if(delay1 ==3 || delay1 ==4)
          {
            if     ( obstacle_flag_L == 2) Center_Line_transform -- ; 
            else if( obstacle_flag_R == 2) Center_Line_transform ++ ; 
          }   */
          
          
          if(delay1 >= CCD_obstacle_over_1  && delay1< CCD_obstacle_over_2 )
          {
            if     ( obstacle_flag_L == 2) Center_Line_transform -- ; 
            else if( obstacle_flag_R == 2) Center_Line_transform ++ ; 
          }
          
          if(delay1 >= CCD_obstacle_over_2 )//120 
          {
            delay1= CCD_obstacle_over_2 ; 
            obstacle_flag_L = 0;
            obstacle_flag_R = 0; 
            Center_Line_transform = 64 - Center_Line;
          }
     
        
    
          
   //     ccd_average[1] = ccd_average[0];  ccd_average[0] =  Center_Line_transform;
        
    //    Center_Line_transform_new =(ccd_average[1] + ccd_average[0])>>1;
    
    //    Center_Line_transform_new = ccd_average[1] *0.3 + ccd_average[0] *0.7;
        Center_Line_transform_new = Center_Line_transform;
    
   //����3��  ����10��
        Center_Line_transform_old=black_transform_save[9];
        
        black_transform_save[9]=black_transform_save[8];
        black_transform_save[8]=black_transform_save[7];
        black_transform_save[7]=black_transform_save[6];
        black_transform_save[6]=black_transform_save[5];
        black_transform_save[5]=black_transform_save[4];
        black_transform_save[4]=black_transform_save[3];
        black_transform_save[3]=black_transform_save[2];
        black_transform_save[2]=black_transform_save[1];
        black_transform_save[1]=black_transform_save[0];
        black_transform_save[0]=Center_Line_transform_new;
        
    //    if(Center_Line<0)Center_Line=0;
   //     else if(Center_Line>127)Center_Line=127;    //��ֹ���������
        
     
        Center_Line_old[1]=Center_Line_old[0];  Center_Line_old[0]=Center_Line;
        Left_Line_old  = Left_Line_new;
        Right_Line_old = Right_Line_new; 
     
     
      
}                                          


/*************************************************
������: void MidFilterint(void)
����:  ��Ȩ������ֵ�˲�
����:��
����ֵ:��
**************************************************/ 
void MidFilterint(void){           //��Ȩ������ֵ�˲�
    int i,old=0,average,mid,temp=0;
    Pixel_L[0]=Pixel_L[2];             //�˵���һ���͵ڶ���������벨
    Pixel_L[1]=Pixel_L[2];
    for(i=1;i<127;i++){                     
        if(old==Pixel_L[i+1])
        {
             Pixel_L[i]=temp; 
        }
        else
        {
              if((Pixel_L[i-1]>Pixel_L[i] && Pixel_L[i-1]<Pixel_L[i+1] ) ||  (Pixel_L[i-1]>Pixel_L[i+1] && Pixel_L[i-1]<Pixel_L[i]))
              {
                   mid=Pixel_L[i-1];
              }
              else if((Pixel_L[i]>Pixel_L[i-1] && Pixel_L[i]<Pixel_L[i+1] ) ||  (Pixel_L[i]>Pixel_L[i+1] && Pixel_L[i]<Pixel_L[i-1]))
              {
                    mid=Pixel_L[i];
              }
              else if((Pixel_L[i+1]>Pixel_L[i] && Pixel_L[i+1]<Pixel_L[i-1] ) ||  (Pixel_L[i+1]>Pixel_L[i-1] && Pixel_L[i+1]<Pixel_L[i]))
              {
                    mid=Pixel_L[i+1];
              }
              else
              {
                    mid=Pixel_L[i];
              }
              average=(Pixel_L[i-1]+Pixel_L[i]+Pixel_L[i+1])/3;
              temp=0.3*mid+0.7*average;
              Pixel_L[i]= temp;
        }
        old=Pixel_L[i-1];
    } 
}



unsigned char abs_mi(unsigned char mi_a,unsigned char mi_b) 
{
  if(mi_a>mi_b)return mi_a-mi_b;
  else return mi_b-mi_a;
}


unsigned char average_Left(int Center_Line) 
{
    unsigned char i;
    unsigned int average = 0;
    for(i=30;i<38;i++) 
    {
   //     if(Center_Line-i<0)  Pixel_L[Center_Line-i]=120; 
        average += Pixel_H[Center_Line_H-i];
    }
   
    return ((unsigned char)(average/8));
}

unsigned char average_Right(int Center_Line) 
{
    unsigned char i;
    unsigned int average = 0;
    for(i=30;i<38;i++) 
    {
    //    if(Center_Line+i>127)  Pixel_L[Center_Line+i]=120;
        average += Pixel_H[Center_Line_H+i];
    }
   
    return ((unsigned char)(average/8));
}
