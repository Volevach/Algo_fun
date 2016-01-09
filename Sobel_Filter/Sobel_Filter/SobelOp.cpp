#include "SobelOp.h"


SobelOp::SobelOp(void)
{
}


SobelOp::~SobelOp(void)
{
}

unsigned char SobelOp::SobelX(unsigned char *in, unsigned int xOffset)
{
    
    short ret = 0;
    ret -= ((short)(in[0]) + 2*(short)(in[xOffset + 0]) + (short)(in[2*xOffset + 0]));
    ret += ((short)(in[2]) + 2*(short)(in[xOffset + 2]) + (short)(in[2*xOffset + 2]));
    return (unsigned short)((ret>0)?ret:0);
}

unsigned char SobelOp::SobelY(unsigned char *in, unsigned int xOffset)
{
    short ret = 0;
    ret -= ((short)(in[0])         + 2*(short)(in[1]) +             (short)(in[2]));
    ret += ((short)(in[2*xOffset]) + 2*(short)(in[2*xOffset + 1]) + (short)(in[2*xOffset + 2]));
    return (unsigned short)((ret>0)?ret:0);
}

unsigned char SobelOp::SobelNorm(unsigned char x, unsigned char y)
{
    return (unsigned char)(sqrt(((double)(x) * (double)(x)) + ((double)(y) * (double)(y))));
}

unsigned char SobelOp::SobelFilt(unsigned char *in, unsigned int xOffset)
{
    unsigned char ret = SobelNorm(SobelX(in, xOffset), SobelY(in, xOffset));
    return (ret > 255) ? 255 : ret;
}

void SobelOp::SobelFiltImage(unsigned char in[MAX_X][MAX_Y], unsigned char out[MAX_X][MAX_Y])
{
    for(unsigned int i = 0; i < MAX_X - 2; i++)
    {
        for(unsigned int j = 0; j < MAX_Y - 2; j++)
        {
            out[i][j] = SobelFilt(&(in[i][j]), MAX_Y);
        }
    }

    for(unsigned int i = MAX_X - 2; i < MAX_X; i++)
    {
        for(unsigned int j = MAX_Y - 2; j < MAX_Y; j++)
        {
            out[i][j] = 0;
        }
    }
}