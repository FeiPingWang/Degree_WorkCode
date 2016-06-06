#ifndef _HXG_H
#define _HXG_H

typedef struct		   
{
	double real;	 	 /*Êµ²¿*/
	double img;			 /*Ðé²¿*/
}complex;

void add(complex a, complex b, complex *c);
void sub(complex a, complex b, complex *c);
void mul(complex a, complex b, complex *c);
void divi(complex a, complex b, complex *c);

void initW(int size);
void changex(int size);
void changey(int size);
void changeR(int size);
void fftx();
void ffty();
void ifft(int length);
void correlation();

#endif