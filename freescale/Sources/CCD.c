#include  "ALL.h"

/* 128�����ص��ƽ��ADֵ */
unsigned char PixelAverageValue;
/* 128�����ص��ƽ����ѹֵ��10�� */
unsigned char PixelAverageVoltage;

/* �趨Ŀ��ƽ����ѹֵ��ʵ�ʵ�ѹ��10�� */
int TargetPixelAverageVoltage = 30;
/* �趨Ŀ��ƽ����ѹֵ��ʵ��ֵ��ƫ�ʵ�ʵ�ѹ��10�� */
int PixelAverageVoltageError = 0;
/* �趨Ŀ��ƽ����ѹֵ�����ƫ�ʵ�ʵ�ѹ��10�� */
int TargetPixelAverageVoltageAllowError = 2;

/* �ع�ʱ�䣬��λms */  
unsigned char IntegrationTime = 10;
unsigned char integration_piont=0;
unsigned char Pixel_H[128],Pixel_L[128],Left_Led,Right_Led;  //Data
char CCD_finsh_flag = 0;

//unsigned char send_data_cnt = 0;
//unsigned char *pixel_pt;


void CalculateIntegrationTime(void) 
{

    /* ����128�����ص��ƽ��ADֵ */
    PixelAverageValue = PixelAverage(128,Pixel_L);
    /* ����128�����ص��ƽ����ѹֵ,ʵ��ֵ��10�� */
    PixelAverageVoltage = (unsigned char)((int)PixelAverageValue * 25 / 128);

    PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
    if(PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
        IntegrationTime--;
    if(PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
        IntegrationTime++;
    if(IntegrationTime <= 1)
        IntegrationTime = 1;
    if(IntegrationTime >= 20)
        IntegrationTime = 20;
    
    
    integration_piont = 20 - IntegrationTime ; //����ƫ��Ƭ֮�� ҲҪ�����ع�ʱ��
  
}


unsigned char PixelAverage(unsigned char len, unsigned char *data) 
{
  unsigned char i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) 
  {
    sum = sum + *data++;
  }
  return ((unsigned char)(sum/len));
}

/*
void SendImageData(unsigned char * ImageData) 
{

    unsigned char i;
    unsigned char crc = 0;

   //  Send Data 
    SCI0_SendChar1('*');
    SCI0_SendChar1('L');
    SCI0_SendChar1('D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) 
    {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    SCI0_SendChar1('#');
}
*/

void StartIntegration(void) 
{
    unsigned char i;

    TSL1401_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL1401_SI = 0;         /* SI  = 0 */
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) 
    {
        SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 1;    // CLK = 1 
        SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 0;    // CLK = 0 
    }
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 1;        // CLK = 1 
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 0;        // CLK = 0 

}

void ImageCapture(unsigned char * ImageData_L,unsigned char * ImageData_H) 
{
    unsigned char i;
 // unsigned int  temp_int;

    TSL1401_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL1401_SI = 0;         /* SI  = 0 */
    SamplingDelay();

    //Delay 20us for sample the first pixel
    
    for(i = 0; i < 25; i++) 
    {                //����25����CCD��ͼ����ȥ�Ƚ�ƽ����
        Cpu_Delay1us();                      //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }  
      /*  SamplingDelay();
        SamplingDelay();*/

    //������LED����ܲ���
    ATD0CTL5_Cx = 6;
    while(ATD0STAT0_SCF == 0);
    Left_Led =  ATD0DR0L;
    
    ATD0CTL5_Cx = 5;
    while(ATD0STAT0_SCF == 0);
    Right_Led =  ATD0DR0L; 
    
    
    //Sampling CCD1 
    ATD0CTL5_Cx = 3;
    while(ATD0STAT0_SCF == 0);
    *ImageData_L++ =  ATD0DR0L;
    
    //Sampling CCD2
    ATD0CTL5_Cx = 4;
    while(ATD0STAT0_SCF == 0);
    *ImageData_H++ =  ATD0DR0L;
    
    TSL1401_CLK = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) 
    {
        SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 1;    /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
     /*   temp_int = AD_Measure12(3);
        *ImageData++ = temp_int; */
        
        ATD0CTL5_Cx = 3;
        while(ATD0STAT0_SCF == 0);
        *ImageData_L++ =  ATD0DR0L;
        
        ATD0CTL5_Cx = 4;
        while(ATD0STAT0_SCF == 0);
        *ImageData_H++ =  ATD0DR0L;
    
        
        TSL1401_CLK = 0;    /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */
    
    CCD_finsh_flag = 1;//CCD�ɼ����
}


void INIT_CCD(void) 
{
    unsigned char i;
    TSL1401_CLK_DDR = 1;
    TSL1401_SI_DDR  = 1;
    TSL1401_CLK = 0;
    TSL1401_SI  = 0;    
    /* Init Pixel Array */
    for(i=0; i<128+10; i++) {Pixel_L[i] = Pixel_H[i] = 0;}
    
   { //���ܼ���ʼ��
     DDRJ_DDRJ0 = 0;//����Ϊ����  
     PPSJ_PPSJ0 = 0;//�½��ش���
     PIEJ_PIEJ0 = 1;//ʹ���ⲿJ0�ж�
     
     DDRJ_DDRJ1 = 0;//����Ϊ����  
     PPSJ_PPSJ1 = 0;//�½��ش���
     PIEJ_PIEJ1 = 1;//ʹ���ⲿJ1�ж�
   }
}


void SendHex(unsigned char hex) 
{
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) 
  {
    SCI0_SendChar1(temp + '0');
  } 
  else 
  {
    SCI0_SendChar1(temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) 
  {
    SCI0_SendChar1(temp + '0');
  } 
  else 
  {
    SCI0_SendChar1(temp - 10 + 'A');
  }
}
