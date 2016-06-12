#ifndef __CROSS_H
#define __CROSS_H
#include "complex.h"
using namespace std;

#define N 32
#define PI 3.1415926

class CL
{
public:
	CL() = default;
	CL();
  	~CL();
	void initW(vector<complex>& obj);	//核运算欧拉公式
	void change(vector<complex>& obj);	//变址运算
	void fft(vector<complex>& obj);	//快速傅里叶变化
	void ifft(vector<complex>& obj);	//傅里叶逆变化
	void calculate(vector<double>& num1,vector<double>& num2); //计算主函数
private:
   	vector<complex> X;
	vector<complex> Y;
	vector<complex> R;
    vector<complex> W;
	vector<double> array;

};

#endif
