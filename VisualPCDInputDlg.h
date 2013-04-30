#if !defined(AFX_VISUALPCDINPUTDLG_H__122BCAC2_5AE1_4B73_9393_49155909707D__INCLUDED_)
#define AFX_VISUALPCDINPUTDLG_H__122BCAC2_5AE1_4B73_9393_49155909707D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisualPCDInputDlg.h : header file
//

#include "AdvEdit.h"
#include "BitmapDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDInputDlg dialog

class CVisualPCDInputDlg : public CBitmapDialog
{
// Construction
public:
	CVisualPCDInputDlg(CWnd* pParent = NULL);   // standard constructor

public:
	ISonicString* pStrInputTitle;
	ISonicString* pStrStatic1;
	ISonicString* pStrStatic2;
	
	//ISonicWndEffect* pThreadEffect;
	
	ISonicImage* pImgWndInput;
	ISonicString* pStrWndInput;
	
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
	
	void ShowFile();

// Dialog Data
	//{{AFX_DATA(CVisualPCDInputDlg)
	enum { IDD = IDD_INPUT };
	CAdvEdit	m_editInput2;
	CAdvEdit	m_editInput1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPCDInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisualPCDInputDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPCDINPUTDLG_H__122BCAC2_5AE1_4B73_9393_49155909707D__INCLUDED_)
