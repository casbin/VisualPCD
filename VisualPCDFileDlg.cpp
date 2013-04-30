// VisualPCDFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "visualpcd.h"
#include "VisualPCDFileDlg.h"
#include "VisualPCDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CVisualPCDDlg* pFileParentThis;

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDFileDlg

IMPLEMENT_DYNAMIC(CVisualPCDFileDlg, CFileDialog)

CVisualPCDFileDlg::CVisualPCDFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd, int iMode) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	pFileParentThis = (CVisualPCDDlg*) pParentWnd;
	m_iMode = iMode;
}


BEGIN_MESSAGE_MAP(CVisualPCDFileDlg, CFileDialog)
	//{{AFX_MSG_MAP(CVisualPCDFileDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CVisualPCDFileDlg::DoModal()
{
	int res = CFileDialog::DoModal();
	if (m_iMode == FILEDIALOG_FILEA)
	{
		pFileParentThis->m_cstrFileALocation = this->GetPathName();
	}
	else if (m_iMode == FILEDIALOG_FILEB)
	{
		pFileParentThis->m_cstrFileBLocation = this->GetPathName();
	}
	else if (m_iMode == FILEDIALOG_REPORT)
	{
		pFileParentThis->m_cstrReportLocation = this->GetPathName();
	}
	else
	{
		pFileParentThis->m_cstrReportLocation = "";
	}
	
	return res;
}

