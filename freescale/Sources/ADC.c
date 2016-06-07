#include "ALL.h"

// CCD1  AD3
// CCD2  AD4
/*
*********************************************************************************************************
* Description: AD_Init
*********************************************************************************************************
*/
void AD_Init(void) {
    ATD0CTL4 = 0x10;                    /* Set sample time and prescaler */
    ATD0CTL3 = 0x88;                    /* Right justified data,Conversion Sequence Length = 1 */
    ATD0CTL0 = 0x0F;                    /* Set wrap around */
    ATD0CTL1 = 0x0F;                    /* 12-bit data */
    ATD0CTL2 = 0x40;                    /* Fast Flag Clear */
}
/*
*********************************************************************************************************
* Description: AD_Measure12
*********************************************************************************************************
*/
unsigned short AD_Measure12(unsigned char Channel) {
    ATD0CTL5_Cx = Channel;
    while(ATD0STAT0_SCF == 0);
    return ATD0DR0L;
}