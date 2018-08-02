// myimgView.cpp : implementation of the CMyimgView class

#include "stdafx.h"
#include "myimg.h"
#include "Mathematic.h"
#include "Convolution.h"
#include "myimgDoc.h"
#include "myimgView.h"
#include "Color.h"
#include "Segment.h"
#include "Sharpen.h"
#include "Fourer.h"
#include "Histogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BITMAPFILEHEADER bf_h;//�ļ�ͷ
BITMAPINFOHEADER bi_h;//��Ϣͷ
RGBQUAD * rgbquad;

unsigned char * src1;			//RAW˳��Ҷ�ͼ
unsigned char * dst1;			//������RAW�Ҷ�ͼ
unsigned char * temp1;
Complex * output;
Complex * outputnew;

RGB * src3;						//RAW˳��ɫͼ
RGB * dst3;						//������RAW��ɫͼ
RGB * temp3;

HSI * hsi3;
HSV * hsv3;

int width,height,bcont,conrgb;	//���ߣ�ÿ���ؿռ䣬��ɫ�峤��
DWORD m_dwLength;
CString FilePathName;
CString FileName;

/////////////////////////////////////////////////////////////////////////////
// CMyimgView

IMPLEMENT_DYNCREATE(CMyimgView, CView)

BEGIN_MESSAGE_MAP(CMyimgView, CView)
	//{{AFX_MSG_MAP(CMyimgView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_COLOR2MONO, OnColor2mono)
	ON_COMMAND(ID_GRAYREVERSE, OnGrayreverse)
	ON_COMMAND(ID_PIECEWISE_LINEAR, OnPiecewiseLinear)
	ON_COMMAND(ID_LOG_TRANS, OnLogTrans)
	ON_COMMAND(ID_LOG_RETRANS, OnLogRetrans)
	ON_COMMAND(ID_NPOWER, OnNpower)
	ON_COMMAND(ID_NROOT, OnNroot)
	ON_COMMAND(ID_GAMA, OnGama)
	ON_COMMAND(ID_RGB2HSI, OnRgb2hsi)
	ON_COMMAND(ID_HSI2RGB, OnHsi2rgb)
	ON_COMMAND(ID_RGB2HSV, OnRgb2hsv)
	ON_COMMAND(ID_HSV2RGB, OnHsv2rgb)
	ON_COMMAND(ID_SEG_ROBERT, OnSegRobert)
	ON_COMMAND(ID_SHARP_ROBERT, OnSharpRobert)
	ON_COMMAND(ID_SEG_SOBEL, OnSegSobel)
	ON_COMMAND(ID_SHARP_SOBEL, OnSharpSobel)
	ON_COMMAND(ID_DFT_TRANS, OnDftTrans)
	ON_COMMAND(ID_IDFT_TRANS, OnIdftTrans)
	ON_COMMAND(ID_DFT2D_TRANS, OnDft2dTrans)
	ON_COMMAND(ID_IDFT2D, OnIdft2d)
	ON_COMMAND(ID_FFT_TRANS, OnFftTrans)
	ON_COMMAND(ID_IFFT_TRANS, OnIfftTrans)
	ON_COMMAND(ID_FFT2D_TRANS, OnFft2dTrans)
	ON_COMMAND(ID_IFFT2D_TRANS, OnIfft2dTrans)
	ON_COMMAND(ID_SHOW_HISTOGRAM, OnShowHistogram)
	ON_COMMAND(ID_HIST_EQUALIZATION, OnHistEqualization)
	ON_COMMAND(ID_CLHE, OnClhe)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyimgView construction/destruction

CMyimgView::CMyimgView()
{
	// TODO: add construction code here

}

CMyimgView::~CMyimgView()
{
}

BOOL CMyimgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyimgView drawing

