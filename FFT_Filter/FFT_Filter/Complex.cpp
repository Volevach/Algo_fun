// class for representing a complex number
// 
// implements the real and imaginary representation of a complex number and the conjucate complex output
// includes helper functions for addition, substraction and multiplication

#include "Complex.h"

// generic constructor initializes all zero
Complex::Complex(void)
{
    f_real = 0.0;
    f_imag = 0.0;
}


// contructor with real and imaginary part provided
Complex::Complex(float re, float im)
{
    f_real = re;
    f_imag = im;
}

// generic destructor
Complex::~Complex(void)
{
}

// Getter for the real part
float Complex::GetReal()
{
    return f_real;
}

// getter for the imag part
float Complex::GetImag()
{
    return f_imag;
}

// getter for the number with negated imaginary part
// returns a complex number
Complex Complex::ConjCompl()
{
    return Complex(f_real, -f_imag);
}


// helper function returning the sum of two complex numbers
Complex CompAdd(Complex a, Complex b)
{
    return Complex(a.GetReal() + b.GetReal(), a.GetImag() + b.GetImag());
}

// helper function returning the difference between two complex numbers
Complex CompSub(Complex a, Complex b)
{
    return Complex(a.GetReal() - b.GetReal(), a.GetImag() - b.GetImag());
}

// helper function returning the product of two complex numbers
Complex CompMul(Complex a, Complex b)
{
	// returns (a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re)
    return Complex((a.GetReal() * b.GetReal()) - (a.GetImag() * b.GetImag()), (a.GetReal() * b.GetImag()) + (a.GetImag() * b.GetReal()));
}