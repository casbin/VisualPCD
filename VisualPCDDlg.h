// VisualPCDDlg.h : header file
//

#include "ISonicUI.h"
#pragma comment(lib, "SonicUI.lib")
using namespace sonic_ui;
#define MAX_LOADSTRING 100

#if !defined(AFX_VisualPCDDLG_H__B5402AA5_2090_46A4_B843_BA5E189067CB__INCLUDED_)
#define AFX_VisualPCDDLG_H__B5402AA5_2090_46A4_B843_BA5E189067CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndShadow.h"
#include "AdvEdit.h"
#include "VisualPCDAboutDlg.h"
#include "PCDControler.h"
#include "BitmapDialog.h"

#include <ximage.h>

#define FILEDIALOG_FILEA 0
#define FILEDIALOG_FILEB 1
#define FILEDIALOG_REPORT 2


/////////////////////////////////////////////////////////////////////////////
// CVisualPCDDlg dialog

class CVisualPCDDlg : public CBitmapDialog
{
// Construction
public:
	CVisualPCDDlg(CWnd* pParent = NULL);	// standard constructor

public:

	ISonicWndEffect* m_pEffect;
	CString* m_pLocation;
	///////////////////////////////////////////////////////////
	ISonicImage* pImgBtnJc;
	ISonicImage* pImgBtnJcHover;
	ISonicImage* pImgBtnJcClick;
	ISonicString* pStrBtnJc;
	ISonicString* pStrBtnJcText;

	int m_iBtnJcX, m_iBtnJcY;
	RECT m_rctBtnJc;
	///////////////////////////////////////////////////////////
	ISonicImage* pImgBtnXs;
	ISonicImage* pImgBtnXsHover;
	ISonicImage* pImgBtnXsClick;
	ISonicString* pStrBtnXs;
	ISonicString* pStrBtnXsText;

	int m_iBtnXsX, m_iBtnXsY;
	RECT m_rctBtnXs;
	///////////////////////////////////////////////////////////
	ISonicImage* pImgBtnTs;
	ISonicImage* pImgBtnTsHover;
	ISonicImage* pImgBtnTsClick;
	ISonicString* pStrBtnTs;
	ISonicString* pStrBtnTsText;
	
	int m_iBtnTsX, m_iBtnTsY;
	RECT m_rctBtnTs;
	///////////////////////////////////////////////////////////
	ISonicImage* pImgWndMainWindow;
	ISonicImage* pImgWndMainWindowPink;

	ISonicImage* pImgBtnMin;
	ISonicImage* pImgBtnMinHover;
	ISonicImage* pImgBtnMinClick;
	ISonicString* pStrBtnMin;

	ISonicImage* pImgBtnClose;
	ISonicImage* pImgBtnCloseHover;
	ISonicImage* pImgBtnCloseClick;
	ISonicString* pStrBtnClose;
///////////////////////////////////////////////////
	ISonicString* pStrTitle;
///////////////////////////////////////////////////
	ISonicImage* pImgPgbEmpty;
	ISonicImage* pImgPgbLeft;
	ISonicImage* pImgPgbMiddle;
	ISonicImage* pImgPgbRight;

	ISonicImage* pImgPgbGlow;
	ISonicString* pStrPgbGlow;
///////////////////////////////////////////////////
	ISonicImage* pImgBtnMenu;
	ISonicImage* pImgBtnMenuHover;
	ISonicImage* pImgBtnMenuClick;
	ISonicString* pStrBtnMenu;
	ISonicString* pStrBtnMenuShadow;
	int m_iMenuShadow;

	ISonicString* pStrBtnMenuText;

	ISonicImage* pImgPum;
	ISonicImage* pImgPumBig[4];
	//ISonicString* pStrPumText[5];
	int m_iKeepMenu;

	ISonicImage* pImgPumItem[5];
	ISonicImage* pImgPumItemHover[5];
	ISonicImage* pImgPumItemClick[5];
	ISonicString* pStrPumItem[5];
///////////////////////////////////////////////////
	ISonicImage* pImgAbout;
	ISonicString* pStrAbout;
	ISonicString* pStrAboutInfo;
	ISonicString* pStrAboutClose;
///////////////////////////////////////////////////
	CWndShadow m_Shadow;

	int m_iBtnMinCloseFlag;
	int m_iBtnJcFlag;
	int m_iInitCount;

	void OnMove(ISonicString * pStr, LPVOID);
	void OnDisplay(ISonicString * pStr, LPVOID);

	void FadeOut(ISonicString* pStr, LPVOID a_iBtnMinCloseFlag);