void CMyimgView::OnDraw(CDC* pDC)
{
	CMyimgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyimgView printing

BOOL CMyimgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyimgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyimgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyimgView diagnostics

#ifdef _DEBUG
void CMyimgView::AssertValid() const
{
	CView::AssertValid();
}

void CMyimgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyimgDoc* CMyimgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyimgDoc)));
	return (CMyimgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyimgView message handlers

void CMyimgView::OnFileOpen()				//��BMP�ļ�
{
	// TODO: Add your command handler code here

	CString strOpenFileType = "ͼ���ļ� (*.BMP)|*.BMP; |ͼ���ļ� (*.JPG)|*.JPG;*.JPEG |ͼ���ļ� (*.GIF)|*.GIF; |ͼ���ļ� (*.PNG)|*.PNG; |ͼ���ļ� (*.TIFF)|*.TIF;*.TIFF |All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE, "*.BMP", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFileType);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	if(dlg.DoModal()==IDOK)
	{
		FileName=dlg.GetFileTitle();
		FilePathName=dlg.GetPathName();
	}
	else
	{ 
		AfxMessageBox("��ѡ��һ��.BMP�ļ�");
		return;
	}
	try
	{
		CFile Fileimg(FilePathName,CFile::modeRead);
		Fileimg.Read(&bf_h,sizeof(BITMAPFILEHEADER));//���ļ�ͷ
		Fileimg.Read(&bi_h,sizeof(BITMAPINFOHEADER));//����Ϣͷ
		if(bf_h.bfType!=0x4d42)
		{
			MessageBox("����BMPͼ��");
			MessageBox("�Ƿ��RAWͼ��");			//������ȡRAW�ļ�
		}
		else if(bi_h.biBitCount==8)
		{
			bcont=bi_h.biBitCount;
			width=bi_h.biWidth;
			height=bi_h.biHeight;
			m_dwLength=width*height;
			conrgb=(int)pow(2,bi_h.biBitCount)*4;
			rgbquad= new RGBQUAD[conrgb];
			Fileimg.Read(rgbquad,conrgb);
			if((src1=new unsigned char[m_dwLength])==NULL)
			{
			MessageBox("src1�����ڴ��");
			 return ;
			}
			if((dst1=new unsigned char[m_dwLength])==NULL)
			{
			MessageBox("dst1�����ڴ��");
			 return ;
			}

			Fileimg.Read(src1,m_dwLength);
			CImage * point_img;
			point_img=new CImage;
			point_img->BMP2RAW(src1,dst1,width,height);
			point_img->COPYIMG1(dst1,src1,width,height);	//��ΪRAW˳��ͼ

			CClientDC dc(this);
			int start_x=0;
			int start_y=0;
			for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
			delete point_img;
		
		}
		else if(bi_h.biBitCount==24)
		{
			bcont=bi_h.biBitCount;
			width=bi_h.biWidth;
			height=bi_h.biHeight;
			m_dwLength=width*height;
			if((src3=new RGB[m_dwLength])==NULL)
			{
			MessageBox("src3�����ڴ��");		
			 return ;
			}
			if((dst3=new RGB[m_dwLength])==NULL)
			{
			MessageBox("dst3�����ڴ��");
			 return ;
			}
			if((temp3=new RGB[m_dwLength])==NULL)
			{
			MessageBox("temp3�����ڴ��");
			 return ;
			}
			
			int c=3*width%4;
			for(int j=0;j<height;j++)
			{
				for(int i=0;i<width;i++)
				{
					Fileimg.Read(&src3[width*(height-j-1)+i].c3,1);		//B
					Fileimg.Read(&src3[width*(height-j-1)+i].c2,1);		//G
					Fileimg.Read(&src3[width*(height-j-1)+i].c1,1);		//R
				}
				if(c!=0)
					Fileimg.Seek(4-c,CFile::current);
			}
			CImage *point_img;
			point_img=new CImage;
			point_img->COPYIMG3(src3,dst3,width,height);
			delete point_img;

			int start_x=0;
			int start_y=0;
			CClientDC dc(this);
			for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(src3[width*y+x].c1,src3[width*y+x].c2,src3[width*y+x].c3));
		}
		else
		{
			MessageBox("����8λ��24λBMPͼƬ");
		}
	Fileimg.Close();
	}
	catch(CFileException *e)
	{
		switch(e->m_cause)
		{
		case CFileException::fileNotFound:
			MessageBox("�ļ�δ�ҵ�!");
			break ;
		case CFileException::badPath:
			MessageBox("·����!");	
			break ;
		case CFileException::accessDenied:
			MessageBox("�޷���Ȩ��!");
			break ;
		default:
			break ;
		}
	}
	
}

void CMyimgView::OnFileSave()				//�����ļ�
{
	// TODO: Add your command handler code here
	FilePathName.Replace(FileName,FileName+"����");
	if(bcont==8)
	{
		
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
	
		CFile Fileimg;
		Fileimg.Open(FilePathName,CFile::modeWrite|CFile::modeCreate);
		Fileimg.Write(&bf_h,sizeof(BITMAPFILEHEADER));
		Fileimg.Write(&bi_h,sizeof(BITMAPINFOHEADER));
		Fileimg.Write(rgbquad,conrgb);
		CImage * point_img;
		point_img= new CImage;
		point_img->BMP2RAW(dst1,temp1,width,height);
		Fileimg.Write(temp1,m_dwLength);						//��ʵ����д���ļ�
		delete point_img;
		AfxMessageBox("����8λBMP");
		return;
	}
	else if(bcont==24)
	{
		CFile Fileimg;
		Fileimg.Open(FilePathName,CFile::modeWrite|CFile::modeCreate);
		Fileimg.Write(&bf_h,sizeof(BITMAPFILEHEADER));
		Fileimg.Write(&bi_h,sizeof(BITMAPINFOHEADER));
		int c=3*width%4;
		for(int j=0;j<height;j++)
			{
				for(int i=0;i<width;i++)
				{
					Fileimg.Write(&dst3[width*(height-j-1)+i].c3,1);
					Fileimg.Write(&dst3[width*(height-j-1)+i].c2,1);
					Fileimg.Write(&dst3[width*(height-j-1)+i].c1,1);
				}
				if(c!=0)
					Fileimg.Seek(4-c,CFile::current);
			}

		AfxMessageBox("����24λBMP");
		return;
	}
	else
	{
		AfxMessageBox("����RAW");
		return;
	}
}

