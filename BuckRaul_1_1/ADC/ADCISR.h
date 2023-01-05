/*
 * ADCISR.h
 *
 *  Created on: Nov 9, 2017
 *      Author: chisst1
 */

#ifndef ADCISR_H_
#define ADCISR_H_

//#include "HW_SW_INTERFACE.h"
#include "Filter.h"

interrupt void ADCCTL_ADCA1_ISR(void);
interrupt void ADCCTL_ADCA2_ISR(void);
interrupt void ADCCTL_ADCA3_ISR(void);
interrupt void ADCCTL_ADCA4_ISR(void);

interrupt void ADCCTL_ADCB1_ISR(void);
interrupt void ADCCTL_ADCB2_ISR(void);
interrupt void ADCCTL_ADCB3_ISR(void);
interrupt void ADCCTL_ADCB4_ISR(void);

interrupt void ADCCTL_ADCC1_ISR(void);
interrupt void ADCCTL_ADCC2_ISR(void);
interrupt void ADCCTL_ADCC3_ISR(void);
interrupt void ADCCTL_ADCC4_ISR(void);

interrupt void ADCCTL_ADCD1_ISR(void);
interrupt void ADCCTL_ADCD2_ISR(void);
interrupt void ADCCTL_ADCD3_ISR(void);
interrupt void ADCCTL_ADCD4_ISR(void);

typedef struct
{
    float finalVout; // variable for final result
    float finalVin; // variable for final result
    float finalIin;
    float finalIout;
    float finalResult5;
}ADC_tstADCResult;

typedef struct
{
    volatile Uint16 *rawResult1; // pointer for raw result
    volatile Uint16 *rawIin; // pointer for raw result
    volatile Uint16 *rawIout;
    volatile Uint16 *rawVout;
    volatile Uint16 *rawVin;
}ADC_tstADCResultRaw;

typedef struct
{
    float fOffset;
    float fSlope;
    D1F stFilter;

}ADC_tstADCResult_Filtered;

#define nFilterArray_Init { {    0 ,                HSI_TestScaleFactor ,                          D1F_5HZ() },  /* P_V_Meas */\
                            {    0 ,                HSI_TestScaleFactor ,                          D1F_5HZ() },  /* P_I_Meas */\
                            {    0 ,                HSI_TestScaleFactor ,                          D1F_5HZ() },  /* P_I_Meas */\
                            {    0 ,                HSI_TestScaleFactor ,                          D1F_5HZ() },  /* P_I_Meas */\
                            {    0 ,                HSI_TestScaleFactor ,                          D1F_5HZ() }  /* P_I_Meas */\
                          }

#define Index_0 0
#define Iin 1
#define Iout 2
#define Vout 3
#define Vin 4

#define nLastMeasIndex  5

extern ADC_tstADCResult ADC_stADCResult;

#endif /* ADCISR_H_ */
