// based on normalize.c by Michael Kohn
// https://www.mikekohn.net/stuff/normalize.c

#pragma once
#include "stdafx.h"


class Wave_Proc
{
public:
    Wave_Proc(void);
    Wave_Proc(FILE*);
    ~Wave_Proc(void);

    typedef struct waveParamT
    {
        unsigned short format_type;
        unsigned short channel_numbers;
        unsigned int sample_rate;
        unsigned int bytes_per_second;
        unsigned short bytes_per_sample;
        unsigned short bits_per_sample;
        unsigned int data_length;
        unsigned int riff_length;
    } wave_param_t;


    int GetChannelNum();
    int GetFormatType();
    int GetDataLen();
    unsigned short ReadWord(FILE* in);

    int WriteWord(FILE *out, int n);
    int WriteHeader(FILE *out, unsigned int data_length);

private:
    int parse_fmt_chunk(FILE* in);
    int parse_data_chunk(FILE* in);
    int parse_header(FILE* in);

    unsigned int read_long(FILE* in);
    unsigned short read_word(FILE* in);
    
    int write_header(FILE *out);
    int write_header(FILE *out, unsigned int data_length);
    int write_long(FILE *out, int n);
    int write_word(FILE *out, int n);
    

    int read_chars(FILE* in, char *s, int n);

    wave_param_t fmt_chunk;
};