void CMyimgView::OnColor2mono()				//��ɫ��Ҷ�
{
	// TODO: Add your command handler code here
	if(bcont==24)
	{
		if((src1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("src1�����ڴ��");
			return ;
		}
		if((dst1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("dst1�����ڴ��");
			 return ;
		}

		CImage * point_img;
		point_img= new CImage;
		point_img->Color2Homo(src3, src1, width, height);
		point_img->COPYIMG1(src1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		bcont=8;
		bi_h.biBitCount=8;
		conrgb=(int)pow(2,bi_h.biBitCount)*4;		//�����ɫ�峤��
		rgbquad= new RGBQUAD[conrgb];				//��ɫ�峤�ȷ��䶯̬�ڴ�
		for(int i=0;i<conrgb;i++)					//������ɫ��
		{
			rgbquad[i].rgbBlue=i;
			rgbquad[i].rgbGreen=i;
			rgbquad[i].rgbRed=i;
			rgbquad[i].rgbReserved=0;
		} 

		delete point_img;
	}
	else
	{
		MessageBox("���ǲ�ɫͼ��");	
	}
	
}

void CMyimgView::OnGrayreverse()		//ͼ��ת
{
	// TODO: Add your command handler code here
	if(bcont==8)
	{
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
		CContrast * point_con;
		point_con= new CContrast;
		point_con->ContrastStretch(dst1,temp1,width,height,CONTRASTFUNC0,0,0,0,0);
		CImage * point_img;
		point_img=new CImage;
		point_img->COPYIMG1(temp1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		delete point_img;
		delete point_con;
	}
	else if(bcont==24)
	{
		MessageBox("���ǻҶ�ͼ��");	
	}

}

void CMyimgView::OnPiecewiseLinear() 
{
	// TODO: Add your command handler code here
	if(bcont==8)
	{
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
		int p0=50,p1=150,p2=30,p3=200;					//Ϊ�ֶ����Ա仯��ֵ �������öԻ���
		CContrast * point_con;
		point_con= new CContrast;
		point_con->ContrastStretch(dst1,temp1,width,height,CONTRASTFUNC1,p0,p1,p2,p3);
		CImage * point_img;
		point_img=new CImage;
		point_img->COPYIMG1(temp1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		delete point_img;
		delete point_con;
	}
	else if(bcont==24)
	{
		MessageBox("���ǻҶ�ͼ��");	
	}

}

void CMyimgView::OnLogTrans() 
{
	// TODO: Add your command handler code here
		if(bcont==8)
	{
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
		CContrast * point_con;
		point_con= new CContrast;
		point_con->ContrastStretch(dst1,temp1,width,height,CONTRASTFUNC2,0,0,0,0);
		CImage * point_img;
		point_img=new CImage;
		point_img->COPYIMG1(temp1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		delete point_img;
		delete point_con;
	}
	else if(bcont==24)
	{
		MessageBox("���ǻҶ�ͼ��");	
	}
}

void CMyimgView::OnLogRetrans() 
{
	// TODO: Add your command handler code here
			if(bcont==8)
	{
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
		CContrast * point_con;
		point_con= new CContrast;
		point_con->ContrastStretch(dst1,temp1,width,height,CONTRASTFUNC3,0,0,0,0);
		CImage * point_img;
		point_img=new CImage;
		point_img->COPYIMG1(temp1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		delete point_img;
		delete point_con;
	}
	else if(bcont==24)
	{
		MessageBox("���ǻҶ�ͼ��");	
	}
}

void CMyimgView::OnNpower() 
{
	// TODO: Add your command handler code here
	if(bcont==8)
	{
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
		CContrast * point_con;
		point_con= new CContrast;
		point_con->ContrastStretch(dst1,temp1,width,height,CONTRASTFUNC4,2,0,0,0);	//p0Ϊ�ݴ�
		CImage * point_img;
		point_img=new CImage;
		point_img->COPYIMG1(temp1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		delete point_img;
		delete point_con;
	}
	else if(bcont==24)
	{
		MessageBox("���ǻҶ�ͼ��");	
	}

}

void CMyimgView::OnNroot() 
{
	// TODO: Add your command handler code here
	if(bcont==8)
	{
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
		CContrast * point_con;
		point_con= new CContrast;
		point_con->ContrastStretch(dst1,temp1,width,height,CONTRASTFUNC5,2,0,0,0);	//p0Ϊ�ݴ�
		CImage * point_img;
		point_img=new CImage;
		point_img->COPYIMG1(temp1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		delete point_img;
		delete point_con;
	}
	else if(bcont==24)
	{
		MessageBox("���ǻҶ�ͼ��");	
	}

}

void CMyimgView::OnGama() 
{
	// TODO: Add your command handler code here
		if(bcont==8)
	{
		if((temp1=new unsigned char[m_dwLength])==NULL)
		{
			MessageBox("temp1�����ڴ��");
			return ;
		}
		CContrast * point_con;
		point_con= new CContrast;
		point_con->ContrastStretch(dst1,temp1,width,height,CONTRASTGAMA,2,2,0,0);	//p0Ϊ�ݴ�,p1λϵ��
		CImage * point_img;
		point_img=new CImage;
		point_img->COPYIMG1(temp1,dst1,width,height);
		CClientDC dc(this);
		int start_x=0;
		int start_y=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		delete point_img;
		delete point_con;
	}
	else if(bcont==24)
	{
		MessageBox("���ǻҶ�ͼ��");	
	}
}

void CMyimgView::OnRgb2hsi() 
{
	// TODO: Add your command handler code here
	if(bcont==24)
	{
		if((hsi3=new HSI[m_dwLength])==NULL)
		{
			MessageBox("hsi3�����ڴ��");
			return ;
		}
		CColor * point_col;
		point_col= new CColor;
		point_col->RGB2HSI(src3,hsi3,width,height);

		CClientDC dc(this);
		int start_x1=0;
		int start_y1=0;
		int start_x2=width;
		int start_y2=0;
		int start_x3=2*width;
		int start_y3=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x1,y+start_y1,RGB(hsi3[width*y+x].d1*255/M_PI,hsi3[width*y+x].d1*255/M_PI,hsi3[width*y+x].d1*255/M_PI));
		for(y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x2,y+start_y2,RGB(hsi3[width*y+x].d2*255,hsi3[width*y+x].d2*255,hsi3[width*y+x].d2*255));
		for(y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x3,y+start_y3,RGB(hsi3[width*y+x].d3,hsi3[width*y+x].d3,hsi3[width*y+x].d3));
		delete point_col;
	}
	else if(bcont==8)
	{
		MessageBox("���ǲ�ɫͼ��");	
	}

}

void CMyimgView::OnHsi2rgb() 
{
	// TODO: Add your command handler code here
	if(bcont==24)
	{

		if((dst3=new RGB[m_dwLength])==NULL)
		{
			MessageBox("hsi3�����ڴ��");
			return ;
		}
		CColor * point_col;
		point_col= new CColor;
		point_col->HSI2RGB(hsi3,dst3,width,height);

		CClientDC dc(this);
		int start_x=0;
		int start_y=0;

		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst3[width*y+x].c1,dst3[width*y+x].c2,dst3[width*y+x].c3));
	}
	else if(bcont==8)
	{
		MessageBox("���ǲ�ɫͼ��");	
	}
}

void CMyimgView::OnRgb2hsv() 
{
	// TODO: Add your command handler code here
		if(bcont==24)
	{
		if((hsv3=new HSV[m_dwLength])==NULL)
		{
			MessageBox("hsi3�����ڴ��");
			return ;
		}
		CColor * point_col;
		point_col= new CColor;
		point_col->RGB2HSV(src3,hsv3,width,height);

		CClientDC dc(this);
		int start_x1=0;
		int start_y1=0;
		int start_x2=width;
		int start_y2=0;
		int start_x3=2*width;
		int start_y3=0;
		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x1,y+start_y1,RGB(hsv3[width*y+x].d1*255/M_PI,hsv3[width*y+x].d1*255/M_PI,hsv3[width*y+x].d1*255/M_PI));
		for(y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x2,y+start_y2,RGB(hsv3[width*y+x].d2*255,hsv3[width*y+x].d2*255,hsv3[width*y+x].d2*255));
		for(y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x3,y+start_y3,RGB(hsv3[width*y+x].d3,hsv3[width*y+x].d3,hsv3[width*y+x].d3));
		delete point_col;
	}
	else if(bcont==8)
	{
		MessageBox("���ǲ�ɫͼ��");	
	}

}

void CMyimgView::OnHsv2rgb() 
{
	// TODO: Add your command handler code here
	if(bcont==24)
	{

		if((dst3=new RGB[m_dwLength])==NULL)
		{
			MessageBox("dst3�����ڴ��");
			return ;
		}
		CColor * point_col;
		point_col= new CColor;
		point_col->HSV2RGB(hsv3,dst3,width,height);

		CClientDC dc(this);
		int start_x=0;
		int start_y=0;

		for(int y=0;y<height;y++)
				for(int x=0;x<width;x++)
					dc.SetPixel(x+start_x,y+start_y,RGB(dst3[width*y+x].c1,dst3[width*y+x].c2,dst3[width*y+x].c3));
	}
	else if(bcont==8)
	{
		MessageBox("���ǲ�ɫͼ��");	
	}
}

void CMyimgView::OnSegRobert() 
{
	if(bcont!=8)
	{
		MessageBox("���ǻҶ�ͼ��");
		return;
	}
	else
	{
	// TODO: Add your command handler code here
		double *src=(double *)malloc(sizeof(double)*width*height);
		double *dst=(double *)malloc(sizeof(double)*width*height);

		CImage *point_img;
		point_img=new CImage;
		point_img->CHAR2DBL(dst1,src,width,height);
	
		CSegment * point_seg;
		point_seg=new CSegment;
	
		point_seg->Robert(src,dst,width,height);
		point_img->DBL2CHAR(dst,dst1,width,height);
		delete point_img;
		delete point_seg;

		CClientDC dc(this);
		int start_x=522;
		int start_y=0;
		for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));

		free(src);
		free(dst);
	}

}

void CMyimgView::OnSharpRobert() 
{
	// TODO: Add your command handler code here
	if(bcont!=8)
	{
		MessageBox("���ǻҶ�ͼ��");
		return;
	}
	else
	{
		double *src=(double *)malloc(sizeof(double)*width*height);
		double *dst=(double *)malloc(sizeof(double)*width*height);
		CImage *point_img;
		point_img=new CImage;
		point_img->CHAR2DBL(dst1,src,width,height);
		CSharpen *point_sharp;
		point_sharp=new CSharpen;
		point_sharp->RobertSharpen(src,dst,width,height,0.2);
		point_img->DBL2CHAR(dst,dst1,width,height);
		delete point_img;
		delete point_sharp;

		CClientDC dc(this);
		int start_x=522;
		int start_y=0;
		for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		free(src);
		free(dst);
	}
}

void CMyimgView::OnSegSobel() 
{
	// TODO: Add your command handler code here
	if(bcont!=8)
	{
		MessageBox("���ǻҶ�ͼ��");
		return;
	}
	else
	{
		double *src=(double *)malloc(sizeof(double)*width*height);
		double *dst=(double *)malloc(sizeof(double)*width*height);
		CImage *point_img;
		point_img=new CImage;
		CSegment * point_seg;
		point_seg=new CSegment;

		point_img->CHAR2DBL(dst1,src,width,height);
		point_seg->Sobel(src,dst,width,height,3);			//para5 ����ѡ��Sobelģ���С 3��5��7
		point_img->DBL2CHAR(dst,dst1,width,height);

		delete point_img;
		delete point_seg;

		CClientDC dc(this);
		int start_x=522;
		int start_y=0;
		for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		free(src);
		free(dst);
	}
}

void CMyimgView::OnSharpSobel() 
{
	// TODO: Add your command handler code here
		if(bcont!=8)
	{
		MessageBox("���ǻҶ�ͼ��");
		return;
	}
	else
	{
		double *src=(double *)malloc(sizeof(double)*width*height);
		double *dst=(double *)malloc(sizeof(double)*width*height);
		CImage *point_img;
		point_img=new CImage;
		point_img->CHAR2DBL(dst1,src,width,height);
		CSharpen *point_sharp;
		point_sharp=new CSharpen;
		point_sharp->SobelSharpen(src,dst,width,height,0.2);
		point_img->DBL2CHAR(dst,dst1,width,height);
		delete point_img;
		delete point_sharp;

		CClientDC dc(this);
		int start_x=522;
		int start_y=0;
		for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
		free(src);
		free(dst);
	}
}

void CMyimgView::OnDftTrans() 
{
	// TODO: Add your command handler code here
	double input[8]={0,1,2,3,4,5,6,7};
	Complex output[8];
	CFourer *point_four;
	point_four=new CFourer;
	point_four->DFT(input,output,8);
	delete point_four;

}

void CMyimgView::OnIdftTrans() 
{
	// TODO: Add your command handler code here
	double input[8]={0,1,2,3,4,5,6,7};
	Complex output[8],outputnew[8];
	CFourer *point_four;
	point_four=new CFourer;
	point_four->DFT(input,output,8);
	point_four->IDFT(output,outputnew,8);			
	delete point_four;
}

void CMyimgView::OnDft2dTrans() 
{
	double *src=(double *)malloc(sizeof(double)*width*height);
	double *dst=(double *)malloc(sizeof(double)*width*height);
	double *Amp=(double *)malloc(sizeof(double)*width*height);
	double *Phase=(double *)malloc(sizeof(double)*width*height);
	output=new Complex[width*height];
	CImage *point_img;
	point_img=new CImage;
	point_img->CHAR2DBL(dst1,src,width,height);
	CFourer *point_four;
	point_four=new CFourer;
	CMathematic *point_math;
	point_math=new CMathematic;
	point_four->DFT2D(src,output,width,height);
	point_four->AmplitudePhase(output,Amp,Phase,width,height);
	for(int i=0;i<width*height;i++)	
	{
		dst[i]=20*log(Amp[i]);
	}
	double max=point_math->findMatrixMax(dst,width,height,NULL);
	for(int j=0;j<width*height;j++)
	{
		dst[j]=dst[j]*255.0/max;
	}
	point_img->DBL2CHAR(dst,dst1,width,height);
	CClientDC dc(this);
	int start_x=522;
	int start_y=0;
	for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
	
	delete point_img;
	delete point_four;
	delete point_math;
	free(src);
	free(dst);
	free(Amp);
	free(Phase);
}

void CMyimgView::OnIdft2d() 
{
	// TODO: Add your command handler code here
	double *src=(double *)malloc(sizeof(double)*width*height);
	double *dst=(double *)malloc(sizeof(double)*width*height);
	double *Amp=(double *)malloc(sizeof(double)*width*height);
	double *Phase=(double *)malloc(sizeof(double)*width*height);
	CImage *point_img;
	point_img=new CImage;

	outputnew=new Complex[width*height];
	CFourer *point_four;
	point_four=new CFourer;
	point_four->AmplitudePhase(output,Amp,Phase,width,height);
	for(int i=0;i<width*height;i++)
	{
//		Amp[i]=2000;										//��ֵ��Ϊ����
//		Phase[i]=0;											//��λ���
	}
	point_four->AmplitudePhase2Complex(output,Amp,Phase,output,width,height);
	point_four->IDFT2D(output,outputnew,width,height);
	CMathematic *point_math;
	point_math=new CMathematic;
	point_four->AmplitudePhase(outputnew,dst,Phase,width,height);
	double max=point_math->findMatrixMax(dst,width,height,NULL);
	for( i=0;i<width*height;i++)
	{
		dst[i]=dst[i]*255.0/max;
		if(dst[i]>255)
		{
			dst[i]=255;
		}
	}
	point_img->DBL2CHAR(dst,dst1,width,height);
	
	CClientDC dc(this);
	int start_x=522;
	int start_y=0;
	for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));

	delete point_img;
	delete point_four;
	delete point_math;
	free(src);
	free(dst);
	free(Amp);
	free(Phase);
}

void CMyimgView::OnFftTrans() 
{
	// TODO: Add your command handler code here
	double input[8]={0,1,2,3,4,5,6,7};
	Complex output[8];
	CFourer *point_four;
	point_four=new CFourer;
	point_four->RealFFT(input,output,8);
	for(int i=0;i<8;i++)
	{
		output[i].real=i;
		output[i].imagin=0;
	}
	point_four->FFT(output,output,8);
	delete point_four;
}

void CMyimgView::OnIfftTrans() 
{
	// TODO: Add your command handler code here
	double input[8]={0,1,2,3,4,5,6,7};
	Complex output[8];
	CFourer *point_four;
	point_four=new CFourer;
	point_four->RealFFT(input,output,8);
	point_four->IFFT(output,output,8);
	delete point_four;
}

void CMyimgView::OnFft2dTrans() 
{
	// TODO: Add your command handler code here
	double *src=(double *)malloc(sizeof(double)*width*height);
	double *dst=(double *)malloc(sizeof(double)*width*height);
	double *Amp=(double *)malloc(sizeof(double)*width*height);
	double *Phase=(double *)malloc(sizeof(double)*width*height);
	output=new Complex[width*height];
	CImage *point_img;
	point_img=new CImage;
	point_img->CHAR2DBL(dst1,src,width,height);
	CFourer *point_four;
	point_four=new CFourer;
	CMathematic *point_math;
	point_math=new CMathematic;
	point_four->FFT2D(src,output,width,height);
	point_four->AmplitudePhase(output,Amp,Phase,width,height);
	for(int i=0;i<width*height;i++)	
	{
		dst[i]=20*log(Amp[i]);
	}
	double max=point_math->findMatrixMax(dst,width,height,NULL);
	for(int j=0;j<width*height;j++)
	{
		dst[j]=dst[j]*255.0/max;
	}
	point_img->DBL2CHAR(dst,dst1,width,height);
	CClientDC dc(this);
	int start_x=522;
	int start_y=0;
	for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
	
	delete point_img;
	delete point_four;
	delete point_math;
	free(src);
	free(dst);
	free(Amp);
	free(Phase);
}

void CMyimgView::OnIfft2dTrans() 
{
	// TODO: Add your command handler code here
	double *src=(double *)malloc(sizeof(double)*width*height);
	double *dst=(double *)malloc(sizeof(double)*width*height);
	double *Amp=(double *)malloc(sizeof(double)*width*height);
	double *Phase=(double *)malloc(sizeof(double)*width*height);
	CImage *point_img;
	point_img=new CImage;

	outputnew=new Complex[width*height];
	CFourer *point_four;
	point_four=new CFourer;
	point_four->AmplitudePhase(output,Amp,Phase,width,height);
	for(int i=0;i<width*height;i++)
	{
//		Amp[i]=2000;										//��ֵ��Ϊ����
//		Phase[i]=0;											//��λ���
	}
	point_four->AmplitudePhase2Complex(output,Amp,Phase,output,width,height);
	point_four->IFFT2D(output,outputnew,width,height);
	CMathematic *point_math;
	point_math=new CMathematic;
	point_four->AmplitudePhase(outputnew,dst,Phase,width,height);
	double max=point_math->findMatrixMax(dst,width,height,NULL);
	for( i=0;i<width*height;i++)
	{
		dst[i]=dst[i]*255.0/max;
		if(dst[i]>255)
		{
			dst[i]=255;
		}
	}
	point_img->DBL2CHAR(dst,dst1,width,height);
	
	CClientDC dc(this);
	int start_x=522;
	int start_y=0;
	for(int y=0;y<height;y++)
			for(int x=0;x<width;x++)
				dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));

	delete point_img;
	delete point_four;
	delete point_math;
	free(src);
	free(dst);
	free(Amp);
	free(Phase);
}

