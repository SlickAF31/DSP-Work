/*
 * GPIO.c
 *
 *  Created on: Sep 7, 2022
 *      Author: raul
 */

/* Project include */
#include "F28x_Project.h"

/* Standard C Lib */


/* Modules includes */


/* Own Headerfiles */
#include "GPIO.h"

/*Global Variables */


/*Own function prototypes */
void GPIO_vSetOutput(Uint16 u16GPIONumber, Uint16 u16GiveDirection)
{
    Uint32 u32Bit;
    u32Bit = 1 << (u16GPIONumber % 32);
    if(u16GPIONumber <= 31)
    {

        if(u16GiveDirection == OUTPUT)
        {
            GpioCtrlRegs.GPADIR.all |= u32Bit;
        }
        else
        {
            GpioCtrlRegs.GPADIR.all &= ~(u32Bit);
        }
    }

    else if (u16GPIONumber <= 63)
    {
        if(u16GiveDirection == OUTPUT)
        {
            GpioCtrlRegs.GPBDIR.all |=  u32Bit;
        }
        else
        {
            GpioCtrlRegs.GPBDIR.all &= ~(u32Bit);
        }
    }

    else if (u16GPIONumber <= 95)
    {
        if(u16GiveDirection == 0)
        {
            GpioCtrlRegs.GPADIR.all |= u32Bit;
        }
        else
        {
            GpioCtrlRegs.GPADIR.all &= ~(u32Bit);
        }
    }

    else if(u16GPIONumber <= 127)
    {
        if(u16GiveDirection == 0)
        {
            GpioCtrlRegs.GPADIR.all |= u32Bit;
        }
        else
        {
            GpioCtrlRegs.GPADIR.all &= ~(u32Bit);
        }
    }

    else if(u16GPIONumber <= 159)
    {
        if(u16GiveDirection == 0)
        {
            GpioCtrlRegs.GPADIR.all |= u32Bit;
        }
        else
        {
            GpioCtrlRegs.GPADIR.all &= ~(u32Bit);
        }
    }

    else if(u16GPIONumber <= 168)
    {

        if(u16GiveDirection == 0)
        {
            GpioCtrlRegs.GPADIR.all |= u32Bit;
        }
        else
        {
            GpioCtrlRegs.GPADIR.all &= ~(u32Bit);
        }
    }

}

void GPIO_vSet(Uint16 u16GPIONumber)
{
    Uint32 u32Bit;
    u32Bit = 1UL << (u16GPIONumber % 32);
    if(u16GPIONumber <= 31)
    {
        GpioDataRegs.GPASET.all |= u32Bit;
    }

    else if (u16GPIONumber <= 63)
    {
        GpioDataRegs.GPBSET.all |= u32Bit;
    }

    else if (u16GPIONumber <= 95)
    {
        GpioDataRegs.GPCSET.all |= u32Bit;
    }

    else if(u16GPIONumber <= 127)
    {
        GpioDataRegs.GPDSET.all |= u32Bit;
    }

    else if(u16GPIONumber <= 159)
    {
        GpioDataRegs.GPESET.all |= u32Bit;
    }

    else if(u16GPIONumber <= 168)
    {
        GpioDataRegs.GPFSET.all |= u32Bit;
    }
}

void GPIO_vClear(Uint16 u16GPIONumber)
{
    Uint32 u32Bit;
    u32Bit = 1UL << (u16GPIONumber % 32);
    if(u16GPIONumber <= 31)
    {
        GpioDataRegs.GPACLEAR.all &= ~(u32Bit);
    }

    else if (u16GPIONumber <= 63)
    {
        GpioDataRegs.GPBCLEAR.all &= ~(u32Bit);
    }

    else if (u16GPIONumber <= 95)
    {
        GpioDataRegs.GPCCLEAR.all &= ~(u32Bit);
    }

    else if(u16GPIONumber <= 127)
    {
        GpioDataRegs.GPDCLEAR.all &= ~(u32Bit);
    }

    else if(u16GPIONumber <= 159)
    {
        GpioDataRegs.GPECLEAR.all &= ~(u32Bit);
    }

    else if(u16GPIONumber <= 168)
    {
        GpioDataRegs.GPFCLEAR.all &= ~(u32Bit);
    }

}
Uint16 GPIO_u16Read(Uint16 u16GPIONumber)
{
    Uint32 u32Bit;
    Uint16 u16BitCheck;
    u32Bit = 1UL << (u16GPIONumber % 32);
    if(u16GPIONumber <= 31)
    {
        if(GpioDataRegs.GPADAT.all &= u32Bit)
        {
            u16BitCheck = 1;
        }
        else
        {
            u16BitCheck = 0;
        }
    }
    else if (u16GPIONumber <= 63)
    {
        if(GpioDataRegs.GPADAT.all &= u32Bit)
        {
            u16BitCheck = 1;
        }
        else
        {
            u16BitCheck = 0;
        }
    }

    else if (u16GPIONumber <= 95)
    {
        if(GpioDataRegs.GPADAT.all &= u32Bit)
        {
            u16BitCheck = 1;
        }
        else
        {
            u16BitCheck = 0;
        }
    }

    else if(u16GPIONumber <= 127)
    {

        if(GpioDataRegs.GPADAT.all &= u32Bit)
        {
            u16BitCheck = 1;
        }
        else
        {
            u16BitCheck = 0;
        }
    }
    else if(u16GPIONumber <= 159)
    {
        if(GpioDataRegs.GPADAT.all &= u32Bit)
        {
            u16BitCheck = 1;
        }
        else
        {
            u16BitCheck = 0;
        }
    }
    else if(u16GPIONumber <= 168)
    {
        if(GpioDataRegs.GPADAT.all &= u32Bit)
        {
            u16BitCheck = 1;
        }
        else
        {
            u16BitCheck = 0;
        }
    }
    return u16BitCheck;
}


void GPIO_vToggle(Uint16 u16GPIONumber)
{
    Uint32 u32Bit;
    u32Bit = 1UL << (u16GPIONumber % 32);
    if(u16GPIONumber <= 31)
    {
        GpioDataRegs.GPATOGGLE.all |= u32Bit;
    }

    else if (u16GPIONumber <= 63)
    {
        GpioDataRegs.GPBTOGGLE.all |= u32Bit;
    }

    else if (u16GPIONumber <= 95)
    {
        GpioDataRegs.GPCTOGGLE.all |= u32Bit;
    }

    else if(u16GPIONumber <= 127)
    {
        GpioDataRegs.GPDTOGGLE.all |= u32Bit;
    }

    else if(u16GPIONumber <= 159)
    {
        GpioDataRegs.GPETOGGLE.all |= u32Bit;
    }

    else if(u16GPIONumber <= 168)
    {
        GpioDataRegs.GPFTOGGLE.all |= u32Bit;
    }
}
