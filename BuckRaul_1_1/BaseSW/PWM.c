
/* Project Include file */
#include "F28x_Project.h"

/* Modules Includes */

/* Own Headerfiles */
#include "PWM.h"
/* End Includes */

/* Global Variables */
Uint16 PWM_u16Frequency;
Uint16 PWM_u16Frequency_Shadow;
Uint16 PWM_u16TZOSHTCLR;
Uint16 u16TryDeadBand;

Uint16 TZ_u16BOOLEnablePWM = 0;

typedef struct {
    Uint32 u32PWMFreq;
    Uint16 u16DutyCycle;
    Uint16 u16DeadBand;

}tstEPWM__Config;

tstEPWM__Config EPWM1;
tstEPWM__Config EPWM2;

typedef struct {
    Uint32 u32PWMFreq_Hz;
    float32 fDuty;
    Uint16 u16DB_RED1_PWM1A_ns;
    Uint16 u16DB_FED1_PWM1A_ns;
    Uint16 u16DB_RED2_PWM1B_ns;
    Uint16 u16DB_FED2_PWM1B_ns;
}tstEPWM__Config_2;

tstEPWM__Config_2 myEPWM;

/* Own Function Prototypes */
Uint32 PWM__u16CalculatePRDREG(Uint32 u32Freq_hz, Uint16 u16UpDown);
float32 PWM__fCalculateDuty(Uint16 u16Duty_perc);
float32 PWM__fCalculateDB(Uint16 u16DeadBand);

Uint32 PWM__u32CalculateTBPRD(Uint32 u32FreqPWM);
float32 PWM__fDutyCalculate(float32 fDuty_ns);
Uint16 PWM_u16CalculatePhase(Uint16 u16Phase_Deg);

void PWM_vTripZoneSW()
{
    if(!TZ_u16BOOLEnablePWM)
    {
        EALLOW;
        EPwm1Regs.TZFRC.bit.OST = 1;
        EDIS;
    }
    else
    {
        EALLOW;
        EPwm1Regs.TZCLR.bit.OST = 1;
        EDIS;
    }

}

void PWM_vTripZone()
{
    PWM_u16TZOSHTCLR = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;

    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // asyncron input for GPIO14

    EALLOW;
    InputXbarRegs.INPUT1SELECT = 14; //select xbar for gpio14 for input

    EPwm1Regs.TZSEL.bit.OSHT1 = 1; //select what type of tripzone do I want (cbc = cycle by cycle & OSHT = one shot trip zone)
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    EPwm2Regs.TZSEL.bit.OSHT1 = 1;
    EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    EDIS;
}

//void PWM_vTZClear()
//{
//    if(!myEPWM.boTripClear)
//    {
//        EALLOW;
//        EPwm1Regs.TZCLR.bit.OST = 1;
//        EPwm2Regs.TZCLR.bit.OST = 1;
//        EDIS;
//
//        myEPWM.boTripClear = 0;
//    }
//}


void PWM_vDoWork_EX9(void)
{
    //Frequency
    EPwm1Regs.TBPRD =  PWM__u16CalculatePRDREG(EPWM1.u32PWMFreq, UP_DOWN_COUNT);
    EPwm2Regs.TBPRD =  PWM__u16CalculatePRDREG(EPWM2.u32PWMFreq, UP_DOWN_COUNT);

    //DutyCycle
    EPwm1Regs.CMPA.bit.CMPA = PWM__fCalculateDuty(EPWM1.u16DutyCycle) * EPwm1Regs.TBPRD;
    EPwm1Regs.CMPB.bit.CMPB = PWM__fCalculateDuty(EPWM1.u16DutyCycle) * EPwm1Regs.TBPRD;
    EPwm2Regs.CMPA.bit.CMPA = PWM__fCalculateDuty(EPWM2.u16DutyCycle) * EPwm2Regs.TBPRD;
    EPwm2Regs.CMPB.bit.CMPB = PWM__fCalculateDuty(EPWM2.u16DutyCycle) * EPwm2Regs.TBPRD;

    //DeadBand
    EPwm1Regs.DBRED.all = PWM__fCalculateDB(EPWM1.u16DeadBand) * EPwm1Regs.TBPRD;
    EPwm1Regs.DBFED.all = PWM__fCalculateDB(EPWM1.u16DeadBand) * EPwm1Regs.TBPRD;
    EPwm2Regs.DBRED.all = PWM__fCalculateDB(EPWM2.u16DeadBand) * EPwm2Regs.TBPRD;
    EPwm2Regs.DBFED.all = PWM__fCalculateDB(EPWM2.u16DeadBand) * EPwm2Regs.TBPRD;
}