void CMyimgView::OnShowHistogram() 
{
	// TODO: Add your command handler code here
	int *hist;
	hist=new int[GRAY_LEVEL];
	double *temp=(double *)malloc(sizeof(double)*GRAY_LEVEL);
	CHistogram *point_hist;
	point_hist=new CHistogram;
	point_hist->setHistogram(dst1,hist,width,height);
	CClientDC dc(this);
	CImage *point_img;
	point_img=new CImage;
	point_img->INT2DBL(hist,temp,GRAY_LEVEL,1);
	CMathematic *point_math;
	point_math=new CMathematic;
	int max=point_math->findMatrixMax(temp,GRAY_LEVEL,1,NULL);
	for(int i=0;i<GRAY_LEVEL;i++)
	{
		if(max!=0&&max>GRAY_LEVEL)
			temp[i]=(GRAY_LEVEL*hist[i]/max);
	}
	int start_x=0;
	int start_y=height+GRAY_LEVEL;
	for(int x=0;x<GRAY_LEVEL;x++)
	{
		dc.SetPixel(start_x,start_y-x,RGB(200,0,0));
		dc.SetPixel(start_x+x,start_y,RGB(200,0,0));
		for(int y=0;y<temp[x];y++)
		{
			dc.SetPixel(start_x+x,start_y-y,RGB(100,100,100));
		}
	}
	free(temp);
	delete point_math;
	delete point_img;
}

