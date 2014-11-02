
/* Declarations from DAVE3 Code Generation */
#include <DAVE3.h>

/* To store the conversion result */
ADC001_ResultHandleType Result;


/* Global Result Register ISR*/
void GlobalResultEvent(void)
{
    /* Read the Result Register*/
    ADC001_GetResult(&ADC001_Handle0,&Result);
}
