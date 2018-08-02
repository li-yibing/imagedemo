// Fourer.cpp: implementation of the CFourer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Fourer.h"
#include "mathematic.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFourer::CFourer()
{
	
}

CFourer::~CFourer()
{
	
}

void CFourer::DFT(double *src, Complex *dst, int size)
{
	for(int m=0;m<size;m++)
	{
		double real=0.0;
		double imagin=0.0;
		for(int n=0;n<size;n++)
		{
			double x=M_PI*2*m*n/size;
			real+=src[n]*cos(x);
			imagin+=src[n]*(-sin(x));
		}	
		dst[m].real=real;
		dst[m].imagin=imagin;
	
	}
}

void CFourer::IDFT(Complex *src, Complex *dst, int size)
{
	for(int m=0;m<size;m++)
	{
		double real=0.0;
		double imagin=0.0;
		for(int n=0;n<size;n++)
		{
			double x=M_PI*2*m*n/size;
			real+=src[n].real*cos(x)-src[n].imagin*sin(x);
			imagin+=src[n].imagin*cos(x)+src[n].real*sin(x);
		}
		real/=size;
		imagin/=size;	
		if(dst!=NULL)
		{
			dst[m].real=real;
			dst[m].imagin=imagin;
		}
	}
}

int CFourer::DFT2D(double *src, Complex *dst, int size_w, int size_h)
{
	for(int v=0;v<size_h;v++)
	{
		for(int u=0;u<size_w;u++)
		{
			double real=0.0;
			double imagin=0.0;
			for(int j=0;j<size_h;j++)
			{
				for(int i=0;i<size_w;i++)
				{
					double R=src[j*size_w+i];
					if(R==0)
					{
						real=real;
						imagin=imagin;
					}
					else
					{
					double x=M_PI*2*((double)u*i/(double)size_w+(double)v*j/(double)size_h);
					real+=cos(x)*R;
					imagin+=-sin(x)*R;
					}
				}		
			}
		dst[v*size_w+u].real=real;
		dst[v*size_w+u].imagin=imagin;
		}
	}
	return 0;
}

int CFourer::IDFT2D(Complex *src, Complex *dst, int size_w, int size_h)
{
	for(int v=0;v<size_h;v++)
	{
		for(int u=0;u<size_w;u++)
		{
			double real=0.0;
			double imagin=0.0;
			for(int j=0;j<size_h;j++)
			{
				for(int i=0;i<size_w;i++)
				{
					 double R=src[j*size_w+i].real;
					 double I=src[j*size_w+i].imagin;
					 double x=M_PI*2*((double)u*i/(double)size_w+(double)v*j/(double)size_h);
					 real+=R*cos(x)-I*sin(x);
					 imagin+=R*sin(x)+I*cos(x);
				}
			}

			dst[v*size_w+u].real=real/(size_w*size_h);
			dst[v*size_h+u].imagin=imagin/(size_w*size_h);	
		}
	}
	return 0;
}

void CFourer::AmplitudePhase(Complex *src, double * Amp, double * Phase, int width, int height)
{
	for(int i=0;i<width*height;i++)
	{
		Amp[i]=sqrt(pow(src[i].real,2)+pow(src[i].imagin,2));
		Phase[i]=atan(src[i].imagin/src[i].real);
	}
}


