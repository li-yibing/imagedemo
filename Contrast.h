// Contrast.h: interface for the CContrast class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTRAST_H__E6FC5FC3_033C_4634_AE22_EA878BA6F2B6__INCLUDED_)
#define AFX_CONTRAST_H__E6FC5FC3_033C_4634_AE22_EA878BA6F2B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CONTRASTFUNC0 -1	//��ת�Ҷ�
#define CONTRASTFUNC1 0		//�ֶ�
#define CONTRASTFUNC2 1		//����
#define CONTRASTFUNC3 2		//������
#define CONTRASTFUNC4 3		//n����
#define CONTRASTFUNC5 4		//n�θ�
#define CONTRASTGAMA  5     //gama
#define GRAYLEVEL 8
#define MAX_PVALUE (1<<GRAYLEVEL)


class CContrast  
{
public:
	void ContrastStretch(unsigned char *src,unsigned char *dst,int width,int height,int method,double p0,double p1,int p2,int p3);
	CContrast();
	virtual ~CContrast();

};

#endif // !defined(AFX_CONTRAST_H__E6FC5FC3_033C_4634_AE22_EA878BA6F2B6__INCLUDED_)
