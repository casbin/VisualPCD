// VisualPCDAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "visualpcd.h"

#include "VisualPCDAboutDlg.h"
#include "VisualPCDDlg.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CVisualPCDDlg* pAboutParentThis;

CVisualPCDAboutDlg* pAboutThis;
ISonicWndEffect* pAboutEffect;
CString* pAboutLocation;

#define FADEIN 0
#define FADEOUT 1

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDAboutDlg dialog


CVisualPCDAboutDlg::CVisualPCDAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVisualPCDAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualPCDAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//InitWindow();

	pAboutParentThis = (CVisualPCDDlg*) pParent;
}


void CVisualPCDAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualPCDAboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVisualPCDAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CVisualPCDAboutDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDAboutDlg message handlers

BOOL CVisualPCDAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	InitWindow();
	InitWindowGently();
	ShowWindowGently();
	
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVisualPCDAboutDlg::InitPointer()
{
	pAboutThis = this;
	pAboutLocation = pAboutParentThis->m_pLocation;
}


void CVisualPCDAboutDlg::InitWindow()
{
	
	this->SetWindowText("VisualPCD - ²ßÂÔ³åÍ»¼ì²â¹¤¾ß");
	pStrAboutTitle = GetSonicUI()->CreateString();
	pStrAboutTitle->Format("VisualPCD - ²ßÂÔ³åÍ»¼ì²â¹¤¾ß");

	SetWindowLong(m_hWnd, GWL_EXSTYLE, 0x00080000);//WS_EX_LAYERED);
	
	
	pImgWndAbout = GetSonicUI()->CreateImage();
	pImgWndAbout->Load(*pAboutLocation + "res\\wnd-about.png");
	pStrWndAbout = GetSonicUI()->CreateString();
	pStrWndAbout->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='', animation=30/", pImgWndAbout->GetObjectId(),  
		pImgWndAbout->GetObjectId(),  pImgWndAbout->GetObjectId());
	//pStrWndAbout->Delegate(DELEGATE_EVENT_CLICK, NULL, NULL, CVisualPCDAboutDlg::CloseWindow);

	pStrAboutInfo = GetSonicUI()->CreateString();
	pStrAboutInfo->Format("VisualPCD v1.1 by Veotax");

	pStrAboutClose = GetSonicUI()->CreateString();
	pStrAboutClose->Format("¹Ø±Õ");


	pAboutEffect = GetSonicUI()->CreateWndEffect();
	pAboutEffect->Attach(GetSafeHwnd(), TRUE);
	pAboutEffect->EnableWholeDrag(TRUE);
	pAboutEffect->SetShapeByImage(pImgWndAbout);
	
}

void CVisualPCDAboutDlg::OnPaint() 
{
	CPaintDC dc(this);
	///////////////////////////////////////////////////////////////////////
	
	pStrAboutInfo->TextOut(dc, 20, 250, m_hWnd);
	pStrAboutClose->TextOut(dc, 20, 230, m_hWnd);

	CDialog::OnPaint();

}

void CVisualPCDAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CVisualPCDAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HideWindowGently();
	CDialog::OnLButtonDown(nFlags, point);
}

void CVisualPCDAboutDlg::CloseWindow()
{
	::EndDialog(pAboutThis->m_hWnd, 0);
}

void CVisualPCDAboutDlg::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	switch (nTimerid)
	{
	case FADEIN:
		if (pAboutThis->m_iTrans < 255)
		{
			pAboutThis->m_iTrans += 40;
			if (pAboutThis->m_iTrans >= 255)
			{
				pAboutThis->DrawWindowGently(255);
			}
			else
			{
				pAboutThis->DrawWindowGently(pAboutThis->m_iTrans);
			}
		}
		else
		{
			pAboutThis->m_iTrans = 0;
			::KillTimer(pAboutThis->m_hWnd, FADEIN);
		}
		break;
	case FADEOUT:
		if (pAboutThis->m_iTrans > 0)
		{
			pAboutThis->m_iTrans -= 40;
			if (pAboutThis->m_iTrans <= 0)
			{
				pAboutThis->DrawWindowGently(0);
			}
			else
			{
				pAboutThis->DrawWindowGently(pAboutThis->m_iTrans);
			}
		}
		else
		{
			//pAboutThis->m_iTrans = 0;
			::KillTimer(pAboutThis->m_hWnd, FADEOUT);
			pAboutThis->CloseWindow();
		}
		break;
	default:
		break;
	}
}

void CVisualPCDAboutDlg::InitWindowGently()
{
	m_iTrans = 0;
	pAboutEffect->SetLayeredAttributes(NULL, 0, 2);
}

void CVisualPCDAboutDlg::ShowWindowGently()
{
	::SetTimer(m_hWnd, FADEIN, 20, (TIMERPROC) CVisualPCDAboutDlg::TimerProc);
}

void CVisualPCDAboutDlg::DrawWindowGently(int nTrans)
{
	pAboutEffect->SetLayeredAttributes(NULL, nTrans, 2);
}

void CVisualPCDAboutDlg::HideWindowGently()
{
	pAboutThis->m_iTrans = 255;
	::SetTimer(pAboutThis->m_hWnd, FADEOUT, 20, (TIMERPROC) CVisualPCDAboutDlg::TimerProc);
}