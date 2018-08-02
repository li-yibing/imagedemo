// Convolution.h: interface for the CConvolution class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONVOLUTION_H__444B9FFC_2782_4C10_8B41_3E45F57126A8__INCLUDED_)
#define AFX_CONVOLUTION_H__444B9FFC_2782_4C10_8B41_3E45F57126A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConvolution  
{
public:
	void RaelRelevant(double *src,double *dst,double *mask,int width,int height,int m_width,int m_height);
	void RotateRealMatrix(double *matrix,double *dst,int width,int height);
	void RealConvolution(double *src,double *dst,double *mask,int width,int height,int m_width,int m_height);
	CConvolution();
	virtual ~CConvolution();

};

#endif // !defined(AFX_CONVOLUTION_H__444B9FFC_2782_4C10_8B41_3E45F57126A8__INCLUDED_)
