// main class for the Band Pass Filter function
// 
// implements constructs for low pass / band pass / high pass and arbitraty signal filter
// currently only the low pass is implemented


#include "BP_Filter.h"

// constructor for filter class inititalization
BP_Filter::BP_Filter(void)
{
    unsigned int i = 0;
    FFT_Trans MyFFT = FFT_Trans();

	// compute the scaling = number of bits (2^16)
    c_flt_scale = Complex(65536.0, 65536.0);
    
	// compute the inverse scaling (1 / 2^16)
	c_flt_scale_inv = Complex(1.0/65536.0, 1.0/65536.0);

    // zero pad the filter coef 
    short u_filt_coef_zero[BLOCK_LEN] = {0};
    for(i = 0; i < FILT_LEN; i++)
    {
        u_filt_coef_zero[i] = (short)(g_filt_coef_low_pass[i] * 65536.0);
    }
    
    // transform the filter function into frequency domain
    MyFFT.FFT_Mono(u_filt_coef_zero, c_filt_coef_freq);

	// scale the filter function 
    for(i = 0; i < BLOCK_LEN; i++)
    {
        c_filt_coef_freq[i] = CompMul(c_filt_coef_freq[i], c_flt_scale_inv); 
    }
}


BP_Filter::~BP_Filter(void)
{
}

// filter function
void BP_Filter::Filter(Complex c_src_sig[BLOCK_LEN][2], Complex c_sink_sig[BLOCK_LEN][2])
{
    unsigned int i;

	// multiply the signal coefficients with the filter coefficients
    for(i = 0; i < BLOCK_LEN; i++)
    {
        c_sink_sig[i][0] = CompMul(c_src_sig[i][0], c_filt_coef_freq[i]);
        c_sink_sig[i][1] = CompMul(c_src_sig[i][1], c_filt_coef_freq[i]);
    }
}

