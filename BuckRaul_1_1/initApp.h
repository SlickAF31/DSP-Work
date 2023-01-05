/*
 * initApp.h
 *
 *  Created on: Oct 11, 2017
 *      Author: chisst1
 */

#ifndef INITAPP_H_
#define INITAPP_H_
#define LAUNCHPAD_28379d

#define initApp_LEDBlueOff GpioDataRegs.GPASET.bit.GPIO31 = 1;
#define initApp_LEDBlueToggle GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

#define initApp_LEDRedOff GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
#define initApp_LEDRedToggle GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

void initApp();


#endif /* INITAPP_H_ */
