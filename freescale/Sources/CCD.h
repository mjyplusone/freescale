#ifndef CCD_H_
#define CCD_H_

/* TSL1401_CLK -- PORTA0 */
#define TSL1401_CLK_DDR     DDRA_DDRA0
#define TSL1401_CLK         PORTA_PA0

/* TSL1401_SI -- PORTA1 */
#define TSL1401_SI_DDR      DDRA_DDRA1
#define TSL1401_SI          PORTA_PA1

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

/* CPU delay 200ns at 80M bus clock */\
#define Cpu_Delay200ns() \
    { __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
    }

#define SamplingDelay() { Cpu_Delay200ns() }




void CalculateIntegrationTime(void);
unsigned char PixelAverage(unsigned char len, unsigned char *data);
//void SendImageData(unsigned char * ImageData);
void StartIntegration(void);
void ImageCapture(unsigned char * ImageData_L,unsigned char * ImageData_H);
void INIT_CCD(void);
void SendHex(unsigned char hex);

extern unsigned char Pixel_H[128],Pixel_L[128],Left_Led,Right_Led;  //Data
extern unsigned char IntegrationTime;//,send_data_cnt;
extern unsigned char integration_piont;
extern unsigned char PixelAverageValue;
extern char CCD_finsh_flag;
#endif 
