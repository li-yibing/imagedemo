// Color.h: interface for the CColor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLOR_H__F608CD61_076C_434D_A046_897F80AE4FD4__INCLUDED_)
#define AFX_COLOR_H__F608CD61_076C_434D_A046_897F80AE4FD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MIN3(x,y,z) (((x)>(y))?(((y)>(z))?(z):(y)):((x)>(z)?(z):(x)))
#define MAX3(x,y,z) (((x)<(y))?(((y)<(z))?(z):(y)):((x)<(z)?(z):(x)))



typedef struct Chanel3_CHAR RGB;
typedef struct Chanel3_DOUBLE C3;
typedef struct Chanel3_DOUBLE HSI;
typedef struct Chanel3_DOUBLE HSV;

struct Chanel3_CHAR{
    unsigned char c1;
    unsigned char c2;
    unsigned char c3;
};

struct Chanel3_DOUBLE{
    double d1;
    double d2;
    double d3;
};

class CColor  
{
public:
	void Merge(double *src1,double *src2,double *src3,C3 *dst,int width,int height);
	void Split(C3 *src,double *dst1,double *dst2,double *dst3,int width,int height);
	void HSV2RGB(HSV *src,RGB *dst,int width,int height);
	void RGB2HSV(RGB *src,HSV *dst,int width,int height);
	void HSI2RGB(HSI *src, RGB *dst, int width, int height);
	void RGB2HSI(RGB *src, HSI *dst, int width, int height);
	CColor();
	virtual ~CColor();

};

#endif // !defined(AFX_COLOR_H__F608CD61_076C_434D_A046_897F80AE4FD4__INCLUDED_)
