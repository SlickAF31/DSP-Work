// SOC Data to match the above channel definitions
#define ADCC_SOC0_ChSel     ADC_NOT_USED
#define ADCC_SOC1_ChSel     ADC_NOT_USED
#define ADCC_SOC2_ChSel     ADC_NOT_USED
#define ADCC_SOC3_ChSel     ADC_NOT_USED
#define ADCC_SOC4_ChSel     ADC_NOT_USED
#define ADCC_SOC5_ChSel     ADC_NOT_USED
#define ADCC_SOC6_ChSel     ADC_NOT_USED
#define ADCC_SOC7_ChSel     ADC_NOT_USED
#define ADCC_SOC8_ChSel     ADC_NOT_USED
#define ADCC_SOC9_ChSel     ADC_NOT_USED
#define ADCC_SOC10_ChSel    ADC_NOT_USED
#define ADCC_SOC11_ChSel    ADC_NOT_USED
#define ADCC_SOC12_ChSel    ADC_NOT_USED
#define ADCC_SOC13_ChSel    ADC_NOT_USED
#define ADCC_SOC14_ChSel    ADC_NOT_USED
#define ADCC_SOC15_ChSel    ADC_NOT_USED

#define ADCC_SOC0_ACQPS     ACQPS_SET
#define ADCC_SOC1_ACQPS     ACQPS_SET
#define ADCC_SOC2_ACQPS     ACQPS_SET
#define ADCC_SOC3_ACQPS     ACQPS_SET
#define ADCC_SOC4_ACQPS     ACQPS_SET
#define ADCC_SOC5_ACQPS     ACQPS_SET
#define ADCC_SOC6_ACQPS     ACQPS_SET
#define ADCC_SOC7_ACQPS     ACQPS_SET
#define ADCC_SOC8_ACQPS     ACQPS_SET
#define ADCC_SOC9_ACQPS     ACQPS_SET
#define ADCC_SOC10_ACQPS    ACQPS_SET
#define ADCC_SOC11_ACQPS    ACQPS_SET
#define ADCC_SOC12_ACQPS    ACQPS_SET
#define ADCC_SOC13_ACQPS    ACQPS_SET
#define ADCC_SOC14_ACQPS    ACQPS_SET
#define ADCC_SOC15_ACQPS    ACQPS_SET

#define ADCC_SOC0_Trigsel     ADCTRIG_CPU_TINT0
#define ADCC_SOC1_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC2_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC3_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC4_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC5_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC6_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC7_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC8_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC9_Trigsel     ADCTRIG_SOFT
#define ADCC_SOC10_Trigsel    ADCTRIG_SOFT
#define ADCC_SOC11_Trigsel    ADCTRIG_SOFT
#define ADCC_SOC12_Trigsel    ADCTRIG_SOFT
#define ADCC_SOC13_Trigsel    ADCTRIG_SOFT
#define ADCC_SOC14_Trigsel    ADCTRIG_SOFT
#define ADCC_SOC15_Trigsel    ADCTRIG_SOFT

// Define which SOC triggers ADCC INT1-4
#define ADCC_INT1_SOC_IRQ_IDX   0
#define ADCC_INT1_SOC_ENABLE    0

#define ADCC_INT2_SOC_IRQ_IDX   15
#define ADCC_INT2_SOC_ENABLE    0

#define ADCC_INT3_SOC_IRQ_IDX   15
#define ADCC_INT3_SOC_ENABLE    0

#define ADCC_INT4_SOC_IRQ_IDX   15
#define ADCC_INT4_SOC_ENABLE    0

// Define the number of SOC's used for ADCC (needed to create global array ADC_Counts_Buf[])
#define ADCC_NUM_SOCS   3
#define ADC_NOT_USED 0x0F
