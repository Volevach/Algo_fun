// main class for the Sobel implementation
// 
// inncludes a generic 2D convolution with a filter operator

#pragma once
#include <math.h>
#include "stdafx.h"

class SobelOp
{
public:
	// generic constructor
    SobelOp(void);

	// generic destructor
    ~SobelOp(void);

    // filter input 2D pixel array with the sobel filter operator
	void SobelFiltImage(unsigned char p_in[MAX_X][MAX_Y], unsigned char p_out[MAX_X][MAX_Y]);
    

private:
	// perform Sobel in X direction on 2d array in p_in with row length u_xOffset
    unsigned char SobelX(unsigned char *p_in, unsigned int u_xOffset);
    
	// perform Sobel in Y direction on 2d array in p_in with row length u_xOffset
	unsigned char SobelY(unsigned char *p_in, unsigned int u_xOffset);
    
	// mormalize the x and y filtered pixel value to get a unidirectional sobel 
	unsigned char SobelNorm(unsigned char x, unsigned char y);
    
	// main function to perform an unidirectional sobel on 2d array in p_in with row length u_xOffset
	unsigned char SobelFilt(unsigned char *p_in, unsigned int u_xOffset);

};

// Sobel opersator for x direction
const short c_sobelXMat[3][3] = {{-1,  0,  1}, {-2, 0 ,2}, {-1, 0, 1}};

// Sobel opersator for x direction
const short c_sobelYMat[3][3] = {{-1, -2, -1}, { 0, 0 ,0}, { 1, 2, 1}};

