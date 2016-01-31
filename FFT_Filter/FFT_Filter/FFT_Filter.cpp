// FFT_Filter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FFT_Trans.h"
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


int main(int argc, char* argv[])
{
    // init vars
    int t = 0, i = 0, rem = 0, len = 0, loop_cnt = 0;
    
    // crete the overlap add buffer
    short i_buffer[BLOCK_LEN - NET_LEN][2] = {0};
    short i_src_data[BLOCK_LEN][2];
    short i_flt_data[BLOCK_LEN][2];
   
    Complex c_freq_coef[BLOCK_LEN][2];
    Complex c_flt_sink[BLOCK_LEN][2];

    // open the wave file to process
    FILE *in;
    
    // create the output file
    FILE *out;
    
    char s_inname[150] = "../Wave/Input/input_music.wav";
    char s_outname[150] = "../Wave/Output/output_data.wav";

    char s_wav_preface[44];

	// open files
    in = fopen(s_inname,"rb");
    out = fopen(s_outname,"wb"); 

	// get wave header
    for(i = 0; i < 44; i++)
    {
        s_wav_preface[i] = (char)getc(in);
    }

    // Inititalize FFT
    FFT_Trans* MyFFT = new FFT_Trans(); 
    
    // Initialize the Filter
    BP_Filter* MyFilt = new BP_Filter();

    // initialize the Wave processing class
    Wave_Proc* MyWave = new Wave_Proc(s_wav_preface);
            
    // currently supporting only stereo wave
    if((MyWave->GetFormatType() != 1) && (MyWave->GetChannelNum() != 2))
    {
        return -1;                   // not stereo wave    
    }
    
    // get the amount of 994 samples blocks and the amount of remainder samples
    len = MyWave->GetDataLen()/4;
    rem = len % NET_LEN;
    loop_cnt = (int)((len - rem)/NET_LEN);

    MyWave->WriteHeader(out, (loop_cnt + 1)*4*NET_LEN);
      
    for(t = 0; t < loop_cnt; t++)
    {
        for(i = 0; i < NET_LEN; i++)
        {
            i_src_data[i][0] = MyWave->ReadWord(in);
            i_src_data[i][1] = MyWave->ReadWord(in);
        }
            
        // zero pad
        for(i = NET_LEN; i < BLOCK_LEN; i++)
        {
            i_src_data[i][0] = 0;
            i_src_data[i][1] = 0;
        }
        
        // run the filter process        
        // perform a 1024 point fft
        MyFFT->FFT_Stereo(i_src_data, c_freq_coef);
    
        // low pass filtering
        MyFilt->Filter(c_freq_coef, c_flt_sink);
    
        // perform a 1024 ifft
        MyFFT->IFFT_Stereo(c_flt_sink, i_flt_data);
        
        
        // write first 30 samples with overlap buffer added
        for(i = 0; i < (BLOCK_LEN - NET_LEN); i++)
        { 
            MyWave->WriteWord(out,i_flt_data[i][0] + i_buffer[i][0]);
            MyWave->WriteWord(out,i_flt_data[i][1] + i_buffer[i][1]);
        }
            
            // write the next 964 samles unaltered
        for(i = (BLOCK_LEN - NET_LEN); i < NET_LEN; i++)
        { 
            MyWave->WriteWord(out,i_flt_data[i][0]); 
            MyWave->WriteWord(out,i_flt_data[i][1]);
        }
            
        // store the last 30 samples into overlap add buffer
        for(i = NET_LEN; i < BLOCK_LEN; i++)
        {
			i_buffer[i - NET_LEN][0] = i_flt_data[i][0];
			i_buffer[i - NET_LEN][1] = i_flt_data[i][1];
        }
    }
     
     //repeat for raminder
    for(i = 0; i < rem; i++)
    {
        i_src_data[i][0] = MyWave->ReadWord(in);
        i_src_data[i][1] = MyWave->ReadWord(in);
    }
         
    for(i = rem; i < BLOCK_LEN; i++)
    {
		i_src_data[i][0] = 0;
		i_src_data[i][1] = 0;
    }
    
   
    // run the filter process        
    // perform a 1024 point fft
    MyFFT->FFT_Stereo(i_src_data, c_freq_coef);
    
    // low pass filtering
    MyFilt->Filter(c_freq_coef, c_flt_sink);
    
    // perform a 1024 ifft
    MyFFT->IFFT_Stereo(c_flt_sink, i_flt_data);

   
    // write first 30 samples with overlap buffer added
    for(i = 0; i < (BLOCK_LEN - NET_LEN); i++)
    { 
        MyWave->WriteWord(out, i_flt_data[i][0] + i_buffer[i][0]);
        MyWave->WriteWord(out, i_flt_data[i][1] + i_buffer[i][1]);
    }
            
    // write the next 964 samles unaltered
    for(i = (BLOCK_LEN - NET_LEN); i < NET_LEN; i++)
    { 
        MyWave->WriteWord(out,i_flt_data[i][0]); 
        MyWave->WriteWord(out,i_flt_data[i][1]);
    }

    fclose(in);
    fclose(out);
    
    delete MyFFT;
    delete MyFilt;
    delete MyWave;

    return 0;
}

