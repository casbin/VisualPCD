#include "ISonicUI.h"
#pragma comment(lib, "SonicUI.lib")
using namespace sonic_ui;
#define MAX_LOADSTRING 100

#if !defined(AFX_VISUALPCDABOUTDLG_H__EEEB1310_3BD3_424C_8BF4_7ECE10B2B858__INCLUDED_)
#define AFX_VISUALPCDABOUTDLG_H__EEEB1310_3BD3_424C_8BF4_7ECE10B2B858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisualPCDAboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDAboutDlg dialog

class CVisualPCDAboutDlg : public CDialog
{
// Construction
public:
	CVisualPCDAboutDlg(CWnd* pParent = NULL);   // standard constructor

public:
	ISonicString* pStrAboutTitle;
	
	//ISonicWndEffect* pThreadEffect;

	ISonicImage* pImgWndAbout;
	ISonicString* pStrWndAbout;
	ISonicString* pStrAboutInfo;
	ISonicString* pStrAboutClose;
	
public:
	void InitPointer();
	void InitWindow();

	void CloseWindow();

	static void TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);

	void InitWindowGently();
	void ShowWindowGently();
	void DrawWindowGently(int nTrans);
	void HideWindowGently();
	int m_iTrans;

// Dialog Data
	//{{AFX_DATA(CVisualPCDAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPCDAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisualPCDAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPCDABOUTDLG_H__EEEB1310_3BD3_424C_8BF4_7ECE10B2B858__INCLUDED_)
