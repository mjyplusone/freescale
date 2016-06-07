#include "ALL.h"

/* CPU delay 1us at 80M bus clock */\
#define Cpu_Delay1us(){ __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);}


char CCD_Show_flag='L';
int key_F=2,key_pid_change;
char aa[2],bb[2];
int OLED_CCD_SHOW;
int column;


void INIT_Key(void)
{ 
   DDRA = DDRA & 0x83;   // X 0 0 0  0 0 X X 配置为输入模式  初始化按键
   PUCR_PUPAE=1;         //配置上拉电阻
   
   DDRB = DDRB & 0xF0;   // X X X X  0 0 0 0 配置为输入模式  初始化按键
   PUCR_PUPBE=1;         //配置上拉电阻
   
   //拨码开关 朝外则为0  朝内为1
}

char key1_press(){if(key_1==0){Cpu_Delay1us();if(key_1==0){while(key_1==0);return 1;}else return 0;	}	else return 0;}
char key2_press(){if(key_2==0){Cpu_Delay1us();if(key_2==0){while(key_2==0);return 1;}else return 0;	}	else return 0;}
char key3_press(){if(key_3==0){Cpu_Delay1us();if(key_3==0){while(key_3==0);return 1;}else return 0;	}	else return 0;}
char key4_press(){if(key_4==0){Cpu_Delay1us();if(key_4==0){while(key_4==0);return 1;}else return 0;	}	else return 0;}
char key5_press(){if(key_5==0){Cpu_Delay1us();if(key_5==0){while(key_5==0);return 1;}else return 0;	}	else return 0;}

char key_press()
{
 
  if(key_1==0)
  {
  Cpu_Delay1us();
  if(key_1==0){while(key_1==0);return 1;}
  } 
  else if(key_2==0){Cpu_Delay1us();if(key_2==0){while(key_2==0);return 2;}}
  else if(key_3==0){Cpu_Delay1us();if(key_3==0){while(key_3==0);return 3;}}
  else if(key_4==0){Cpu_Delay1us();if(key_4==0){while(key_4==0);return 4;}}
  else if(key_5==0){Cpu_Delay1us();if(key_5==0){while(key_5==0);return 5;}}
  else return 0;
}


/*  
     E.g.

       if(key1_press())LCD_P8x16Str(5,4,"key1");
       if(key2_press())LCD_P8x16Str(5,4,"key2");
       if(key3_press())LCD_P8x16Str(5,4,"key3");
       if(key4_press())LCD_P8x16Str(5,4,"key4");
       if(key5_press())LCD_P8x16Str(5,4,"key5");
           
              
       switch(key_press())  
       {
        case 1: LCD_P8x16Str(5,4,"key1"); break;
        case 2: LCD_P8x16Str(5,4,"key2"); break;
        case 3: LCD_P8x16Str(5,4,"key3"); break;
        case 4: LCD_P8x16Str(5,4,"key4"); break;
        case 5: LCD_P8x16Str(5,4,"key5"); break;
       }
           
*/



