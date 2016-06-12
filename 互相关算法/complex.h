#ifndef __COMPLEX_H
#define __COMPLEX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#define N 64
int size = N;
class CL;

class complex{
public:
	complex() = default;
	complex(double i,double j) : real(i), img(j) {};
	~complex();
	complex& operator=(const complex &rhs);

	friend complex& operator+(const complex &lhs, const complex &rhs);
	friend complex& operator-(const complex &lhs, const complex &rhs);
	friend complex& operator*(const complex &lhs, const complex &rhs);
	friend complex& operator/(const complex &lhs, const complex &rhs);
	friend CL;	//ÓÑÔªÀà

private:
	double real;
	double img;
};

complex& operator+(const complex &lhs, const complex &rhs);
complex& operator-(const complex &lhs, const complex &rhs);
complex& operator*(const complex &lhs, const complex &rhs);
complex& operator/(const complex &lhs, const complex &rhs);

#endif
