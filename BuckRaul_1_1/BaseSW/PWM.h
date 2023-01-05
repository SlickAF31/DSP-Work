#ifndef PWM_H_
#define PWM_H_

#define PWMCLK_Hz 100000000
#define PWMCLK_KHz 100000

#define PWMFreq_Max 500000
#define PWMFreq_Min 1000

#define PWMDeadBand_Max 500
#define PWMDeadBand_Min 0

#define PWMPhase_Max 360
#define PWMPhase_Min 0

#define PWMDutyCycle_Max 0.9
#define PWMDUtyCycle_Min 0.1


#define DEFAULT_FREQUENCY 10000

void PWM_vInit();
void PWM_vDoWork();

void PWM_vTripZone();

void PWM_vInit_Ex9(void);
void PWM_vDoWork_EX9(void);

void PWM_vCheckMaxMin(void);
void PWM_vTZClear();

void PWM_vDoWork_EX11();
void PWM_vInit_Ex11();
void PWM_vCheckMaxMin_Ex11();

void PWM_vTripZoneSW();


#define USE_PWM 1

#define UP_DOWN_COUNT 1
#define UP_COUNT 2




#endif /* PWM_H_ */
