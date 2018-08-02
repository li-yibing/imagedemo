// Mathematic.cpp: implementation of the CMathematic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Mathematic.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMathematic::CMathematic()
{

}

CMathematic::~CMathematic()
{

}

void CMathematic::matrixDBL2INT(double *src, int *dst, int width, int height)
{
	for(int i=0;i<width*height;i++)
        dst[i]=(int)src[i];

}

double CMathematic::findMatrixMax(double *src, int width, int height, Position *max_position)
{
	double max=-1.0;
    double value=0.0;
    int x,y;
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++){
            value=src[j*width+i];
            if(value>max){
                max=value;
                x=i;
                y=j;
            }
        
        }
    if(max_position!=NULL){
        max_position->x=x;
        max_position->y=y;
    }
    return max;
}

void CMathematic::Copy_Complex(Complex *src, Complex *dst)
{
	dst->real=src->real;
	dst->imagin=src->imagin;
}

void CMathematic::Add_Complex(Complex *src1, Complex *src2, Complex *dst)
{
	dst->real=src1->real+src2->real;
	dst->imagin=src1->imagin+src2->imagin;
}

void CMathematic::Sub_Complex(Complex *src1, Complex *src2, Complex *dst)
{
	dst->real=src1->real-src2->real;
	dst->imagin=src1->imagin-src2->imagin;
}

void CMathematic::Multy_Complex(Complex *src1, Complex *src2, Complex *dst)
{
	double r1=src1->real;
	double i1=src1->imagin;
	double r2=src2->real;
	double i2=src2->imagin;
	dst->real=r1*r2-i1*i2;
	dst->imagin=r1*i2+r2*i1;
}
