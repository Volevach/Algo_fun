// based on normalize.c by Michael Kohn
// https://www.mikekohn.net/stuff/normalize.c

#include "Wave_Proc.h"

Wave_Proc::Wave_Proc()
{

}

Wave_Proc::Wave_Proc(FILE* in)
{
    file_in = in;

    parse_header();
    parse_fmt_chunk();
    fmt_chunk.data_length = parse_data_chunk();

}


Wave_Proc::~Wave_Proc(void)
{

}


int Wave_Proc::read_chars(char *s, int n)
{
    int t,ch;

    for (t=0; t<n; t++)
    {
        ch=getc(file_in);
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

unsigned int Wave_Proc::read_long()
{
    unsigned int t;

    t=getc(file_in);
    t=(getc(file_in)<<8)+t;
    t=(getc(file_in)<<16)+t;
    t=(getc(file_in)<<24)+t;

    return t;
}

unsigned short Wave_Proc::read_word()
{
    unsigned short t;
    t = (unsigned short)(getc(file_in)) + ((unsigned short)(getc(file_in)) << 8);
    return t;
}

int Wave_Proc::parse_fmt_chunk()
{
    int length;
    char chunk_type[5];
    read_chars(chunk_type,4);
    length = read_long();
    fmt_chunk.format_type = read_word();
    fmt_chunk.channel_numbers = read_word();
    fmt_chunk.sample_rate = read_long();
    fmt_chunk.bytes_per_second = read_long();
    fmt_chunk.bytes_per_sample = read_word();
    fmt_chunk.bits_per_sample = read_word();

    printf("FMT Chunk\n");
    printf("----------------------------\n");
    printf("          Length: %d\n",length);
    printf("     Format Type: ");
    switch(fmt_chunk.format_type)
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

    printf(" Channel Numbers: %d\n",fmt_chunk.channel_numbers);
    printf("     Sample Rate: %d\n",fmt_chunk.sample_rate);
    printf("Bytes Per Second: %d\n",fmt_chunk.bytes_per_second);
    printf("Bytes Per Sample: ");
    switch (fmt_chunk.bytes_per_sample)
    {
        case 1:
            printf("8 bit mono (%d)\n",fmt_chunk.bytes_per_sample); 
            break;
        case 2:
            printf("8 bit stereo or 16 bit mono (%d)\n",fmt_chunk.bytes_per_sample);
            break;
        case 4:
            printf("16 bit stereo (%d)\n",fmt_chunk.bytes_per_sample);
            break;
    }
    
    printf(" Bits Per Sample: %d\n",fmt_chunk.bits_per_sample);
    printf("----------------------------\n");

    return 0;
}

int Wave_Proc::parse_data_chunk()
{
    int length;
    char riff_type[5];

    read_chars(riff_type,4);
    length=read_long();
            
    printf("DATA chunk\n");
    printf("----------------------------\n");
    printf("          Length: %d\n",length);

    
    return length;
}

int Wave_Proc::parse_header()
{
    char riff_type[5];
    char fourcc[5];
    read_chars(fourcc,4);
    if (strncmp(fourcc,"RIFF",4)!=0)
    {
        printf("This file is not a RIFF/WAV\n");
        return -1;
    }
    
    fmt_chunk.riff_length=read_long();
    read_chars(riff_type,4);
    
    printf("RIFF Header\n");
    printf("----------------------------\n");
    printf("          Length: %d\n",fmt_chunk.riff_length);
    printf("            Type: %s\n",riff_type);
    printf("----------------------------\n");
    return 0;
}

int Wave_Proc::write_header(FILE *out)
{
    fprintf(out,"RIFF");
    write_long(out,fmt_chunk.riff_length);
    fprintf(out,"WAVE");
    fprintf(out,"fmt ");
    write_long(out,16);
    write_word(out,fmt_chunk.format_type);
    write_word(out,fmt_chunk.channel_numbers);
    write_long(out,fmt_chunk.sample_rate);
    write_long(out,fmt_chunk.bytes_per_second);
    write_word(out,fmt_chunk.bytes_per_sample);
    write_word(out,fmt_chunk.bits_per_sample);
    fprintf(out,"data");
    write_long(out,fmt_chunk.data_length);
    return 0;
}

int Wave_Proc::GetChannelNum()
{
    return fmt_chunk.channel_numbers;
}

int Wave_Proc::GetFormatType()
{
    return fmt_chunk.format_type;
}

int Wave_Proc::GetDataLen()
{
    return fmt_chunk.data_length;
}

unsigned short Wave_Proc::ReadWord()
{
    return read_word();
}

int Wave_Proc::WriteWord(FILE *out, int n)
{
    return write_word(out, n);
}

int Wave_Proc::WriteHeader(FILE *out)
{
    return write_header(out);
}
