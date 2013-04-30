// MyDocument.cpp : implementation file
//

#include "stdafx.h"
#include "MyDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDocument

IMPLEMENT_DYNCREATE(CMyDocument, CDocument)

CMyDocument::CMyDocument()
{
}

BOOL CMyDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMyDocument::~CMyDocument()
{
}


BEGIN_MESSAGE_MAP(CMyDocument, CDocument)
	//{{AFX_MSG_MAP(CMyDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDocument diagnostics

#ifdef _DEBUG
void CMyDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDocument serialization

void CMyDocument::Serialize(CArchive& ar)
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
// CMyDocument commands
