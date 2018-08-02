// Contrast.cpp: implementation of the CContrast class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myimg.h"
#include "Contrast.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContrast::CContrast()
{

}

CContrast::~CContrast()
{

}

void CContrast::ContrastStretch(unsigned char *src, unsigned char *dst, int width, int height, int method, double p0, double p1, int p2, int p3)
{

	unsigned char ContrastTable[MAX_PVALUE];//�Ҷȱ任��
	if(method==CONTRASTFUNC0){				//ͼ��ת
        for(int i=0;i<MAX_PVALUE;i++)
            ContrastTable[i]=MAX_PVALUE-1-i;
    }
    else if(method==CONTRASTFUNC1){			//�ֶ����Ա任
        for(int i=0;i<MAX_PVALUE;i++)
            ContrastTable[i]=i<=p0?(int)(i*p1/p0):
            i<=p2?(int)((i-p0)*(p3-p1)/(p2-p0)+p1):
            (int)((i-p2)*(MAX_PVALUE-1-p3)/(MAX_PVALUE-1-p2)+p3);
    }
    else if(method==CONTRASTFUNC2){				//�����任
        for(int i=0;i<MAX_PVALUE;i++)
            ContrastTable[i]=105.*(double)log10(1+i);	//105*log10(256)Լ����255

    }
	else if(method==CONTRASTFUNC3){				//�������任
        for(int i=0;i<MAX_PVALUE;i++)
            ContrastTable[(int)(105*log10((double)(1+i)))]=i;
        for(i=0;i<MAX_PVALUE;i++)
            if(ContrastTable[i]==0)
                ContrastTable[i]=ContrastTable[i+1];
    }
	else if(method==CONTRASTFUNC4){				//N����
        double coef=255/pow(255.,(double) p0);	//coefΪϵ�� ����Χ����255
        for(int i=0;i<MAX_PVALUE;i++)
            ContrastTable[i]=coef*pow((double)i,(double)p0);
    }
	else if(method==CONTRASTFUNC5){				//N�θ�
        double coef=255/pow(255.,(double) p0);
        for(int i=0;i<MAX_PVALUE;i++)
            ContrastTable[(int)(coef*pow((double)i,(double)p0))]=i;
        for(i=0;i<MAX_PVALUE;i++)
            if(ContrastTable[i]==0)
                ContrastTable[i]=ContrastTable[i+1];
    } 
	else if(method==CONTRASTGAMA){				//gama
        double gama=p0;
        double coef=255/pow(255.,gama);
        coef=(p1<=coef&&p1>0.0)?p1:coef;		//p1Ϊϵ��������0��coef��ȡp1
        for(int i=0;i<MAX_PVALUE;i++)
            ContrastTable[i]=coef*pow((double)i,gama);
    }
	
    ///////////////////////////////���ؽ��/////////////////////////////////////
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
            dst[j*width+i]= ContrastTable[(int)src[j*width+i]];
}
