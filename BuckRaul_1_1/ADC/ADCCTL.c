/**
 * @file ADC1C1.c
 * @author Stefan Chisozan
 * @date 28.07.2016
 * @brief ADC Control - source file
 * @department D&D AE
 *
 * @bug No known bugs.
 */
#include "F28x_Project.h"
#include "ADCCTLi.h"
#include "ADCCTL.h"
#include "GPIO.h"
#include "ADCISR.h"
#include "ADCCTLi_A.h"
#include "ADCCTLi_B.h"
#include "ADCCTLi_C.h"
#include "ADCCTLi_D.h"

int ADCA_ChSel[16] =   {ADCA_SOC0_ChSel,ADCA_SOC1_ChSel,ADCA_SOC2_ChSel,ADCA_SOC3_ChSel,
                        ADCA_SOC4_ChSel,ADCA_SOC5_ChSel,ADCA_SOC6_ChSel,ADCA_SOC7_ChSel,
                        ADCA_SOC8_ChSel,ADCA_SOC9_ChSel,ADCA_SOC10_ChSel,ADCA_SOC11_ChSel,
                        ADCA_SOC12_ChSel,ADCA_SOC13_ChSel,ADCA_SOC14_ChSel,ADCA_SOC15_ChSel};

int ADCA_ACQPS[16] =   {ADCA_SOC0_ACQPS,ADCA_SOC1_ACQPS,ADCA_SOC2_ACQPS,ADCA_SOC3_ACQPS,
                        ADCA_SOC4_ACQPS,ADCA_SOC5_ACQPS,ADCA_SOC6_ACQPS,ADCA_SOC7_ACQPS,
                        ADCA_SOC8_ACQPS,ADCA_SOC9_ACQPS,ADCA_SOC10_ACQPS,ADCA_SOC11_ACQPS,
                        ADCA_SOC12_ACQPS,ADCA_SOC13_ACQPS,ADCA_SOC14_ACQPS,ADCA_SOC15_ACQPS};

int ADCA_TrigSel[16] = {ADCA_SOC0_Trigsel,ADCA_SOC1_Trigsel,ADCA_SOC2_Trigsel,ADCA_SOC3_Trigsel,
                        ADCA_SOC4_Trigsel,ADCA_SOC5_Trigsel,ADCA_SOC6_Trigsel,ADCA_SOC7_Trigsel,
                        ADCA_SOC8_Trigsel,ADCA_SOC9_Trigsel,ADCA_SOC10_Trigsel,ADCA_SOC11_Trigsel,
                        ADCA_SOC12_Trigsel,ADCA_SOC13_Trigsel,ADCA_SOC14_Trigsel,ADCA_SOC15_Trigsel};


int ADCB_ChSel[16] =   {ADCB_SOC0_ChSel,ADCB_SOC1_ChSel,ADCB_SOC2_ChSel,ADCB_SOC3_ChSel,
                        ADCB_SOC4_ChSel,ADCB_SOC5_ChSel,ADCB_SOC6_ChSel,ADCB_SOC7_ChSel,
                        ADCB_SOC8_ChSel,ADCB_SOC9_ChSel,ADCB_SOC10_ChSel,ADCB_SOC11_ChSel,
                        ADCB_SOC12_ChSel,ADCB_SOC13_ChSel,ADCB_SOC14_ChSel,ADCB_SOC15_ChSel};

int ADCB_ACQPS[16] =   {ADCB_SOC0_ACQPS,ADCB_SOC1_ACQPS,ADCB_SOC2_ACQPS,ADCB_SOC3_ACQPS,
                        ADCB_SOC4_ACQPS,ADCB_SOC5_ACQPS,ADCB_SOC6_ACQPS,ADCB_SOC7_ACQPS,
                        ADCB_SOC8_ACQPS,ADCB_SOC9_ACQPS,ADCB_SOC10_ACQPS,ADCB_SOC11_ACQPS,
                        ADCB_SOC12_ACQPS,ADCB_SOC13_ACQPS,ADCB_SOC14_ACQPS,ADCB_SOC15_ACQPS};

