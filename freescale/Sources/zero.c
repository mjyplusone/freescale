#include "ALL.h"
 
void Get_Gyro_Zero(void) 
{
    int i,gyro_all,gyro_zero;
    for(i=0;i<1000;i++) 
    {
        gyro_all += GetData(GYRO_YOUT_H); //Y����ٶ�
    }  
    gyro_zero =  gyro_all/1000;  
}