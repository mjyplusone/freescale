#include "ALL.h"

void INIT_PWM() 
{
//busF / ��Ƶϵ�� /��PWMSCLA * 2 ��
    PWMPRCLK = 0x33;   //Aʱ�Ӻ�Bʱ�ӵķ�Ƶϵ��Ϊ8,Ƶ��Ϊ10MHz
//    PWMSCLA  =  100;   //SAʱ��Ƶ��Ϊ400KHz
//    PWMSCLB  =  100;   //SBʱ��Ƶ��Ϊ400KHz
    
// ǰ�� �� ��� �Һ�
    
    //67���� Ϊ PWM4   left down  ��
    PWMCTL_CON67= 1;   //����ͨ��0,1Ϊ16λ��PWM
    PWMPOL_PPOL7= 1;   //ͨ��01�ļ���Ϊ�ߵ�ƽ��Ч
    PWMCLK_PCLK7 =0;   //ͨ��07��Aʱ����Ϊʱ��Դ
    PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
    PWMPER67  = 1000;  //ͨ��01������Ϊ1Hz 
    PWMDTY67  = 0;     //ͨ��01��ռ�ձ�Ϊ0%  
    PWME_PWME7 = 1;    //ʹ��ͨ��01

//23���� Ϊ PWM1      left up     ����
    PWMCTL_CON23= 1;   //����ͨ��0,1Ϊ16λ��PWM
    PWMPOL_PPOL3= 1;   //ͨ��01�ļ���Ϊ�ߵ�ƽ��Ч
    PWMCLK_PCLK3 =0;   //ͨ��03��Bʱ����Ϊʱ��Դ
    PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
    PWMPER23  = 1000;  //ͨ��01������Ϊ1Hz 
    PWMDTY23  = 0;   //ͨ��01��ռ�ձ�Ϊ0%  
    PWME_PWME3 = 1;    //ʹ��ͨ��23
    
      
// ǰ�� �� ��� �Һ�
   
 //45���� Ϊ PWM3      right up    �ҷ�
    PWMCTL_CON45= 1;   //����ͨ��0,1Ϊ16λ��PWM
    PWMPOL_PPOL5= 1;   //ͨ��01�ļ���Ϊ�ߵ�ƽ��Ч
    PWMCLK_PCLK5 =0;   //ͨ��05��Aʱ����Ϊʱ��Դ
    PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
    PWMPER45  = 1000;  //ͨ��01������Ϊ1Hz 
    PWMDTY45  = 0;     //ͨ��01��ռ�ձ�Ϊ20%  
    PWME_PWME5 = 1;    //ʹ��ͨ��01
    
 //01���� Ϊ PWM2      right down    ����
    PWMCTL_CON01= 1;   //����ͨ��0,1Ϊ16λ��PWM
    PWMPOL_PPOL1= 1;   //ͨ��01�ļ���Ϊ�ߵ�ƽ��Ч
    PWMCLK_PCLK1 =0;   //ͨ��01��Aʱ����Ϊʱ��Դ
    PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
    PWMPER01  = 1000;  //ͨ��01������Ϊ1Hz 
    PWMDTY01  = 0;     //ͨ��01��ռ�ձ�Ϊ0%  
    PWME_PWME1 = 1;    //ʹ��ͨ��01
}
/*
choose   =0 �������� =1 ��������
dir      =0 Ϊ��ǰת  =1  Ϊ���ת
rate     ռ�ձ�
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
