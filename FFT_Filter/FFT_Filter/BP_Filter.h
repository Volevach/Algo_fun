#pragma once
#include "stdafx.h"
#include "complex.h"
#include "FFT_1024.h"

#define FILT_LEN 31

class BP_Filter
{
public:
    BP_Filter(void);
    ~BP_Filter(void);
    void low_pass(Complex src_sig[BLOCK_LEN][2], Complex sink_sig[BLOCK_LEN][2]); 
    void high_pass(Complex src_sig[BLOCK_LEN][2], Complex sink_sig[BLOCK_LEN][2]);
    void band_pass(Complex src_sig[BLOCK_LEN][2], Complex sink_sig[BLOCK_LEN][2]);
    void sig_filter(Complex src_sig[BLOCK_LEN][2], Complex sink_sig[BLOCK_LEN][2], Complex filter_par[BLOCK_LEN]);

private:
    Complex filt_coef_freq[BLOCK_LEN];   
    Complex flt_scale;
    Complex flt_scale_inv;
};

const double filt_coef[FILT_LEN] = 
{
    0.0016,    0.0018,    0.0025,    0.0036,    0.0051,    0.0070,    0.0091,    0.0115,
    0.0140,    0.0164,    0.0188,    0.0208,    0.0226,    0.0239,    0.0247,    0.0250,
    0.0247,    0.0239,    0.0226,    0.0208,    0.0188,    0.0164,    0.0140,    0.0115,
    0.0091,    0.0070,    0.0051,    0.0036,    0.0025,    0.0018,    0.0016
};


