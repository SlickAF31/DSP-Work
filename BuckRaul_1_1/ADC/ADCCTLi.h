/**
 * @file ADC1Ci.h
 * @author Stefan Chisozan
 * @date 28.07.2016
 * @brief ADC Control - Internal header file
 * @department D&D AE
 *
 * @bug No known bugs.
 */
#ifndef _ADCCTLI_H_
#define _ADCCTLI_H_


/* ADC Configuration Start */

#define CalAdcaINL (void   (*)(void))0x0703B4
#define CalAdcbINL (void   (*)(void))0x0703B2
#define CalAdccINL (void   (*)(void))0x0703B0
#define CalAdcdINL (void   (*)(void))0x0703AE


#define ACQPS_SET	21   // ADC sample window is 22 CPU clock cycles

#define ADC_BUF_SIZE    (ADCA_NUM_SOCS + ADCB_NUM_SOCS + ADCC_NUM_SOCS + ADCD_NUM_SOCS)

#define ADCTRIG_SOFT		0
#define ADCTRIG_CPU_TINT0	1
#define ADCTRIG_CPU_TINT1	2
#define ADCTRIG_CPU_TINT2	3
#define ADCTRIG_XINT2		4
#define ADCTRIG_EPWM1_SOCA	5
#define ADCTRIG_EPWM1_SOCB	6
#define ADCTRIG_EPWM2_SOCA	7
#define ADCTRIG_EPWM2_SOCB	8
#define ADCTRIG_EPWM3_SOCA	9
#define ADCTRIG_EPWM3_SOCB	10
#define ADCTRIG_EPWM4_SOCA	11
#define ADCTRIG_EPWM4_SOCB	12
#define ADCTRIG_EPWM5_SOCA	13
#define ADCTRIG_EPWM5_SOCB	14
#define ADCTRIG_EPWM6_SOCA	15
#define ADCTRIG_EPWM6_SOCB	16
#define ADCTRIG_EPWM7_SOCA	17
#define ADCTRIG_EPWM7_SOCB	18

/************************************************************************************************/

// ADC Prescalers
#define ADC_CLK_PRESCALE_DIV_1           0
#define ADC_CLK_PRESCALE_INVALID         1
#define ADC_CLK_PRESCALE_DIV_2           2
#define ADC_CLK_PRESCALE_DIV_2p5         3
#define ADC_CLK_PRESCALE_DIV_3           4
#define ADC_CLK_PRESCALE_DIV_3p5         5
#define ADC_CLK_PRESCALE_DIV_4           6
#define ADC_CLK_PRESCALE_DIV_4p5         7
#define ADC_CLK_PRESCALE_DIV_5           8
#define ADC_CLK_PRESCALE_DIV_5p5         9
#define ADC_CLK_PRESCALE_DIV_6          10
#define ADC_CLK_PRESCALE_DIV_6p5        11
#define ADC_CLK_PRESCALE_DIV_7          12
#define ADC_CLK_PRESCALE_DIV_7p5        13
#define ADC_CLK_PRESCALE_DIV_8          14
#define ADC_CLK_PRESCALE_DIV_8p5        15

/************************************************************************************************/

#endif
