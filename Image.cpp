// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Image.h"
#include "Color.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage()
{

}

CImage::~CImage()
{

}

void CImage::BMP2RAW(unsigned char *src, unsigned char *dst, int width, int height)			//实质是将BMP图像数据逆序排列
{
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
			dst[width*y+x]=src[width*(height-y-1)+x];
}


void CImage::Color2Homo(RGB *src, unsigned char *dst, int width, int height)
{
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
			dst[width*y+x]=(src[width*(y)+x].c1+src[width*(y)+x].c2+src[width*(y)+x].c3)/3;
}

void CImage::COPYIMG1(unsigned char *src, unsigned char *dst, int width, int height)
{
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
			dst[width*y+x]=src[width*y+x];
}

void CImage::COPYIMG3(RGB *src, RGB *dst, int width, int height)
{
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
		{
			dst[width*y+x].c1=src[width*y+x].c1;
			dst[width*y+x].c2=src[width*y+x].c2;
			dst[width*y+x].c3=src[width*y+x].c3;
		}
}

void CImage::CHAR2DBL(unsigned char *src,double *dst,int width,int height)
{
	for(int i=0;i<width*height;i++)
	{
		dst[i]=(double)src[i];
	}
}

void CImage::DBL2CHAR(double *src, unsigned char *dst, int width, int height)
{
	for(int i=0;i<width*height;i++)
	{
		dst[i]=(unsigned char)src[i]+0.5;
	}
}

void CImage::INT2DBL(int *src, double *dst, int width, int height)
{
	for(int i=0;i<width*height;i++)
		dst[i]=(double)src[i];
}

void CImage::DBL2INT(double *src, int *dst, int width, int height)
{
	for(int i=0;i<width*height;i++)
		dst[i]=(int)src[i];
}
