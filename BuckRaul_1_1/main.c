#include "F28x_Project.h"

#include "initApp.h"

#include  "ADCCTL.h"
#include "PWM.h"
#include "Timer.h"


void main()
{
    initApp();

    PWM_vInit();
    PWM_vTripZone();
    ADC_vInit();
    TIMER_vInit();


    for(;;)
    {
        PWM_vDoWork();
        PWM_vTripZoneSW();
    }
}


