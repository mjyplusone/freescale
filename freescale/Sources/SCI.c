#include  "ALL.h"
unsigned char sci_data;
short OutData[4]={0,0,0,0}; 
   
void INIT_SCI() 
{
                            
      SCI0BDH=0x00;
      SCI0BDL=0x56; //总线为 80M，波特率为 57600   计算公式: 80M/(16*57600)  = 86.8(0X56)
  //    SCI0BDL=0X82;
      SCI0CR1=0x00;
      SCI0CR2=0x0C; //不允许中断，允许发送，允许接受
}
//单个字节发送子函数
void SCI_Transmit(unsigned char data)
{
  while(!SCI0SR1_TDRE);//SC0DR 处于忙状态，等待。
  SCI0DRL=data;
}

//单个字节接收子函数 
unsigned char SCI_Receive()
{  
   while(!SCI0SR1_RDRF);
   return SCI0DRL;
}

//可发送数组 需要结尾标志0
void SCI_Send(unsigned char *data) 
{
    do 
    {
      while(!SCI0SR1_TDRE);//SC0DR 处于忙状态，等待。
      SCI0DRL=*data;
      data++;
    }while(*data);                  
}
   
void SCI_Control(void) 
{
   unsigned char tem;
   unsigned char temp[5];  
     if(SCI0SR1_RDRF) //判断是否收到数据
  {  
       tem = SCI0DRL;//取走第一个char,判断需要改变的量
     // extern float Speed_Control_P, Speed_Control_I;  
     //  SCI_Control_flag =1;//关闭其他发送数据的方式
       SCI_Send("OK\n");//返回成功信息
       
       tem = SCI_Receive();
       if(tem == 'A')//Angle 参数
       {
          tem = SCI_Receive();
          if(tem == 'P')
          {
            tem = SCI_Receive(); //取走空格
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0'; //录入数据
            Angle_P =  temp[0]*10 + temp[1];  
            
            SCI_Send("Angle_P "); //返回成功信息
            SCI_Transmit((int)Angle_P/10+'0');SCI_Transmit((int)Angle_P%10+'0'); 
          }
          else if(tem == 'D')
          {
            tem = SCI_Receive();
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0';// temp[1]为小数点
            temp[2]=SCI_Receive()-'0'; temp[3]=SCI_Receive()-'0';
            temp[4]=SCI_Receive()-'0';
            Angle_D =  (float)(temp[0]*1000 + temp[2]*100 + temp[3]*10 + temp[4] )/1000; 
            
            SCI_Send("Angle_D ");
            SCI_Transmit((int)(Angle_D)+'0');SCI_Transmit('.');
            SCI_Transmit((int)(Angle_D*10)%10+'0');SCI_Transmit((int)(Angle_D*100)%10+'0');
            SCI_Transmit((int)(Angle_D*1000)%10+'0');
          } 
          else if(tem == 'S')
          {
            tem = SCI_Receive();
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0';// temp[1]为小数点
            temp[2]=SCI_Receive()-'0'; temp[3]=SCI_Receive()-'0';
            temp[4]=SCI_Receive()-'0';
            Angle_Set = (float)(temp[0]*1000 + temp[2]*100 + temp[3]*10 + temp[4] )/1000;
            
            SCI_Send("Angle_Set ");
            SCI_Transmit((int)(Angle_Set)+'0');SCI_Transmit('.');
            SCI_Transmit((int)(Angle_Set*10)%10+'0');SCI_Transmit((int)(Angle_Set*100)%10+'0');
            SCI_Transmit((int)(Angle_Set*1000)%10+'0');
          }
       } 
       else if(tem == 'S')//Speed 参数
       {
          tem = SCI_Receive();
          if(tem == 'P')
          {
            tem = SCI_Receive(); 
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0';
            Speed_Control_P =  temp[0]*10 + temp[1];
            
            SCI_Send("Speed_Control_P ");
            SCI_Transmit((int)Speed_Control_P/10+'0');SCI_Transmit((int)Speed_Control_P%10+'0');    
          } 
          else if(tem == 'I')
          {
            tem = SCI_Receive();
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0';
            temp[2]=SCI_Receive()-'0'; temp[3]=SCI_Receive()-'0';
            temp[4]=SCI_Receive()-'0';
            Speed_Control_I =   (float)(temp[0]*1000 + temp[2]*100 + temp[3]*10 + temp[4] )/1000;
            
            SCI_Send("Speed_Control_I ");
            SCI_Transmit((int)(Speed_Control_I)+'0');SCI_Transmit('.');
            SCI_Transmit((int)(Speed_Control_I*10)%10+'0');SCI_Transmit((int)(Speed_Control_I*100)%10+'0');
            SCI_Transmit((int)(Speed_Control_I*1000)%10+'0');
          }
          else if(tem == 'S')
          {
            tem = SCI_Receive(); 
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0';
            Speed_Set =  temp[0]*10 + temp[1]; 
            
            SCI_Send("Speed_Set "); 
            SCI_Transmit(Speed_Set/10+'0');SCI_Transmit(Speed_Set%10+'0');   
          }    
       }
       else if(tem == 'D')//Direction 参数
       {
          tem = SCI_Receive();
          if(tem == 'P')
          {
            tem = SCI_Receive(); 
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0';
            Direction_Control_P =  temp[0]*10 + temp[1]; 
            
            SCI_Send("Direction_Control_P ");
            SCI_Transmit((int)Direction_Control_P/10+'0');SCI_Transmit((int)Direction_Control_P%10+'0');     
          }
          else if(tem == 'D')
          {
            tem = SCI_Receive();
            temp[0]=SCI_Receive()-'0'; temp[1]=SCI_Receive()-'0';
            temp[2]=SCI_Receive()-'0'; temp[3]=SCI_Receive()-'0';
            temp[4]=SCI_Receive()-'0';
            Direction_Control_D =  (float)(temp[0]*1000 + temp[1]*100 + temp[3]*10 + temp[4] )/100;
            
            SCI_Send("Direction_Control_D ");
             SCI_Transmit((int)(Direction_Control_D)/10+'0');
            SCI_Transmit((int)Direction_Control_D%10+'0');SCI_Transmit('.');
            SCI_Transmit((int)(Direction_Control_D*10)%10+'0');
            SCI_Transmit((int)(Direction_Control_D*100)%10+'0');
          }   
       }

       SCI_Transmit('\n');//结束时换行  
  }           
}
   
