#ifndef    __ANGLE_H
#define    __ANGLE_H

#define Gravity_X_Zero 360
#define Gravity_Y_Zero -270
#define Gravity_Z_Zero 0 //待测

void delayM(unsigned int t); 
void sda_high(void);  //SDA高电平的产生 
void sda_low(void);  //SDA低电平的产生 
void scl_high(void);  //SCL高电平产生 
void scl_low(void); //SCL低电平的产生 
void I2C_Start(void); 
void I2C_Stop(void); 
void I2C_SendACK(char ack); 
void I2C_RecvACK(void); 
void I2C_SendByte(uchar dat);    
uchar I2C_RecvByte(void); 
void Single_WriteI2C(uchar REG_Address,uchar REG_data); 
uchar Single_ReadI2C(uchar REG_Address); 
void InitMPU6050(void); 
short GetData(uchar REG_Address);
float MPU6050_Get_Angle(float,float); 
void trans (int a,unsigned char b[3]);
void trans_four(float a, char b[4]);
void trans_five(float a, char b[5]);

void Kalman_Filter(float,float);

void Angle_Calcu(void);
void Get_Gyro_Zero(void);
void Get_Gravity_Zero(void);
void Show_Angle(void);
void Angle_Control(void);
void Speed_Adjust(float,float);


void Get_MMA7361(void);


extern int Angle_Speed;
extern int Accel_x,Accel_y,Accel_z;
extern float Gyro_y ;
extern float x_zero,y_zero,z_zero;
extern float Angle_P,Angle_D,Angle_Set;
extern short Dead_Motor_0,Dead_Motor_1;
extern int x_MMA7361,y_MMA7361,z_MMA7361; //MMA7361

#endif

/*   函数废弃
void Get_Gravity(void)
void Get_Gyro(void); 
*/