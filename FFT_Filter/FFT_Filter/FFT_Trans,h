// main class for the FFT implementation
// 
// inncludes a generic FFT implementastion
// with stages parameter set to 10 it corresponds to a FFT of length 1024


#pragma once
#include "stdafx.h"
#include "Complex.h"

class FFT_Trans
{
public:
    FFT_Trans(void);
    ~FFT_Trans(void);

    void FFT_Trans_stereo(const short time_coef[BLOCK_LEN][2], Complex freq_coef[BLOCK_LEN][2]);
    void IFFT_Trans_stereo(const Complex freq_coef[BLOCK_LEN][2],  short time_coef[BLOCK_LEN][2]);
    void FFT_Trans_mono(const short time_coef[BLOCK_LEN], Complex freq_coef[BLOCK_LEN]);

private:
    unsigned short bitRevInd[BLOCK_LEN];
    Complex twiddle_fac[STAGES];
    Complex w_0;
    int d_fac[STAGES];
    
    void bitReverse(const Complex a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2]);
    void bitReverse_to_complx2(const short a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2]);
    void bitReverse_to_complx(const short a[BLOCK_LEN], Complex b[BLOCK_LEN]);
};

static const double PI = 3.1415926;