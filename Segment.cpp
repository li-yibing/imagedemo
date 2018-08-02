// Segment.cpp: implementation of the CSegment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Segment.h"
#include "Convolution.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSegment::CSegment()
{

}

CSegment::~CSegment()
{

}

void CSegment::Robert(double *src, double *dst, int width, int height)
{
	double RobertMask_x[9]={0,0,0,0,-1,0,0,0,1};
	double RobertMask_y[9]={0,0,0,0,0,-1,0,1,0};

	double *dst_x=(double *)malloc(sizeof(double)*width*height);
	double *dst_y=(double *)malloc(sizeof(double)*width*height);

	CConvolution * point_convol;
	point_convol= new CConvolution;
	point_convol->RealConvolution(src,dst_x,RobertMask_x,width,height,3,3);
	point_convol->RealConvolution(src,dst_y,RobertMask_y,width,height,3,3);

	for(int j=0;j<height;j++)  
       for(int i=0;i<width;i++){  
           dst[j*width+i]=abs(dst_x[j*width+i])+abs(dst_y[j*width+i]); 
       }  
    free(dst_x);  
    free(dst_y);    
    delete point_convol;
}

void CSegment::Sobel(double *src, double *dst, int width, int height, int sobel_size)
{
	double *dst_x=(double *)malloc(sizeof(double)*width*height);
	double *dst_y=(double *)malloc(sizeof(double)*width*height);
	CConvolution * point_convol;
	point_convol= new CConvolution;
	if(sobel_size==3)
	{
		double SobelMask1[3]={0.25,0.5,0.25};
//		double SobelMask1[3]={1,2,1};				//»Ò¶È·¶Î§Òç³ö
		double SobelMask2[3]={1,0,-1};

		point_convol->RealConvolution(src,dst_x,SobelMask2,width,height,1,3);
		point_convol->RealConvolution(dst_x,dst_x,SobelMask1,width,height,3,1);
		
		point_convol->RealConvolution(src,dst_y,SobelMask1,width,height,1,3);
		point_convol->RealConvolution(dst_y,dst_y,SobelMask2,width,height,3,1);
	}
	else if(sobel_size==5){  
        double SobelMask1[5]={0.0625,0.25,0.375,0.25,0.0625};  
        double SobelMask2[5]={1/3.0,2/3.0,0,-2/3.0,-1/3.0};  
        point_convol->RealConvolution(src, dst_x, SobelMask2, width, height, 1, 5);  
        point_convol->RealConvolution(dst_x, dst_x, SobelMask1, width, height, 5, 1);  
          
        point_convol->RealConvolution(src, dst_y, SobelMask1, width, height, 1, 5);  
        point_convol->RealConvolution(dst_y, dst_y, SobelMask2, width, height, 5, 1);  
      
    }
	else if(sobel_size==7){  
        double SobelMask1[7]={0.015625,0.09375,0.234375,0.3125,0.234375,0.09375,0.015625};  
        double SobelMask2[7]={0.1,0.4,0.5,0,-0.5,-0.4,-0.1};  
        point_convol->RealConvolution(src, dst_x, SobelMask2, width, height, 1, 7);  
        point_convol->RealConvolution(dst_x, dst_x, SobelMask1, width, height, 7, 1);  
          
        point_convol->RealConvolution(src, dst_y, SobelMask1, width, height, 1, 7);  
        point_convol->RealConvolution(dst_y, dst_y, SobelMask2, width, height, 7, 1);  
          
    }  
	for(int j=0;j<height;j++)  
        for(int i=0;i<width;i++)
		{  
            dst[j*width+i]=abs(dst_x[j*width+i])+abs(dst_y[j*width+i]);  
        }  
	delete point_convol;
    free(dst_x);  
    free(dst_y);  
}
