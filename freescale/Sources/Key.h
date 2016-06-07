#include <hidef.h>      /* common defines and macros */
#include "derivative.h"
#ifndef    __KEY_H
#define    __KEY_H


#define key_1 PORTA_PA2
#define key_2 PORTA_PA3
#define key_3 PORTA_PA4
#define key_4 PORTA_PA5
#define key_5 PORTA_PA6

#define Boma_1 PORTB_PB3
#define Boma_2 PORTB_PB2
#define Boma_3 PORTB_PB1
#define Boma_4 PORTB_PB0

void INIT_Key(void);

char key1_press(void);
char key2_press(void);
char key3_press(void);
char key4_press(void);
char key5_press(void);

char key_press(void);

void Key_Oled(void);

#endif