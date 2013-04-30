// VisualPCDResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPCD.h"
#include "VisualPCDDlg.h"
#include "VisualPCDResultDlg.h"

#include <windows.h>

#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED 0x00080000
#endif

#ifndef AC_SRC_ALPHA
#define AC_SRC_ALPHA 0x01
#endif

#ifndef ULW_ALPHA
#define ULW_ALPHA 0x00000002
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CVisualPCDDlg* pResultParentThis;

CVisualPCDResultDlg* pResultThis;
ISonicWndEffect* pResultEffect;
CString* pResultLocation;

#define FADEIN 0
#define FADEOUT 1

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDResultDlg dialog


CVisualPCDResultDlg::CVisualPCDResultDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CVisualPCDResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualPCDResultDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pResultParentThis = (CVisualPCDDlg*) pParent;
}


void CVisualPCDResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualPCDResultDlg)
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVisualPCDResultDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CVisualPCDResultDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDResultDlg message handlers

BOOL CVisualPCDResultDlg::OnInitDialog()
{
	CBitmapDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	
	//////////////////////////////////////////////////////////////////////////
	//::ShowWindow(m_hWnd, SW_HIDE);
	//SetLayeredWindowAttributes(m_hWnd, NULL, 0, LWA_ALPHA);
	//::AnimateWindow(m_hWnd, 1000, AW_HIDE);
	
	InitPointer();
	InitButton();
	InitWindow();
	InitControl();
	InitEdit();
	


	InitWindowGently();
	ShowWindowGently();

	
	
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVisualPCDResultDlg::InitPointer()
{
	pResultThis = this;
	pResultLocation = pResultParentThis->m_pLocation;
	//pResultParentThis->EnableWindow(TRUE);
}


void CVisualPCDResultDlg::InitWindow()
{
	
	this->SetWindowText("策略冲突检测报告");
	pStrResultTitle = GetSonicUI()->CreateString();
	pStrResultTitle->Format("the analysis report of conflict");//策略冲突检测报告");
	//SetWindowLong(m_hWnd, GWL_EXSTYLE, 0x00080000);//WS_EX_LAYERED);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if(hInst)
	{ 
		typedef BOOL (WINAPI *ShowLayer)(HWND,COLORREF,BYTE,DWORD); 
		ShowLayer fun = NULL;
		// 读取函数指针
		fun = (ShowLayer)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		//ShowLayer有自定义类型的成分 实质上是
		//SetLayeredWindowAttributes = (lpfnSetLayeredWindowAttributes)
		//GetProcAddress(hUser32, "SetLayeredWindowAttributes"); 
		if (fun)
			fun(m_hWnd, RGB(255, 0, 255), 254, 3);
		FreeLibrary(hInst); 
	}

	//SetLayeredWindowAttributes();
	
	pImgWndResult = GetSonicUI()->CreateImage();
	pImgWndResult->Load(*pResultLocation + "res\\wnd-graph.bmp");

	//pStrWndResult = GetSonicUI()->CreateString();
	//pStrWndResult->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='', animation=30/", pImgWndResult->GetObjectId(),  
	//	pImgWndResult->GetObjectId(),  pImgWndResult->GetObjectId());

	
	pResultEffect = GetSonicUI()->CreateWndEffect();

	//pResultEffect->Attach(pResultThis->GetSafeHwnd(), TRUE);
	//pResultEffect->SetShapeByImage(pImgWndResult, RGB(0, 0, 0));

	pResultEffect->Attach(pResultThis->GetSafeHwnd(), FALSE);
	//pResultEffect->SetShapeByImage(pImgWndResult, RGB(255, 0, 255));
	pResultEffect->EnableWholeDrag(TRUE);


	LoadBitmap(NULL, *pResultLocation + "res\\wnd-graph.bmp");
	SetTransparent(TRUE);
	SetTransColor(RGB(255, 0, 255));


	//RECT rectParent;
	//::GetWindowRect(pResultParentThis->m_hWnd, &rectParent);
	//RECT rectResult = {rectParent.left + 350, rectParent.top + 300, 100, 100};
	//::MoveWindow(this->m_hWnd, rectParent.left + 350, rectParent.top + 225, pImgWndResult->GetWidth(), pImgWndResult->GetHeight(), TRUE);

	RECT rectParent;
	::GetWindowRect(pResultParentThis->m_hWnd, &rectParent);
	//RECT rectResult = {rectParent.left + 350, rectParent.top + 300, 100, 100};
	::MoveWindow(this->m_hWnd, rectParent.right + 10, rectParent.bottom - pImgWndResult->GetHeight(), pImgWndResult->GetWidth(), pImgWndResult->GetHeight(), TRUE);
	

}

void CVisualPCDResultDlg::InitControl()
{
	RECT rect = {20, 40, 354, 290};
	m_editResult.MoveWindow(&rect, FALSE);
	m_editResult.m_rcClient.SetRect(0, 0, rect.right - rect.left, rect.bottom - rect.top);
}

void CVisualPCDResultDlg::InitEdit()
{
	ShowReport();

	//m_editResult.m_bHover = TRUE;
	//m_editResult.Invalidate();
}

void CVisualPCDResultDlg::InitButton()
{
	pImgBtnClose = GetSonicUI()->CreateImage();
	pImgBtnClose->Load(*pResultLocation + "res\\btn-close.bmp");
	pImgBtnClose->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseHover = GetSonicUI()->CreateImage();
	pImgBtnCloseHover->Load(*pResultLocation + "res\\btn-close-hover.bmp");
	pImgBtnCloseHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseClick = GetSonicUI()->CreateImage();
	pImgBtnCloseClick->Load(*pResultLocation + "res\\btn-close-click.bmp");
	pImgBtnCloseClick->SetColorKey(RGB(255, 0, 255));

	pStrBtnClose = GetSonicUI()->CreateString();
	pStrBtnClose->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='关闭', animation=30/", pImgBtnClose->GetObjectId(), pImgBtnCloseHover->GetObjectId(), 	pImgBtnCloseClick->GetObjectId());
	pStrBtnClose->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDResultDlg::OnClose);
}

