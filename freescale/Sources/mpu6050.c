#include "ALL.h"

void delayM(unsigned int t) 

{  
   unsigned int i,j; 

   for(i=0;i<t;i++) 

   for(j=0;j<120;j++); 

}  


void sda_high()    //SDA�ߵ�ƽ�Ĳ��� 

{ 
    DDRE_DDRE3=1; 

    SDA=1; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop); 

} 

//************************************** 

//SDA�͵�ƽ�Ĳ��� 

//************************************** 

void sda_low()   //SDA�͵�ƽ�Ĳ��� 

{ 

    DDRE_DDRE3=1; 

    SDA=0; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop);   

} 

//************************************** 

//SCL�ߵ�ƽ���� 

//************************************** 

void scl_high()  //SCL�ߵ�ƽ���� 

{ 
    DDRE_DDRE2=1;; 

    SCL=1; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop); 

} 

//************************************** 

//SCL�͵�ƽ�Ĳ��� 

//************************************** 

void scl_low() //SCL�͵�ƽ�Ĳ��� 

{ 
    DDRE_DDRE2=1;; 

    SCL=0; 

    _asm(nop);                     

    _asm(nop); 

    _asm(nop);                    

    _asm(nop); 
} 

//************************************** 

//I2C��ʼ�ź� 

//************************************** 

void I2C_Start() 

{ 

    sda_high();                    //���������� 

    scl_high();                    //����ʱ���� 

    delayM(1);                 //��ʱ 

    sda_low();                    //�����½��� 

    delayM(1);                 //��ʱ 

    scl_low();                    //����ʱ���� 

} 

//************************************** 

//I2Cֹͣ�ź� 

//************************************** 

void I2C_Stop() 
{ 

    sda_low();                    //���������� 

    scl_high();                    //����ʱ���� 

    delayM(1);                 //��ʱ 

    sda_high();                    //���������� 

    delayM(1);                //��ʱ 

} 

//************************************** 

//I2C����Ӧ���ź� 

//��ڲ���:ack (0:ACK 1:NAK) 

//************************************** 

void I2C_SendACK(char ack) 

{    

    if(ack)   sda_high(); 

    else    

     sda_low(); //дӦ���ź� 

     scl_high();                    //����ʱ���� 

     delayM(1);                   //��ʱ 

     scl_low();                    //����ʱ���� 

     delayM(1);                   //��ʱ 

} 

//************************************** 

//I2C����Ӧ���ź� 

//************************************** 

uchar I2C_RecvACK() 

{    

    DDRE_DDRE3=0; 
    

    scl_high();                    //����ʱ���� 

    DDRE_DDRE3=0; 

    delayM(1);                //��ʱ 

    if(SDA==1) 

    { 
        cy=1; 
    } 

    else  

    { 
        cy=0; 
    } 

//    cy = SDA;                   //��Ӧ���ź� 

    scl_low();                    //����ʱ���� 

    delayM(1);                //��ʱ 

    DDRE_DDRE3=1;      
    
    return cy; 

} 

//************************************** 

//��I2C���߷���һ���ֽ����� 

//************************************** 

void I2C_SendByte(uchar dat) 

{ 

    uchar i; 

    for (i=0; i<8; i++)         //8λ������ 

    { 

        if((dat<<i)&0x80) 

        { 

            sda_high(); 

        } 

        else  

        { 

            sda_low(); 

        } 

       // SDA = cy;               //�����ݿ� 

        scl_high();                //����ʱ���� 

        delayM(1);              //��ʱ 

        scl_low();                //����ʱ���� 

        delayM(1);              //��ʱ 

    } 

    I2C_RecvACK(); 

} 

//************************************** 

//��I2C���߽���һ���ֽ����� 

//************************************** 

uchar I2C_RecvByte() 

{ 

    uchar i; 

    uchar dat = 0,cy; 

    sda_high();                    //ʹ���ڲ�����,׼����ȡ����, 

    DDRE_DDRE3=0; 

    for (i=0; i<8; i++)         //8λ������ 

    { 

        dat <<= 1; 

        scl_high();                //����ʱ���� 

        delayM(1);             //��ʱ 

        if(SDA==1) 

        { 

            cy=1;         
        } 

        else  

        { 

            cy=0; 

        } 

        dat |= cy;             //������              

        scl_low();                //����ʱ���� 

        delayM(1);             //��ʱ 

    } 

    DDRE_DDRE3=1; 

    return dat; 

} 

//************************************** 

//��I2C�豸д��һ���ֽ����� 

//************************************** 

void Single_WriteI2C(uchar REG_Address,uchar REG_data) 

{ 

    I2C_Start();                  //��ʼ�ź� 

    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź� 

    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ�� 

    I2C_SendByte(REG_data);       //�ڲ��Ĵ������ݪ� 

    I2C_Stop();                   //����ֹͣ�ź� 

} 

//************************************** 

//��I2C�豸��ȡһ���ֽ����� 

//************************************** 

uchar Single_ReadI2C(uchar REG_Address) 

{ 

   uchar REG_data; 

   I2C_Start();                   //��ʼ�ź� 

   I2C_SendByte(SlaveAddress);    //�����豸��ַ+д�ź� 

   I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ  

   I2C_Start();                   //��ʼ�ź� 

   I2C_SendByte(SlaveAddress+1);  //�����豸��ַ+���ź� 

   REG_data=I2C_RecvByte();       //�����Ĵ������� 

   I2C_SendACK(1);                //����Ӧ���ź� 

   I2C_Stop();                    //ֹͣ�ź� 

   return REG_data; 

} 

//************************************** 

//��ʼ��MPU6050 

//************************************** 

void InitMPU6050() 

{ 
   Single_WriteI2C(PWR_MGMT_1, 0x00); //�������״̬ 

   Single_WriteI2C(SMPLRT_DIV, 0x07); 

   Single_WriteI2C(CONFIG, 0x06); 

   Single_WriteI2C(GYRO_CONFIG, 0x18); 

   Single_WriteI2C(ACCEL_CONFIG, 0x01); 

} 

//************************************** 

//�ϳ����� 

//************************************** 

int GetData(uchar REG_Address) 

{ 

   uchar H,L; 

   H=Single_ReadI2C(REG_Address); 

   L=Single_ReadI2C(REG_Address+1); 

   return (H<<8)+L;   //�ϳ����� 

} 


short MPU6050_Get_Angle(float x,float y,float z,uchar dir) 

{ 

    float temp; 

    float res=0; 

    switch(dir) 

    { 

        case 0://����ȻZ��ĽǶ� 

        temp=sqrt((x*x+y*y))/z; 

        res=atan(temp); 

        break; 

        case 1://����ȻX��ĽǶ� 

        temp=x/sqrt((y*y+z*z)); 

        res=atan(temp); 

        break; 

        case 2://����ȻY��ĽǶ� 

        temp=y/sqrt((x*x+z*z)); 

        res=atan(temp); 

        break; 

    } 

    return res*180.0/3.1415926;//�ѻ���ת���ɽǶ� 

} 


void trans (int a, char b[2])
{
   b[0]=a/10+'0';
   b[1]=a%10+'0';
}
