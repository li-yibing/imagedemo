// myimg.h : main header file for the MYIMG application
//

#if !defined(AFX_MYIMG_H__21C43D5D_958D_4FF1_B07D_847095D6EE38__INCLUDED_)
#define AFX_MYIMG_H__21C43D5D_958D_4FF1_B07D_847095D6EE38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyimgApp:
// See myimg.cpp for the implementation of this class
//

class CMyimgApp : public CWinApp
{
public:
	CMyimgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyimgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyimgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMG_H__21C43D5D_958D_4FF1_B07D_847095D6EE38__INCLUDED_)
