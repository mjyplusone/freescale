#ifndef    __PWM_H
#define    __PWM_H


extern  void INIT_mpu();

#define  uchar unsigned char 

#define  uint  unsigned int 

#define SMPLRT_DIV  0x19 //�����ǲ����ʪ�����ֵ��0x07(125Hz) 

#define CONFIG   0x1A //��ͨ�˲�Ƶ�ʪ�����ֵ��0x06(5Hz) 

#define GYRO_CONFIG  0x1B //�������Լ켰������Χ������ֵ��0x18(���Լ쪢2000deg/s) 

#define ACCEL_CONFIG 0x1C //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʪ�����ֵ��0x01(���Լ쪢2G��5Hz) 

#define ACCEL_XOUT_H 0x3B 

#define ACCEL_XOUT_L 0x3C 

#define ACCEL_YOUT_H 0x3D 

#define ACCEL_YOUT_L 0x3E 

#define ACCEL_ZOUT_H 0x3F 

#define ACCEL_ZOUT_L 0x40 

#define TEMP_OUT_H  0x41 

#define TEMP_OUT_L  0x42 

#define GYRO_XOUT_H  0x43 

#define GYRO_XOUT_L 0x44  

#define GYRO_YOUT_H  0x45 

#define GYRO_YOUT_L  0x46 

#define GYRO_ZOUT_H  0x47 

#define GYRO_ZOUT_L  0x48 

#define PWR_MGMT_1  0x6B //��Դ��������ֵ��0x00(��������) 

#define WHO_AM_I   0x75 //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��) 

#define SlaveAddress 0xD0 //IICд��ʱ�ĵ�ַ�ֽ����ݪ�+1Ϊ��ȡ 

#define SDA PORTE_PE3 

#define SCL PORTE_PE2 
