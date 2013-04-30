#if !defined(AFX_VISUALPCDFILEDLG_H__DDFACE02_4314_4783_BB26_A1328D53E45A__INCLUDED_)
#define AFX_VISUALPCDFILEDLG_H__DDFACE02_4314_4783_BB26_A1328D53E45A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisualPCDFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDFileDlg dialog

class CVisualPCDFileDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CVisualPCDFileDlg)

public:
	CVisualPCDFileDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL,
		int iMode = 0);

	int m_iMode;
	int DoModal();

protected:
	//{{AFX_MSG(CVisualPCDFileDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPCDFILEDLG_H__DDFACE02_4314_4783_BB26_A1328D53E45A__INCLUDED_)
