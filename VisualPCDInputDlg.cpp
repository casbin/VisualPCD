// VisualPCDInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPCD.h"
#include "VisualPCDDlg.h"
#include "VisualPCDInputDlg.h"

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

CVisualPCDDlg* pInputParentThis;

CVisualPCDInputDlg* pInputThis;
ISonicWndEffect* pInputEffect;
CString* pInputLocation;

#define FADEIN 0
#define FADEOUT 1

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDInputDlg dialog


CVisualPCDInputDlg::CVisualPCDInputDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CVisualPCDInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualPCDInputDlg)
	//}}AFX_DATA_INIT
	pInputParentThis = (CVisualPCDDlg*) pParent;
}


void CVisualPCDInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualPCDInputDlg)
	DDX_Control(pDX, IDC_EDIT_INPUT2, m_editInput2);
	DDX_Control(pDX, IDC_EDIT_INPUT1, m_editInput1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVisualPCDInputDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CVisualPCDInputDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDInputDlg message handlers

BOOL CVisualPCDInputDlg::OnInitDialog()
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

void CVisualPCDInputDlg::InitPointer()
{
	pInputThis = this;
	pInputLocation = pInputParentThis->m_pLocation;
	//pResultParentThis->EnableWindow(TRUE);
}


void CVisualPCDInputDlg::InitWindow()
{
	
// 	this->SetWindowText("策略文件内容");
// 	pStrInputTitle = GetSonicUI()->CreateString();
// 	pStrInputTitle->Format("策略文件内容");
// 
// 	pStrStatic1 = GetSonicUI()->CreateString();
// 	pStrStatic1->Format("策略文件1内容：");
// 	pStrStatic2 = GetSonicUI()->CreateString();
// 	pStrStatic2->Format("策略文件2内容：");
	this->SetWindowText("Content of Policy Files");
	pStrInputTitle = GetSonicUI()->CreateString();
	pStrInputTitle->Format("Content of Policy Files");
	
	pStrStatic1 = GetSonicUI()->CreateString();
	pStrStatic1->Format("Content of Policy File 1: ");
	pStrStatic2 = GetSonicUI()->CreateString();
	pStrStatic2->Format("Content of Policy File 1");

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
	
	pImgWndInput = GetSonicUI()->CreateImage();
	pImgWndInput->Load(*pInputLocation + "res\\wnd-input.bmp");
	
	//pStrWndResult = GetSonicUI()->CreateString();
	//pStrWndResult->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='', animation=30/", pImgWndResult->GetObjectId(),  
	//	pImgWndResult->GetObjectId(),  pImgWndResult->GetObjectId());
	
	
	pInputEffect = GetSonicUI()->CreateWndEffect();
	
	//pInputEffect->Attach(pInputThis->GetSafeHwnd(), TRUE);
	//pInputEffect->SetShapeByImage(pImgWndResult, RGB(0, 0, 0));
	
	pInputEffect->Attach(pInputThis->GetSafeHwnd(), FALSE);
	//pInputEffect->SetShapeByImage(pImgWndResult, RGB(255, 0, 255));
	pInputEffect->EnableWholeDrag(TRUE);
	
	
	LoadBitmap(NULL, *pInputLocation + "res\\wnd-input.bmp");
	SetTransparent(TRUE);
	SetTransColor(RGB(255, 0, 255));
	
	
	RECT rectParent;
	::GetWindowRect(pInputParentThis->m_hWnd, &rectParent);
	::MoveWindow(this->m_hWnd, rectParent.left - pImgWndInput->GetWidth() - 10, rectParent.top, pImgWndInput->GetWidth(), pImgWndInput->GetHeight(), TRUE);
	
	
	
}

void CVisualPCDInputDlg::InitControl()
{
	RECT rect1 = {20, 60, 354, 400};
	m_editInput1.MoveWindow(&rect1, FALSE);
	m_editInput1.m_rcClient.SetRect(0, 0, rect1.right - rect1.left, rect1.bottom - rect1.top);

	RECT rect2 = {20, 450, 354, 570};
	m_editInput2.MoveWindow(&rect2, FALSE);
	m_editInput2.m_rcClient.SetRect(0, 0, rect2.right - rect2.left, rect2.bottom - rect2.top);
}

void CVisualPCDInputDlg::InitEdit()
{
	ShowFile();
	
	//m_editResult.m_bHover = TRUE;
	//m_editResult.Invalidate();
}

void CVisualPCDInputDlg::InitButton()
{
	pImgBtnClose = GetSonicUI()->CreateImage();
	pImgBtnClose->Load(*pInputLocation + "res\\btn-close.bmp");
	pImgBtnClose->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseHover = GetSonicUI()->CreateImage();
	pImgBtnCloseHover->Load(*pInputLocation + "res\\btn-close-hover.bmp");
	pImgBtnCloseHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseClick = GetSonicUI()->CreateImage();
	pImgBtnCloseClick->Load(*pInputLocation + "res\\btn-close-click.bmp");
	pImgBtnCloseClick->SetColorKey(RGB(255, 0, 255));
	
	pStrBtnClose = GetSonicUI()->CreateString();
	pStrBtnClose->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='关闭', animation=30/", pImgBtnClose->GetObjectId(), pImgBtnCloseHover->GetObjectId(), 	pImgBtnCloseClick->GetObjectId());
	pStrBtnClose->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDInputDlg::OnClose);
}

void CVisualPCDInputDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	pStrBtnClose->TextOut(dc, 330, 0, pInputThis->m_hWnd);

	pStrInputTitle->TextOut(dc, 10, 6, pInputThis->m_hWnd);
	pStrStatic1->TextOut(dc, 20, 40, pInputThis->m_hWnd);
	pStrStatic2->TextOut(dc, 20, 430, pInputThis->m_hWnd);

	CBitmapDialog::OnPaint();
	
	// Do not call CBitmapDialog::OnPaint() for painting messages
}

void CVisualPCDInputDlg::OnClose(ISonicString* pStr, LPVOID)
{
	pInputThis->HideWindowGently();
}

void CVisualPCDInputDlg::CloseWindow()
{
	::EndDialog(pInputThis->m_hWnd, 0);
}

void CVisualPCDInputDlg::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	switch (nTimerid)
	{
	case FADEIN:
		if (pInputThis->m_iTrans < 255)
		{
			pInputThis->m_iTrans += 40;
			if (pInputThis->m_iTrans >= 255)
			{
				pInputThis->DrawWindowGently(255);
			}
			else
			{
				pInputThis->DrawWindowGently(pInputThis->m_iTrans);
			}
		}
		else
		{
			pInputThis->m_iTrans = 0;
			::KillTimer(pInputThis->m_hWnd, FADEIN);
		}
		break;
	case FADEOUT:
		if (pInputThis->m_iTrans > 0)
		{
			pInputThis->m_iTrans -= 40;
			if (pInputThis->m_iTrans <= 0)
			{
				pInputThis->DrawWindowGently(0);
			}
			else
			{
				pInputThis->DrawWindowGently(pInputThis->m_iTrans);
			}
		}
		else
		{
			//pInputThis->m_iTrans = 0;
			::KillTimer(pInputThis->m_hWnd, FADEOUT);
			pInputThis->CloseWindow();
		}
		break;
	default:
		break;
	}
}

void CVisualPCDInputDlg::InitWindowGently()
{
	m_iTrans = 0;
	pInputEffect->SetLayeredAttributes(NULL, 0, 2);
}

void CVisualPCDInputDlg::ShowWindowGently()
{
	::SetTimer(m_hWnd, FADEIN, 20, (TIMERPROC) CVisualPCDInputDlg::TimerProc);
}

void CVisualPCDInputDlg::DrawWindowGently(int nTrans)
{
	pInputEffect->SetLayeredAttributes(NULL, nTrans, 2);
}

void CVisualPCDInputDlg::HideWindowGently()
{
	pInputThis->m_iTrans = 255;
	::SetTimer(pInputThis->m_hWnd, FADEOUT, 20, (TIMERPROC) CVisualPCDInputDlg::TimerProc);
}

void CVisualPCDInputDlg::ShowFile()
{

	string strFileALocation = pInputParentThis->m_cstrFileALocation;
	string strFileBLocation = pInputParentThis->m_cstrFileBLocation;

	XMLParser* parser = new XMLParser(strFileALocation, strFileBLocation);

	vector<string> nstrFileAQuints = parser->FileAQuintsToString();
	vector<string> nstrFileBQuints = parser->FileBQuintsToString();

	string strFileA;
	vector<string>::iterator iter;
	for (iter = nstrFileAQuints.begin(); iter < nstrFileAQuints.end(); iter ++)
	{
		strFileA += (*iter);
		strFileA += "\r\n";
	}
	m_editInput1.SetWindowText(strFileA.c_str());
	::PostMessage(m_editInput1.m_hWnd, EM_SETSEL, 0, 0);

	string strFileB;
	for (iter = nstrFileBQuints.begin(); iter < nstrFileBQuints.end(); iter ++)
	{
		strFileB += (*iter);
		strFileB += "\r\n";
	}
	m_editInput2.SetWindowText(strFileB.c_str());
	::PostMessage(m_editInput2.m_hWnd, EM_SETSEL, 0, 0);



	//m_editResult.SetSel(0,0);
	
}