int ADCB_TrigSel[16] = {ADCB_SOC0_Trigsel,ADCB_SOC1_Trigsel,ADCB_SOC2_Trigsel,ADCB_SOC3_Trigsel,
                        ADCB_SOC4_Trigsel,ADCB_SOC5_Trigsel,ADCB_SOC6_Trigsel,ADCB_SOC7_Trigsel,
                        ADCB_SOC8_Trigsel,ADCB_SOC9_Trigsel,ADCB_SOC10_Trigsel,ADCB_SOC11_Trigsel,
                        ADCB_SOC12_Trigsel,ADCB_SOC13_Trigsel,ADCB_SOC14_Trigsel,ADCB_SOC15_Trigsel};


int ADCC_ChSel[16] =   {ADCC_SOC0_ChSel,ADCC_SOC1_ChSel,ADCC_SOC2_ChSel,ADCC_SOC3_ChSel,
                        ADCC_SOC4_ChSel,ADCC_SOC5_ChSel,ADCC_SOC6_ChSel,ADCC_SOC7_ChSel,
                        ADCC_SOC8_ChSel,ADCC_SOC9_ChSel,ADCC_SOC10_ChSel,ADCC_SOC11_ChSel,
                        ADCC_SOC12_ChSel,ADCC_SOC13_ChSel,ADCC_SOC14_ChSel,ADCC_SOC15_ChSel};

int ADCC_ACQPS[16] =   {ADCC_SOC0_ACQPS,ADCC_SOC1_ACQPS,ADCC_SOC2_ACQPS,ADCC_SOC3_ACQPS,
                        ADCC_SOC4_ACQPS,ADCC_SOC5_ACQPS,ADCC_SOC6_ACQPS,ADCC_SOC7_ACQPS,
                        ADCC_SOC8_ACQPS,ADCC_SOC9_ACQPS,ADCC_SOC10_ACQPS,ADCC_SOC11_ACQPS,
                        ADCC_SOC12_ACQPS,ADCC_SOC13_ACQPS,ADCC_SOC14_ACQPS,ADCC_SOC15_ACQPS};

int ADCC_TrigSel[16] = {ADCC_SOC0_Trigsel,ADCC_SOC1_Trigsel,ADCC_SOC2_Trigsel,ADCC_SOC3_Trigsel,
                        ADCC_SOC4_Trigsel,ADCC_SOC5_Trigsel,ADCC_SOC6_Trigsel,ADCC_SOC7_Trigsel,
                        ADCC_SOC8_Trigsel,ADCC_SOC9_Trigsel,ADCC_SOC10_Trigsel,ADCC_SOC11_Trigsel,
                        ADCC_SOC12_Trigsel,ADCC_SOC13_Trigsel,ADCC_SOC14_Trigsel,ADCC_SOC15_Trigsel};


int ADCD_ChSel[16] =   {ADCD_SOC0_ChSel,ADCD_SOC1_ChSel,ADCD_SOC2_ChSel,ADCD_SOC3_ChSel,
                        ADCD_SOC4_ChSel,ADCD_SOC5_ChSel,ADCD_SOC6_ChSel,ADCD_SOC7_ChSel,
                        ADCD_SOC8_ChSel,ADCD_SOC9_ChSel,ADCD_SOC10_ChSel,ADCD_SOC11_ChSel,
                        ADCD_SOC12_ChSel,ADCD_SOC13_ChSel,ADCD_SOC14_ChSel,ADCD_SOC15_ChSel};

int ADCD_ACQPS[16] =   {ADCD_SOC0_ACQPS,ADCD_SOC1_ACQPS,ADCD_SOC2_ACQPS,ADCD_SOC3_ACQPS,
                        ADCD_SOC4_ACQPS,ADCD_SOC5_ACQPS,ADCD_SOC6_ACQPS,ADCD_SOC7_ACQPS,
                        ADCD_SOC8_ACQPS,ADCD_SOC9_ACQPS,ADCD_SOC10_ACQPS,ADCD_SOC11_ACQPS,
                        ADCD_SOC12_ACQPS,ADCD_SOC13_ACQPS,ADCD_SOC14_ACQPS,ADCD_SOC15_ACQPS};

