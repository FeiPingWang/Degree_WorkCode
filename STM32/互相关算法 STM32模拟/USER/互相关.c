#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415926   
#define N  64		 //���ݵĳ���	 

extern unsigned short AD_Value[256][2];
													 

typedef struct		   
{
	double real;	 	 /*ʵ��*/
	double img;			 /*�鲿*/
}complex;

//֮ǰʧ������Ϊ������ڴ�ռ䲻��
complex x[N], y[N], R[N], W[N*2];/*������е�ֵ*/

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

void initW(int size)	  		//ŷ����ʽ����   
{
	int i=0;
//	W = (complex *)(size*sizeof(complex));
//	printf("����initw");
	for (i = 0; i< size ; i++)
	{
		W[i].real = cos(2 * PI / size*i);
		W[i].img = -1 * sin(2 * PI / size*i);
	}
//	printf("����initw");
}

void changex(int size)			//��ַ����X
{
	complex temp;
	unsigned short i = 0, j = 0, k = 0;
	double t;
	printf("����changex");
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

void changey(int size)   //��ַ����Y
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

void changeR(int size)		//��ַ����Rxy
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

void fftx()//���ٸ���Ҷ����
{
	int i = 0, j = 0, k = 0, l = 0;
	complex up, down, product;
	printf("����fftx\n");
	changex(N);
	for (i = 0; i<log(N) / log(2); i++) /*һ����������*/
	{
		l = 1 << i;
		for (j = 0; j<N; j += 2 * l) 	/*һ���������*/
		{
			for (k = 0; k<l; k++) 	/*һ����������*/
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

void ffty()//���ٸ���Ҷ����
{
	int i = 0, j = 0, k = 0, l = 0;
	complex up, down, product;
	changey(N);
	for (i = 0; i<log(N) / log(2); i++) /*һ����������*/
	{
		l = 1 << i;
		for (j = 0; j<N; j += 2 * l) /*һ���������*/
		{
			for (k = 0; k<l; k++) /*һ����������*/
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

void ifft(int length) //����Ҷ��任  
{
	int i = 0, j = 0, k = 0, l = length;
	complex up, down;
	for (i = 0; i<(int)(log(length) / log(2)); i++) /*һ����������*/
	{
		l /= 2;
		for (j = 0; j<length; j += 2 * l) 			/*һ���������*/
		{										
			for (k = 0; k<l; k++) 					/*һ����������*/
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
	/*��x���и���Ҷ�任*/
	double rest[N * 2] = { 0 };
	int i=0,j=0;
	int k=0;
	int max=0;
	complex result;
//	printf("kais");
	for (i = 0; i< N; i++)			//����x���еĸ�����ʽ
	{
	//	x[i].real = AD_Value[i][0];	  //��AD_Value[0]���������뵽X[]��
		 x[i].real = datax[i];
		x[i].img = 0;
	}
	initW(N);
//	printf("׼������fftx");																		 
	fftx();

	/*��y���и���Ҷ�任*/
	
	for (j = 0; j < N; j++)				//����y���еĸ�����ʽ
	{
	//	y[j].real = AD_Value[j][1];		//��AD_Value[1]���������뵽y[]��
		y[j].real =	 datay[j];
		y[j].img = 0;
	}
	initW(N);
	ffty();

	/*��xy���л���ر任*/

	for (k = 0; k < N; k++)    //ȡxk�Ĺ��� 
		x[k].img = -x[k].img;
	for (k = 0; k < N; k++)
	{
		mul(x[k], y[k], &result);	//x��y��ʵ���鲿��� �������result�� Ȼ���������R[]
		R[k] = result;             	//�������R(xy)�Ļ���غ���
	}
	initW(N);
	ifft(N);                        //�Խ��R(xy)�Ļ���غ���������Ҷ��任
	printf("\nxy����ر任���\n");
	for (k = 0; k < N; k++)
	{
		//	 if(k%5==0 && k!=0)
		//	 	printf("\n");
		//rest[k]=sqrt(R[k].real*R[k].real + R[k].img*R[k].img);
		//printf("%.4f ", rest[k]/N*2);	    //����������
		printf("%d %g\n",k,R[k].real);
	}
	/*��ֵ����*/
	max = R[0].real;
	for(i=0;i<N;i++)
	{
	   if(R[i].real>max)
	   {
	   		max=R[i].real;
			max_time=i;	  //���ַ�ֵ��λ��
	   }
	}
	printf("��ֵ��Խʱ��\n");  
	printf("%d\n",max);
	printf("%d\n",max_time);  //�����ֵ��λ��
	/*��Խʱ��*/
	//λ��*ÿ����������ʱ������
}
