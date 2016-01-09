#pragma once
#include <math.h>
class SobelOp
{
public:
    SobelOp(void);
    ~SobelOp(void);

    unsigned char SobelFilt(unsigned char in[3][3]);

private:
    unsigned char SobelX(unsigned char in[3][3]);
    unsigned char SobelY(unsigned char in[3][3]);
    unsigned char SobelNorm(unsigned char x, unsigned char y);

};

const unsigned char sobelXMat[3][3] = {{-1,  0,  1}, {-2, 0 ,2}, {-1, 0, 1}};
const unsigned char sobelYMat[3][3] = {{-1, -2, -1}, { 0, 0 ,0}, { 1, 2, 1}};

