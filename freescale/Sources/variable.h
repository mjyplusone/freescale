extern float Angle_gy;      //由角速度计算的倾斜角度

extern float Angle_ax;      //由加速度计算的倾斜角度

extern float Angle;         //小车最终倾斜角度

extern short gyro_zero;//陀螺仪零点

extern unsigned char TimerFlag20ms;


void trans (int a,unsigned char b[3]);
void trans_four(float a, char b[4]);
void trans_five(float a, char b[5]);
void trans_float(float a,char b[4]); 
void trans_unsigned(int a,unsigned char b[2]);



#ifndef int8_t
typedef signed char         int8_t;
#endif
#ifndef int16_t
typedef signed int          int16_t;
#endif
#ifndef int32_t
typedef signed long int     int32_t;
#endif

#ifndef uint8_t
typedef unsigned char       uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int        uint16_t;
#endif
#ifndef uint32_t
typedef unsigned long int   uint32_t;
#endif
#ifndef TPE_Float
typedef float               TPE_Float;
#endif
#ifndef char_t
typedef char                char_t;
#endif
