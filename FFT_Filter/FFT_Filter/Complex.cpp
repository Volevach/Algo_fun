#include "Complex.h"


Complex::Complex(void)
{
    real = 0.0;
    imag = 0.0;
}

Complex::Complex(float re, float im)
{
    real = re;
    imag = im;
}


Complex::~Complex(void)
{
}

float Complex::GetReal()
{
    return real;
}

float Complex::GetImag()
{
    return imag;
}

Complex Complex::ConjCompl()
{
    return Complex(real, -imag);
}

Complex compAdd(Complex a, Complex b)
{
    return Complex(a.GetReal() + b.GetReal(), a.GetImag() + b.GetImag());
}

Complex compSub(Complex a, Complex b)
{
    return Complex(a.GetReal() - b.GetReal(), a.GetImag() - b.GetImag());
}

Complex compMul(Complex a, Complex b)
{
    return Complex((a.GetReal() * b.GetReal()) - (a.GetImag() * b.GetImag()), (a.GetReal() * b.GetImag()) + (a.GetImag() * b.GetReal()));
}