void CMyimgView::OnHistEqualization() 
{
	// TODO: Add your command handler code here
	int *hist;
	hist=new int[GRAY_LEVEL];
	double *temp=(double *)malloc(sizeof(double)*GRAY_LEVEL);
	CHistogram *point_hist;
	point_hist=new CHistogram;
	point_hist->setHistogram(dst1,hist,width,height);
	point_hist->HistogramEqualization(dst1,dst1,width,height);
	CClientDC dc(this);
	CImage *point_img;
	point_img=new CImage;
	point_img->INT2DBL(hist,temp,GRAY_LEVEL,1);
	CMathematic *point_math;
	point_math=new CMathematic;
	int max=point_math->findMatrixMax(temp,GRAY_LEVEL,1,NULL);
	for(int i=0;i<GRAY_LEVEL;i++)
	{
		if(max!=0&&max>GRAY_LEVEL)
			temp[i]=(GRAY_LEVEL*hist[i]/max);
	}
/********************��ʾֱ��ͼ*********************/
	int start_x=0;
	int start_y=height+GRAY_LEVEL;
	for(int x=0;x<GRAY_LEVEL;x++)
	{
		dc.SetPixel(start_x,start_y-x,RGB(200,0,0));
		dc.SetPixel(start_x+x,start_y,RGB(200,0,0));
		for(int y=0;y<temp[x];y++)
		{
			dc.SetPixel(start_x+x,start_y-y,RGB(100,100,100));
		}
	}
/**************************************************/
/*******************��ʾHE���**********************/
	start_x=width+GRAY_LEVEL;
	start_y=0;
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
			dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
/**********************************************************/
/*********************��ȡ�µ�ֱ��ͼ***********************/
	point_hist->setHistogram(dst1,hist,width,height);
	point_img->INT2DBL(hist,temp,GRAY_LEVEL,1);
	max=point_math->findMatrixMax(temp,GRAY_LEVEL,1,NULL);
	for(i=0;i<GRAY_LEVEL;i++)
	{
		if(max!=0&&max>GRAY_LEVEL)
			temp[i]=(GRAY_LEVEL*hist[i]/max);
	}
/**********************************************************/
/*********************��ʾ�µ�ֱ��ͼ***********************/
	start_x=GRAY_LEVEL+5;
	start_y=height+GRAY_LEVEL;
	for(x=0;x<GRAY_LEVEL;x++)
	{
		dc.SetPixel(start_x,start_y-x,RGB(200,0,0));
		dc.SetPixel(start_x+x,start_y,RGB(200,0,0));
		for(int y=0;y<temp[x];y++)
		{
			dc.SetPixel(start_x+x,start_y-y,RGB(100,100,100));
		}
	}
/************************************************************/
	free(temp);
	delete point_math;
	delete point_img;

}

