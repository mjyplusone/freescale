#include "ALL.h"

void INIT_PWM() 
{
//busF / 分频系数 /（PWMSCLA * 2 ）
    PWMPRCLK = 0x33;   //A时钟和B时钟的分频系数为8,频率为10MHz
//    PWMSCLA  =  100;   //SA时钟频率为400KHz
//    PWMSCLB  =  100;   //SB时钟频率为400KHz
    
// 前提 ： 左黑 右红
    
    //67级联 为 PWM4   left down  左反
    PWMCTL_CON67= 1;   //联结通道0,1为16位的PWM
    PWMPOL_PPOL7= 1;   //通道01的极性为高电平有效
    PWMCLK_PCLK7 =0;   //通道07用A时钟作为时钟源
    PWMCAE   = 0x00;   //脉冲模式为左对齐模式
    PWMPER67  = 1000;  //通道01的周期为1Hz 
    PWMDTY67  = 0;     //通道01的占空比为0%  
    PWME_PWME7 = 1;    //使能通道01

//23级联 为 PWM1      left up     左正
    PWMCTL_CON23= 1;   //联结通道0,1为16位的PWM
    PWMPOL_PPOL3= 1;   //通道01的极性为高电平有效
    PWMCLK_PCLK3 =0;   //通道03用B时钟作为时钟源
    PWMCAE   = 0x00;   //脉冲模式为左对齐模式
    PWMPER23  = 1000;  //通道01的周期为1Hz 
    PWMDTY23  = 0;   //通道01的占空比为0%  
    PWME_PWME3 = 1;    //使能通道23
    
      
// 前提 ： 左黑 右红
   
 //45级联 为 PWM3      right up    右反
    PWMCTL_CON45= 1;   //联结通道0,1为16位的PWM
    PWMPOL_PPOL5= 1;   //通道01的极性为高电平有效
    PWMCLK_PCLK5 =0;   //通道05用A时钟作为时钟源
    PWMCAE   = 0x00;   //脉冲模式为左对齐模式
    PWMPER45  = 1000;  //通道01的周期为1Hz 
    PWMDTY45  = 0;     //通道01的占空比为20%  
    PWME_PWME5 = 1;    //使能通道01
    
 //01级联 为 PWM2      right down    右正
    PWMCTL_CON01= 1;   //联结通道0,1为16位的PWM
    PWMPOL_PPOL1= 1;   //通道01的极性为高电平有效
    PWMCLK_PCLK1 =0;   //通道01用A时钟作为时钟源
    PWMCAE   = 0x00;   //脉冲模式为左对齐模式
    PWMPER01  = 1000;  //通道01的周期为1Hz 
    PWMDTY01  = 0;     //通道01的占空比为0%  
    PWME_PWME1 = 1;    //使能通道01
}
/*
choose   =0 控制左轮 =1 控制右轮
dir      =0 为想前转  =1  为向后转
rate     占空比
*/
void motor(int choose,int dir,int rate) 
{
 
  if(choose==  Left  ) 
  {
     if(dir==  Front ){PWMDTY67  = 0;    PWMDTY23  = rate;  }
     else             {PWMDTY67  = rate; PWMDTY23  = 0; }
  }
  else 
   {
     if(dir==  Front ){PWMDTY45  = 0;    PWMDTY01  = rate; }
     else             {PWMDTY45  = rate; PWMDTY01  = 0; }
   }
}
