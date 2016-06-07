#include "ALL.h"

void delayM(unsigned int t) 

{  
   unsigned int i,j; 

   for(i=0;i<t;i++) 

   for(j=0;j<120;j++); 

}  


void sda_high()    //SDA高电平的产生 

{ 
    DDRE_DDRE3=1; 

    SDA=1; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop); 

} 

//************************************** 

//SDA低电平的产生 

//************************************** 

void sda_low()   //SDA低电平的产生 

{ 

    DDRE_DDRE3=1; 

    SDA=0; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop);   

} 

//************************************** 

//SCL高电平产生 

//************************************** 

void scl_high()  //SCL高电平产生 

{ 
    DDRE_DDRE2=1;; 

    SCL=1; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop); 

} 

//************************************** 

//SCL低电平的产生 

//************************************** 

void scl_low() //SCL低电平的产生 

{ 
    DDRE_DDRE2=1;; 

    SCL=0; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop); 
} 

//************************************** 

//I2C起始信号 

//************************************** 

void I2C_Start() 

{ 

    sda_high();                    //拉高数据线 

    scl_high();                    //拉高时钟线 

    delayM(1);                 //延时 

    sda_low();                    //产生下降沿 

    delayM(1);                 //延时 

    scl_low();                    //拉低时钟线 

} 

//************************************** 

//I2C停止信号 

//************************************** 

void I2C_Stop() 
{ 

    sda_low();                    //拉低数据线 

    scl_high();                    //拉高时钟线 

    delayM(1);                 //延时 

    sda_high();                    //产生上升沿 

    delayM(1);                //延时 

} 

//************************************** 

//I2C发送应答信号 

//入口参数:ack (0:ACK 1:NAK) 

//************************************** 

void I2C_SendACK(char ack) 

{    

    if(ack)   sda_high(); 

    else    

     sda_low(); //写应答信号 

     scl_high();                    //拉高时钟线 

     delayM(1);                   //延时 

     scl_low();                    //拉低时钟线 

     delayM(1);                   //延时 

} 

//************************************** 

//I2C接收应答信号 

//************************************** 

uchar I2C_RecvACK() 

{    

    DDRE_DDRE3=0; 
    

    scl_high();                    //拉高时钟线 

    DDRE_DDRE3=0; 

    delayM(1);                //延时 

    if(SDA==1) 

    { 
        cy=1; 
    } 

    else  

    { 
        cy=0; 
    } 

//    cy = SDA;                   //读应答信号 

    scl_low();                    //拉低时钟线 

    delayM(1);                //延时 

    DDRE_DDRE3=1;      
    
    return cy; 

} 

//************************************** 

//向I2C总线发送一个字节数据 

//************************************** 

void I2C_SendByte(uchar dat) 

{ 

    uchar i; 

    for (i=0; i<8; i++)         //8位计数器 

    { 

        if((dat<<i)&0x80) 

        { 

            sda_high(); 

        } 

        else  

        { 

            sda_low(); 

        } 

       // SDA = cy;               //送数据口 

        scl_high();                //拉高时钟线 

        delayM(1);              //延时 

        scl_low();                //拉低时钟线 

        delayM(1);              //延时 

    } 

    I2C_RecvACK(); 

} 

//************************************** 

//从I2C总线接收一个字节数据 

//************************************** 

uchar I2C_RecvByte() 

{ 

    uchar i; 

    uchar dat = 0,cy; 

    sda_high();                    //使能内部上拉,准备读取数据, 

    DDRE_DDRE3=0; 

    for (i=0; i<8; i++)         //8位计数器 

    { 

        dat <<= 1; 

        scl_high();                //拉高时钟线 

        delayM(1);             //延时 

        if(SDA==1) 

        { 

            cy=1;         
        } 

        else  

        { 

            cy=0; 

        } 

        dat |= cy;             //读数据              

        scl_low();                //拉低时钟线 

        delayM(1);             //延时 

    } 

    DDRE_DDRE3=1; 

    return dat; 

} 

//************************************** 

//向I2C设备写入一个字节数据 

//************************************** 

void Single_WriteI2C(uchar REG_Address,uchar REG_data) 

{ 

    I2C_Start();                  //起始信号 

    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号 

    I2C_SendByte(REG_Address);    //内部寄存器地址 

    I2C_SendByte(REG_data);       //内部寄存器数据 

    I2C_Stop();                   //发送停止信号 

} 

//************************************** 

//从I2C设备读取一个字节数据 

//************************************** 

uchar Single_ReadI2C(uchar REG_Address) 

{ 

   uchar REG_data; 

   I2C_Start();                   //起始信号 

   I2C_SendByte(SlaveAddress);    //发送设备地址+写信号 

   I2C_SendByte(REG_Address);     //发送存储单元地址从0开始  

   I2C_Start();                   //起始信号 

   I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号 

   REG_data=I2C_RecvByte();       //读出寄存器数据 

   I2C_SendACK(1);                //接收应答信号 

   I2C_Stop();                    //停止信号 

   return REG_data; 

} 

//************************************** 

//初始化MPU6050 

//************************************** 

void InitMPU6050() 

{ 
   Single_WriteI2C(PWR_MGMT_1, 0x00); //解除休眠状态 

   Single_WriteI2C(SMPLRT_DIV, 0x07); 

   Single_WriteI2C(CONFIG, 0x06); 

   Single_WriteI2C(GYRO_CONFIG, 0x18); 

   Single_WriteI2C(ACCEL_CONFIG, 0x01); 

} 

//************************************** 

//合成数据 

//************************************** 

int GetData(uchar REG_Address) 

{ 

   uchar H,L; 

   H=Single_ReadI2C(REG_Address); 

   L=Single_ReadI2C(REG_Address+1); 

   return (H<<8)+L;   //合成数据 

} 


short MPU6050_Get_Angle(float x,float y,float z,uchar dir) 

{ 

    float temp; 

    float res=0; 

    switch(dir) 

    { 

        case 0://与自然Z轴的角度 

        temp=sqrt((x*x+y*y))/z; 

        res=atan(temp); 

        break; 

        case 1://与自然X轴的角度 

        temp=x/sqrt((y*y+z*z)); 

        res=atan(temp); 

        break; 

        case 2://与自然Y轴的角度 

        temp=y/sqrt((x*x+z*z)); 

        res=atan(temp); 

        break; 

    } 

    return res*180.0/3.1415926;//把弧度转换成角度 

} 


void trans (int a, char b[2])
{
   b[0]=a/10+'0';
   b[1]=a%10+'0';
}
