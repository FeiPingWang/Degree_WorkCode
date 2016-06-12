#include "complex.h"
using namespace std;

complex&
operator+(const complex &lhs,const complex &rhs)
{
	complex res;
	res.real = lhs.real + rhs.real;
	res.img = lhs.img + rhs.img;
	return res;
}

complex&
operator-(const complex &lhs,const complex &rhs)
{
	complex res;
	res.real = lhs.real - rhs.real;
	res.img = lhs.img - rhs.img;
	return res;
}

complex&
operator*(const complex &lhs,const complex &rhs)
{
	complex res;
	res.real = lhs.real*rhs.real - lhs.img*rhs.img;
	res.img  = lhs.real*rhs.img + lhs.img*rhs.real;
	return res;
}

complex&
operator/(const complex &lhs,const complex &rhs)
{
	complex res;
	res.real = (lhs.real*rhs.real + lhs.img * rhs.img) \
			   /(rhs.real*rhs.real+rhs.img*rhs.img);
	res.img = (lhs.img*rhs.real - lhs.real*rhs.img) \
			  /(rhs.real*rhs.real+rhs.img*rhs.img);
	return res;
}

//¸³ÖµÔËËã·û
complex&
complex::operator=(const complex &rhs)
{
	if(this->real != rhs.real || this->img != rhs.img)
	{
		this->real = rhs.real;
		this->img = rhs.img;
	}
	return *this;
}