void CFourer::AmplitudePhase2Complex(Complex *src, double *Amp, double *Phase, Complex *dst, int width, int height)
{
	for(int i=0;i<width*height;i++)
	{
		if(src[i].real>=0&&src[i].imagin>=0)
		{
			dst[i].real=Amp[i]*cos(Phase[i]);
			dst[i].imagin=Amp[i]*sin(Phase[i]);
		}
		else if(src[i].real<0&&src[i].imagin>0)
		{
			dst[i].real=-Amp[i]*cos(Phase[i]);
			dst[i].imagin=-Amp[i]*sin(Phase[i]);
		}
		else if(src[i].real<0&&src[i].imagin<0)
		{
			dst[i].real=-Amp[i]*cos(Phase[i]);
			dst[i].imagin=-Amp[i]*sin(Phase[i]);
		}
		else if(src[i].real>0&&src[i].imagin<0)
		{
			dst[i].real=Amp[i]*cos(Phase[i]);
			dst[i].imagin=Amp[i]*sin(Phase[i]);
		}
	}
}
///*
void CFourer::RealFFT(double *src, Complex *dst, int size)
{
	int k=size;
	int z=0;
	CMathematic * point_math;
	point_math=new CMathematic;
	while (k/=2)
	{
		z++;
	}
	k=z;							//k为傅立叶变换的总级数
	if(size!=(1<<k))
		exit(0);
	Complex *src_com=(Complex *)malloc(sizeof(Complex)*size);
	if(src_com==NULL)
		exit(0);

	for(int i=0;i<size;i++)			
	{
		src_com[i].real=src[i];
		src_com[i].imagin=0;
	}
	FFTComplex_remap(src_com,size);
	for(i=0;i<k;i++)				//i为傅立叶变幻的当前级数
	{
		z=0;
		for(int j=0;j<size;j++)
		{
			if(j/(1<<i)%2==1)
			{
				Complex wn;
				getWN(z, size, &wn);
				point_math->Multy_Complex(&src_com[j],&wn,&src_com[j]);
				z+=1<<(k-i-1);
				Complex temp;
				int neighbour=j-(1<<(i));
				temp.real=src_com[neighbour].real;
				temp.imagin=src_com[neighbour].imagin;
				point_math->Add_Complex(&temp, &src_com[j], &src_com[neighbour]);
				point_math->Sub_Complex(&temp, &src_com[j], &src_com[j]);

			}
			else
				z=0;
		}
	}
	for(i=0;i<size;i++)
	{
		point_math->Copy_Complex(&src_com[i],&dst[i]);
	}
	free(src_com);
	delete point_math;
}
//*/

int CFourer::FFTComplex_remap(Complex * src, int size)
{
	if(size==1)
		return 0;
	Complex * temp=(Complex *)malloc(sizeof(Complex)*size);
	CMathematic *point_math;
	point_math=new CMathematic;
	for(int i=0;i<size;i++)
		if(i%2==0)
			point_math->Copy_Complex(&(src[i]),&(temp[i/2]));
		else
			point_math->Copy_Complex(&(src[i]),&(temp[(size+i)/2]));
	for(i=0;i<size;i++)
		point_math->Copy_Complex(&(temp[i]),&(src[i]));
	free(temp);
	FFTComplex_remap(src,size/2);
	FFTComplex_remap(src+size/2,size/2);
	delete point_math;
	return 1;
}

void CFourer::getWN(int step, int size, Complex *dst)
{
	double x=2.0*M_PI*step/size;
	dst->real=cos(x);
	dst->imagin=-sin(x);
}

void CFourer::IFFT(Complex *src, Complex *dst, int size)
{

	int k=size;							//k为总级数
	int z=0;							//z为当前级数 
	while(k/=2)
	{
		z++;
	}
	k=z;
	if(size!=(1<<k))
		exit(0);
	Complex *src_com=(Complex*)malloc(sizeof(Complex)*size);
	if(src_com==NULL)
		exit(0);
	for(int i=0;i<size;i++)
	{
		src_com[i].real=src[i].real;
		src_com[i].imagin=-src[i].imagin;
	}
	FFTComplex_remap(src_com,size);
	CMathematic *point_math;
	point_math=new CMathematic;
	for(i=0;i<k;i++)
	{  
		z=0;  
        for(int j=0;j<size;j++)
		{  
            if((j/(1<<i))%2==1)
			{  
                Complex wn;  
                getWN(z, size, &wn);  
                point_math->Multy_Complex(&src_com[j], &wn,&src_com[j]);  
                z+=1<<(k-i-1);  
                Complex temp;  
                int neighbour=j-(1<<(i));  
                point_math->Copy_Complex(&src_com[neighbour], &temp);  
                point_math->Add_Complex(&temp, &src_com[j], &src_com[neighbour]);  
                point_math->Sub_Complex(&temp, &src_com[j], &src_com[j]);  
            }  
            else  
                z=0;  
        }  
	}
	for(i=0;i<size;i++)
	{
		dst[i].real=src_com[i].real/size;
		dst[i].imagin=src_com[i].imagin/size;
	}
	delete point_math;
	free(src_com);
}

