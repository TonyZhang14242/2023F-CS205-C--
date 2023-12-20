#include <iostream>
#ifndef COMPLEX_H
#define COMPLEX_H

class Complex{
    private:
        double real;
        double imag;

    public:
        Complex(): real(1), imag(1) {}
        Complex(double re): real(re), imag(0){}
        Complex(double re, double im): real(re), imag(im) {}
        Complex(const Complex& rhs);
        Complex operator+(const Complex& rhs) const;
        friend Complex operator+(double n, Complex& rhs);

        Complex operator-(const Complex& rhs) const;
        friend Complex operator-(double n,Complex& rhs);


        Complex operator*(const Complex& rhs) const;
        friend Complex operator*(double n, Complex& rhs);

        Complex operator~() const;

        friend bool operator==(const Complex& lhs, const Complex& rhs);
        friend bool operator!=(const Complex& lhs, const Complex& rhs);

        friend std::ostream& operator<<(std::ostream &os, const Complex& c);
        friend std::istream& operator>>(std::istream &is, Complex &c);
};

#endif