// SOC Data to match the above channel definitions
#define ADCA_SOC0_ChSel     0
#define ADCA_SOC1_ChSel     ADC_NOT_USED
#define ADCA_SOC2_ChSel     2
#define ADCA_SOC3_ChSel     3
#define ADCA_SOC4_ChSel     ADC_NOT_USED
#define ADCA_SOC5_ChSel     ADC_NOT_USED
#define ADCA_SOC6_ChSel     ADC_NOT_USED
#define ADCA_SOC7_ChSel     ADC_NOT_USED
#define ADCA_SOC8_ChSel     ADC_NOT_USED
#define ADCA_SOC9_ChSel     ADC_NOT_USED
#define ADCA_SOC10_ChSel    ADC_NOT_USED
#define ADCA_SOC11_ChSel    ADC_NOT_USED
#define ADCA_SOC12_ChSel    ADC_NOT_USED
#define ADCA_SOC13_ChSel    ADC_NOT_USED
#define ADCA_SOC14_ChSel    ADC_NOT_USED
#define ADCA_SOC15_ChSel    ADC_NOT_USED

// Select the acquisition rate
#define ADCA_SOC0_ACQPS     ACQPS_SET
#define ADCA_SOC1_ACQPS     ACQPS_SET
#define ADCA_SOC2_ACQPS     ACQPS_SET
#define ADCA_SOC3_ACQPS     ACQPS_SET
#define ADCA_SOC4_ACQPS     ACQPS_SET
#define ADCA_SOC5_ACQPS     ACQPS_SET
#define ADCA_SOC6_ACQPS     ACQPS_SET
#define ADCA_SOC7_ACQPS     ACQPS_SET
#define ADCA_SOC8_ACQPS     ACQPS_SET
#define ADCA_SOC9_ACQPS     ACQPS_SET
#define ADCA_SOC10_ACQPS    ACQPS_SET
#define ADCA_SOC11_ACQPS    ACQPS_SET
#define ADCA_SOC12_ACQPS    ACQPS_SET
#define ADCA_SOC13_ACQPS    ACQPS_SET
#define ADCA_SOC14_ACQPS    ACQPS_SET
#define ADCA_SOC15_ACQPS    ACQPS_SET

// Select a trigger for SOC
#define ADCA_SOC0_Trigsel     ADCTRIG_CPU_TINT0
#define ADCA_SOC1_Trigsel     ADCTRIG_SOFT
#define ADCA_SOC2_Trigsel     ADCTRIG_CPU_TINT0
#define ADCA_SOC3_Trigsel     ADCTRIG_CPU_TINT0
#define ADCA_SOC4_Trigsel     ADCTRIG_SOFT
#define ADCA_SOC5_Trigsel     ADCTRIG_SOFT
#define ADCA_SOC6_Trigsel     ADCTRIG_SOFT
#define ADCA_SOC7_Trigsel     ADCTRIG_SOFT
#define ADCA_SOC8_Trigsel     ADCTRIG_SOFT
#define ADCA_SOC9_Trigsel     ADCTRIG_SOFT
#define ADCA_SOC10_Trigsel    ADCTRIG_SOFT
#define ADCA_SOC11_Trigsel    ADCTRIG_SOFT
#define ADCA_SOC12_Trigsel    ADCTRIG_SOFT
#define ADCA_SOC13_Trigsel    ADCTRIG_SOFT
#define ADCA_SOC14_Trigsel    ADCTRIG_SOFT
#define ADCA_SOC15_Trigsel    ADCTRIG_SOFT

// Define which SOC triggers ADCA INT1-4
#define ADCA_INT1_SOC_IRQ_IDX   0
#define ADCA_INT1_SOC_ENABLE    1

#define ADCA_INT2_SOC_IRQ_IDX   1
#define ADCA_INT2_SOC_ENABLE    0

#define ADCA_INT3_SOC_IRQ_IDX   2
#define ADCA_INT3_SOC_ENABLE    0

#define ADCA_INT4_SOC_IRQ_IDX   3
#define ADCA_INT4_SOC_ENABLE    0

// Define the number of SOC's used for ADCA (needed to create global array ADC_Counts_Buf[])
#define ADCA_NUM_SOCS   3
#define ADC_NOT_USED 0x0F
