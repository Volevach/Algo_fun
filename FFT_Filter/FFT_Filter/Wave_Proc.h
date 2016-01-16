// based on normalize.c by Michael Kohn
// https://www.mikekohn.net/stuff/normalize.c

#pragma once
#include "stdafx.h"
#include "WaveParam.h"


class Wave_Proc
{
public:
    Wave_Proc(void);
    Wave_Proc(char wav_preface[44]);
    ~Wave_Proc(void);
    
    int GetChannelNum();
    int GetFormatType();
    int GetDataLen();
    short ReadWord(FILE* in);

    int WriteWord(FILE *out, int n);
    int WriteHeader(FILE *out, unsigned int data_length);

private:

    unsigned int read_long(FILE* in);
    short read_word(FILE* in);
    
    int write_header(FILE *out);
    int write_header(FILE *out, unsigned int data_length);
    int write_long(FILE *out, int n);
    int write_word(FILE *out, int n);
    

    int read_chars(FILE* in, char *s, int n);

    WaveParam* fmt_chunk;
};

