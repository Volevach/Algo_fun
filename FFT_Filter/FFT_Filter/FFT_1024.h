#pragma once
#include "stdafx.h"
#include "Complex.h"

class FFT_1024
{
public:
    FFT_1024(void);
    ~FFT_1024(void);

    void FFT_1024_stereo(unsigned short time_coef[BLOCK_LEN][2], Complex freq_coef[BLOCK_LEN][2]);
    void IFFT_1024_stereo(Complex freq_coef[BLOCK_LEN][2], unsigned short time_coef[BLOCK_LEN][2]);
    void FFT_1024_mono(unsigned short time_coef[BLOCK_LEN], Complex freq_coef[BLOCK_LEN]);

private:
    unsigned short bitRevInd[BLOCK_LEN];
    Complex twiddle_fac[STAGES];
    Complex w_0;
    int d_fac[STAGES];
    
    void bitReverse(Complex a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2]);
    void bitReverse_to_complx2(unsigned short a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2]);
    void bitReverse_to_complx(unsigned short a[BLOCK_LEN], Complex b[BLOCK_LEN]);
};

static const double PI = 3.1415926;