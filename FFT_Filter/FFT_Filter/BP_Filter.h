// main class for the Band Pass Filter function
// 
// implements constructs for low pass / band pass / high pass and arbitraty signal filter
// currently only the low pass is implemented

#pragma once
#include "stdafx.h"
#include "complex.h"
#include "FFT_Trans.h"

#define FILT_LEN 31

class BP_Filter
{
public:
	// constructor 
    BP_Filter(void);

	// destructor
    ~BP_Filter(void);

	// filter function, input and output as stereo complex frequency domain representation
    void Filter(Complex c_src_sig[BLOCK_LEN][2], Complex c_sink_sig[BLOCK_LEN][2]); 
    	
private:
	// filter coefficients
    Complex c_filt_coef_freq[BLOCK_LEN];   
    
	// filter scaling for balancing out the FFT / IFFT
	Complex c_flt_scale;

	// quotient of fitler scaling
    Complex c_flt_scale_inv;
};

// filter coefficients for low pass filter
const double g_filt_coef_low_pass[FILT_LEN] = 
{
    0.0016,    0.0018,    0.0025,    0.0036,    0.0051,    0.0070,    0.0091,    0.0115,
    0.0140,    0.0164,    0.0188,    0.0208,    0.0226,    0.0239,    0.0247,    0.0250,
    0.0247,    0.0239,    0.0226,    0.0208,    0.0188,    0.0164,    0.0140,    0.0115,
    0.0091,    0.0070,    0.0051,    0.0036,    0.0025,    0.0018,    0.0016
};


