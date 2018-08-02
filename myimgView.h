// myimgView.h : interface of the CMyimgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIMGVIEW_H__B98A153F_244A_4045_B4B2_F14437954CBC__INCLUDED_)
#define AFX_MYIMGVIEW_H__B98A153F_244A_4045_B4B2_F14437954CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Image.h"
#include "Color.h"
#include "Contrast.h"

class CMyimgView : public CView
{
protected: // create from serialization only
	CMyimgView();
	DECLARE_DYNCREATE(CMyimgView)

// Attributes
public:
	CMyimgDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyimgView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyimgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyimgView)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnColor2mono();
	afx_msg void OnGrayreverse();
	afx_msg void OnPiecewiseLinear();
	afx_msg void OnLogTrans();
	afx_msg void OnLogRetrans();
	afx_msg void OnNpower();
	afx_msg void OnNroot();
	afx_msg void OnGama();
	afx_msg void OnRgb2hsi();
	afx_msg void OnHsi2rgb();
	afx_msg void OnRgb2hsv();
	afx_msg void OnHsv2rgb();
	afx_msg void OnSegRobert();
	afx_msg void OnSharpRobert();
	afx_msg void OnSegSobel();
	afx_msg void OnSharpSobel();
	afx_msg void OnDftTrans();
	afx_msg void OnIdftTrans();
	afx_msg void OnDft2dTrans();
	afx_msg void OnIdft2d();
	afx_msg void OnFftTrans();
	afx_msg void OnIfftTrans();
	afx_msg void OnFft2dTrans();
	afx_msg void OnIfft2dTrans();
	afx_msg void OnShowHistogram();
	afx_msg void OnHistEqualization();
	afx_msg void OnClhe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in myimgView.cpp
inline CMyimgDoc* CMyimgView::GetDocument()
   { return (CMyimgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMGVIEW_H__B98A153F_244A_4045_B4B2_F14437954CBC__INCLUDED_)
