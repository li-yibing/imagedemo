// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__4E18C8E6_B1B4_4319_B54B_4567384BB6E4__INCLUDED_)
#define AFX_IMAGE_H__4E18C8E6_B1B4_4319_B54B_4567384BB6E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Color.h"

class CImage  
{
public:
	void DBL2INT(double *src, int *dst, int width, int height);
	void INT2DBL(int *src, double *dst, int width,int height);
	void DBL2CHAR(double *src,unsigned char *dst,int width,int height);
	void CHAR2DBL(unsigned char *src,double *dst,int width,int height);
	void COPYIMG3(RGB *src,RGB *dst,int width,int height);
	void COPYIMG1(unsigned char *src,unsigned char *dst,int width,int height);
	void Color2Homo(RGB *src, unsigned char *dst, int width, int height);
	
	void BMP2RAW(unsigned char *src, unsigned char *dst, int width, int height);
	CImage();
	virtual ~CImage();

};

#endif // !defined(AFX_IMAGE_H__4E18C8E6_B1B4_4319_B54B_4567384BB6E4__INCLUDED_)
