// Convolution.cpp: implementation of the CConvolution class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Convolution.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConvolution::CConvolution()
{

}

CConvolution::~CConvolution()
{

}

void CConvolution::RealConvolution(double *src, double *dst, double *mask, int width, int height, int m_width,int m_height)
{
	double *temp=(double *)malloc(sizeof(double)*width*height);
	RotateRealMatrix(mask,temp,m_width,m_height);
	RaelRelevant(src,dst,temp,width,height,m_width,m_height);
}

void CConvolution::RotateRealMatrix(double *matrix, double *dst, int width, int height)
{
	double *temp=(double *)malloc(sizeof(double)*width*height);
	for(int i=0;i<width*height;i++)
		temp[width*height-1-i]=matrix[i];
	for(i=0;i<width*height;i++)
		dst[i]=temp[i];
	free(temp);
}


void CConvolution::RaelRelevant(double *src, double *dst, double *mask, int width, int height, int m_width, int m_height)
{
	double *temp=(double *)malloc(sizeof(double)*width*height);
	int mask_center_x=m_width/2;
    int mask_center_y=m_height/2;
	
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
		{
            double value=0.0;
            for(int n=0;n<m_height;n++)
                for(int m=0;m<m_width;m++)
				{
                    if((i+m-mask_center_x)<width&&(j+n-mask_center_y)<height&&
                       (i+m-mask_center_x)>=0&&(j+n-mask_center_y)>=0)
					{
                        value+=src[(j+n-mask_center_y)*width+(i+m-mask_center_x)]*mask[n*m_width+m];
                    }
                }
            temp[j*width+i]=value;
        }
    for(int i=0;i<width*height;i++)
        dst[i]=temp[i];
    free(temp);
}
