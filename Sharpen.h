// Sharpen.h: interface for the CSharpen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHARPEN_H__50707077_B288_4B00_A68D_DB5148C97644__INCLUDED_)
#define AFX_SHARPEN_H__50707077_B288_4B00_A68D_DB5148C97644__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Segment.h"

class CSharpen  
{
public:
	void SobelSharpen(double *src,double *dst,int width,int height,double c);
	void RobertSharpen(double * src, double *dst, int width,int height,double c);
	CSharpen();
	virtual ~CSharpen();

};

#endif // !defined(AFX_SHARPEN_H__50707077_B288_4B00_A68D_DB5148C97644__INCLUDED_)