void Key_Oled(void) 
{
    switch(key_press()) 
    {
      case 0:break;
      
      case 1:   if(CCD_Show_flag == 'L') CCD_Show_flag = 'H';
                else CCD_Show_flag = 'L'; 
                LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
                LCD_WrCmd(0xc1);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
                break;
                
      case 2:   if(key_F==0) 
                {
                    key_F=1;
                    key_pid_change=1;
                    LCD_Fill(0x00);
                    LCD_Print(5,0,"Direction--PID");
                    LCD_Print(5,2,"P:");
                    trans_unsigned(Direction_Control_P,aa);
                    LCD_P8x16Str(20,2,aa);
                    LCD_Print(55,2,"<--");
                    LCD_Print(5,4,"D:");
                    trans_unsigned(Direction_Control_D,bb);
                    LCD_P8x16Str(20,4,bb);
                    break;
                } 
                else if(key_F==1) 
                {
                    key_F=2;
                    key_pid_change=2;
                    LCD_Fill(0x00);
                    LCD_Print(5,0,"Direction--PID");
                    LCD_Print(5,2,"P:");
                    trans_unsigned(Direction_P,aa);
                    LCD_P8x16Str(20,2,aa);
                    LCD_Print(5,4,"D:");
                    trans_unsigned(Direction_D,bb);
                    LCD_P8x16Str(20,4,bb);
                    LCD_Print(55,4,"<--");
                    break;
                } 
                else if(key_F==2) 
                {
                    key_F=0;
                    CCD_Show_flag = 0;
                    LCD_Fill(0x00);
                    LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
                    LCD_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
                    LCD_Print(5,0,"Direction--PID");
                    LCD_Print(5,2,"P:");
                    trans_unsigned(Direction_P,aa);
                    LCD_P8x16Str(20,2,aa);
                    LCD_Print(5,4,"D:");
                    trans_unsigned(Direction_D,bb);
                    LCD_P8x16Str(20,4,bb);
                    break;
                }
                
      case 3:   if(key_pid_change==1) 
                {
                    Direction_P += 1;
                    LCD_Fill(0x00);
                    LCD_Print(5,0,"Direction--PID");
                    LCD_Print(5,2,"P:");
                    trans_unsigned(Direction_P,aa);
                    LCD_P8x16Str(20,2,aa);
                    LCD_Print(5,4,"D:");
                    trans_unsigned(Direction_D,bb);
                    LCD_P8x16Str(20,4,bb);
                    break;
                } 
                else if(key_pid_change==2) 
                {
                    Direction_D += 1;
                    LCD_Fill(0x00);
                    LCD_Print(5,0,"Direction--PID");
                    LCD_Print(5,2,"P:");
                    trans_unsigned(Direction_P,aa);
                    LCD_P8x16Str(20,2,aa);
                    LCD_Print(5,4,"D:");
                    trans_unsigned(Direction_D,bb);
                    LCD_P8x16Str(20,4,bb);
                    break;
                }
       case 4:   if(key_pid_change==1) 
                {
                    Direction_P -= 1;
                    LCD_Fill(0x00);
                    LCD_Print(5,0,"Direction--PID");
                    LCD_Print(5,2,"P:");
                    trans_unsigned(Direction_P,aa);
                    LCD_P8x16Str(20,2,aa);
                    LCD_Print(5,4,"D:");
                    trans_unsigned(Direction_D,bb);
                    LCD_P8x16Str(20,4,bb);
                    break;
                } 
                else if(key_pid_change==2) 
                {
                    Direction_D -= 1;
                    LCD_Fill(0x00);
                    LCD_Print(5,0,"Direction--PID");
                    LCD_Print(5,2,"P:");
                    trans_unsigned(Direction_P,aa);
                    LCD_P8x16Str(20,2,aa);
                    LCD_Print(5,4,"D:");
                    trans_unsigned(Direction_D,bb);
                    LCD_P8x16Str(20,4,bb);
                    break;
                }
    }
    
     
   
    if(CCD_Show_flag == 'H')
    {
      LCD_Fill(0x00);
      for(OLED_CCD_SHOW=0; OLED_CCD_SHOW<128; OLED_CCD_SHOW++) 
      {LCD_PutPixel(OLED_CCD_SHOW,Pixel_H[OLED_CCD_SHOW]/4);}
      for(column=0;column<64;column++)//H边线 
      {
        LCD_PutPixel(Left_Line_H,column);
      }
      for(column=0;column<64;column++)//H边线 
      {                     
        LCD_PutPixel(Right_Line_H,column);
      } 
      for(column=0;column<64;column++)// 
      {
        LCD_PutPixel2(Center_Line_H,column);
      } 
    }
    
    if(CCD_Show_flag == 'L')
    {
      LCD_Fill(0x00);
      for(OLED_CCD_SHOW=0; OLED_CCD_SHOW<128; OLED_CCD_SHOW++) 
      {LCD_PutPixel(OLED_CCD_SHOW,Pixel_L[OLED_CCD_SHOW]/4);}
      
      for(column=0;column<64;column++)//三条边线 
      {
        LCD_PutPixel(Left_Line_new,column);
      } 
      for(column=0;column<64;column++)// 
      {
        LCD_PutPixel(Right_Line_new,column);
      } 
      for(column=0;column<64;column++)// 
      {
        LCD_PutPixel2(Center_Line,column);
      } 
       for(column=0;column<64;column++)// 
      {
        LCD_PutPixel2(64-Center_Line_transform_new,column);
      } 
    }
}
