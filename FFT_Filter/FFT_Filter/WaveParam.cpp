#include "WaveParam.h"


WaveParam::WaveParam(void)
{
    format_type = 0;
    channel_numbers = 0;
    sample_rate = 0;
    bytes_per_second = 0;
    bytes_per_sample = 0 ;
    bits_per_sample = 0;
    data_length = 0;
    riff_length = 0;
}


WaveParam::~WaveParam(void)
{
}
