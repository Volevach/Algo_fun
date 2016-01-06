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


    int write_header(FILE *out, const wave_param_t *wave_param);
    int write_long(FILE *out, int n);
    int write_word(FILE *out, int n);

private:
    int parse_fmt_chunk();
    int parse_data_chunk();
    int parse_header();

    unsigned int read_long();
    unsigned short read_word();
    int read_chars(char *s, int n);

    wave_param_t fmt_chunk;
    FILE* file_in;
        
};

