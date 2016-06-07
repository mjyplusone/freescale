#include "ALL.h"

int Direction_Old,Direction_New;                                           
int Direction_Speed;    
               // 48          //55          
int Direction_P=50,Direction_D=36;   //方向控制PD 
               //电压 7.8V  前瞻30cm    47  50
              
int Direction_Control_P,Direction_Control_D;     

int delay=0;

int obstacle_P_add=10;                   

void DirectionControl(void)  //方向控制周期10ms
{   
  
     int Center_Line_transform_new_abs;
  //   Direction_P=46,Direction_D=55;
 /*  if((Center_Line_transform_new <= -33) || (Center_Line_transform_new >= 33))
     { //只检测到左边界，很大的急弯，控制力最大
      Direction_P=34;  Direction_D=50;    //0.3   1
     }
     else if((black_middle_transform_new >= (0 - 33)) && (black_middle_transform_new < (0 - 21)))
     {  //检测到左右两边界，进入到小弯，或刚进大弯，控制力较大
      Right_direction_P=0.44;   Right_direction_D=1.4;    //0.42   1
     }
     else if((black_middle_transform_new >= (0 - 21)) && (black_middle_transform_new < (0 - 10)))
     { //检测到左右两边界，较直的向前，仍在两黑线之中，控制力中等
      Right_direction_P=0.68;   Right_direction_D=1.4;   //0.67  1
     }
     else if((black_middle_transform_new >= (0 - 10)) && (black_middle_transform_new < (0 - 4)))
     { //检测到左右两边界，较直的向前，仍在两黑线之中，控制力中等
      Right_direction_P=0.74;   Right_direction_D=1.3;    //0.7   1
     }
     else if(black_middle_transform_new >= (0 - 4))
     { //与中心线位置较近，控制力较小
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
    



        
     /*    if(delay <= 7)  //根据速度改变  1 2 3 4
        {
           Center_Line_transform_new = 0 ;
           Direction_Control_P=0;
           Direction_Control_D=0; 
        }  */
        if(delay <= cross_time_1)  //根据速度改变  1 2 3 4
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
           { //与中心线位置较近，控制力较小
            Direction_Control_P=25;   Direction_Control_D=45;    //1.6 1.2      1.1   1
           }         
           else if(Center_Line_transform_new_abs <= 10)
           { //检测到左右两边界，较直的向前，仍在两黑线之中，控制力中等
            Direction_Control_P=30;   Direction_Control_D=50;    //0.74 1.3    0.7   1
           }
           else if(Center_Line_transform_new_abs <= 21)
           { //检测到左右两边界，较直的向前，仍在两黑线之中，控制力中等
            Direction_Control_P=35;   Direction_Control_D=55;   //0.68 1.4     0.67  1
           }
           else if(Center_Line_transform_new_abs <= 33)
           {  //检测到左右两边界，进入到小弯，或刚进大弯，控制力较大
            Direction_Control_P=42;   Direction_Control_D=55;    //0.44 1.4    0.42   1
           }
           else //if((Center_Line_transform_new <= -33) || (Center_Line_transform_new >= 33))
           { //只检测到左边界，很大的急弯，控制力最大
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


void DirectionOutCal(void)   //方向调整均分在4个5ms控制周期内完成~~
{
    float Direction_Out;
    
    Direction_Out=Direction_New-Direction_Old;
    Direction_Out=Direction_Out*(Direction_piece_flag*1.0/4)+Direction_Old;
    
    Direction_Speed=Direction_Out;//*0.8;
}
