#pragma once
class Complex
{
public:
    Complex(void);
    Complex(float, float);
    ~Complex(void);
    
    float GetReal();
    float GetImag();
    Complex ConjCompl();

private:
    float real;
    float imag;

};

Complex compAdd(Complex a, Complex b);
Complex compSub(Complex a, Complex b);
Complex compMul(Complex a, Complex b);