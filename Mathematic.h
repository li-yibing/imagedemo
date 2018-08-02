// Mathematic.h: interface for the CMathematic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHEMATIC_H__64F4AA7C_7E2F_49AD_9F61_880214F84C67__INCLUDED_)
#define AFX_MATHEMATIC_H__64F4AA7C_7E2F_49AD_9F61_880214F84C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

#define M_PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384

struct Complex_ 
{
	double real;
	double imagin;
};
struct Position_
{
	int x;
	int y;
};

typedef struct Complex_ Complex;
typedef struct Position_ Position;

class CMathematic  
{
public:
	void Multy_Complex(Complex *src1, Complex *src2, Complex *dst);
	void Sub_Complex(Complex * src1, Complex *src2, Complex *dst);
	void Add_Complex(Complex *src1, Complex *src2, Complex *dst);
	void Copy_Complex(Complex *src, Complex *dst);
	double findMatrixMax(double *src, int width,int height,Position *max_position);
	void matrixDBL2INT(double *src,int *dst,int width,int height);
	CMathematic();
	virtual ~CMathematic();

};

#endif // !defined(AFX_MATHEMATIC_H__64F4AA7C_7E2F_49AD_9F61_880214F84C67__INCLUDED_)
