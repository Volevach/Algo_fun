#include "FFT_1024.h"


FFT_1024::FFT_1024(void)
{
    unsigned short i = 0;
    int d = 2;
        
    for(i = 0; i < BLOCK_LEN; i++)
    {
        unsigned char b = (unsigned char)(i & 0xFF);
        b = ((b * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
        bitRevInd[i] = (short)((short)b << 2) + ((i & 0x100) >> 7) + ((i & 0x200) >> 9);
    }
    
    //precalculate twiddle factors
    for(i = 0; i < STAGES; i++)
    {
        d_fac[i] = d; 
        twiddle_fac[i] = Complex((float)cos(-2.0 * PI / d), (float)sin(-2.0 * PI / d));
        d <<= 1;
    }
    
    w_0 = Complex(1.0, 0.0);
}


FFT_1024::~FFT_1024(void)
{

}

void FFT_1024::FFT_1024_mono(const short time_coef[BLOCK_LEN], Complex freq_coef[BLOCK_LEN])
{
    int n, d, k, m;
    
    Complex w;
    Complex wd;
    Complex t;
    Complex x;
    
    bitReverse_to_complx(time_coef, freq_coef);
    
    for(n = 1; n <= 10; n++)
    {
        d = (int)(pow(2.0,n));
        wd = Complex((float)cos(-2.0 * PI / d), (float)sin(-2.0 * PI / d));
        for(k = 0; k < BLOCK_LEN; k+=d)
        {
            w = Complex(1.0, 0.0);
            for(m = 0; m < (d/2); m++)
            {

                t = compMul(w, freq_coef[m + k + (d/2)]);
                x = freq_coef[m + k];
                freq_coef[m + k] = compAdd(x, t);
                freq_coef[m + k + (d/2)] = compSub(x, t);

                // twidde :)
                w = compMul(w,wd);
            }
        }
    }
}

void FFT_1024::FFT_1024_stereo(const short time_coef[BLOCK_LEN][2], Complex freq_coef[BLOCK_LEN][2])
{
    int n, d, k, m;
    
    Complex w;
    Complex wd;
    Complex t;
    Complex x;
    
    bitReverse_to_complx2(time_coef, freq_coef);
    
    for(n = 1; n <= 10; n++)
    {
        d = d_fac[n-1];
        wd = twiddle_fac[n-1];
        for(k = 0; k < BLOCK_LEN; k+=d)
        {
            w = w_0;
            for(m = 0; m < (d/2); m++)
            {
                // left channel
                t = compMul(w, freq_coef[m + k + (d/2)][0]);
                x = freq_coef[m + k][0];
                freq_coef[m + k][0] = compAdd(x, t);
                freq_coef[m + k + (d/2)][0] = compSub(x, t);
                
                // right channel
                t = compMul(w, freq_coef[m + k + (d/2)][1]);
                x = freq_coef[m + k][1];
                freq_coef[m + k][1] = compAdd(x, t);
                freq_coef[m + k + (d/2)][1] = compSub(x, t);
                
                // twidde :)
                w = compMul(w,wd);
            }
        }
    }
}

void FFT_1024::IFFT_1024_stereo(const Complex freq_coef[BLOCK_LEN][2], short time_coef[BLOCK_LEN][2])
{
    int n, d, k, m;
    
    Complex w;
    Complex wd;
    Complex t;
    Complex x;
    Complex freq_coef_rev[BLOCK_LEN][2];
    
    bitReverse(freq_coef, freq_coef_rev);
    
    for(n = 1; n <= 10; n++)
    {
        d = d_fac[n-1];
        wd = twiddle_fac[n-1].ConjCompl();
        for(k = 0; k < BLOCK_LEN; k+=d)
        {
            w = w_0;
            for(m = 0; m < (d/2); m++)
            {
                // left channel
                t = compMul(w, freq_coef_rev[m + k + (d/2)][0]);
                x = freq_coef_rev[m + k][0];
                freq_coef_rev[m + k][0] = compAdd(x, t);
                freq_coef_rev[m + k + (d/2)][0] = compSub(x, t);
                
                // right channel
                t = compMul(w, freq_coef_rev[m + k + (d/2)][1]);
                x = freq_coef_rev[m + k][1];
                freq_coef_rev[m + k][1] = compAdd(x, t);
                freq_coef_rev[m + k + (d/2)][1] = compSub(x, t);
                
                // twidde :)
                w = compMul(w,wd);
            }
        }
    }
    
    for(n = 0; n < BLOCK_LEN; n++)
    {
        time_coef[n][0] = (short)( ((int)freq_coef_rev[n][0].GetReal()) >> 10);
        time_coef[n][1] = (short)( ((int)freq_coef_rev[n][1].GetReal()) >> 10);  
    }
}


void FFT_1024::bitReverse(const Complex a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2])
{
    int i = 0;
    for(i = 0; i < BLOCK_LEN; i++)
    {
        b[i][0] = a[bitRevInd[i]][0];
        b[i][1] = a[bitRevInd[i]][1];
    }
}

void FFT_1024::bitReverse_to_complx2(const short a[BLOCK_LEN][2], Complex b[BLOCK_LEN][2])
{
    int i = 0;
    for(i = 0; i < BLOCK_LEN; i++)
    {
        b[i][0] = Complex((float)a[bitRevInd[i]][0], 0.0);
        b[i][1] = Complex((float)a[bitRevInd[i]][1], 0.0);
    }
}

void FFT_1024::bitReverse_to_complx(const short a[BLOCK_LEN], Complex b[BLOCK_LEN])
{
    int i = 0;
    for(i = 0; i < BLOCK_LEN; i++)
    {
        b[i] = Complex((float)a[bitRevInd[i]],0.0);
    }
}