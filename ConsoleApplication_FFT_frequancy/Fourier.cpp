
#include <math.h>
#include ".\fourier.h"

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

float hann(float theta) 
{
	return	0.5 * (1 - cos(0.5 * theta));
}

CFourier::CFourier(void)
{
	pi=4*atan((double)1);vector=NULL;
}

CFourier::~CFourier(void)
{if(vector!=NULL)
		delete [] vector;
}

// FFT 1D
void CFourier::_FFT(float data[], unsigned long number_of_samples, unsigned int sample_rate, int sign)
{
	unsigned long n,mmax,m,j,istep,i;
	double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;

	if(vector!=NULL)
        delete [] vector;
	vector=new float [2*sample_rate];

	for(n=0; n<sample_rate;n++)
	{
		if(n<number_of_samples)
			vector[2*n]=data[n];
		else
			vector[2*n]=0;
		vector[2*n+1]=0;
	}

	//бинарная инверсия (обратите внимание, что индексы
	 //начнем с 0, ведь это означает, что
	 //реальная часть комплекса находится на четных индексах
	 // и сложная часть находится на нечетных индексах)
	n=sample_rate << 1;
	j=0;
	for (i=0;i<n/2;i+=2) {
		if (j > i) {
			SWAP(vector[j],vector[i]);
			SWAP(vector[j+1],vector[i+1]);
			if((j/2)<(n/4)){
				SWAP(vector[(n-(i+2))],vector[(n-(j+2))]);
				SWAP(vector[(n-(i+2))+1],vector[(n-(j+2))+1]);
			}
		}
		m=n >> 1;
		while (m >= 2 && j >= m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
		
	mmax=4; // размер окна
	while (n > mmax) {
		istep=mmax << 1;
		theta=sign*(2*pi/mmax);
		wtemp=sin(0.5*theta);
		//wtemp = 1-cos(0.5 * theta);
		//0.5 * (1 - cos((2 * M_PI * i) / (SampleCount - 1)));
		wpr = hann(theta);
		wpr = -2.0 * wtemp * wtemp;
		//wpi=sin(theta);
		wpi = sin(theta);
		wr=1.0;
		wi=0.0;
		for (m=1;m<mmax;m+=2) {
			for (i=m;i<=n;i+=istep) {
				j=i+mmax;
				tempr=wr*vector[j-1]-wi*vector[j];
				tempi=wr*vector[j]+wi*vector[j-1];
				vector[j-1]=vector[i-1]-tempr;
				vector[j]=vector[i]-tempi;
				vector[i-1] += tempr;
				vector[i] += tempi;
			}
			wr=(wtemp=wr)*wpr-wi*wpi+wr;
			wi=wi*wpr+wtemp*wpi+wi;
		}
		mmax=istep;
	}
	
	fundamental_frequency=0;
	for(i=2; i<=sample_rate; i+=2)
	{
		if((pow(vector[i],2)+pow(vector[i+1],2))>(pow(vector[fundamental_frequency],2)+pow(vector[fundamental_frequency+1],2))){
			fundamental_frequency=i;
		}
	}
		
	fundamental_frequency=(long)floor((float)fundamental_frequency/2);

}
