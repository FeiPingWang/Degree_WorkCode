#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415926   
#define N  64		 //数据的长度	 

extern unsigned short AD_Value[256][2];
													 

typedef struct		   
{
	double real;	 	 /*实部*/
	double img;			 /*虚部*/
}complex;

//之前失败是因为分配的内存空间不够
complex x[N], y[N], R[N], W[N*2];/*输出序列的值*/

void add(complex a, complex b, complex *c)
{
	c->real = a.real + b.real;
	c->img = a.img + b.img;
}
void sub(complex a, complex b, complex *c)
{
	c->real = a.real - b.real;
	c->img = a.img - b.img;
}
void mul(complex a, complex b, complex *c)
{
	c->real = a.real*b.real - a.img*b.img;
	c->img = a.real*b.img + a.img*b.real;
}
void divi(complex a, complex b, complex *c)
{
	c->real = (a.real*b.real + a.img*b.img) / (b.real*b.real + b.img*b.img);
	c->img = (a.img*b.real - a.real*b.img) / (b.real*b.real + b.img*b.img);
}

void initW(int size)	  		//欧拉公式运算   
{
	int i=0;
//	W = (complex *)(size*sizeof(complex));
//	printf("进入initw");
	for (i = 0; i< size ; i++)
	{
		W[i].real = cos(2 * PI / size*i);
		W[i].img = -1 * sin(2 * PI / size*i);
	}
//	printf("结束initw");
}

void changex(int size)			//变址运算X
{
	complex temp;
	unsigned short i = 0, j = 0, k = 0;
	double t;
	printf("进入changex");
	for (i = 0; i<size; i++)
	{
		k = i; j = 0;
		t = (log(size) / log(2));
		while ((t--)>0)
		{
			j = j << 1;
			j |= (k & 1);
			k = k >> 1;
		}
		if (j>i)
		{
			temp = x[i];
			x[i] = x[j];
			x[j] = temp;
		}
	}
}

void changey(int size)   //变址运算Y
{
	complex temp;
	unsigned short i = 0, j = 0, k = 0;
	double t;
	for (i = 0; i<size; i++)
	{
		k = i; j = 0;
		t = (log(size) / log(2));
		while ((t--)>0)
		{
			j = j << 1;
			j |= (k & 1);
			k = k >> 1;
		}
		if (j>i)
		{
			temp = y[i];
			y[i] = y[j];
			y[j] = temp;
		}
	}
}

void changeR(int size)		//变址运算Rxy
{					   	
	complex temp;
	unsigned short i = 0, j = 0, k = 0;
	double t;
	for (i = 0; i<size; i++)
	{
		k = i; j = 0;
		t = (log(size) / log(2));
		while ((t--)>0)
		{
			j = j << 1;
			j |= (k & 1);
			k = k >> 1;
		}
		if (j>i)
		{
			temp = R[i];
			R[i] = R[j];
			R[j] = temp;
		}
	}
}

void fftx()//快速傅里叶函数
{
	int i = 0, j = 0, k = 0, l = 0;
	complex up, down, product;
	printf("进入fftx\n");
	changex(N);
	for (i = 0; i<log(N) / log(2); i++) /*一级蝶形运算*/
	{
		l = 1 << i;
		for (j = 0; j<N; j += 2 * l) 	/*一组蝶形运算*/
		{
			for (k = 0; k<l; k++) 	/*一个蝶形运算*/
			{
				mul(x[j + k + l], W[N*k / 2 / l], &product);
				add(x[j + k], product, &up);
				sub(x[j + k], product, &down);
				x[j + k] = up;
				x[j + k + l] = down;
			}
		}
	}
}

void ffty()//快速傅里叶函数
{
	int i = 0, j = 0, k = 0, l = 0;
	complex up, down, product;
	changey(N);
	for (i = 0; i<log(N) / log(2); i++) /*一级蝶形运算*/
	{
		l = 1 << i;
		for (j = 0; j<N; j += 2 * l) /*一组蝶形运算*/
		{
			for (k = 0; k<l; k++) /*一个蝶形运算*/
			{
				mul(y[j + k + l], W[N*k / 2 / l], &product);
				add(y[j + k], product, &up);
				sub(y[j + k], product, &down);
				y[j + k] = up;
				y[j + k + l] = down;
			}
		}
	}
}