/**********************************************  
/
/   虚拟示波器使用函数
/   调用 OutPut_Data(void)  则把float OutData[4] 分别发送至4个通道 
***********************************************/  
//获得校验数（高低位）
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void OutPut_Data()
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
  {
  /*     float时
    temp[i]  = (int16)OutData[i];
    temp1[i] = (uint16)temp[i];
    databuf[i*2]   = (int8)(temp1[i]%256);
    databuf[i*2+1] = (int8)(temp1[i]/256);
  */
  
    databuf[i*2] =    (int8)(OutData[i]%256);
    databuf[i*2+1]  = (int8)(OutData[i]/256);
  
  }
  
  //8个数据加上最后两个校验位
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++) SCI_Transmit(databuf[i]); 
}


void SCI0_Init(void)
{
/*  Init_SCI init code */
  SCI0CR1 = 0x00;
  SCI0SR2 = 0x80;                      /* Switch to the alternative register set */
  SCI0ASR1 = 0x83;                     /* Clear alternative status flags */
  SCI0ACR1 = 0x00;
  SCI0ACR2 = 0x00;
  SCI0SR2 = 0x00;                      /* Switch to the normal register set */
  (void) SCI0SR1;                      /* Reset interrupt request flags */
  SCI0CR2 = 0x00;                      /* Disable error interrupts */
  SCI0BDH=0x00;
  SCI0BDL=0x2B;                       /* Set prescaler bits */
  SCI0CR2 |= (SCI0CR2_TE_MASK | SCI0CR2_RE_MASK); /* Enable transmitter, Enable receiver */
}

/*
*********************************************************************************************************
* Description: SCI0_SendChar
*********************************************************************************************************
*/
uint8_t SCI0_SendChar(uint8_t Chr) 
{
  if(SCI0SR1_TDRE == 0) {              /* Is the transmitter empty? */
    return ERR_TXFULL;                 /* If no then error */
  }
  SCI0DRL = (uint8_t)Chr;
  return ERR_OK;                       /* OK */
}


/*
*********************************************************************************************************
* Description: SCI0_SendChar1
*********************************************************************************************************
*/
void SCI0_SendChar1(uint8_t Chr) 
{
  while(SCI0SR1_TDRE == 0) {           /* Is the transmitter empty? */
  }
  SCI0DRL = (uint8_t)Chr;
}


/*
*********************************************************************************************************
* Description: SCI0_RecvChar
*********************************************************************************************************
*/
uint8_t SCI0_RecvChar(uint8_t *Chr) 
{
  uint8_t Result = ERR_OK;             /* Return error code */
  uint8_t StatReg = SCI0SR1;           /* Read status register */

  if (StatReg & (SCI0SR1_OR_MASK|SCI0SR1_NF_MASK|SCI0SR1_FE_MASK|SCI0SR1_PF_MASK)) { /* Is any error flag set? */
    Result = ERR_COMMON;               /* If yes then set common error value */
  } else if ((StatReg & SCI0SR1_RDRF_MASK) == 0) {  /* Is the reciver empty and no error is set? */
    return ERR_RXEMPTY;                /* If yes then error */
  } else {
    /* Else branch due to MISRA compliance */
  }
  *Chr = SCI0DRL;                      /* Read data from the receiver */
  return Result;                       /* Return error code */
}


/*
*********************************************************************************************************
* Description: SCI0_RecvChar1
*********************************************************************************************************
*/
uint8_t SCI0_RecvChar1(void)
{
  while(SCI0SR1_RDRF == 0) {           /* Is the reciver empty? */
  }
  return (uint8_t)SCI0DRL;             /* Read data from the receiver */
}
