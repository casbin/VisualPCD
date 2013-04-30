#include "ISonicUI.h"
#pragma comment(lib, "SonicUI.lib")
using namespace sonic_ui;
#define MAX_LOADSTRING 100

#if !defined(AFX_VISUALPCDGRAPHDLG_H__B6F302D7_0592_4D91_825F_C1C924673803__INCLUDED_)
#define AFX_VISUALPCDGRAPHDLG_H__B6F302D7_0592_4D91_825F_C1C924673803__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisualPCDGraphDlg.h : header file
//

#include "BitmapDialog.h"

#include "Arrow.h"

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDGraphDlg dialog

class CVisualPCDGraphDlg : public CBitmapDialog
{
// Construction
public:
	CVisualPCDGraphDlg(CWnd* pParent = NULL);   // standard constructor

public:
	ISonicString* pStrGraphTitle;
	ISonicString* pStrStatic1;
	ISonicString* pStrStatic2;
	
	//ISonicWndEffect* pThreadEffect;
	
	ISonicImage* pImgWndGraph;
	ISonicString* pStrWndGraph;
	
	ISonicImage* pImgBtnClose;
	ISonicImage* pImgBtnCloseHover;
	ISonicImage* pImgBtnCloseClick;
	ISonicString* pStrBtnClose;


	string m_strFileALocation;
	string m_strFileBLocation;

	vector<int> m_niSubjectContain;
	vector<int> m_niResourceContain;
	vector<int> m_niTargetPolicies;
	int m_iTargetPolicy;
	
	
public:
	void InitPointer();
	void InitWindow();
	void InitControl();
	void InitButton();
	
	void OnClose(ISonicString* pStr, LPVOID);
	void CloseWindow();
	
	static void TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
	
	void InitWindowGently();
	void ShowWindowGently();
	void DrawWindowGently(int nTrans);
	void HideWindowGently();

	string itos(int i);
	int GetCircleX(int iCentreX, int iCentreY, int iRadius, int iSize, int iNo);
	int GetCircleY(int iCentreX, int iCentreY, int iRadius, int iSize, int iNo);
	
	void ShowGraph();
	void InitGraph();
	void DrawGraph(HDC hDC);
	void ChangeGraph(HDC hDC);
	int m_iGraphX;
	int m_iGraphY;

	XMLParser* m_parser;
	vector<string> m_nstrSubjects;
	vector<string> m_nstrResources;
	vector<POINT> m_niSubjects;
	vector<POINT> m_niResources;
	int m_iSub;
	int m_iRes;
	vector<Policet> m_nplcQuints;
	int m_iQuints;

	ARROWSTRUCT m_pArrowSolid;
	ARROWSTRUCT m_pArrowHollow;

	vector<RECT> m_nrctLine;
	vector<int> m_nLineDivisor;
	vector<int> m_nLineAddent;

	HHOOK m_hHook;

	int m_iTrans;
	

// Dialog Data
	//{{AFX_DATA(CVisualPCDGraphDlg)
	enum { IDD = IDD_GRAPH };
	CStatic	m_picGraph;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPCDGraphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVisualPCDGraphDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPCDGRAPHDLG_H__B6F302D7_0592_4D91_825F_C1C924673803__INCLUDED_)