void CFourer::FFT2D(double * src, Complex *dst, int width, int height)
{
	int k=width;							//k为总级数
	int z=0;								//z为当前级数 
	while(k/=2)
	{
		z++;
	}
	if(width!=(1<<z))
		exit(0);
	k=height;
	z=0;
	while(k/=2)
	{
		z++;
	}
	if(height!=(1<<z))
		exit(0);
	Complex *temp=(Complex *)malloc(sizeof(Complex)*width*height);
	if(temp==NULL)
		exit(0);
	for(int i=0;i<height;i++)
	{
		RealFFT(&src[i*width],&temp[i*width],width);
	}
	Complex *Column=(Complex *)malloc(sizeof(Complex)*height);  
    if(Column==NULL)
		exit(0);
	for(i=0;i<width;i++)
	{
		ColumnVector(&temp[i],Column,width,height);
		FFT(Column,Column,height);
		IColumnVector(Column,&temp[i],width,height);
	}
	CMathematic *point_math;
	point_math=new CMathematic;
	for(i=0;i<width*height;i++)
		point_math->Copy_Complex(&temp[i],&dst[i]);
	free(temp);
	free(Column);
	delete point_math;
}

void CFourer::FFT(Complex *src, Complex *dst, int size)
{
	int k=size;
	int z=0;
	CMathematic * point_math;
	point_math=new CMathematic;
	while (k/=2)
	{
		z++;
	}
	k=z;							//k为傅立叶变换的总级数
	if(size!=(1<<k))
		exit(0);
	Complex *src_com=(Complex *)malloc(sizeof(Complex)*size);
	if(src_com==NULL)
		exit(0);

	for(int i=0;i<size;i++)			
	{
		src_com[i].real=src[i].real;
		src_com[i].imagin=src[i].imagin;
	}
	FFTComplex_remap(src_com,size);
	for(i=0;i<k;i++)				//i为傅立叶变幻的当前级数
	{
		z=0;
		for(int j=0;j<size;j++)
		{
			if(j/(1<<i)%2==1)
			{
				Complex wn;
				getWN(z, size, &wn);
				point_math->Multy_Complex(&src_com[j],&wn,&src_com[j]);
				z+=1<<(k-i-1);
				Complex temp;
				int neighbour=j-(1<<(i));
				temp.real=src_com[neighbour].real;
				temp.imagin=src_com[neighbour].imagin;
				point_math->Add_Complex(&temp, &src_com[j], &src_com[neighbour]);
				point_math->Sub_Complex(&temp, &src_com[j], &src_com[j]);
			}
			else
				z=0;
		}
	}
	for(i=0;i<size;i++)
	{
		point_math->Copy_Complex(&src_com[i],&dst[i]);
	}
	free(src_com);
	delete point_math;
}

void CFourer::ColumnVector(Complex *src, Complex *dst, int width, int height)
{
	CMathematic *point_math;
	point_math=new CMathematic;
	for(int i=0;i<height;i++)
	{
		point_math->Copy_Complex(&src[i*width],&dst[i]);
	}
	delete point_math;
}

void CFourer::IColumnVector(Complex *src, Complex *dst, int width, int height)
{
	CMathematic *point_math;
	point_math=new CMathematic;
	for(int i=0;i<height;i++)
	{
		point_math->Copy_Complex(&src[i],&dst[i*width]);
	}
	delete point_math;
}

void CFourer::IFFT2D(Complex *src, Complex *dst, int width, int height)
{
	int k=width;							//k为总级数
	int z=0;								//z为当前级数 
	while(k/=2)
	{
		z++;
	}
	if(width!=(1<<z))
		exit(0);
	k=height;
	z=0;
	while(k/=2)
	{
		z++;
	}
	if(height!=(1<<z))
		exit(0);
	Complex *temp=(Complex *)malloc(sizeof(Complex)*width*height);
	if(temp==NULL)
		exit(0);
	Complex *Column=(Complex *)malloc(sizeof(Complex)*height);  
    if(Column==NULL)
		exit(0);
	for(int i=0;i<width;i++)
	{
		ColumnVector(&src[i],Column,width,height);
		IFFT(Column,Column,height);
		IColumnVector(Column,&temp[i],width,height);
	}
	for(i=0;i<width*height;i++)
	{
		temp[i].imagin=-temp[i].imagin;
	}
	for(i=0;i<height;i++)
	{
		IFFT(&temp[i*width],&temp[i*width],width);
	}
	CMathematic *point_math;
	point_math=new CMathematic;
	for(i=0;i<width*height;i++)
		point_math->Copy_Complex(&temp[i],&dst[i]);
	delete point_math;
	free(temp);
	free(Column);
}
