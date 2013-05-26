#pragma once

class mycomplex
{
public:
	mycomplex(void);
	mycomplex(double r, double i);
	mycomplex(const mycomplex& c);
	~mycomplex(void);
	mycomplex& operator=(const mycomplex& rhs);
private:
	double real;
	double imag;

public:
	mycomplex& operator+=(const mycomplex& rhs);
	mycomplex& operator-=(const mycomplex& rhs);
	mycomplex& operator*=(const mycomplex& rhs);
	mycomplex& operator/=(const mycomplex& rhs);

public:
	double getReal() const { return real; }
	double getImag() const { return imag; }
	void setReal(double r) { real = r; }
	void setImag(double i) { imag = i; }
};

const mycomplex operator+(const mycomplex& lhs, const mycomplex& rhs);
const mycomplex operator-(const mycomplex& lhs, const mycomplex& rhs);
const mycomplex operator*(const mycomplex& lhs, const mycomplex& rhs);
const mycomplex operator/(const mycomplex& lhs, const mycomplex& rhs);