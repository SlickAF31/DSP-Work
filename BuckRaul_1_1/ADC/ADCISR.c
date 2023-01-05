/*
 * ADCISR.c
 *
 *  Created on: Nov 9, 2017
 *      Author: chisst1
 */

/* External headefiles */
#include "F28x_Project.h"
#include "ADCCTLi.h"
#include "ADCCTL.h"
#include "GPIO.h"
#include "ADCCTli_A.h"
#include "ADCCTli_B.h"
#include "ADCCTli_C.h"
#include "ADCCTli_D.h"

/* Own Headerfiles */
#include "ADCISRi.h"
#include "ADCISR.h"

#define nLength 100


const ADC_tstADCResultRaw ADC_stADCResultRaw = {&AdcaResultRegs.ADCRESULT0, //ADC A0 - SOC0  / Temp
                                                &AdcaResultRegs.ADCRESULT2, //ADC A2 - SOC2 / I out
                                                &AdcaResultRegs.ADCRESULT3, //ADC A3 - SOC3 / I in
                                                &AdcbResultRegs.ADCRESULT0, //ADC B2 - SOC0
                                                &AdcbResultRegs.ADCRESULT1, //ADC B3 - SOC1
                                               };

ADC_tstADCResult ADC_stADCResult;

ADC_tstADCResult_Filtered ADC_stMeasurementData[nLastMeasIndex] = nFilterArray_Init;


/************* ADC A Interrupt Service Routines *****************/

interrupt void ADCCTL_ADCA1_ISR(void)
{
    float fBuf;

    fBuf = *ADC_stADCResultRaw.rawIin * ADC_stMeasurementData[Iin].fSlope ;
    CalcD1F(fBuf, &ADC_stMeasurementData[Iin].stFilter);
    ADC_stADCResult.finalIin = (ADC_stMeasurementData[Iin].stFilter._out / 60) / 0.05 ;//calculate I in

    fBuf = *ADC_stADCResultRaw.rawIout * ADC_stMeasurementData[Iout].fSlope ;
    CalcD1F(fBuf, &ADC_stMeasurementData[Iout].stFilter);
    ADC_stADCResult.finalIout = ADC_stMeasurementData[Iout].stFilter._out / (60 * 0.05) ;  //calculate I out


    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

interrupt void ADCCTL_ADCA2_ISR(void)
{

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}


interrupt void ADCCTL_ADCA3_ISR(void)
{
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}


interrupt void ADCCTL_ADCA4_ISR(void)
{
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 4; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

/************* ADC B Interrupt Service Routines *****************/

interrupt void ADCCTL_ADCB1_ISR(void)
{
    float fBuf;

    fBuf = *ADC_stADCResultRaw.rawVout * ADC_stMeasurementData[Vout].fSlope - ADC_stMeasurementData[Vout].fOffset ;
    CalcD1F(fBuf, &ADC_stMeasurementData[Vout].stFilter);
    ADC_stADCResult.finalVout = ADC_stMeasurementData[Vout].stFilter._out * 7.25;  //Vout

    fBuf = *ADC_stADCResultRaw.rawVin * ADC_stMeasurementData[Vin].fSlope - ADC_stMeasurementData[Vin].fOffset ;
    CalcD1F(fBuf, &ADC_stMeasurementData[Vin].stFilter);
    ADC_stADCResult.finalVin = ADC_stMeasurementData[Vin].stFilter._out * 20; // V in

    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void ADCCTL_ADCB2_ISR(void)
{
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}


interrupt void ADCCTL_ADCB3_ISR(void)
{
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}


interrupt void ADCCTL_ADCB4_ISR(void)
{
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 4; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

/************* ADC C Interrupt Service Routines *****************/

interrupt void ADCCTL_ADCC1_ISR(void)
{
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // clear grup flag
}


interrupt void ADCCTL_ADCC2_ISR(void)
{
    AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10; //
}


interrupt void ADCCTL_ADCC3_ISR(void)
{
    AdccRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}


interrupt void ADCCTL_ADCC4_ISR(void)
{
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 4; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

/************* ADC D Interrupt Service Routines *****************/

interrupt void ADCCTL_ADCD1_ISR(void)
{
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void ADCCTL_ADCD2_ISR(void)
{
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}


interrupt void ADCCTL_ADCD3_ISR(void)
{
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}


interrupt void ADCCTL_ADCD4_ISR(void)
{
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 4; //clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}