Uint32 PWM__u16CalculatePRDREG(Uint32 u32Freq_hz, Uint16 u16UpDown)
{
    if(u16UpDown == UP_DOWN_COUNT)
    {
        return (PWMCLK_Hz/u32Freq_hz) / 2;
    }
    else
    {
        return (PWMCLK_Hz/u32Freq_hz);
    }

}

float32 PWM__fCalculateDuty(Uint16 u16Duty_perc)
{
    return ((float)u16Duty_perc / 100);
}

float32 PWM__fCalculateDB(Uint16 u16DeadBand)
{
    return((float)u16DeadBand / 100);
}


void PWM_vInit_Ex9()
{
    EPWM1.u32PWMFreq = 100000;
    EPWM1.u16DutyCycle = 50;
    EPWM1.u16DeadBand = 0;

    EPWM2.u32PWMFreq = 100000;
    EPWM2.u16DutyCycle = 50;
    EPWM2.u16DeadBand = 0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;



    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;

    EPwm1Regs.TBPRD = 1000;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;
    EPwm1Regs.TBCTR = 0;

    EPwm2Regs.TBPRD =1000;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;
    EPwm2Regs.TBCTL.bit.CLKDIV = 0;
    EPwm2Regs.TBCTR = 0;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;
    EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;

    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
    EPwm1Regs.DBCTL.bit.DEDB_MODE = 0;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.OUTSWAP = 0x0;

    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
    EPwm2Regs.DBCTL.bit.DEDB_MODE = 0;
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.OUTSWAP = 0x0;

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void PWM_vInit()
{
    TZ_u16BOOLEnablePWM = 0;

    myEPWM.u32PWMFreq_Hz = 100000;
    myEPWM.fDuty = 0.5;
    myEPWM.u16DB_RED1_PWM1A_ns = 0;
    myEPWM.u16DB_FED1_PWM1A_ns = 0;
    myEPWM.u16DB_RED2_PWM1B_ns = 0;
    myEPWM.u16DB_FED2_PWM1B_ns = 0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;

    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync Output on CRT = zero;

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;

    EPwm1Regs.TBPRD = (PWMCLK_Hz/myEPWM.u32PWMFreq_Hz) / 2;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;
    EPwm1Regs.TBCTR = 0;

    EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD / 2;
    EPwm1Regs.CMPB.bit.CMPB = EPwm1Regs.TBPRD / 2;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;

    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
    EPwm1Regs.DBCTL.bit.DEDB_MODE = 0;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.OUTSWAP = 0x0;
    EPwm1Regs.DBCTL.bit.HALFCYCLE = 1;

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void PWM_vDoWork(void)
{
    EALLOW;
    //Frequency
    EPwm1Regs.TBPRD = PWM__u32CalculateTBPRD(myEPWM.u32PWMFreq_Hz) - 1;

    //Duty Cycle
    EPwm1Regs.CMPA.bit.CMPA = myEPWM.fDuty * (EPwm1Regs.TBPRD + 1);
    EPwm1Regs.CMPB.bit.CMPB = (1 - (myEPWM.fDuty)) * (EPwm1Regs.TBPRD + 1);

    //DeadBand
    EPwm1Regs.DBRED.all = myEPWM.u16DB_RED1_PWM1A_ns;
    EPwm1Regs.DBFED.all = myEPWM.u16DB_FED1_PWM1A_ns;
    EPwm2Regs.DBRED.all = myEPWM.u16DB_RED2_PWM1B_ns;
    EPwm2Regs.DBFED.all = myEPWM.u16DB_FED2_PWM1B_ns;

    EDIS;
}

Uint32 PWM__u32CalculateTBPRD(Uint32 u32FreqPWM)
{
    return ((PWMCLK_Hz/u32FreqPWM) / 2);
}

Uint16 PWM_u16CalculatePhase(Uint16 u16Phase_Deg)
{
    if(u16Phase_Deg <= 180)
    {
        return (EPwm2Regs.TBPRD * (((float)u16Phase_Deg / 180)));
    }
    else
    {
        return (EPwm2Regs.TBPRD * (((float)u16Phase_Deg / 360)));
    }
}

Uint16 PWM__u32CalculateDB(Uint16 u16DB)
{
    if(EPwm1Regs.DBCTL.bit.HALFCYCLE)
    {
        return u16DB/5;
    }
    else
    {
        return u16DB/10;
    }
}

//void PWM_vCheckMaxMin(void)
//{
//    //checkFreq
//    if(EPWM1_EX10.u32PWMFreq_Khz > PWMFreq_Max)
//    {
//        EPWM1_EX10.u32PWMFreq_Khz = PWMFreq_Max;
//        EPwm1Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Max) - 1;
//        EPwm2Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Max) - 1;
//    }
//    if(EPWM1_EX10.u32PWMFreq_Khz < PWMFreq_Min)
//    {
//        EPWM1_EX10.u32PWMFreq_Khz = PWMFreq_Min;
//        EPwm1Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Min) - 1;
//        EPwm2Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Min) - 1;
//    }
//
//    //checkDuty
//    if(EPWM1_EX10.fDUtyCycle > PWMDutyCycle_Max)
//    {
//        EPWM1_EX10.fDUtyCycle = PWMDutyCycle_Max;
//        EPwm1Regs.CMPA.bit.CMPA = (1 - (PWMDutyCycle_Max)) * (EPwm1Regs.TBPRD + 1);
//        EPwm1Regs.CMPB.bit.CMPB = (1 - (PWMDutyCycle_Max)) * (EPwm1Regs.TBPRD + 1);
//        EPwm2Regs.CMPA.bit.CMPA = (1 - (PWMDutyCycle_Max)) * (EPwm2Regs.TBPRD + 1);
//        EPwm2Regs.CMPB.bit.CMPB = (1 - (PWMDutyCycle_Max)) * (EPwm2Regs.TBPRD + 1);
//    }
//    if(EPWM1_EX10.fDUtyCycle < PWMDUtyCycle_Min)
//    {
//        EPWM1_EX10.fDUtyCycle = PWMDUtyCycle_Min;
//        EPwm1Regs.CMPA.bit.CMPA = (1 - (PWMDUtyCycle_Min)) * (EPwm1Regs.TBPRD + 1);
//        EPwm1Regs.CMPB.bit.CMPB = (1 - (PWMDUtyCycle_Min)) * (EPwm1Regs.TBPRD + 1);
//        EPwm2Regs.CMPA.bit.CMPA = (1 - (PWMDUtyCycle_Min)) * (EPwm2Regs.TBPRD + 1);
//        EPwm2Regs.CMPB.bit.CMPB = (1 - (PWMDUtyCycle_Min)) * (EPwm2Regs.TBPRD + 1);
//    }
//
//    //checkPhase
//    if(EPWM2_EX10.u16Phase_degree > PWMPhase_Max)
//    {
//        EPWM2_EX10.u16Phase_degree = PWMPhase_Max;
//        EPwm2Regs.TBPHS.bit.TBPHS = PWM_u16CalculatePhase(PWMPhase_Max);
//        EPwm2Regs.TBCTL.bit.PHSDIR = TB_DOWN;
//    }
//
//    //checkDeadBand
//    if(EPWM1_EX10.u16DeadBand_ns > PWMDeadBand_Max)
//    {
//        EPWM1_EX10.u16DeadBand_ns = PWMDeadBand_Max;
//        EPwm1Regs.DBRED.all = PWMDeadBand_Max;
//        EPwm1Regs.DBFED.all = PWMDeadBand_Max;
//        EPwm2Regs.DBRED.all = PWMDeadBand_Max;
//        EPwm2Regs.DBFED.all = PWMDeadBand_Max;
//    }
//}



//void PWM_vInit_Ex11()
//{
//    myEPWM.u32PWMFreq_Hz = 100000;
//    myEPWM.fDuty = 0.5;
//    myEPWM.u16Phase_Deg = 0;
//    myEPWM.u16DB_RED1 = 0;
//    myEPWM.u16DB_FED1 = 0;
//    myEPWM.u16DB_RED2 = 0;
//    myEPWM.u16DB_FED2 = 0;
//    myEPWM.boTripClear = 0;
//
//    EALLOW;
//    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
//
//
//    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
//    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;
//
//    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
//    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
//
//    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync Output on CRT = zero;
//
//    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
//    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
//    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;
//    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;
//    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
//    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
//    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
//    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
//
//    EPwm1Regs.TBPRD = (PWMCLK_Hz/myEPWM.u32PWMFreq_Hz) / 2;
//    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;
//    EPwm1Regs.TBCTL.bit.CLKDIV = 0;
//    EPwm1Regs.TBCTR = 0;
//
//    EPwm2Regs.TBPRD = (PWMCLK_Hz/myEPWM.u32PWMFreq_Hz) / 2;
//    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;
//    EPwm2Regs.TBCTL.bit.CLKDIV = 0;
//    EPwm2Regs.TBCTR = 0;
//    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
//
//    EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD / 2;
//    EPwm1Regs.CMPB.bit.CMPB = EPwm1Regs.TBPRD / 2;
//    EPwm2Regs.CMPA.bit.CMPA = EPwm2Regs.TBPRD / 2;
//    EPwm2Regs.CMPB.bit.CMPB = EPwm2Regs.TBPRD / 2;
//
//    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
//    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
//    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;
//    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;
//
//    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
//    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
//    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;
//    EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;
//
//    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
//    EPwm1Regs.DBCTL.bit.DEDB_MODE = 0;
//    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
//    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
//    EPwm1Regs.DBCTL.bit.OUTSWAP = 0x0;
//    EPwm1Regs.DBCTL.bit.HALFCYCLE = 1;
//
//    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;
//    EPwm2Regs.DBCTL.bit.DEDB_MODE = 0;
//    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
//    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
//    EPwm2Regs.DBCTL.bit.OUTSWAP = 0x0;
//    EPwm2Regs.DBCTL.bit.HALFCYCLE = 1;
//
//
//    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
//
//    EDIS;
//}

//void PWM_vDoWork_EX11()
//{
//
//    EALLOW;
//    //Frequency
//    EPwm1Regs.TBPRD = PWM__u32CalculateTBPRD(myEPWM.u32PWMFreq_Hz) - 1;
//    EPwm2Regs.TBPRD = PWM__u32CalculateTBPRD(myEPWM.u32PWMFreq_Hz) - 1;
//
//    //Duty Cycle
//    EPwm1Regs.CMPA.bit.CMPA = (1 - myEPWM.fDuty) * (EPwm1Regs.TBPRD + 1);
//    EPwm1Regs.CMPB.bit.CMPB = (1 - myEPWM.fDuty) * (EPwm1Regs.TBPRD + 1);
//    EPwm2Regs.CMPA.bit.CMPA = (1 - myEPWM.fDuty) * (EPwm1Regs.TBPRD + 1);
//    EPwm2Regs.CMPB.bit.CMPB = (1 - myEPWM.fDuty) * (EPwm1Regs.TBPRD + 1);
//
////    Phase
//
//    Uint16 u16Old;
//    u16Old = myEPWM.u16Phase_Deg ;
//    if(u16Old <= 180)
//    {
//        EPwm2Regs.TBPHS.bit.TBPHS = PWM_u16CalculatePhase(myEPWM.u16Phase_Deg);
//        EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
//    }
//    else
//    {
//        EPwm2Regs.TBPHS.bit.TBPHS = PWM_u16CalculatePhase(myEPWM.u16Phase_Deg);
//        EPwm2Regs.TBCTL.bit.PHSDIR = TB_DOWN;
//    }
//
//
//    //DeadBand
//    EPwm1Regs.DBRED.all = PWM__u32CalculateDB(myEPWM.u16DB_RED1);
//    EPwm1Regs.DBFED.all = PWM__u32CalculateDB(myEPWM.u16DB_FED1);
//    EPwm2Regs.DBRED.all = PWM__u32CalculateDB(myEPWM.u16DB_RED2);
//    EPwm2Regs.DBFED.all = PWM__u32CalculateDB(myEPWM.u16DB_FED2);
//
//    EDIS;
//}
//
//void PWM_vCheckMaxMin_Ex11()
//{
//
//    //checkFreq
//    if(myEPWM.u32PWMFreq_Hz > PWMFreq_Max)
//    {
//        myEPWM.u32PWMFreq_Hz = PWMFreq_Max;
//        EPwm1Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Max) - 1;
//        EPwm2Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Max) - 1;
//    }
//    if(myEPWM.u32PWMFreq_Hz < PWMFreq_Min)
//    {
//        myEPWM.u32PWMFreq_Hz = PWMFreq_Min;
//        EPwm1Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Min) - 1;
//        EPwm2Regs.TBPRD = PWM__u32CalculateTBPRD(PWMFreq_Min) - 1;
//    }
//
//    //checkDuty
//    if(myEPWM.fDuty > PWMDutyCycle_Max)
//    {
//        myEPWM.fDuty = PWMDutyCycle_Max;
//        EPwm1Regs.CMPA.bit.CMPA = (1 - PWMDutyCycle_Max) * (EPwm1Regs.TBPRD + 1);
//        EPwm1Regs.CMPB.bit.CMPB = (1 - PWMDutyCycle_Max) * (EPwm1Regs.TBPRD + 1);
//        EPwm2Regs.CMPA.bit.CMPA = (1 - PWMDutyCycle_Max) * (EPwm1Regs.TBPRD + 1);
//        EPwm2Regs.CMPB.bit.CMPB = (1 - PWMDutyCycle_Max) * (EPwm1Regs.TBPRD + 1);
//    }
//
//    if(myEPWM.fDuty < PWMDUtyCycle_Min)
//    {
//         myEPWM.fDuty = PWMDUtyCycle_Min;
//         EPwm1Regs.CMPA.bit.CMPA = (1 - PWMDUtyCycle_Min) * (EPwm1Regs.TBPRD + 1);
//         EPwm1Regs.CMPB.bit.CMPB = (1 - PWMDUtyCycle_Min) * (EPwm1Regs.TBPRD + 1);
//         EPwm2Regs.CMPA.bit.CMPA = (1 - PWMDUtyCycle_Min) * (EPwm1Regs.TBPRD + 1);
//         EPwm2Regs.CMPB.bit.CMPB = (1 - PWMDUtyCycle_Min) * (EPwm1Regs.TBPRD + 1);
//    }
//
//    //checkPhase
//    if(myEPWM.u16Phase_Deg > PWMPhase_Max)
//    {
//        myEPWM.u16Phase_Deg = PWMPhase_Max;
//        EPwm2Regs.TBPHS.bit.TBPHS = PWMPhase_Max;
//        EPwm2Regs.TBCTL.bit.PHSDIR = TB_DOWN;
//    }
//
//    //checkDeadBand
//    if(myEPWM.u16DB_RED1 > PWMDeadBand_Max || myEPWM.u16DB_FED1 > PWMDeadBand_Max || myEPWM.u16DB_RED2 > PWMDeadBand_Max || myEPWM.u16DB_FED2 > PWMDeadBand_Max)
//    {
//        myEPWM.u16DB_RED1 = PWMDeadBand_Max;
//        myEPWM.u16DB_FED1 = PWMDeadBand_Max;
//        myEPWM.u16DB_RED2 = PWMDeadBand_Max;
//        myEPWM.u16DB_FED2 = PWMDeadBand_Max;
//        EPwm1Regs.DBRED.all = PWMDeadBand_Max;
//        EPwm1Regs.DBFED.all = PWMDeadBand_Max;
//        EPwm2Regs.DBRED.all = PWMDeadBand_Max;
//        EPwm2Regs.DBFED.all = PWMDeadBand_Max;
//    }
//}


