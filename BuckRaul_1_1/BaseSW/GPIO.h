    /*
 * GPIO.h
 *
 *  Created on: Sep 7, 2022
 *      Author: raul
 */

#ifndef GPIO_H_
#define GPIO_H_

#define OUTPUT 1
#define INPUT 0

void GPIO_vSetOutput(Uint16 u16GPIONumber, Uint16 u16GiveDirection);
void GPIO_vTimerSet_ms(Uint32 u32TimerPeriod);

void GPIO_vSet(Uint16 u16GPIONumber);
void GPIO_vClear(Uint16 u16GPIONumber);
Uint16 GPIO_u16Read(Uint16 u16GPIONumber);
void GPIO_vToggle(Uint16 u16GPIONumber);



#endif /* GPIO_H_ */
