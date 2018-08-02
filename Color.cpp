// Color.cpp: implementation of the CColor class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "myimg.h"
#include "Color.h"
#include "Mathematic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColor::CColor()
{

}

CColor::~CColor()
{

}

void CColor::RGB2HSI(RGB *src, HSI *dst, int width, int height)
{
	double r,g,b;

	for(int i=0;i<height*width;i++)
	{
		r=src[i].c1;
		g=src[i].c2;
		b=src[i].c3;
	
	double delta=acos((2*r-g-b)/(2*sqrt((r-g)*(r-g)+(r-b)*(g-b))));
    dst[i].d1=b<=g?delta:2*M_PI-delta;									//H 0~2*M_PI
    dst[i].d2=1.0-3.0*(MIN3(r,g,b)/(r+g+b));							//S 0~1
    dst[i].d3=(r+g+b)/3.0;												//I 0~255
	}
}

void CColor::HSI2RGB(HSI *src, RGB *dst, int width, int height)
{
	double src_h,src_s,src_i;
    double r,g,b;
    for(int i=0;i<width*height;i++){
        src_h=src[i].d1;
        src_s=src[i].d2;
        src_i=src[i].d3;
        if(src_h>=0.0&&src_h<(2./3.*M_PI)){
            b=src_i*(1.0-src_s);
            r=src_i*(1.0+(src_s*cos(src_h)/cos(1./3.*M_PI-src_h)));
            g=3.0*src_i-(r+b);
        }else if(src_h>=(2./3.*M_PI)&&src_h<(4./3.*M_PI)){
            src_h-=(2./3.*M_PI);
            r=src_i*(1.0-src_s);
            g=src_i*(1.0+(src_s*cos(src_h)/cos(1./3.*M_PI-src_h)));
            b=3.0*src_i-(r+g);
        }else if(src_h>=(4./3.*M_PI)&&src_h<(2.*M_PI)){
            src_h-=(4./3.*M_PI);
            g=src_i*(1.0-src_s);
            b=src_i*(1.0+(src_s*cos(src_h)/cos(1./3.*M_PI-src_h)));
            r=3.0*src_i-(g+b);
        }
        dst[i].c1=(unsigned char)r;
        dst[i].c2=(unsigned char)g;
        dst[i].c3=(unsigned char)b;
    }
}

void CColor::RGB2HSV(RGB *src, HSV *dst, int width, int height)
{
	double max=0.0,min=0.0;
    double r,g,b;
    for(int i=0;i<width*height;i++){
        r=src[i].c1;
        g=src[i].c2;
        b=src[i].c3;
        max=MAX3(r, g, b);
        min=MIN3(r, g, b);
        dst[i].d3=(double)max;								//V 0~255
        if(max!=0)
            dst[i].d2=(max-min)/max;						//S 0~1
        else{
            dst[i].d2=0.0;
            dst[i].d1=0.0;
        }
        if(dst[i].d2>0.0){
            double delta=max-min;
            double dr=(max-r)/delta;
            double dg=(max-g)/delta;
            double db=(max-b)/delta;
            if(r==max)										//H 0~2*M_PI
                dst[i].d1=(g==min?5.+db:1.-dg);
            else if(g==max)
                dst[i].d1=(b==min?1.+dr:3.-db);
            else if(r==min)
                dst[i].d1=(r==min?3.+dg:5.-dr);

            dst[i].d1*=(dst[i].d1<6.0?60.0:0.0);
        }
    }
}

void CColor::HSV2RGB(HSV *src, RGB *dst, int width, int height)
{
	int *temp_int=(int *)malloc(sizeof(int)*width*height);
    double *temp_double=(double *)malloc(sizeof(double)*width*height);
    Split(src, temp_double, NULL, NULL, width, height);
	CMathematic *point_math;
	point_math=new CMathematic;
    point_math->matrixDBL2INT(temp_double, temp_int, width, height);
    double h,s,v;
    double r,g,b;
    int h_int;
    for(int i=0;i<width*height;i++){
        h=src[i].d1;
        s=src[i].d2;
        v=src[i].d3/255.0;
        h_int=temp_int[i];
        int Hi=((int)h_int/60)%6;
        double f=(double)(h/60.-Hi);
        double p=v*(1.-s);
        double q=v*(1.-f*s);
        double t=v*(1.-(1.-f)*s);
        switch (Hi) {
            case 0:r=v;g=t;b=p;break;
            case 1:r=q;g=v;b=p;break;
            case 2:r=p;g=v;b=t;break;
            case 3:r=p;g=q;b=v;break;
            case 4:r=t;g=p;b=v;break;
            case 5:r=v;g=p;b=q;break;
            default:
                break;
        }
        dst[i].c1=r*(255);
        dst[i].c2=g*(255);
        dst[i].c3=b*(255);
    }
    free(temp_int);
    free(temp_double);
}

void CColor::Split(C3 *src, double *dst1, double *dst2, double *dst3, int width, int height)
{
	for(int i=0;i<width*height;i++)
	{
        if(dst1!=NULL)dst1[i]=src[i].d1;
        if(dst2!=NULL)dst2[i]=src[i].d2;
        if(dst3!=NULL)dst3[i]=src[i].d3;
    }

}
void CColor::Merge(double *src1, double *src2, double *src3, C3 *dst, int width, int height)
{
	for(int i=0;i<width*height;i++)
	{
        dst[i].d1=(src1!=NULL?src1[i]:0.0);
        dst[i].d2=(src2!=NULL?src2[i]:0.0);
        dst[i].d3=(src3!=NULL?src3[i]:0.0);
    }
}
