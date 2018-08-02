// Sharpen.cpp: implementation of the CSharpen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Sharpen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSharpen::CSharpen()
{

}

CSharpen::~CSharpen()
{

}

void CSharpen::RobertSharpen(double *src, double *dst, int width, int height,double c)	//c为增强的系数 过大会导致溢出 待解决
{
	CSegment * point_seg;
	point_seg=new CSegment;
	point_seg->Robert(src,dst,width,height);
	for(int i=0;i<width*height;i++)
	{
		dst[i]=src[i]+c*dst[i];
	}
	delete point_seg;
}

void CSharpen::SobelSharpen(double *src, double *dst, int width, int height, double c)
{
	CSegment * point_seg;
	point_seg=new CSegment;
	point_seg->Sobel(src,dst,width,height,3);
	for(int i=0;i<width*height;i++)
	{
		dst[i]=src[i]+c*dst[i];
	}
	delete point_seg;
}
