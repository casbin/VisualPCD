#include "ISonicUI.h"
#pragma comment(lib, "SonicUI.lib")
using namespace sonic_ui;
#define MAX_LOADSTRING 100

#include "AdvEdit.h"
#include "BitmapDialog.h"

#if !defined(AFX_VISUALPCDRESULTDLG_H__27AF7E52_5567_4175_A295_9024C7F00A17__INCLUDED_)
#define AFX_VISUALPCDRESULTDLG_H__27AF7E52_5567_4175_A295_9024C7F00A17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisualPCDResultDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDResultDlg dialog

class CVisualPCDResultDlg : public CBitmapDialog
{
// Construction
public:
	CVisualPCDResultDlg(CWnd* pParent = NULL);   // standard constructor

public:
	ISonicString* pStrResultTitle;
	
	//ISonicWndEffect* pThreadEffect;
	
	ISonicImage* pImgWndResult;
	ISonicString* pStrWndResult;

	ISonicImage* pImgBtnClose;
	ISonicImage* pImgBtnCloseHover;
	ISonicImage* pImgBtnCloseClick;
	ISonicString* pStrBtnClose;

	
public:
	void InitPointer();
	void InitWindow();
	void InitControl();
	void InitEdit();
	void InitButton();
	
	void OnClose(ISonicString* pStr, LPVOID);
	void CloseWindow();

	static void TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
	
	void InitWindowGently();
	void ShowWindowGently();
	void DrawWindowGently(int nTrans);
	void HideWindowGently();
	int m_iTrans;

	void ShowReport();


	//void GetDLU(CPaintDC& dc);

// Dialog Data
	//{{AFX_DATA(CVisualPCDResultDlg)
	enum { IDD = IDD_RESULT };
	CAdvEdit	m_editResult;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPCDResultDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisualPCDResultDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPCDRESULTDLG_H__27AF7E52_5567_4175_A295_9024C7F00A17__INCLUDED_)