void CMyimgView::OnClhe() 
{
	// TODO: Add your command handler code here
	int *hist;
	hist=new int[GRAY_LEVEL];
	double *temp=(double *)malloc(sizeof(double)*GRAY_LEVEL);
	CHistogram *point_hist;
	point_hist=new CHistogram;
	point_hist->setHistogram(dst1,hist,width,height);

/*************��ʾԭʼֱ��ͼ**************/
	CClientDC dc(this);
	CImage *point_img;
	point_img=new CImage;
	point_img->INT2DBL(hist,temp,GRAY_LEVEL,1);
	CMathematic *point_math;
	point_math=new CMathematic;
	int max=point_math->findMatrixMax(temp,GRAY_LEVEL,1,NULL);
	for(int i=0;i<GRAY_LEVEL;i++)
	{
		if(max!=0&&max>GRAY_LEVEL)
			temp[i]=(GRAY_LEVEL*hist[i]/max);
	}
	int start_x=0;
	int start_y=height+GRAY_LEVEL;
	for(int x=0;x<GRAY_LEVEL;x++)
	{
		dc.SetPixel(start_x,start_y-x,RGB(200,0,0));
		dc.SetPixel(start_x+x,start_y,RGB(200,0,0));
		for(int y=0;y<temp[x];y++)
		{
			dc.SetPixel(start_x+x,start_y-y,RGB(100,100,100));
		}
	}
/*************************************/


/*************�ü�ֱ��ͼ************/
	int *dst_hist;
	dst_hist=new int[GRAY_LEVEL];
	point_hist->clipHistogram(hist,dst_hist,0.01,width,height);
/*************************************/

/****************���CLHEͼ��*********************/
	point_hist->CLHistogramEqulization(dst1,dst1,width,height);
/*************************************************/
/*************��ʾCLHE****************/
	start_x=width+GRAY_LEVEL;
	start_y=0;
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
			dc.SetPixel(x+start_x,y+start_y,RGB(dst1[width*y+x],dst1[width*y+x],dst1[width*y+x]));
/*************************************/
/************��һ���ü����*************/
	point_img->INT2DBL(dst_hist,temp,GRAY_LEVEL,1);
	max=point_math->findMatrixMax(temp,GRAY_LEVEL,1,NULL);
	for(i=0;i<GRAY_LEVEL;i++)
	{
		if(max!=0&&max>GRAY_LEVEL)
		{
			temp[i]=(GRAY_LEVEL*temp[i]/max);
		}
	}
/***************************************/
/*************��ʾ�ü�ֱ��ͼ*****************/
	start_x=GRAY_LEVEL+5;
	start_y=height+GRAY_LEVEL;
	for(x=0;x<GRAY_LEVEL;x++)
	{
		dc.SetPixel(start_x,start_y-x,RGB(200,0,0));
		dc.SetPixel(start_x+x,start_y,RGB(200,0,0));
		for(int y=0;y<temp[x];y++)
		{
			dc.SetPixel(start_x+x,start_y-y,RGB(100,100,100));
		}
	}
/***************************************/
/*********************��ȡ�µ�ֱ��ͼ***********************/
	point_hist->setHistogram(dst1,hist,width,height);
	point_img->INT2DBL(hist,temp,GRAY_LEVEL,1);
	max=point_math->findMatrixMax(temp,GRAY_LEVEL,1,NULL);
	for(i=0;i<GRAY_LEVEL;i++)
	{
		if(max!=0&&max>GRAY_LEVEL)
			temp[i]=(GRAY_LEVEL*hist[i]/max);
	}
/**********************************************************/
/*********************��ʾ�µ�ֱ��ͼ***********************/
	start_x+=GRAY_LEVEL+5;
	start_y=height+GRAY_LEVEL;
	for(x=0;x<GRAY_LEVEL;x++)
	{
		dc.SetPixel(start_x,start_y-x,RGB(200,0,0));
		dc.SetPixel(start_x+x,start_y,RGB(200,0,0));
		for(int y=0;y<temp[x];y++)
		{
			dc.SetPixel(start_x+x,start_y-y,RGB(100,100,100));
		}
	}
/************************************************************/

	free(temp);
	delete point_math;
	delete point_img;
}

