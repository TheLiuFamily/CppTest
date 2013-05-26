#include "mycomplex.h"


mycomplex::mycomplex(void)
	: real(0)
	, imag(0)
{
}
mycomplex::mycomplex(double r, double i)
	: real(r)
	, imag(i)
{

}
mycomplex::mycomplex(const mycomplex& c)
{
	real = c.real;
	imag = c.imag;
}
mycomplex::~mycomplex(void)
{
}

mycomplex& mycomplex::operator=(const mycomplex& rhs)
{
	real = rhs.real;
	imag = rhs.imag;

	return *this;
}


mycomplex& mycomplex::operator+=(const mycomplex& rhs)
{
	real += rhs.real;
	imag += rhs.imag;
	return *this;
}
mycomplex& mycomplex::operator-=(const mycomplex& rhs)
{
	real -= rhs.real;
	imag -= rhs.imag;
	return *this;
}
mycomplex& mycomplex::operator*=(const mycomplex& rhs)
{

	*this = mycomplex(real*rhs.real - imag*rhs.imag
		, imag*rhs.real + real*rhs.imag);
	return *this;
}
mycomplex& mycomplex::operator/=(const mycomplex& rhs)
{
	double temp = rhs.real*rhs.real+rhs.imag*rhs.imag;
	*this = mycomplex((real*rhs.real+imag*rhs.imag)/temp
		, (imag*rhs.real-real*rhs.imag)/temp);
	return *this;
}

const mycomplex operator+(const mycomplex& lhs, const mycomplex& rhs)
{
	return mycomplex(lhs) += rhs;
}
const mycomplex operator-(const mycomplex& lhs, const mycomplex& rhs)
{
	return mycomplex(lhs) -= rhs;
}
const mycomplex operator*(const mycomplex& lhs, const mycomplex& rhs)
{
	return mycomplex(lhs) *= rhs;
}
const mycomplex operator/(const mycomplex& lhs, const mycomplex& rhs)
{
	return mycomplex(lhs) /= rhs;
}