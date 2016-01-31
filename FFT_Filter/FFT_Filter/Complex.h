// class for representing a complex number
// 
// implements the real and imaginary representation of a complex number and the conjucate complex output
// includes helper functions for addition, substraction and multiplication


#pragma once
class Complex
{
public:
	// generic constructor
    Complex(void);

	// constructior with real and imaginary part provided
    Complex(float re, float im);
    
	// generic destructor
	~Complex(void);
    
	// returns the real fraction of the imaginary number as float
    float GetReal();

	// returns the imaginary fraction of the imaginary number as float
    float GetImag();

	// returns the conjugated complex representation of the number
    Complex ConjCompl();

private:
	// float member variables for the real and imaginary part
    float f_real;
    float f_imag;

};

// helper function returning the sum of two complex numbers
Complex CompAdd(Complex a, Complex b);

// helper function returning the difference between two complex numbers
Complex CompSub(Complex a, Complex b);

// helper function returning the product of two complex numbers
Complex CompMul(Complex a, Complex b);