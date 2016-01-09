#pragma once
#include <math.h>
#include "stdafx.h"

class SobelOp
{
public:
    SobelOp(void);
    ~SobelOp(void);

    void SobelFiltImage(unsigned char in[MAX_X][MAX_Y], unsigned char out[MAX_X][MAX_Y]);
    

private:
    unsigned char SobelX(unsigned char *in, unsigned int xOffset);
    unsigned char SobelY(unsigned char *in, unsigned int xOffset);
    unsigned char SobelNorm(unsigned char x, unsigned char y);
    unsigned char SobelFilt(unsigned char *in, unsigned int xOffset);

};

const short sobelXMat[3][3] = {{-1,  0,  1}, {-2, 0 ,2}, {-1, 0, 1}};
const short sobelYMat[3][3] = {{-1, -2, -1}, { 0, 0 ,0}, { 1, 2, 1}};

