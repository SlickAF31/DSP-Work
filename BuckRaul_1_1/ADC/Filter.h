/*
 * Filter.h
 *
 *  Created on: Nov 15, 2017
 *      Author: browal1
 */

#ifndef HELLA_SOURCES_DRIVERS_FILTER_H_
#define HELLA_SOURCES_DRIVERS_FILTER_H_

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

//
// Digital IIR Filter
// Assumed: A0=1, therefore A0 is not needed in structure
//
typedef struct {
    float32 _a1;
    float32 _b0;
    float32 _b1;
    float32 _m1;
    float32 _out;
} D1F;

// 1'st order Butterworth IIR filter with 5Hz cutoff, 20kHz sample rate
// a0=1 (assumed)
// a1=-9.9843043608309423e-001
// a2=0
// b0=1
// b1=1
// b2=0 (assumed)
// gain=7.8478195845288479e-004
//
// Initializer ordering: a1, b0, b1, m1, out
#define D1F_5HZ()   { -9.9843043608309423e-001, 7.8478195845288479e-004, 7.8478195845288479e-004, 0, 0 }

// 1'st order Butterworth IIR filter with 10Hz cutoff, 20kHz sample rate
// a0=1 (assumed)
// a1=-9.9686333183343789e-001
// a2=0
// b0=1
// b1=1
// b2=0 (assumed)
// gain=1.5683340832810533e-003
//
// Initializer ordering: a1, b0, b1, m1, out
#define D1F_10HZ()   { -9.9686333183343789e-001, 1.5683340832810533e-003, 1.5683340832810533e-003, 0, 0 }

// 1'st order Butterworth IIR filter with 50Hz cutoff, 20kHz sample rate
// a0=1 (assumed)
// a1=-0.98441410064697266
// a2=0
// b0=1
// b1=1
// b2=0 (assumed)
// gain=0.00779293629195154660
//
// Initializer ordering: a1, b0, b1, m1, out
#define D1F_50HZ()   { -0.98441410064697266, 0.00779293629195154660, 0.00779293629195154660, 0, 0 }

// 1'st order Butterworth IIR filter with 250Hz cutoff, 20kHz sample rate
// a0=1 (assumed)
// a1=-0.92439049482345581
// a2=0
// b0=1
// b1=1
// b2=0 (assumed)
// gain=0.037804754170896515
//
// Initializer ordering: a1, b0, b1, m1, out
#define D1F_250HZ()   { -0.92439049482345581, 0.037804754170896515, 0.037804754170896515, 0, 0 }

// 1'st order Butterworth IIR filter with 1kHz cutoff, 20kHz sample rate
// a0=1 (assumed)
// a1=-0.72654253244400024
// a2=0
// b0=1
// b1=1
// b2=0 (assumed)
// gain=0.136728735997319
//
// Initializer ordering: a1, b0, b1, m1, out
#define D1F_1000HZ()   { -0.72654253244400024, 0.136728735997319, 0.136728735997319, 0, 0 }

// 1'st order Butterworth IIR filter with 2kHz cutoff, 20kHz sample rate
// a0=1 (assumed)
// a1=-0.50952547788619995
// a2=0
// b0=1
// b1=1
// b2=0 (assumed)
// gain=0.2452372752527856
//
// Initializer ordering: a1, b0, b1, m1, out
#define D1F_2000HZ()   { -0.50952547788619995, 0.2452372752527856, 0.2452372752527856, 0, 0 }

//=====================================================================================================================
// ToDo: CalcD1F
// This will perform a first order filtering of the input variable, based on passed filter parameters
//=====================================================================================================================
static inline void CalcD1F(float val, D1F *coef)
{   //This function ASSUMES a normalized First-Order filter; i.e. the coef A0=1.0
    //Perform IIR operation (this is IIR Direct Form 2 Transposed)
    coef->_out = (coef->_b0 * val) +  coef->_m1;               //Calculate filter output
    coef->_m1  = (coef->_b1 * val) - (coef->_out * coef->_a1);  //Update the filter memory blocks

    //return coef->_out;
}

static inline void InitD1F(float val, D1F *coef)
{
    coef->_out = val;
    coef->_m1  = (coef->_b1 * val) - (coef->_out * coef->_a1);  //Update the filter memory blocks
}

#endif /* HELLA_SOURCES_DRIVERS_FILTER_H_ */
