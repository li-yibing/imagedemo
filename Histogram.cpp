// Histogram.cpp: implementation of the CHistogram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Histogram.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHistogram::CHistogram()
{

}

CHistogram::~CHistogram()
{

}

void CHistogram::InitHistogram(int *hist)
{
	for(int i=0;i<GRAY_LEVEL;i++)
	{
		hist[i]=0;
	}
}

void CHistogram::setHistogram(unsigned char *src, int *hist, int width, int height)
{
	InitHistogram(hist);
	for(int i=0;i<width*height;i++)
	{
		int tempv=src[i];
		hist[tempv]++;
	}
}

int CHistogram::findHistogramMax(int *hist)
{
	for(int i=GRAY_LEVEL-1;i>=0;i--)
	{
        if(hist[i]!=0)
            return i;
    }
    return -1;
}

int CHistogram::findHistogramMin(int *hist)
{
	for(int i=0;i<GRAY_LEVEL;i++)
	{
        if(hist[i]!=0)
            return i;
    }
    return -1;
}


void CHistogram::EqualizationHist(int *src_hist, int *dst_map)
{
	int temphist[GRAY_LEVEL];
	InitHistogram(temphist);
	int max=findHistogramMax(src_hist);
	int min=findHistogramMin(src_hist);
	temphist[min]=src_hist[min];
	for(int i=min+1;i<=max;i++)
	{
		temphist[i]=temphist[i-1]+src_hist[i];
	}
	for(i=min;i<=max;i++)									
		temphist[i]-=temphist[min];
	int total=temphist[max];
    for(i=min;i<=max;i++)
	{
        dst_map[i]=((int)(GRAY_LEVEL-1.0)*temphist[i]/total+0.5);
    }

}

void CHistogram::HistogramEqualization(unsigned char *src, unsigned char *dst, int width, int height)
{
	int hist[GRAY_LEVEL];
	int MapTable[GRAY_LEVEL];
	setHistogram(src,hist,width,height);
	for(int i=0;i<GRAY_LEVEL;i++)
	{
		MapTable[i]=0;
	}
	EqualizationHist(hist,MapTable);
	for(i=0;i<width*height;i++)
	{
		dst[i]=MapTable[src[i]];
	}
}

int CHistogram::clipHistogram(int *src_hist, int *dst_hist, double limit, int width, int height)
{
	double cutlimit=width*height*limit;

	double overheight=10.0;
	for(int i=0;i<GRAY_LEVEL;i++)
	{
		dst_hist[i]=src_hist[i];
	}
	while(overheight>1.0)
	{
		int totalExcess=0;
		for(i=0;i<GRAY_LEVEL;i++)
		{
			if(dst_hist[i]>cutlimit)
			{
				totalExcess+=(dst_hist[i]-cutlimit);
				dst_hist[i]-=(dst_hist[i]-cutlimit);
			}
		}
		overheight=totalExcess/GRAY_LEVEL;
		for(i=0;i<GRAY_LEVEL;i++)
		{
			dst_hist[i]+=overheight;
		}
	}
	return 1;
}

void CHistogram::CLHistogramEqulization(unsigned char *src, unsigned char *dst, int width, int height)
{
	int hist[GRAY_LEVEL];
	int MapTable[GRAY_LEVEL];
	setHistogram(src,hist,width,height);
	clipHistogram(hist,hist,0.01,width,height);
	for(int i=0;i<GRAY_LEVEL;i++)
	{
		MapTable[i]=0;
	}
	EqualizationHist(hist,MapTable);
	for(i=0;i<width*height;i++)
	{
		dst[i]=MapTable[src[i]];
	}
}
