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

	// constructor initializing the FFT with precalculations of indexes and twiddle factors
    FFT_Trans(void);

	// generic destructor
    ~FFT_Trans(void);

	// FFT for two coefficient streams of length BLOCK_LEN
    void FFT_Stereo(const short i_time_coef[BLOCK_LEN][2], Complex c_freq_coef[BLOCK_LEN][2]);
    
	// IFFT for two coefficient streams of length BLOCK_LEN
	void IFFT_Stereo(const Complex c_freq_coef[BLOCK_LEN][2],  short i_time_coef[BLOCK_LEN][2]);
    
	// FFT for one coefficient stream of length BLOCK_LEN
	void FFT_Mono(const short i_time_coef[BLOCK_LEN], Complex c_freq_coef[BLOCK_LEN]);

private:
	// indexes and their correspoing bit reversal representation
    unsigned short u_bit_rev_ind[BLOCK_LEN];

	// precalculated twiddle factors
    Complex c_twiddle_fac[STAGES];

	// start value for the FFT twiddle
    Complex c_w_0;

	// scaling for each stage
    int i_d_fac[STAGES];
    
	// bit reverse copy from a complex stream to a complex stream
    void BitReverse(const Complex a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2]);
    
	// bit reverse copt from a real stream to a complex stream with two channels
	void BitReverse_to_complx2(const short a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2]);
    
	// bit reverse copt from a real stream to a complex stream with one channel
	void BitReverse_to_complx(const short a[BLOCK_LEN], Complex b[BLOCK_LEN]);
};

// just PI
static const double PI = 3.1415926;