#pragma once
class WaveParam
{
public:
    WaveParam(void);
    ~WaveParam(void);
    
    unsigned short format_type;
    unsigned short channel_numbers;
    unsigned int sample_rate;
    unsigned int bytes_per_second;
    unsigned short bytes_per_sample;
    unsigned short bits_per_sample;
    unsigned int data_length;
    unsigned int riff_length;
  
};

