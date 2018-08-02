// Histogram.h: interface for the CHistogram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTOGRAM_H__F377720F_2163_4DA3_9259_6EE1CEA04C19__INCLUDED_)
#define AFX_HISTOGRAM_H__F377720F_2163_4DA3_9259_6EE1CEA04C19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define GRAY_LEVEL 256


class CHistogram  
{
public:
	void CLHistogramEqulization(unsigned char *src, unsigned char *dst, int width, int height);
	int clipHistogram(int *src_hist, int *dst_hist, double limit, int width, int height);
	void HistogramEqualization(unsigned char *src,unsigned char *dst,int width,int height);
	void EqualizationHist(int *src_hist, int *dst_map);
	int findHistogramMin(int * hist);
	int findHistogramMax(int * hist);
	void setHistogram(unsigned char *src, int *hist, int width, int height);
	void InitHistogram(int *hist);
	CHistogram();
	virtual ~CHistogram();

};

#endif // !defined(AFX_HISTOGRAM_H__F377720F_2163_4DA3_9259_6EE1CEA04C19__INCLUDED_)