int ADCD_TrigSel[16] = {ADCD_SOC0_Trigsel,ADCD_SOC1_Trigsel,ADCD_SOC2_Trigsel,ADCD_SOC3_Trigsel,
                        ADCD_SOC4_Trigsel,ADCD_SOC5_Trigsel,ADCD_SOC6_Trigsel,ADCD_SOC7_Trigsel,
                        ADCD_SOC8_Trigsel,ADCD_SOC9_Trigsel,ADCD_SOC10_Trigsel,ADCD_SOC11_Trigsel,
                        ADCD_SOC12_Trigsel,ADCD_SOC13_Trigsel,ADCD_SOC14_Trigsel,ADCD_SOC15_Trigsel};

void ADC__vSOC_CNF(volatile struct ADC_REGS *AdcxRegs, int ChSel[], int Trigsel[], int ACQPS[]);

void ADC_vInit()
{
    EALLOW;
    AdcaRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_PRESCALE_DIV_4; //set ADCCLK divider to SYSCLK/4 : 50MHZ = 200MHZ / 4
    AdcbRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_PRESCALE_DIV_4; //set ADCCLK divider to SYSCLK/4 : 50MHZ = 200MHZ / 4
    AdccRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_PRESCALE_DIV_4; //set ADCCLK divider to SYSCLK/4 : 50MHZ = 200MHZ / 4
    AdcdRegs.ADCCTL2.bit.PRESCALE = ADC_CLK_PRESCALE_DIV_4; //set ADCCLK divider to SYSCLK/4 : 50MHZ = 200MHZ / 4
    EDIS;

    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    EALLOW;
    PieVectTable.ADCA1_INT = &ADCCTL_ADCA1_ISR; //function for ADCA interrupt 1
    PieVectTable.ADCA2_INT = &ADCCTL_ADCA2_ISR; //function for ADCA interrupt 2
    PieVectTable.ADCA3_INT = &ADCCTL_ADCA3_ISR; //function for ADCA interrupt 3
    PieVectTable.ADCA4_INT = &ADCCTL_ADCA4_ISR; //function for ADCA interrupt 4

    PieVectTable.ADCB1_INT = &ADCCTL_ADCB1_ISR; //function for ADCB interrupt 1
    PieVectTable.ADCB2_INT = &ADCCTL_ADCB2_ISR; //function for ADCB interrupt 2
    PieVectTable.ADCB3_INT = &ADCCTL_ADCB3_ISR; //function for ADCB interrupt 3
    PieVectTable.ADCB4_INT = &ADCCTL_ADCB4_ISR; //function for ADCB interrupt 4

    PieVectTable.ADCC1_INT = &ADCCTL_ADCC1_ISR; //function for ADCC interrupt 1
    PieVectTable.ADCC2_INT = &ADCCTL_ADCC2_ISR; //function for ADCC interrupt 2
    PieVectTable.ADCC3_INT = &ADCCTL_ADCC3_ISR; //function for ADCC interrupt 3
    PieVectTable.ADCC4_INT = &ADCCTL_ADCC4_ISR; //function for ADCC interrupt 4

    PieVectTable.ADCD1_INT = &ADCCTL_ADCD1_ISR; //function for ADCD interrupt 1
    PieVectTable.ADCD2_INT = &ADCCTL_ADCD2_ISR; //function for ADCD interrupt 2
    PieVectTable.ADCD3_INT = &ADCCTL_ADCD3_ISR; //function for ADCD interrupt 3
    PieVectTable.ADCD4_INT = &ADCCTL_ADCD4_ISR; //function for ADCD interrupt 4

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = ADCA_INT1_SOC_IRQ_IDX; //end of ADCA_INT1_SOC_IRQ_IDX will set INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = ADCA_INT1_SOC_ENABLE;   //enable INT1 flag
    PieCtrlRegs.PIEIER1.bit.INTx1 = ADCA_INT1_SOC_ENABLE; // ADCA1

    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = ADCB_INT1_SOC_IRQ_IDX; //end of SOC0 will set INT1 flag
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = ADCB_INT1_SOC_ENABLE;   //enable INT1 flag
    PieCtrlRegs.PIEIER1.bit.INTx2 = ADCB_INT1_SOC_ENABLE; // ADCB1

    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = ADCC_INT1_SOC_IRQ_IDX; //end of SOC0 will set INT1 flag
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    AdccRegs.ADCINTSEL1N2.bit.INT1E = ADCC_INT1_SOC_ENABLE;   //enable INT1 flag
    PieCtrlRegs.PIEIER1.bit.INTx3 = ADCC_INT1_SOC_ENABLE; // ADCC1

    AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = ADCD_INT1_SOC_IRQ_IDX; //end of SOC0 will set INT1 flag
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    AdcdRegs.ADCINTSEL1N2.bit.INT1E = ADCD_INT1_SOC_ENABLE;   //enable INT1 flag
    PieCtrlRegs.PIEIER1.bit.INTx6 = ADCD_INT1_SOC_ENABLE; // ADCD1

    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = ADCA_INT2_SOC_IRQ_IDX; //end of ADCA_INT2_SOC_IRQ_IDX will set INT2 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //make sure INT2 flag is cleared
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = ADCA_INT2_SOC_ENABLE; //enable INT2 flag
    PieCtrlRegs.PIEIER10.bit.INTx2 = ADCA_INT2_SOC_ENABLE; // ADCA2

    AdcbRegs.ADCINTSEL1N2.bit.INT2SEL = ADCB_INT2_SOC_IRQ_IDX; //end of SOC1 will set INT2 flag
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //make sure INT2 flag is cleared
    AdcbRegs.ADCINTSEL1N2.bit.INT2E = ADCB_INT2_SOC_ENABLE; //enable INT2 flag
    PieCtrlRegs.PIEIER10.bit.INTx6 = ADCB_INT2_SOC_ENABLE; // ADCB2

    AdccRegs.ADCINTSEL1N2.bit.INT2SEL = ADCC_INT2_SOC_IRQ_IDX; //end of SOC1 will set INT2 flag
    AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //make sure INT2 flag is cleared
    AdccRegs.ADCINTSEL1N2.bit.INT2E = ADCC_INT2_SOC_ENABLE; //enable INT2 flag
    PieCtrlRegs.PIEIER10.bit.INTx10 = ADCC_INT2_SOC_ENABLE; // ADCC2

    AdcdRegs.ADCINTSEL1N2.bit.INT2SEL = ADCD_INT2_SOC_IRQ_IDX; //end of SOC1 will set INT2 flag
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //make sure INT2 flag is cleared
    AdcdRegs.ADCINTSEL1N2.bit.INT2E = ADCD_INT2_SOC_ENABLE; //enable INT2 flag
    PieCtrlRegs.PIEIER10.bit.INTx14 = ADCD_INT2_SOC_ENABLE; // ADCD2

    AdcaRegs.ADCINTSEL3N4.bit.INT3SEL = ADCA_INT3_SOC_IRQ_IDX; //end of ADCA_INT3_SOC_IRQ_IDX will set INT3 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //make sure INT3 flag is cleared
    AdcaRegs.ADCINTSEL3N4.bit.INT3E = ADCA_INT3_SOC_ENABLE; //enable INT3 flag
    PieCtrlRegs.PIEIER10.bit.INTx3 = ADCA_INT3_SOC_ENABLE; // ADCA3

    AdcbRegs.ADCINTSEL3N4.bit.INT3SEL = ADCB_INT3_SOC_IRQ_IDX; //end of SOC2 will set INT3 flag
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //make sure INT3 flag is cleared
    AdcbRegs.ADCINTSEL3N4.bit.INT3E = ADCB_INT3_SOC_ENABLE; //enable INT3 flag
    PieCtrlRegs.PIEIER10.bit.INTx7 = ADCB_INT3_SOC_ENABLE; // ADCB3

    AdccRegs.ADCINTSEL3N4.bit.INT3SEL = ADCC_INT3_SOC_IRQ_IDX; //end of SOC2 will set INT3 flag
    AdccRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //make sure INT3 flag is cleared
    AdccRegs.ADCINTSEL3N4.bit.INT3E = ADCC_INT3_SOC_ENABLE; //enable INT3 flag
    PieCtrlRegs.PIEIER10.bit.INTx11 = ADCC_INT3_SOC_ENABLE; // ADCC3

    AdcdRegs.ADCINTSEL3N4.bit.INT3SEL = ADCD_INT3_SOC_IRQ_IDX; //end of SOC2 will set INT3 flag
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT3 = 1; //make sure INT3 flag is cleared
    AdcdRegs.ADCINTSEL3N4.bit.INT3E = ADCD_INT3_SOC_ENABLE; //enable INT3 flag
    PieCtrlRegs.PIEIER10.bit.INTx15 = ADCD_INT3_SOC_ENABLE; // ADCD3

    AdcaRegs.ADCINTSEL3N4.bit.INT4SEL = ADCA_INT4_SOC_IRQ_IDX; //end of ADCA_INT4_SOC_IRQ_IDX will set INT4 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT4 = 1; //make sure INT4 flag is cleared
    AdcaRegs.ADCINTSEL3N4.bit.INT4E = ADCA_INT4_SOC_ENABLE; //enable INT4 flag
    PieCtrlRegs.PIEIER10.bit.INTx4 = ADCA_INT4_SOC_ENABLE; // ADCA4

    AdcbRegs.ADCINTSEL3N4.bit.INT4SEL = ADCB_INT4_SOC_IRQ_IDX; //end of SOC3 will set INT4 flag
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT4 = 1; //make sure INT4 flag is cleared
    AdcbRegs.ADCINTSEL3N4.bit.INT4E = ADCB_INT4_SOC_ENABLE; //enable INT4 flag
    PieCtrlRegs.PIEIER10.bit.INTx8 = ADCB_INT4_SOC_ENABLE; // ADCB4

    AdccRegs.ADCINTSEL3N4.bit.INT4SEL = ADCC_INT4_SOC_IRQ_IDX; //end of SOC3 will set INT4 flag
    AdccRegs.ADCINTFLGCLR.bit.ADCINT4 = 1; //make sure INT4 flag is cleared
    AdccRegs.ADCINTSEL3N4.bit.INT4E = ADCC_INT4_SOC_ENABLE; //enable INT4 flag
    PieCtrlRegs.PIEIER10.bit.INTx12 = ADCC_INT4_SOC_ENABLE; // ADCC4

    AdcdRegs.ADCINTSEL3N4.bit.INT4SEL = ADCD_INT4_SOC_IRQ_IDX; //end of SOC3 will set INT4 flag
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT4 = 1; //make sure INT4 flag is cleared
    AdcdRegs.ADCINTSEL3N4.bit.INT4E = ADCD_INT4_SOC_ENABLE; //enable INT4 flag
    PieCtrlRegs.PIEIER10.bit.INTx16 = ADCD_INT4_SOC_ENABLE; // ADCD4

    AdcaRegs.ADCINTFLGCLR.all = 0x000F; //interrupt flag clear register
    AdcbRegs.ADCINTFLGCLR.all = 0x000F;
    AdccRegs.ADCINTFLGCLR.all = 0x000F;
    AdcdRegs.ADCINTFLGCLR.all = 0x000F;

    EDIS;

    ADC__vSOC_CNF(&AdcaRegs, ADCA_ChSel, ADCA_TrigSel, ADCA_ACQPS);
    ADC__vSOC_CNF(&AdcbRegs, ADCB_ChSel, ADCB_TrigSel, ADCB_ACQPS);
    ADC__vSOC_CNF(&AdccRegs, ADCC_ChSel, ADCC_TrigSel, ADCC_ACQPS);
    ADC__vSOC_CNF(&AdcdRegs, ADCD_ChSel, ADCD_TrigSel, ADCD_ACQPS);

    EALLOW;

    IER |= M_INT1;
    //
    //power up the ADC's
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;


    EDIS;
    /* End ADC Configuration */
}


