#if !defined(AFX_VISUALPCDTRANSDLG_H__E4F91124_BE67_42CA_AC33_FA9A060A6307__INCLUDED_)
#define AFX_VISUALPCDTRANSDLG_H__E4F91124_BE67_42CA_AC33_FA9A060A6307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisualPCDTransDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDTransDlg dialog

class CVisualPCDTransDlg : public CDialog
{
// Construction
public:
	CVisualPCDTransDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVisualPCDTransDlg)
	enum { IDD = IDD_TRANS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPCDTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisualPCDTransDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPCDTRANSDLG_H__E4F91124_BE67_42CA_AC33_FA9A060A6307__INCLUDED_)
