// Fourer.h: interface for the CFourer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOURER_H__87DE08F3_0BAE_47E8_A92E_C94BC331CB1F__INCLUDED_)
#define AFX_FOURER_H__87DE08F3_0BAE_47E8_A92E_C94BC331CB1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mathematic.h"

class CFourer  
{
public:
	void IFFT2D(Complex *src, Complex *dst, int width, int height);
	void IColumnVector(Complex *src, Complex *dst, int width, int height);
	void ColumnVector(Complex *src, Complex *dst, int width, int height);
	void FFT(Complex *src, Complex *dst, int size);
	void FFT2D(double * src, Complex * dst, int width, int height);
	void IFFT(Complex *src, Complex *dst, int size);
	void getWN(int step, int size, Complex *dst);
	int FFTComplex_remap(Complex * src, int size);
	void RealFFT(double *src, Complex *dst, int size);
	void AmplitudePhase2Complex(Complex *src,double * Amp, double *Phase, Complex *dst, int width, int height);
	void AmplitudePhase(Complex * src, double * Amp, double * Phase, int width, int height);
	int IDFT2D(Complex * src, Complex * dst, int size_w, int size_h);
	int DFT2D(double * src, Complex * dst, int size_w, int size_h);
	void IDFT(Complex * src, Complex * dst, int size);
	void DFT(double * src, Complex * dst, int size);
	CFourer();
	virtual ~CFourer();

};

#endif // !defined(AFX_FOURER_H__87DE08F3_0BAE_47E8_A92E_C94BC331CB1F__INCLUDED_)
