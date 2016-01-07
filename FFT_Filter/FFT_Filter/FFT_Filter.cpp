// FFT_Filter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FFT_1024.h"
#include "BP_Filter.h"
#include "Wave_Proc.h"

/* 
 * 
 * overlap add used:
 *
 *      fft len         =  1024
 *      filter len      =    31
 * =>   data block len  = 1024 - 31 + 1 = 994
*/


int main(int argc, int* argv[])
{
    // init vars
    int t = 0, i = 0, rem = 0, len = 0, loop_cnt = 0;
    
    // crete the overlap add buffer
    unsigned short buffer[BLOCK_LEN - NET_LEN][2] = {0};
    unsigned short src_data[BLOCK_LEN][2];
    unsigned short flt_data[BLOCK_LEN][2];
   
    Complex freq_coef[BLOCK_LEN][2];
    Complex flt_sink[BLOCK_LEN][2];

    // open the wave file to process
    FILE *in;
    
    // create the output file
    FILE *out;
    
    char inname[150] = "../Wave/Input/TI_Skript.wav";
    char outname[150] = "../Wave/Output/output_data_seq_c.wav";
        
    in = fopen(inname,"rb");
    out = fopen(outname,"wb");    

    // Inititalize FFT
    FFT_1024* MyFFT = new FFT_1024(); 
    
    // Initialize the Filter
    BP_Filter* MyFilt = new BP_Filter();

    // initialize the Wave processing class
    Wave_Proc* MyWave = new Wave_Proc(in);
            
    // currently supporting only stereo wave
    if((MyWave->GetFormatType() != 1) && (MyWave->GetChannelNum() != 2))
    {
        return -1;                   // not stereo wave    
    }
    
    // get the amount of 994 samples blocks and the amount of remainder samples
    len = MyWave->GetDataLen()/4;
    rem = len % NET_LEN;
    loop_cnt = (int)((len - rem)/NET_LEN);

    MyWave->WriteHeader(out, (len + rem)*4);
      
    for(t = 0; t < loop_cnt; t++)
    {
        for(i = 0; i < NET_LEN; i++)
        {
            src_data[i][0] = MyWave->ReadWord(in);
            src_data[i][1] = MyWave->ReadWord(in);
        }
            
        // zero pad
        for(i = NET_LEN; i < BLOCK_LEN; i++)
        {
            src_data[i][0] = 0;
            src_data[i][1] = 0;
        }
        
        // run the filter process        
        // perform a 1024 point fft
        MyFFT->FFT_1024_stereo(src_data, freq_coef);
    
        // low pass filtering
        // MyFilt->low_pass(freq_coef, flt_sink);
    
        // perform a 1024 ifft
        //MyFFT->IFFT_1024_stereo(flt_sink, flt_data);
        MyFFT->IFFT_1024_stereo(freq_coef, flt_data);
        
        // write first 30 samples with overlap buffer added
        for(i = 0; i < (BLOCK_LEN - NET_LEN); i++)
        { 
            MyWave->WriteWord(out,flt_data[i][0] + buffer[i][0]); 
            MyWave->WriteWord(out,flt_data[i][1] + buffer[i][1]);
        }
            
            // write the next 964 samles unaltered
        for(i = (BLOCK_LEN - NET_LEN); i < NET_LEN; i++)
        { 
            MyWave->WriteWord(out,flt_data[i][0]); 
            MyWave->WriteWord(out,flt_data[i][1]);
        }
            
        // store the last 30 samples into overlap add buffer
        for(i = NET_LEN; i < BLOCK_LEN; i++)
        {
            buffer[i - NET_LEN][0] = flt_data[i][0];
            buffer[i - NET_LEN][1] = flt_data[i][1];   
        }
    }
     
     //repeat for raminder
    for(i = 0; i < rem; i++)
    {
        src_data[i][0] = MyWave->ReadWord(in);
        src_data[i][1] = MyWave->ReadWord(in);
    }
         
    for(i = rem; i < BLOCK_LEN; i++)
    {
        src_data[i][0] = 0;
        src_data[i][1] = 0;
    }
    
   
    // run the filter process        
    // perform a 1024 point fft
    MyFFT->FFT_1024_stereo(src_data, freq_coef);
    
    // low pass filtering
    //MyFilt->low_pass(freq_coef, flt_sink);
    
    // perform a 1024 ifft
    //MyFFT->IFFT_1024_stereo(flt_sink, flt_data);

    MyFFT->IFFT_1024_stereo(freq_coef, flt_data);
    
    // write first 30 samples with overlap buffer added
    for(i = 0; i < (BLOCK_LEN - NET_LEN); i++)
    { 
        MyWave->WriteWord(out,flt_data[i][0] + buffer[i][0]); 
        MyWave->WriteWord(out,flt_data[i][1] + buffer[i][1]);
    }
            
    // write the next 964 samles unaltered
    for(i = (BLOCK_LEN - NET_LEN); i < NET_LEN; i++)
    { 
        MyWave->WriteWord(out,flt_data[i][0]); 
        MyWave->WriteWord(out,flt_data[i][1]);
    }

    fclose(in);
    fclose(out);
    
    delete MyFFT;
    delete MyFilt;
    delete MyWave;

    return 0;
}

