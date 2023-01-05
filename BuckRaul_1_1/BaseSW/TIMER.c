#include "F28x_Project.h"

#include "GPIO.h"
#include "Timer.h"

#define PIEACK_GRUP1 1;

Uint32 TIMER_u32TimerPeriodInterrupt;

__interrupt void vCPUTimer0_ISR();

void TIMER_vInit()
{
    EALLOW;
    PieVectTable.TIMER0_INT = &vCPUTimer0_ISR;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GRUP1;

    CpuTimer0Regs.TCR.bit.TSS = 1; // Stop timer
    CpuTimer0Regs.PRD.all = 10000;
    CpuTimer0Regs.TPR.all = 0;
    CpuTimer0Regs.TPRH.all = 0;
    CpuTimer0Regs.TCR.bit.SOFT = 1;
    CpuTimer0Regs.TCR.bit.FREE = 1;
    CpuTimer0Regs.TCR.bit.TIF = 1;
    CpuTimer0Regs.TCR.bit.TIE = 1;  //TIMER INTERRUPT ENABLE
    CpuTimer0Regs.TCR.bit.TSS = 0;  //Start Timer

    IER |= M_INT1;
    EDIS;
}

void TIMER_vSetPeriod(Uint32 u32TimerPeriod_ms)
{
    CpuTimer0Regs.PRD.all = u32TimerPeriod_ms * 200 * 1000;
}
__interrupt void vCPUTimer0_ISR(void)
{
    EALLOW;

    PieCtrlRegs.PIEACK.all = PIEACK_GRUP1;
    EDIS;
}
