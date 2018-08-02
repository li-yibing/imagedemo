// myimgDoc.cpp : implementation of the CMyimgDoc class
//

#include "stdafx.h"
#include "myimg.h"

#include "myimgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyimgDoc

IMPLEMENT_DYNCREATE(CMyimgDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyimgDoc, CDocument)
	//{{AFX_MSG_MAP(CMyimgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyimgDoc construction/destruction

CMyimgDoc::CMyimgDoc()
{
	// TODO: add one-time construction code here

}

CMyimgDoc::~CMyimgDoc()
{
}

BOOL CMyimgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyimgDoc serialization

void CMyimgDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyimgDoc diagnostics

#ifdef _DEBUG
void CMyimgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyimgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyimgDoc commands
