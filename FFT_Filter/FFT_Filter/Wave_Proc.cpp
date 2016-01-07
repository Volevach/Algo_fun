// based on normalize.c by Michael Kohn
// https://www.mikekohn.net/stuff/normalize.c

#include "Wave_Proc.h"

Wave_Proc::Wave_Proc()
{
    fmt_chunk = new WaveParam();
}

Wave_Proc::Wave_Proc(FILE* in)
{
    fmt_chunk = new WaveParam();
    parse_header(in);
    parse_fmt_chunk(in);
    fmt_chunk->data_length = parse_data_chunk(in);
}

Wave_Proc::Wave_Proc(char wav_preface[44])
{
    fmt_chunk = new WaveParam();

    int length;
    char fourcc[5];
    for(int i = 0; i < 4; i++)
    {
        fourcc[i] = wav_preface[i];
    }
    fourcc[4] = 0;


    unsigned char riff_type[5];
    
   
    if (strncmp(fourcc,"RIFF",4)!=0)
    {
        printf("This file is not a RIFF/WAV\n");
    }
    
    fmt_chunk->riff_length= (unsigned int)wav_preface[4] + ((unsigned int)wav_preface[5] << 8) + ((unsigned int)wav_preface[6] << 16) + ((unsigned int)wav_preface[7] << 24);
    for(int i = 0; i < 4; i++)
    {
        fourcc[i] = wav_preface[i + 8];
    }
    fourcc[4] = 0;
    
    printf("RIFF Header\n");
    printf("----------------------------\n");
    printf("          Length: %d\n",fmt_chunk->riff_length);
    printf("            Type: %s\n",fourcc);
    printf("----------------------------\n");
    
    
    fmt_chunk->format_type = ((unsigned short)wav_preface[20] & 0xFF) + (((unsigned short)wav_preface[21] << 8) & 0xFF00);
    fmt_chunk->channel_numbers = ((unsigned short)wav_preface[22] & 0xFF) + (((unsigned short)wav_preface[23] << 8) & 0xFF00);
    fmt_chunk->sample_rate = ((unsigned int)wav_preface[24] & 0xFF) + (((unsigned int)wav_preface[25] << 8) & 0xFF00);// + ((unsigned int)wav_preface[26] << 16) + ((unsigned int)wav_preface[27] << 24);
    fmt_chunk->bytes_per_second = (unsigned int)wav_preface[28] + ((unsigned int)wav_preface[29] << 8) + ((unsigned int)wav_preface[30] << 16) + ((unsigned int)wav_preface[31] << 24);
    fmt_chunk->bytes_per_sample = ((unsigned short)wav_preface[32] & 0xFF) + (((unsigned short)wav_preface[33] << 8) & 0xFF00);
    fmt_chunk->bits_per_sample = ((unsigned short)wav_preface[34] & 0xFF) + (((unsigned short)wav_preface[35] << 8) & 0xFF00);

    printf("FMT Chunk\n");
    printf("----------------------------\n");
    printf("     Format Type: ");
    switch(fmt_chunk->format_type)
    {
        case 0:
            printf("Mono\n"); 
            break;
        case 1:
            printf("Stereo\n");
            break;
        default:
            printf("unknown\n");
            break;
    }

    printf(" Channel Numbers: %d\n",fmt_chunk->channel_numbers);
    printf("     Sample Rate: %d\n",fmt_chunk->sample_rate);
    printf("Bytes Per Second: %d\n",fmt_chunk->bytes_per_second);
    printf("Bytes Per Sample: ");
    switch (fmt_chunk->bytes_per_sample)
    {
        case 1:
            printf("8 bit mono (%d)\n",fmt_chunk->bytes_per_sample); 
            break;
        case 2:
            printf("8 bit stereo or 16 bit mono (%d)\n",fmt_chunk->bytes_per_sample);
            break;
        case 4:
            printf("16 bit stereo (%d)\n",fmt_chunk->bytes_per_sample);
            break;
    }
    
    printf(" Bits Per Sample: %d\n",fmt_chunk->bits_per_sample);
    printf("----------------------------\n");
    
    fmt_chunk->data_length = (unsigned int)wav_preface[40] + ((unsigned int)wav_preface[41] << 8) + ((unsigned int)wav_preface[42] << 16) + ((unsigned int)wav_preface[43] << 24);
}


Wave_Proc::~Wave_Proc(void)
{
    delete fmt_chunk;
}


int Wave_Proc::read_chars(FILE* in, char *s, int n)
{
    int t, ch;

    for (t=0; t<n; t++)
    {
        ch=getc(in);
        if (ch==EOF) return -1;
        s[t]=ch;
    }
    s[t]=0;

    return 0;
}

int Wave_Proc::write_long(FILE *out, int n)
{

    putc((n&255),out);
    putc(((n>>8)&255),out);
    putc(((n>>16)&255),out);
    putc(((n>>24)&255),out);

    return 0;
}

int Wave_Proc::write_word(FILE *out, int n)
{

    putc((n&255),out);
    putc(((n>>8)&255),out);

    return 0;
}

