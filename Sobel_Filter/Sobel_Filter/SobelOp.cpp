// main class for the Sobel implementation
// 
// inncludes a generic 2D convolution with a filter operator

#include "SobelOp.h"

// generic constructor
SobelOp::SobelOp(void)
{
}

// generic destructor
SobelOp::~SobelOp(void)
{
}

// perform Sobel in X direction on 2d array in p_in with row length u_xOffset
unsigned char SobelOp::SobelX(unsigned char *p_in, unsigned int u_xOffset)
{
    
    short i_ret = 0;

	// calculate the filtered pixel value
    i_ret -= ((short)(p_in[0]) + 2*(short)(p_in[u_xOffset + 0]) + (short)(p_in[2*u_xOffset + 0]));
    i_ret += ((short)(p_in[2]) + 2*(short)(p_in[u_xOffset + 2]) + (short)(p_in[2*u_xOffset + 2]));
    
	// return the value or 0 if value less than 0
	return (unsigned char)((i_ret>0)?i_ret:0);
}

// perform Sobel in Y direction on 2d array in p_in with row length u_xOffset
unsigned char SobelOp::SobelY(unsigned char *p_in, unsigned int u_xOffset)
{
    short i_ret = 0;

	// calculate the filtered pixel value
    i_ret -= ((short)(p_in[0])         + 2*(short)(p_in[1]) +             (short)(p_in[2]));
    i_ret += ((short)(p_in[2*u_xOffset]) + 2*(short)(p_in[2*u_xOffset + 1]) + (short)(p_in[2*u_xOffset + 2]));
    
	// return the value or 0 if value less than 0
	return (unsigned char)((i_ret>0)?i_ret:0);
}

// mormalize the x and y filtered pixel value to get a unidirectional sobel 
unsigned char SobelOp::SobelNorm(unsigned char x, unsigned char y)
{
	// return sqrt(x^2 + y^2)
    return (unsigned char)(sqrt(((double)(x) * (double)(x)) + ((double)(y) * (double)(y))));
}

// filter input 2D pixel array with the sobel filter operator
unsigned char SobelOp::SobelFilt(unsigned char *p_in, unsigned int u_xOffset)
{
	// calculate the unidirectional filtered pixel value
    unsigned char u_ret = SobelNorm(SobelX(p_in, u_xOffset), SobelY(p_in, u_xOffset));
    
	// return vaslue truncsted to 8 bit
	return (u_ret > 255) ? 255 : u_ret;
}


// filter input 2D pixel array with the sobel filter operator
void SobelOp::SobelFiltImage(unsigned char p_in[MAX_X][MAX_Y], unsigned char p_out[MAX_X][MAX_Y])
{
	// run the sobel window for every pixel in the image of sixe MAX_X x MAX_Y
    for(unsigned int i = 0; i < MAX_X - 2; i++)
    {
        for(unsigned int j = 0; j < MAX_Y - 2; j++)
        {
            p_out[i][j] = SobelFilt(&(p_in[i][j]), MAX_Y);
        }
    }

	// fill the corner pixels with zero
    for(unsigned int i = MAX_X - 2; i < MAX_X; i++)
    {
        for(unsigned int j = MAX_Y - 2; j < MAX_Y; j++)
        {
            p_out[i][j] = 0;
        }
    }
}