	void OnMinimize(ISonicString* pStr, LPVOID);
	void OnClose(ISonicString* pStr, LPVOID);
	void GetTabButtonRect();
	static void TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);

	void UpdateShadow(void);

	BOOL FolderExist(CString strPath);
	BOOL FileExist(CString strFileName);
	CString initKBDir();
	void InitPointer();
	void InitWindow();
	void InitControl();
	void InitButton();
	void InitPopupMenu();
	void InitProgressBar();
	void InitAbout();

	ISonicString* pStrStatic1;
	ISonicString* pStrStatic2;
	ISonicString* pStrStatic3;

	//void RenderProgressBar(ISonicPaint* pPaint, LPVOID);
	void DrawProgressBar(HDC hDC, int nPosX, int nPosY, int nProgress);
	void DrawProgressBarGlow(HDC hDC, int nPosX, int nPosY, int nProgressGlow);
	void StartProgressBar();
	void StopProgressBar();
	int m_iProgress;
	int m_iProgressGlow;
	int m_iProgressX;
	int m_iProgressY;
	RECT m_rectProgress;

	void DrawPopupMenu(HDC hDC, int nStartX, int nStartY, int nCutX, int nCutY);
	void DrawPopupMenu(HDC hDC, int nStartX, int nStartY, int nCutX, int nCutY, int nBig);
	void DrawPopupMenu(HDC hDC);
	void ShowPopupMenu(ISonicString* pStr, LPVOID);
	void KeepPopupMenu(HDC hDC);
	void ClearPopupMenu(ISonicString* pStr, LPVOID);

	int m_iMenuButtonX, m_iMenuButtonY;
	int m_iMenuCutX, m_iMenuCutY;

	HRGN m_rgnMenuButton;
	HRGN m_rgnMenu;
	RECT m_rctMenuButton;
	RECT m_rctMenu;

	int m_iPopup, m_iPopupA;
	int m_iPopout, m_iIsPopdown;

	CAdvEdit m_edit1;
	CAdvEdit m_edit2;
	CAdvEdit m_edit3;

	CString itos(int i);

	void ShowAbout(ISonicString* pStr, LPVOID);
	//void DrawAbout(HDC hDC, int nPosX, int nPosY);
	//void CloseAbout(ISonicString* pStr, LPVOID);
	int m_iKeepAbout;

	void ShowInput(ISonicString* pStr, LPVOID);
	void ShowGraph(ISonicString* pStr, LPVOID);
	void ShowResult(ISonicString* pStr, LPVOID);

	CString m_cstrFileALocation;
	CString m_cstrFileBLocation;
	CString m_cstrKBDir;
	CString m_cstrLogFileLocation;
	CString m_cstrReportLocation;
	PCDControler* m_controler;

	BOOL startEngine();
	void RestoreConfig(ISonicString* pStr, LPVOID);
	void OpenFileA(ISonicString* pStr, LPVOID);
	void OpenFileB(ISonicString* pStr, LPVOID);
	void CloseApp(ISonicString* pStr, LPVOID);

	void InitWindowGently();
	void ShowWindowGently();
	void DrawWindowGently(int nTrans);
	void HideWindowGently();
	int m_iTrans;

	void InitScaleWindowGently();
	void ShowScaleWindowGently();
	void ClipScaleWindowGently(int iX1, int iY1, int iX2, int iY2, int iStep);
	void DrawScaleWindowGently(HDC hDC, int nTrans, int nScale);
	void HideScaleWindowGently();
	int m_iScaleDisp;
	int m_iScaleDispV;
	int m_iScaleTrans;
	int m_iScaleTransV;
	int m_iWndMainX, m_iWndMainY;
	CxImage m_cimgWndMain;
	CxImage m_cimgWndMainBuffer[31];
	HBITMAP m_hbmpWndMainBuffer[31];
	RECT m_rctWndMain;
	RECT m_rctWndMainMax;
	HDC m_hTopDC;
	float m_fWndMainRatio;
	int m_iScaleWindowPhase;

	CDC m_memDC;
	//CVisualPCDAboutDlg* m_dlgAbout;

	CString m_strKBDir;

	//void RenderImage(ISonicPaint * pPaint, LPVOID);

// Dialog Data
	//{{AFX_DATA(CVisualPCDDlg)
	enum { IDD = IDD_VISUALPCD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPCDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVisualPCDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//LRESULT CALLBACK 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VisualPCDDLG_H__B5402AA5_2090_46A4_B843_BA5E189067CB__INCLUDED_)
