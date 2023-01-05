#include "F28x_Project.h"

#include "eCAP.h"


void eCAP_vInit()
{
    //stop counter
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = TIME_STAMP_CTRSTOP_CONTROL_STOP;

    InitAPwm1Gpio(); //select GPIO5 for output APWM

    ECap1Regs.ECCTL2.bit.CAP_APWM = ENABLE_AWPM_MODE;
    ECap1Regs.CAP1 = 10000; //set freq for 100KHz
    ECap1Regs.CAP2 = 50000; //set duty 50%
    ECap1Regs.ECCLR.all = CLEAR_PENDING__INTERRUPTS;
    ECap1Regs.ECEINT.bit.CTR_EQ_CMP = COUNT_EQ_COMP_INT_ENABLE;

    //start counter
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = TIME_STAMP_CTRSTOP_CONTROL_FREE_RUN;
}

void eCAP_vRun(Uint32 eCAP_u32SetFreq, float32 eCAP_fDuty)
{
    ECap1Regs.CAP1 = eCAP_u32SetFreq * 10;
    ECap1Regs.CAP2 = eCAP_fDuty * ECap1Regs.CAP1;
}