unsigned int Wave_Proc::read_long(FILE* in)
{
    unsigned int t;

    t=getc(in);
    t=(getc(in)<<8)+t;
    t=(getc(in)<<16)+t;
    t=(getc(in)<<24)+t;
    return t;
}

unsigned short Wave_Proc::read_word(FILE* in)
{
    unsigned short t;
    t = (unsigned short)(getc(in)) + ((unsigned short)(getc(in)) << 8);
    return t;
}

int Wave_Proc::parse_fmt_chunk(FILE* in)
{
    int length;
    char chunk_type[5];
    read_chars(in, chunk_type,4);
    length = read_long(in);
    fmt_chunk->format_type = read_word(in);
    fmt_chunk->channel_numbers = read_word(in);
    fmt_chunk->sample_rate = read_long(in);
    fmt_chunk->bytes_per_second = read_long(in);
    fmt_chunk->bytes_per_sample = read_word(in);
    fmt_chunk->bits_per_sample = read_word(in);

    printf("FMT Chunk\n");
    printf("----------------------------\n");
    printf("          Length: %d\n",length);
    printf("     Format Type: ");
    switch(fmt_chunk->format_type)
    {
        case 0:
            printf("Mono\n"); 
            break;
        case 1:
            printf("Stereo\n");
            break;
        default:
            printf("unknown\n");
            break;
    }

    printf(" Channel Numbers: %d\n",fmt_chunk->channel_numbers);
    printf("     Sample Rate: %d\n",fmt_chunk->sample_rate);
    printf("Bytes Per Second: %d\n",fmt_chunk->bytes_per_second);
    printf("Bytes Per Sample: ");
    switch (fmt_chunk->bytes_per_sample)
    {
        case 1:
            printf("8 bit mono (%d)\n",fmt_chunk->bytes_per_sample); 
            break;
        case 2:
            printf("8 bit stereo or 16 bit mono (%d)\n",fmt_chunk->bytes_per_sample);
            break;
        case 4:
            printf("16 bit stereo (%d)\n",fmt_chunk->bytes_per_sample);
            break;
    }
    
    printf(" Bits Per Sample: %d\n",fmt_chunk->bits_per_sample);
    printf("----------------------------\n");

    return 0;
}

int Wave_Proc::parse_data_chunk(FILE* in)
{
    int length;
    char riff_type[5];

    read_chars(in, riff_type,4);
    length=read_long(in);
            
    printf("DATA chunk\n");
    printf("----------------------------\n");
    printf("          Length: %d\n",length);

    
    return length;
}

int Wave_Proc::parse_header(FILE* in)
{
    char riff_type[5];
    char fourcc[5];
    read_chars(in, fourcc,4);
    if (strncmp(fourcc,"RIFF",4)!=0)
    {
        printf("This file is not a RIFF/WAV\n");
        return -1;
    }
    
    fmt_chunk->riff_length=read_long(in);
    read_chars(in, riff_type,4);
    
    printf("RIFF Header\n");
    printf("----------------------------\n");
    printf("          Length: %d\n",fmt_chunk->riff_length);
    printf("            Type: %s\n",riff_type);
    printf("----------------------------\n");
    return 0;
}

int Wave_Proc::write_header(FILE *out)
{
    fprintf(out,"RIFF");
    write_long(out,fmt_chunk->riff_length);
    fprintf(out,"WAVE");
    fprintf(out,"fmt ");
    write_long(out,16);
    write_word(out,fmt_chunk->format_type);
    write_word(out,fmt_chunk->channel_numbers);
    write_long(out,fmt_chunk->sample_rate);
    write_long(out,fmt_chunk->bytes_per_second);
    write_word(out,fmt_chunk->bytes_per_sample);
    write_word(out,fmt_chunk->bits_per_sample);
    fprintf(out,"data");
    write_long(out,fmt_chunk->data_length);
    return 0;
}

int Wave_Proc::write_header(FILE *out, unsigned int data_length)
{
    fprintf(out,"RIFF");
    write_long(out,fmt_chunk->riff_length);
    fprintf(out,"WAVE");
    fprintf(out,"fmt ");
    write_long(out,16);
    write_word(out,fmt_chunk->format_type);
    write_word(out,fmt_chunk->channel_numbers);
    write_long(out,fmt_chunk->sample_rate);
    write_long(out,fmt_chunk->bytes_per_second);
    write_word(out,fmt_chunk->bytes_per_sample);
    write_word(out,fmt_chunk->bits_per_sample);
    fprintf(out,"data");
    write_long(out,data_length);
    return 0;
}

int Wave_Proc::GetChannelNum()
{
    return fmt_chunk->channel_numbers;
}

int Wave_Proc::GetFormatType()
{
    return fmt_chunk->format_type;
}

int Wave_Proc::GetDataLen()
{
    return fmt_chunk->data_length;
}

unsigned short Wave_Proc::ReadWord(FILE* in)
{
    return read_word(in);
}

int Wave_Proc::WriteWord(FILE *out, int n)
{
    return write_word(out, n);
}

int Wave_Proc::WriteHeader(FILE *out, unsigned int data_length)
{
    return write_header(out, data_length);
}
