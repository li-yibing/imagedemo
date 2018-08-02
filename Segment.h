// Segment.h: interface for the CSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEGMENT_H__150F680F_D418_49BB_9CFE_1DA3AB1DDA19__INCLUDED_)
#define AFX_SEGMENT_H__150F680F_D418_49BB_9CFE_1DA3AB1DDA19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSegment  
{
public:
	void Sobel(double *src, double *dst, int width,int height, int sobel_size);
	void Robert(double *src,double *dst, int width,int height);
	CSegment();
	virtual ~CSegment();
	
};

#endif // !defined(AFX_SEGMENT_H__150F680F_D418_49BB_9CFE_1DA3AB1DDA19__INCLUDED_)
