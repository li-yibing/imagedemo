// myimgDoc.h : interface of the CMyimgDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIMGDOC_H__8DE153EF_5B16_405A_BA68_C3F856F653DE__INCLUDED_)
#define AFX_MYIMGDOC_H__8DE153EF_5B16_405A_BA68_C3F856F653DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyimgDoc : public CDocument
{
protected: // create from serialization only
	CMyimgDoc();
	DECLARE_DYNCREATE(CMyimgDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyimgDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyimgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyimgDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMGDOC_H__8DE153EF_5B16_405A_BA68_C3F856F653DE__INCLUDED_)