void CVisualPCDResultDlg::OnPaint() 
{
	CPaintDC dc(this);
	//m_editResult.OnNcPaint();

	pStrResultTitle->TextOut(dc, 10, 6);

	pStrBtnClose->TextOut(dc, 330, 0, pResultThis->m_hWnd);

	CBitmapDialog::OnPaint();
}

void CVisualPCDResultDlg::OnOK() 
{
	// TODO: Add extra validation here
	CBitmapDialog::OnOK();
}

void CVisualPCDResultDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//HideWindowGently();
	CBitmapDialog::OnLButtonDown(nFlags, point);
}

void CVisualPCDResultDlg::OnClose(ISonicString* pStr, LPVOID)
{
	pResultParentThis->m_iProgress = 0;
	RECT rect = {pResultParentThis->m_iProgressX + 1, pResultParentThis->m_iProgressY + 1, 
		pResultParentThis->m_iProgressX + 1 + 238, pResultParentThis->m_iProgressY + 1 + 11};
	pResultParentThis->InvalidateRect(&rect);
	pResultThis->HideWindowGently();
}

void CVisualPCDResultDlg::CloseWindow()
{
	::EndDialog(pResultThis->m_hWnd, 0);
}

void CVisualPCDResultDlg::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	switch (nTimerid)
	{
	case FADEIN:
		if (pResultThis->m_iTrans < 255)
		{
			pResultThis->m_iTrans += 40;
			if (pResultThis->m_iTrans >= 255)
			{
				pResultThis->DrawWindowGently(255);
			}
			else
			{
				pResultThis->DrawWindowGently(pResultThis->m_iTrans);
			}
		}
		else
		{
			pResultThis->m_iTrans = 0;
			::KillTimer(pResultThis->m_hWnd, FADEIN);
		}
		break;
	case FADEOUT:
		if (pResultThis->m_iTrans > 0)
		{
			pResultThis->m_iTrans -= 40;
			if (pResultThis->m_iTrans <= 0)
			{
				pResultThis->DrawWindowGently(0);
			}
			else
			{
				pResultThis->DrawWindowGently(pResultThis->m_iTrans);
			}
		}
		else
		{
			//pResultThis->m_iTrans = 0;
			::KillTimer(pResultThis->m_hWnd, FADEOUT);
			pResultThis->CloseWindow();
		}
		break;
	default:
		break;
	}
}

void CVisualPCDResultDlg::InitWindowGently()
{
	m_iTrans = 0;
	pResultEffect->SetLayeredAttributes(NULL, 0, 2);
}

void CVisualPCDResultDlg::ShowWindowGently()
{
	::SetTimer(m_hWnd, FADEIN, 20, (TIMERPROC) CVisualPCDResultDlg::TimerProc);
}

void CVisualPCDResultDlg::DrawWindowGently(int nTrans)
{
	pResultEffect->SetLayeredAttributes(NULL, nTrans, 2);
}

void CVisualPCDResultDlg::HideWindowGently()
{
	pResultThis->m_iTrans = 255;
	::SetTimer(pResultThis->m_hWnd, FADEOUT, 20, (TIMERPROC) CVisualPCDResultDlg::TimerProc);
}

void CVisualPCDResultDlg::ShowReport()
{
	vector<string> nstrReport = pResultParentThis->m_controler->getReport();
	string strReport;
	
	vector<string>::iterator iter;
	for (iter = nstrReport.begin(); iter < nstrReport.end(); iter ++)
	{
		strReport += (*iter);
		strReport += "\r\n";
	}
	
	m_editResult.SetWindowText(strReport.c_str());
	::PostMessage(m_editResult.m_hWnd, EM_SETSEL, 0, 0);

	//m_editResult.SetSel(0,0);
}
