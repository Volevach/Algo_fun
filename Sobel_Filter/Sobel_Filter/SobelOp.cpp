#include "SobelOp.h"


SobelOp::SobelOp(void)
{
}


SobelOp::~SobelOp(void)
{
}

unsigned char SobelOp::SobelX(unsigned char in[3][3])
{
    unsigned char i, j, ret = 0;
    for(i = 0; i < 3; i++)
    {
        for(j  = 0; j < 3; j++)
        {
            ret += in[i][j] * sobelXMat[i][j];
        }
    }
    return ret;
}

unsigned char SobelOp::SobelY(unsigned char in[3][3])
{
    unsigned char i, j, ret = 0;
    for(i = 0; i < 3; i++)
    {
        for(j  = 0; j < 3; j++)
        {
            ret += in[i][j] * sobelYMat[i][j];
        }
    }
    return ret;
}

unsigned char SobelOp::SobelNorm(unsigned char x, unsigned char y)
{
    return (unsigned char)(sqrt(((double)(x) * (double)(x)) + ((double)(y) * (double)(y))));
}

unsigned char SobelOp::SobelFilt(unsigned char in[3][3])
{
    return SobelNorm(SobelX(in), SobelY(in));
}