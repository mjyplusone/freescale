#include "ALL.h"

float Angle_gy;      //由角速度计算的倾斜角度

float Angle_ax;      //由加速度计算的倾斜角度

float Angle;         //小车最终倾斜角度

//unsigned char TimerFlag20ms = 0;

short gyro_zero; //陀螺仪零点


void trans (int a,unsigned char b[3])
{
   if(a>=0) 
   {
      b[0]='+';
      b[1]=a/10%10+'0';
      b[2]=a%10+'0';
   }
   else                
   {
      a=-a;
      b[0]='-';
      b[1]=a/10%10+'0';
      b[2]=a%10+'0';
   }
   b[3]='\0';
}

void trans_unsigned (int a,unsigned char b[2])
{ 
      b[0]=a/10%10+'0';
      b[1]=a%10+'0';
      b[2]='\0';
}

void trans_four(float a, char b[4])
{
   if(a>=0) 
   {
      b[0]='+';
      b[1]=((int)a/100)+'0';
      b[2]=((int)a/10%10)+'0';
      b[3]=((int)a%10)+'0';
   }
   else 
   {
      a=-a;
      b[0]='-';
      b[1]=((int)a/100)+'0';
      b[2]=((int)a/10%10)+'0';
      b[3]=((int)a%10)+'0';
   }
   b[4]='\0';
}

void trans_five(float a, char b[5])
{
   if(a>=0) 
   {
      b[0]='+';
      b[1]=((int)a/1000)+'0';
      b[2]=((int)a/100%10)+'0';
      b[3]=((int)a/10%10)+'0';
      b[4]=((int)a%10)+'0';
   }
   else 
   {
      a=-a;
      b[0]='-';
      b[1]=((int)a/1000)+'0';
      b[2]=((int)a/100%10)+'0';
      b[3]=((int)a/10%10)+'0';
      b[4]=((int)a%10)+'0';
   }
   b[5]='\0';
}

void trans_float(float a,char b[4]) 
{
    b[0]=(int)a%10+'0';
    b[1]='.';
    b[2]=(int)(a*10)%10+'0';
    b[3]=(int)(a*100)%10+'0';
    b[4]='\0';
}