void ADC__vSOC_CNF(volatile struct ADC_REGS *AdcxRegs, int ChSel[], int Trigsel[], int ACQPS[])
{
//  extern void DSP28x_usDelay(Uint32 Count);

    EALLOW;
    AdcxRegs->ADCCTL1.bit.INTPULSEPOS = 1;

// Select the channel to be converted when SOCx is received
    AdcxRegs->ADCSOC0CTL.bit.CHSEL = ChSel[0];
    AdcxRegs->ADCSOC1CTL.bit.CHSEL = ChSel[1];
    AdcxRegs->ADCSOC2CTL.bit.CHSEL = ChSel[2];
    AdcxRegs->ADCSOC3CTL.bit.CHSEL = ChSel[3];
    AdcxRegs->ADCSOC4CTL.bit.CHSEL = ChSel[4];
    AdcxRegs->ADCSOC5CTL.bit.CHSEL = ChSel[5];
    AdcxRegs->ADCSOC6CTL.bit.CHSEL = ChSel[6];
    AdcxRegs->ADCSOC7CTL.bit.CHSEL = ChSel[7];
    AdcxRegs->ADCSOC8CTL.bit.CHSEL = ChSel[8];
    AdcxRegs->ADCSOC9CTL.bit.CHSEL = ChSel[9];
    AdcxRegs->ADCSOC10CTL.bit.CHSEL = ChSel[10];
    AdcxRegs->ADCSOC11CTL.bit.CHSEL = ChSel[11];
    AdcxRegs->ADCSOC12CTL.bit.CHSEL = ChSel[12];
    AdcxRegs->ADCSOC13CTL.bit.CHSEL = ChSel[13];
    AdcxRegs->ADCSOC14CTL.bit.CHSEL = ChSel[14];
    AdcxRegs->ADCSOC15CTL.bit.CHSEL = ChSel[15];
// comment
    AdcxRegs->ADCSOC0CTL.bit.TRIGSEL = Trigsel[0];
    AdcxRegs->ADCSOC1CTL.bit.TRIGSEL = Trigsel[1];
    AdcxRegs->ADCSOC2CTL.bit.TRIGSEL = Trigsel[2];
    AdcxRegs->ADCSOC3CTL.bit.TRIGSEL = Trigsel[3];
    AdcxRegs->ADCSOC4CTL.bit.TRIGSEL = Trigsel[4];
    AdcxRegs->ADCSOC5CTL.bit.TRIGSEL = Trigsel[5];
    AdcxRegs->ADCSOC6CTL.bit.TRIGSEL = Trigsel[6];
    AdcxRegs->ADCSOC7CTL.bit.TRIGSEL = Trigsel[7];
    AdcxRegs->ADCSOC8CTL.bit.TRIGSEL = Trigsel[8];
    AdcxRegs->ADCSOC9CTL.bit.TRIGSEL = Trigsel[9];
    AdcxRegs->ADCSOC10CTL.bit.TRIGSEL = Trigsel[10];
    AdcxRegs->ADCSOC11CTL.bit.TRIGSEL = Trigsel[11];
    AdcxRegs->ADCSOC12CTL.bit.TRIGSEL = Trigsel[12];
    AdcxRegs->ADCSOC13CTL.bit.TRIGSEL = Trigsel[13];
    AdcxRegs->ADCSOC14CTL.bit.TRIGSEL = Trigsel[14];
    AdcxRegs->ADCSOC15CTL.bit.TRIGSEL = Trigsel[15];
// commect
    AdcxRegs->ADCSOC0CTL.bit.ACQPS = ACQPS[0];
    AdcxRegs->ADCSOC1CTL.bit.ACQPS = ACQPS[1];
    AdcxRegs->ADCSOC2CTL.bit.ACQPS = ACQPS[2];
    AdcxRegs->ADCSOC3CTL.bit.ACQPS = ACQPS[3];
    AdcxRegs->ADCSOC4CTL.bit.ACQPS = ACQPS[4];
    AdcxRegs->ADCSOC5CTL.bit.ACQPS = ACQPS[5];
    AdcxRegs->ADCSOC6CTL.bit.ACQPS = ACQPS[6];
    AdcxRegs->ADCSOC7CTL.bit.ACQPS = ACQPS[7];
    AdcxRegs->ADCSOC8CTL.bit.ACQPS = ACQPS[8];
    AdcxRegs->ADCSOC9CTL.bit.ACQPS = ACQPS[9];
    AdcxRegs->ADCSOC10CTL.bit.ACQPS = ACQPS[10];
    AdcxRegs->ADCSOC11CTL.bit.ACQPS = ACQPS[11];
    AdcxRegs->ADCSOC12CTL.bit.ACQPS = ACQPS[12];
    AdcxRegs->ADCSOC13CTL.bit.ACQPS = ACQPS[13];
    AdcxRegs->ADCSOC14CTL.bit.ACQPS = ACQPS[14];
    AdcxRegs->ADCSOC15CTL.bit.ACQPS = ACQPS[15];

    EDIS;
}
