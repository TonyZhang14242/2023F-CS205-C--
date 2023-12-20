#include "complex.h"
Complex::Complex(const Complex &rhs)
{
    real = rhs.real;
    imag = rhs.imag;
}

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    os << c.real;
    if (c.imag > 0)
    {
        os << "+";
    }
    if (c.imag != 0)
    {
        os << c.imag << "i";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Complex &c)
{
    is >> c.real >> c.imag;
    return is;
}

Complex Complex::operator+(const Complex& rhs) const{
    Complex tmp;
    tmp.real = this->real + rhs.real;
    tmp.imag = this->imag+ rhs.imag;
    return tmp;
}

Complex operator+(double n,Complex &rhs)
{
    Complex tmp;
    tmp.real = n + rhs.real;
    tmp.imag = rhs.imag;
    return tmp;
}

Complex Complex::operator-(const Complex& rhs) const{
    Complex tmp;
    tmp.real = this->real - rhs.real;
    tmp.imag = this->imag - rhs.imag;
    return tmp;
}

Complex operator-(double n, Complex &rhs){
    Complex tmp;
    tmp.real = n - rhs.real;
    tmp.imag = rhs.imag;
    return tmp;
}

Complex Complex::operator*(const Complex& rhs) const{
    Complex tmp;
    tmp.real = this->real * rhs.real - this->imag * rhs.imag;
    tmp.imag = this->real * rhs.imag + rhs.real * this->imag;
    return tmp;
}

Complex operator*(double n, Complex &rhs){
    Complex tmp;
    tmp.real = n * rhs.real;
    tmp.imag = n * rhs.imag;
    return tmp;
}

Complex Complex::operator~() const{
    Complex tmp;
    tmp.real = -this->real;
    tmp.imag = -this->imag;
    return tmp;
}

bool operator==(const Complex& lhs, const Complex& rhs){
    return (lhs.real == rhs.real) && (lhs.imag == rhs.imag);
}

bool operator!=(const Complex& lhs, const Complex& rhs){
    return !(lhs == rhs);
}
