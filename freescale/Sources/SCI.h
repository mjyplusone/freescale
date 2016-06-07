#ifndef    __SCI_H
#define    __SCI_H

extern unsigned char sci_data;
void INIT_SCI(void);
void SCI_Transmit(unsigned char data);
unsigned char SCI_Receive(void);
void SCI_Send(unsigned char *data);
void SCI_Control(void);

//ÐéÄâÊ¾²¨Æ÷Ê¹ÓÃ
typedef short                int16;
typedef signed char          int8;
typedef unsigned short       uint16;  

void OutPut_Data(void);  
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
extern short OutData[4];  



uint8_t SCI0_SendChar(uint8_t Chr); 
void SCI0_SendChar1(uint8_t Chr); 
uint8_t SCI0_RecvChar(uint8_t *Chr); 
uint8_t SCI0_RecvChar1(void) ;


#define ERR_OK           0U            /* OK */
#define ERR_SPEED        1U            /* This device does not work in the active speed mode. */
#define ERR_RANGE        2U            /* Parameter out of range. */
#define ERR_VALUE        3U            /* Parameter of incorrect value. */
#define ERR_OVERFLOW     4U            /* Timer overflow. */
#define ERR_MATH         5U            /* Overflow during evaluation. */
#define ERR_ENABLED      6U            /* Device is enabled. */
#define ERR_DISABLED     7U            /* Device is disabled. */
#define ERR_BUSY         8U            /* Device is busy. */
#define ERR_NOTAVAIL     9U            /* Requested value or method not available. */
#define ERR_RXEMPTY      10U           /* No data in receiver. */
#define ERR_TXFULL       11U           /* Transmitter is full. */
#define ERR_BUSOFF       12U           /* Bus not available. */
#define ERR_OVERRUN      13U           /* Overrun error is detected. */
#define ERR_FRAMING      14U           /* Framing error is detected. */
#define ERR_PARITY       15U           /* Parity error is detected. */
#define ERR_NOISE        16U           /* Noise error is detected. */
#define ERR_IDLE         17U           /* Idle error is detected. */
#define ERR_FAULT        18U           /* Fault error is detected. */
#define ERR_BREAK        19U           /* Break char is received during communication. */
#define ERR_CRC          20U           /* CRC error is detected. */
#define ERR_ARBITR       21U           /* A node losts arbitration. This error occurs if two nodes start transmission at the same time. */
#define ERR_PROTECT      22U           /* Protection error is detected. */
#define ERR_UNDERFLOW    23U           /* Underflow error is detected. */
#define ERR_UNDERRUN     24U           /* Underrun error is detected. */
#define ERR_COMMON       25U           /* Common error of a device. */
#define ERR_LINSYNC      26U           /* LIN synchronization error is detected. */
#define ERR_FAILED       27U           /* Requested functionality or process failed. */
#define ERR_QFULL        28U           /* Queue is full. */




#endif


//All.h  + value.h