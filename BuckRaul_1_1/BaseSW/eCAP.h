

#ifndef BASESW_ECAP_H_
#define BASESW_ECAP_H_

#define CLEAR_PENDING__INTERRUPTS 0x0FF;


#define ENABLE_AWPM_MODE 1;
#define DISABLE_AWPM_MODE 0;

#define COUNT_EQ_COMP_INT_DISABLE 0;
#define COUNT_EQ_COMP_INT_ENABLE 1;

//start or stop eCAP counter
#define TIME_STAMP_CTRSTOP_CONTROL_STOP 0;
#define TIME_STAMP_CTRSTOP_CONTROL_FREE_RUN 1;

void eCAP_vInit();
void eCAP_vRun(Uint32 eCAP_u32SetFreq, float32 eCAP_fDuty);


#endif /* BASESW_ECAP_H_ */
