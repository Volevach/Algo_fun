// main class for the FFT implementation
// 
// inncludes a generic FFT implementastion
// with stages parameter set to 10 it corresponds to a FFT of length 1024

#include "FFT_Trans.h"

// constructor initializing the FFT with precalculations of indexes and twiddle factors
FFT_Trans::FFT_Trans(void)
{
    unsigned short i = 0;
    int d = 2;
        
	// calculate indexes corresponding to reversed bit order
    for(i = 0; i < BLOCK_LEN; i++)
    {
		// bit magic from bit twiddling hacks:
		// https://graphics.stanford.edu/~seander/bithacks.html
        
		unsigned char b = (unsigned char)(i & 0xFF);
        b = ((b * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
        u_bit_rev_ind[i] = (short)((short)b << 2) + ((i & 0x100) >> 7) + ((i & 0x200) >> 9);
    }
    
    //precalculate twiddle factors
    for(i = 0; i < STAGES; i++)
    {
        i_d_fac[i] = d; 
        c_twiddle_fac[i] = Complex((float)cos(-2.0 * PI / d), (float)sin(-2.0 * PI / d));
        d <<= 1;
    }
    
	// start value for FFT (1)
    c_w_0 = Complex(1.0, 0.0);
}

// generic destructor
FFT_Trans::~FFT_Trans(void)
{

}

// FFT for one coefficient stream of length BLOCK_LEN
void FFT_Trans::FFT_Mono(const short i_time_coef[BLOCK_LEN], Complex c_freq_coef[BLOCK_LEN])
{
    int n, d, k, m;
    
    Complex w;
    Complex wd;
    Complex t;
    Complex x;
    
	// first copy to the complex output vector with bit reversal
    BitReverse_to_complx(i_time_coef, c_freq_coef);
    
	// perform inplace radix 2 FFT with reversed bit indexed vector
    for(n = 1; n <= STAGES; n++)
    {
        d = (int)(pow(2.0,n));
        wd = Complex((float)cos(-2.0 * PI / d), (float)sin(-2.0 * PI / d));
        for(k = 0; k < BLOCK_LEN; k+=d)
        {
            w = Complex(1.0, 0.0);
            for(m = 0; m < (d/2); m++)
            {

                t = CompMul(w, c_freq_coef[m + k + (d/2)]);
                x = c_freq_coef[m + k];
                c_freq_coef[m + k] = CompAdd(x, t);
                c_freq_coef[m + k + (d/2)] = CompSub(x, t);

                // twidde :)
                w = CompMul(w,wd);
            }
        }
    }
}

// FFT for two coefficient streams of length BLOCK_LEN
void FFT_Trans::FFT_Stereo(const short i_time_coef[BLOCK_LEN][2], Complex c_freq_coef[BLOCK_LEN][2])
{
    int n, d, k, m;
    
    Complex w;
    Complex wd;
    Complex t;
    Complex x;
    
	// first copy the real input vector to the output with bit reversed indexes
    BitReverse_to_complx2(i_time_coef, c_freq_coef);
    
	// perform inplace radix 2 FFT
    for(n = 1; n <= STAGES; n++)
    {
        d = i_d_fac[n-1];
        wd = c_twiddle_fac[n-1];
        for(k = 0; k < BLOCK_LEN; k+=d)
        {
            w = c_w_0;
            for(m = 0; m < (d/2); m++)
            {
                // left channel
                t = CompMul(w, c_freq_coef[m + k + (d/2)][0]);
                x = c_freq_coef[m + k][0];
                c_freq_coef[m + k][0] = CompAdd(x, t);
                c_freq_coef[m + k + (d/2)][0] = CompSub(x, t);
                
                // right channel
                t = CompMul(w, c_freq_coef[m + k + (d/2)][1]);
                x = c_freq_coef[m + k][1];
                c_freq_coef[m + k][1] = CompAdd(x, t);
                c_freq_coef[m + k + (d/2)][1] = CompSub(x, t);
                
                // twidde :)
                w = CompMul(w,wd);
            }
        }
    }
}

// IFFT for two coefficient streams of length BLOCK_LEN
void FFT_Trans::IFFT_Stereo(const Complex c_freq_coef[BLOCK_LEN][2], short i_time_coef[BLOCK_LEN][2])
{
    int n, d, k, m;
    
    Complex w;
    Complex wd;
    Complex t;
    Complex x;
    Complex c_freq_coef_rev[BLOCK_LEN][2];
    
	// copy bit reversed to a temporary vector
    BitReverse(c_freq_coef, c_freq_coef_rev);
    
	// perform radix 2 IFFT inplace with bit reversed indexes
    for(n = 1; n <= STAGES; n++)
    {
        d = i_d_fac[n-1];
        wd = c_twiddle_fac[n-1].ConjCompl();
        for(k = 0; k < BLOCK_LEN; k+=d)
        {
            w = c_w_0;
            for(m = 0; m < (d/2); m++)
            {
                // left channel
                t = CompMul(w, c_freq_coef_rev[m + k + (d/2)][0]);
                x = c_freq_coef_rev[m + k][0];
                c_freq_coef_rev[m + k][0] = CompAdd(x, t);
                c_freq_coef_rev[m + k + (d/2)][0] = CompSub(x, t);
                
                // right channel
                t = CompMul(w, c_freq_coef_rev[m + k + (d/2)][1]);
                x = c_freq_coef_rev[m + k][1];
                c_freq_coef_rev[m + k][1] = CompAdd(x, t);
                c_freq_coef_rev[m + k + (d/2)][1] = CompSub(x, t);
                
                // twidde :)
                w = CompMul(w,wd);
            }
        }
    }
    
	// copy the real value to the ouput samples vector and scale by 2^STAGES
    for(n = 0; n < BLOCK_LEN; n++)
    {
        i_time_coef[n][0] = (short)( ((int)c_freq_coef_rev[n][0].GetReal()) >> STAGES);
        i_time_coef[n][1] = (short)( ((int)c_freq_coef_rev[n][1].GetReal()) >> STAGES);  
    }
}

// bit reverse copy from a complex stream to a complex stream
void FFT_Trans::BitReverse(const Complex a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2])
{
    int i = 0;

	// copy a to b with bit reversed indexes
    for(i = 0; i < BLOCK_LEN; i++)
    {
        b[i][0] = a[u_bit_rev_ind[i]][0];
        b[i][1] = a[u_bit_rev_ind[i]][1];
    }
}

// bit reverse copt from a real stream to a complex stream with two channels
void FFT_Trans::BitReverse_to_complx2(const short a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2])
{
    int i = 0;
 
	// copy a to b with bit reversed indexes
	for(i = 0; i < BLOCK_LEN; i++)
    {
        b[i][0] = Complex((float)a[u_bit_rev_ind[i]][0], 0.0);
        b[i][1] = Complex((float)a[u_bit_rev_ind[i]][1], 0.0);
    }
}

// bit reverse copt from a real stream to a complex stream with one channel
void FFT_Trans::BitReverse_to_complx(const short a[BLOCK_LEN], Complex b[BLOCK_LEN])
{
    int i = 0;
    
	// copy a to b with bit reversed indexes
	for(i = 0; i < BLOCK_LEN; i++)
    {
        b[i] = Complex((float)a[u_bit_rev_ind[i]],0.0);
    }
}