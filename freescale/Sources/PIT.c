#include "ALL.h"

//使用两个PIT会相互影响，因此其中一个PIT用ECT替代
void INIT_PIT()
{
    PITCFLMT_PITE=0; //定时中断模块关
    
    PITCE_PCE0=1;//定时器通道0使能

    PITMTLD0=160-1;// 80m赫兹 160分频 每个周期2us
                                                  
    PITLD0=1000-1;//  2us*500=1ms
    
    PITMUX_PMUX0=0;   //第0通道使用微计数器0
  
    //PITINTE_PINTE0=1;//定时器中断通道0,中断使能
    
    PITCFLMT_PITE=1;//定时器通道使能 
    
    PACTL = 0x50;    //始能脉冲累加器，累加上升沿    打开脉冲累加器
    
    DDRH_DDRH4  = 1;    //数据选择器 控制端口配置
    
    DDRH_DDRH6  = 0;
    
    DDRH_DDRH7  = 0;
   
    PITCE_PCE1=1;//定时器通道1使能
    
    PITMTLD1=160-1;// 80m赫兹 160分频 每个周期2us
                                                  
    PITLD1=2500-1;//  2us*2500=5ms
    
    PITMUX_PMUX1=0;   //第0通道使用微计数器0
    
    PITINTE_PINTE1=1;//定时器中断通道0,中断使能   
}
 
//-----ECT 初始化程序--------1ms//
void ECT_Init(void)
{
     
     //ECT模块速度反馈初始化
     TIOS = 0x0f;                     //通道0123设为输出比较，通道4567设为输入捕捉
     TC0= 0xee;
     TC1= 0xee;     
     TCTL3= 0x40;                     //第7通道设定为上升沿捕捉 ,其他通道禁止捕捉  
     TSCR2= 0b00000111;                //总线线频率128分频，1.6 us计数周期 ,禁止溢出中断 ,计数器重启禁止，自由计数 
     TIE  = 0x01;                     //禁止中断 启动 0 1 通道中断       
     TSCR1= 0x80;                     //启动定时器             
     //TCTL4=0x01;
     PACTL=0b01010000;
     PACNT=0;
     
}

