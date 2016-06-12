#include "cross.h"

void 
CL::initW(vector<complex>& obj)		//此公式求出后面快速傅里叶变换的系数
{
	for(int i = 0;i < N; i++)
	{
		obj[i].real = cos(2 * PI * i / N);
		obj[i].img = -1 * sin(2 * PI * i / N);
	}
}

void
CL::change(vector<complex>& obj)	//变址
{
	complex temp;
	unsigned short  i = 0, j = 0, k = 0;
	double t;
	for (int i = 0; i < N; ++i)
	{
		k = i; 
		j = 0;
		t = (log(N)/log(2));
		while((t--) >0)
		{
			j = j<< 1;
			j |= (k & 1);
			k = k >> 1;
		}
		if(j > i)
		{
			temp = obj[i];
			obj[i] = obj[j];
			obj[j] = temp;
		}
	}
}

void
CL::fft(vector<complex>& obj)	//快速傅里叶变换
{
	int i = 0, j = 0, k = 0, L = 0;
	complex up, down, product;
	change(obj);
	for (int i = 0; i < log(N) / log(2); i++)
	{
		L = 1 << i;
		for (j = 0; j < N; j += 2 * L)
		{
			for (k = 0; k < L; k++)
			{
				product = obj[j + k + L] * W[N*k / 2 / L];
				up = obj[j + k] + product;
				down = obj[j + k] - product;
				obj[j + k] = up;
				obj[j + k + L] = down;
			}
		}
	}
}	 

void
CL::ifft(vector<complex>& obj)	//傅里叶逆变换
{
	int i = 0, j = 0, k = 0, L = N;
	complex up, down;
	for (int i = 0; i < (int)(log(N) / log(2)); i++)
	{
		L /= 2;
		for (j = 0; j < N; j += 2 * L)
		{
			for (k = 0; k < L; k++)
			{
				up = R[j + k] + R[j + k + L];
				up.real /= 2;
				up.img /= 2;
				down = R[j + k] - R[j + k + L];
				down = down / W[N*k / 2 / L];
				R[j + k] = up;
				R[j + k + L] = down;
			}
		}
	}
	change(R);	//变址R
}

void
CL::calculate(vector<double>& num1, vector<double>& num2)
{
	complex tmp,result;
	vector<complex> W(N, tmp);
	vector<complex> R(N, tmp);

	for (int i = 0; i < N; i++)
	{
		X[i].real = num1[i];
		X[i].img = 0;
	}
	initW(W);
	fft(X);

	for (int i = 0; i < N; i++)
	{
		Y[i].real = num2[i];
		Y[i].img = 0;
	}
	initW(W);
	fft(Y);

	for (int k = 0; k < N; k++)
		X[k].img = -X[k].img;	//共轭
	for (int k = 0; k < N; k++)
	{
		result = X[k] * Y[k];
		R[k] = result;
	}
	initW(W);
	ifft(R);

	for (int k = 0; k < N / 2; k++)
		array[k] = R[N / 2 + k].real;
	for (int k = N / 2; k < N; k++)
		array[k] = R[k - N / 2].real;
}