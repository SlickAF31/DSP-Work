// SOC Data to match the above channel definitions
#define ADCD_SOC0_ChSel     ADC_NOT_USED
#define ADCD_SOC1_ChSel     ADC_NOT_USED
#define ADCD_SOC2_ChSel     ADC_NOT_USED
#define ADCD_SOC3_ChSel     ADC_NOT_USED
#define ADCD_SOC4_ChSel     ADC_NOT_USED
#define ADCD_SOC5_ChSel     ADC_NOT_USED
#define ADCD_SOC6_ChSel     ADC_NOT_USED
#define ADCD_SOC7_ChSel     ADC_NOT_USED
#define ADCD_SOC8_ChSel     ADC_NOT_USED
#define ADCD_SOC9_ChSel     ADC_NOT_USED
#define ADCD_SOC10_ChSel    ADC_NOT_USED
#define ADCD_SOC11_ChSel    ADC_NOT_USED
#define ADCD_SOC12_ChSel    ADC_NOT_USED
#define ADCD_SOC13_ChSel    ADC_NOT_USED
#define ADCD_SOC14_ChSel    ADC_NOT_USED
#define ADCD_SOC15_ChSel    ADC_NOT_USED

#define ADCD_SOC0_ACQPS     ACQPS_SET
#define ADCD_SOC1_ACQPS     ACQPS_SET
#define ADCD_SOC2_ACQPS     ACQPS_SET
#define ADCD_SOC3_ACQPS     ACQPS_SET
#define ADCD_SOC4_ACQPS     ACQPS_SET
#define ADCD_SOC5_ACQPS     ACQPS_SET
#define ADCD_SOC6_ACQPS     ACQPS_SET
#define ADCD_SOC7_ACQPS     ACQPS_SET
#define ADCD_SOC8_ACQPS     ACQPS_SET
#define ADCD_SOC9_ACQPS     ACQPS_SET
#define ADCD_SOC10_ACQPS    ACQPS_SET
#define ADCD_SOC11_ACQPS    ACQPS_SET
#define ADCD_SOC12_ACQPS    ACQPS_SET
#define ADCD_SOC13_ACQPS    ACQPS_SET
#define ADCD_SOC14_ACQPS    ACQPS_SET
#define ADCD_SOC15_ACQPS    ACQPS_SET

#define ADCD_SOC0_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC1_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC2_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC3_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC4_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC5_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC6_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC7_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC8_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC9_Trigsel     ADCTRIG_SOFT
#define ADCD_SOC10_Trigsel    ADCTRIG_SOFT
#define ADCD_SOC11_Trigsel    ADCTRIG_SOFT
#define ADCD_SOC12_Trigsel    ADCTRIG_SOFT
#define ADCD_SOC13_Trigsel    ADCTRIG_SOFT
#define ADCD_SOC14_Trigsel    ADCTRIG_SOFT
#define ADCD_SOC15_Trigsel    ADCTRIG_SOFT

// Define which SOC triggers ADCD INT1-4
#define ADCD_INT1_SOC_IRQ_IDX   15
#define ADCD_INT1_SOC_ENABLE    0

#define ADCD_INT2_SOC_IRQ_IDX   15
#define ADCD_INT2_SOC_ENABLE    0

#define ADCD_INT3_SOC_IRQ_IDX   15
#define ADCD_INT3_SOC_ENABLE    0

#define ADCD_INT4_SOC_IRQ_IDX   15
#define ADCD_INT4_SOC_ENABLE    0

// Define the number of SOC's used for ADCC (needed to create global array ADC_Counts_Buf[])
#define ADCD_NUM_SOCS   0
#define ADC_NOT_USED 0x0F
