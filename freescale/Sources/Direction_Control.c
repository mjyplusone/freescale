#include "ALL.h"

int Direction_Old,Direction_New;                                           
int Direction_Speed;    
               // 48          //55          
int Direction_P=50,Direction_D=36;   //�������PD 
               //��ѹ 7.8V  ǰհ30cm    47  50
              
int Direction_Control_P,Direction_Control_D;     

int delay=0;

int obstacle_P_add=10;                   

void DirectionControl(void)  //�����������10ms
{   
  
     int Center_Line_transform_new_abs;
  //   Direction_P=46,Direction_D=55;
 /*  if((Center_Line_transform_new <= -33) || (Center_Line_transform_new >= 33))
     { //ֻ��⵽��߽磬�ܴ�ļ��䣬���������
      Direction_P=34;  Direction_D=50;    //0.3   1
     }
     else if((black_middle_transform_new >= (0 - 33)) && (black_middle_transform_new < (0 - 21)))
     {  //��⵽�������߽磬���뵽С�䣬��ս����䣬�������ϴ�
      Right_direction_P=0.44;   Right_direction_D=1.4;    //0.42   1
     }
     else if((black_middle_transform_new >= (0 - 21)) && (black_middle_transform_new < (0 - 10)))
     { //��⵽�������߽磬��ֱ����ǰ������������֮�У��������е�
      Right_direction_P=0.68;   Right_direction_D=1.4;   //0.67  1
     }
     else if((black_middle_transform_new >= (0 - 10)) && (black_middle_transform_new < (0 - 4)))
     { //��⵽�������߽磬��ֱ����ǰ������������֮�У��������е�
      Right_direction_P=0.74;   Right_direction_D=1.3;    //0.7   1
     }
     else if(black_middle_transform_new >= (0 - 4))
     { //��������λ�ýϽ�����������С
      Right_direction_P=1.6;   Right_direction_D=1.2;    //1.1   1
     }                                          
   */
    
    if(Center_Line_transform_new < 0)Center_Line_transform_new_abs = -Center_Line_transform_new;
    else Center_Line_transform_new_abs = Center_Line_transform_new;
  
  
    if(cross_flag==1)
    {
      cross_flag=0;
      if(delay >= cross_time_2){delay=0;}
    }
    



        
     /*    if(delay <= 7)  //�����ٶȸı�  1 2 3 4
        {
           Center_Line_transform_new = 0 ;
           Direction_Control_P=0;
           Direction_Control_D=0; 
        }  */
        if(delay <= cross_time_1)  //�����ٶȸı�  1 2 3 4
        {
           Center_Line_transform_new = 0 ;
           Direction_Control_P=0;
           Direction_Control_D=0; 
        }
        else if(delay > cross_time_1 && delay < cross_time_2) // 5 6 7
        {
           Center_Line_transform_new = 64 - Center_Line_H ;
           Direction_Control_P=25;
           Direction_Control_D=25; 
        } 
        else
        {
           delay=cross_time_2;
       /*    if(Center_Line_transform_new_abs >=20 && Center_Line_transform_new_abs <=42)
           { 
             Direction_Control_P=Direction_P + 10;
             Direction_Control_D=Direction_D + 10;    
           }
           else if(Center_Line_transform_new_abs <= 8)
           { 
             Direction_Control_P=Direction_P - 5;
             Direction_Control_D=Direction_D - 5; 
           }
           else if(Center_Line_transform_new_abs >=43)
           { 
             Direction_Control_P=Direction_P - 7;
             Direction_Control_D=Direction_D - 7;    
           }
           else
           { 
             Direction_Control_P=Direction_P ;
             Direction_Control_D=Direction_D ; 
           }*/
           
            if(Center_Line_transform_new_abs >=20 && Center_Line_transform_new_abs <=30)
           { 
             Direction_Control_P=Direction_P + 8; //10
             Direction_Control_D=Direction_D + 8; //10   
           }
           else if(Center_Line_transform_new_abs >=31 && Center_Line_transform_new_abs <=42)
           { 
             Direction_Control_P=Direction_P + 13; //10
             Direction_Control_D=Direction_D + 13; //10   
           }
           else if(Center_Line_transform_new_abs <= 15) // 8
           { 
             Direction_Control_P=Direction_P - 25;
             Direction_Control_D=Direction_D - 20; 
           }                             
           else if(Center_Line_transform_new_abs >=43)
           { 
             Direction_Control_P=Direction_P - 8;//7;
             Direction_Control_D=Direction_D - 8;//7;    
           }
           
          
        }
            
             if(Right_Angle_flag != 0 ) //|| delay1 < 30)
           { 
             Direction_Control_P=Direction_P ;
             Direction_Control_D=Direction_D ; 
           }
           
           
           if(delay1 < CCD_obstacle_over_2 ) //|| delay1 < 30)
           { 
             Direction_Control_P=Direction_P ;
             Direction_Control_D=Direction_D -10 ; 
           }            
                    
   /*        if(Zhangai_flag != 0 )
           { 
             Direction_Control_P=Direction_P +8;
             Direction_Control_D=Direction_D +8;
             // Zhangai_flag = 0; 
           }     */
           
                  
                   
       //      Direction_Control_P=Direction_P ;
       //      Direction_Control_D=Direction_D ; 
                   
      /*     if(Center_Line_transform_new_abs <= 4)
           { //��������λ�ýϽ�����������С
            Direction_Control_P=25;   Direction_Control_D=45;    //1.6 1.2      1.1   1
           }         
           else if(Center_Line_transform_new_abs <= 10)
           { //��⵽�������߽磬��ֱ����ǰ������������֮�У��������е�
            Direction_Control_P=30;   Direction_Control_D=50;    //0.74 1.3    0.7   1
           }
           else if(Center_Line_transform_new_abs <= 21)
           { //��⵽�������߽磬��ֱ����ǰ������������֮�У��������е�
            Direction_Control_P=35;   Direction_Control_D=55;   //0.68 1.4     0.67  1
           }
           else if(Center_Line_transform_new_abs <= 33)
           {  //��⵽�������߽磬���뵽С�䣬��ս����䣬�������ϴ�
            Direction_Control_P=42;   Direction_Control_D=55;    //0.44 1.4    0.42   1
           }
           else //if((Center_Line_transform_new <= -33) || (Center_Line_transform_new >= 33))
           { //ֻ��⵽��߽磬�ܴ�ļ��䣬���������
            Direction_Control_P=47;  Direction_Control_D=55;    //                0.3   1
           }  */
       
 //   }
   
    delay++;
    
    Direction_Old=Direction_New;
    Direction_New=Direction_Control_P*Center_Line_transform_new+Direction_Control_D*(Center_Line_transform_new-Center_Line_transform_old);
    Direction_New = Direction_New/10;
    
    Direction_piece_flag = 0;
   
   /*
    Direction_Error_Last=Direction_Error_Now;
    Direction_Error_Now=64-Center_Line;     
    Direction_P=Direction_Error_Now*Direction_Control_P;
    Direction_Offset=Direction_Error_Now-Direction_Error_Last;
    Direction_D=Direction_Offset*Direction_Control_D;

    Direction_Old=Direction_New;
    Direction_New=(Direction_P+Direction_D)/10;
    */ 
}


void DirectionOutCal(void)   //�������������4��5ms�������������~~
{
    float Direction_Out;
    
    Direction_Out=Direction_New-Direction_Old;
    Direction_Out=Direction_Out*(Direction_piece_flag*1.0/4)+Direction_Old;
    
    Direction_Speed=Direction_Out;//*0.8;
}