void ifft(int length) //傅里叶逆变换  
{
	int i = 0, j = 0, k = 0, l = length;
	complex up, down;
	for (i = 0; i<(int)(log(length) / log(2)); i++) /*一级蝶形运算*/
	{
		l /= 2;
		for (j = 0; j<length; j += 2 * l) 			/*一组蝶形运算*/
		{										
			for (k = 0; k<l; k++) 					/*一个蝶形运算*/
			{
				add(R[j + k], R[j + k + l], &up);
				up.real /= 2; up.img /= 2;
				sub(R[j + k], R[j + k + l], &down);
				down.real /= 2; down.img /= 2;
				divi(down, W[length*k / 2 / l], &down);
				R[j + k] = up;
				R[j + k + l] = down;
			}
		}
	}
	changeR(length);
}

void correlation()
{
	int datax[]={8,8,0,4,5,8,8,0,4,5,8,2,2,3,6,5,3,2,5,2,5,7,4,1,8,3,4,7,4,7,4,1,8,8,6,4,5,8,8,0,4,5,8,2,2,3,6,5,9,2,5,2,5,7,4,1,8,5,8,0,4,5,8,7};
	int datay[]={4,1,8,8,5,6,7,8,8,0,4,5,8,8,0,4,5,8,2,2,3,6,5,3,2,5,2,5,7,4,1,8,3,4,7,4,7,4,1,8,8,6,4,5,8,8,0,4,5,8,2,2,3,6,5,9,2,5,2,5,7,4,1,8};
	int	max_time=0;
	/*对x进行傅里叶变换*/
	double rest[N * 2] = { 0 };
	int i=0,j=0;
	int k=0;
	int max=0;
	complex result;
//	printf("kais");
	for (i = 0; i< N; i++)			//输入x序列的复数形式
	{
	//	x[i].real = AD_Value[i][0];	  //把AD_Value[0]的数据输入到X[]中
		 x[i].real = datax[i];
		x[i].img = 0;
	}
	initW(N);
//	printf("准备进入fftx");																		 
	fftx();

	/*对y进行傅里叶变换*/
	
	for (j = 0; j < N; j++)				//输入y序列的复数形式
	{
	//	y[j].real = AD_Value[j][1];		//把AD_Value[1]的数据输入到y[]中
		y[j].real =	 datay[j];
		y[j].img = 0;
	}
	initW(N);
	ffty();

	/*求xy进行互相关变换*/

	for (k = 0; k < N; k++)    //取xk的共轭 
		x[k].img = -x[k].img;
	for (k = 0; k < N; k++)
	{
		mul(x[k], y[k], &result);	//x和y的实部虚部相乘 结果存在result中 然后存入数组R[]
		R[k] = result;             	//结果就是R(xy)的互相关函数
	}
	initW(N);
	ifft(N);                        //对结果R(xy)的互相关函数做傅里叶逆变换
	printf("\nxy互相关变换结果\n");
	for (k = 0; k < N; k++)
	{
		//	 if(k%5==0 && k!=0)
		//	 	printf("\n");
		//rest[k]=sqrt(R[k].real*R[k].real + R[k].img*R[k].img);
		//printf("%.4f ", rest[k]/N*2);	    //串口输出结果
		printf("%d %g\n",k,R[k].real);
	}
	/*峰值搜索*/
	max = R[0].real;
	for(i=0;i<N;i++)
	{
	   if(R[i].real>max)
	   {
	   		max=R[i].real;
			max_time=i;	  //出现峰值的位置
	   }
	}
	printf("峰值渡越时间\n");  
	printf("%d\n",max);
	printf("%d\n",max_time);  //输出峰值的位置
	/*渡越时间*/
	//位置*每两个读数的时间间隔；
}
