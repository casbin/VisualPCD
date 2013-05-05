// VisualPCDDlg.cpp : implementation file
//


#include "stdafx.h"
#include "VisualPCD.h"
#include "VisualPCDDlg.h"
#include "VisualPCDAboutDlg.h"
#include "VisualPCDInputDlg.h"
#include "VisualPCDGraphDlg.h"
#include "VisualPCDResultDlg.h"
#include "VisualPCDFileDlg.h"
#include "VisualPCDTransDlg.h"

#include <windows.h>
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PROGRESS_GLOW 0
#define PROGRESS 1
#define POPUPMENU 2
#define FADEIN 3
#define FADEOUT 4
#define ANTI_TWINKLE 5
#define SCALE_FADEIN 6
#define SCALE_FADEOUT 7
#define UPDATE_EDIT 8

CVisualPCDDlg* pThis;
ISonicWndEffect* pEffect;
CString* pLocation;
CVisualPCDTransDlg* dlgMainWndTrans;


void WINAPI GlobalOnMove(ISonicString * pStr, LPVOID);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDDlg dialog

CVisualPCDDlg::CVisualPCDDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CVisualPCDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualPCDDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_controler = NULL;
	//SetWindowLong(this->m_hWnd,GWL_EXSTYLE,0);


}

void CVisualPCDDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualPCDDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
}

BEGIN_MESSAGE_MAP(CVisualPCDDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CVisualPCDDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDDlg message handlers

BOOL CVisualPCDDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//pStr = GetSonicUI()->CreateString();
	//pStr->Format("/c=%x, a='http://hi.csdn.net/zskof', linkl=1, linkc=1, linkh=%x, font, font_height=14/点我打开链接2", RGB(0, 0, 255), RGB(255, 0, 0));

	//InvalidateRect(NULL, TRUE);

	//pPaint = GetSonicUI()->CreatePaint();
	//pPaint->Create(TRUE/*是否需要memDC*/, 300/*宽*/, 200/*高*/);
	//pPaint->Delegate(DELEGATE_EVENT_PAINT, NULL, *this, CVisualPCDDlg::RenderImage);

	

	m_iBtnJcFlag = 0;

//////////////////////////////////////////////////////////////////////////
	InitPointer();
	InitWindow();

	InitControl();
	InitButton();

	InitProgressBar();	
	InitPopupMenu();
	InitAbout();

	//pThis->ShowResult(NULL, NULL);

	InitWindowGently();
	ShowWindowGently();

	//InitScaleWindowGently();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVisualPCDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBitmapDialog::OnSysCommand(nID, lParam);
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVisualPCDDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CPaintDC dc(this);

		HDC hDC = dc.GetSafeHdc();
		HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
		GetWindowRgn(hrgn);
		CombineRgn(hrgn, hrgn, m_rgnMenu, RGN_DIFF);
		//CombineRgn(hrgn, hrgn, m_rgnMenuButton, RGN_DIFF);
		SelectClipRgn(hDC, hrgn);
		
///////////////////////////////////////////////////////////////////////
		pStrStatic1->TextOut(hDC, 30, 260, m_hWnd);
		pStrStatic2->TextOut(hDC, 30, 310, m_hWnd);
		pStrStatic3->TextOut(hDC, 140, 560, m_hWnd);
///////////////////////////////////////////////////////////////////////
		pStrBtnJc->TextOut(hDC, m_iBtnJcX, m_iBtnJcY, m_hWnd);
		pStrBtnJcText->TextOut(hDC, m_iBtnJcX + 20, m_iBtnJcY + 5, m_hWnd);

		pStrBtnXs->TextOut(hDC, m_iBtnXsX, m_iBtnXsY, m_hWnd);
		pStrBtnXsText->TextOut(hDC, m_iBtnXsX + 20, m_iBtnXsY + 5, m_hWnd);

		pStrBtnTs->TextOut(hDC, m_iBtnTsX, m_iBtnTsY, m_hWnd);
		pStrBtnTsText->TextOut(hDC, m_iBtnTsX + 7, m_iBtnTsY + 5, m_hWnd);

		pStrBtnMin->TextOut(hDC, 262, 0, m_hWnd);
		pStrBtnClose->TextOut(hDC, 287, 0, m_hWnd);
///////////////////////////////////////////////////////////////////////
		if (m_iMenuShadow == 0)
			pStrBtnMenu->TextOut(hDC, m_iMenuButtonX, m_iMenuButtonY, m_hWnd);
		else
			pStrBtnMenuShadow->TextOut(hDC, m_iMenuButtonX, m_iMenuButtonY, m_hWnd);
		pStrBtnMenuText->TextOut(hDC, m_iMenuButtonX + 16, m_iMenuButtonY + 5, m_hWnd);

		if (m_iKeepMenu == 1)
			KeepPopupMenu(hDC);
///////////////////////////////////////////////////////////////////////
		pStrTitle->TextOut(hDC, 80, 6, m_hWnd);
///////////////////////////////////////////////////////////////////////
		DrawProgressBar(hDC, m_iProgressX, m_iProgressY, m_iProgress);
///////////////////////////////////////////////////////////////////////	
		
		//pImgBtnMenu->Draw(dc, 20, 400);
		//pStrBtnJc->TextOut(dc, 20, 40, m_hWnd);


		//dc.BitBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, SRCCOPY); //将位图画到客户区上
		//dcBmp.SelectObject(pOldBmp);
		SelectClipRgn(hDC, NULL);
		DeleteObject(hrgn);
		//::ReleaseDC(m_hWnd, hDC);
		CBitmapDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVisualPCDDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
int CVisualPCDDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	RECT rect;
	CClientDC dc(this);
	int width = dc.GetDeviceCaps(HORZRES);
	int height = dc.GetDeviceCaps(VERTRES);
	GetWindowRect( &rect );
	width = ( width - ( rect.right - rect.left ))/2 ;
	height = (height - (rect.bottom - rect.top ))/2 ;
	MoveWindow( width , height , (rect.right - rect.left ) , (rect.bottom - rect.top ) ,true);
	
	 //淡入
	
	return 0;
}*/

CString CVisualPCDDlg::itos(int i)
{
	CString strTemp;
	strTemp.Format(_T("%d"), i);
	return strTemp;
}

static UINT ControlerThread(LPVOID pParam)
{
	pThis->m_controler = new PCDControler();
	//pThis->m_controler->redirectTo(FILE_OUTPUT);
	pThis->StartProgressBar();

	string strFileALocation = pThis->m_cstrFileALocation;
	string strFileBLocation = pThis->m_cstrFileBLocation;
	string strKBDir = pThis->m_cstrKBDir;
	string strLogFileLocation = pThis->m_cstrLogFileLocation;
	
	pThis->m_controler->setPolicyFiles(strFileALocation, strFileBLocation);
	pThis->m_controler->setDefaultKnowledgeBase(strKBDir);
	pThis->m_controler->setLogFile(strLogFileLocation);
	DWORD dwTime = pThis->m_controler->implementDetection();

	pThis->m_edit3.SetWindowText(pThis->itos(dwTime));
	//pThis->m_controler->printReport();
	//pThis->m_controler->releaseResource();
	
	//pThis->ShowResult(NULL, NULL);

	return 0;
}

void CVisualPCDDlg::OnMove(ISonicString* pStr, LPVOID)
{
	//pThis->ShowScaleWindowGently();

	/*
	HWND hWindow;
	char pszWindowTitle[] = "RacerPro";
	hWindow = ::FindWindow(NULL, pszWindowTitle);
	if (hWindow == NULL)
	{
		::MessageBox(pThis->m_hWnd, "请打开推理引擎！", "运行出现错误", MB_OK);
		return;
	}
	*/

	pThis->m_edit1.GetWindowText(pThis->m_cstrFileALocation);
	pThis->m_edit2.GetWindowText(pThis->m_cstrFileBLocation);

	if (!FileExist(pThis->m_cstrFileALocation))
	{
		::MessageBox(pThis->m_hWnd, "策略文件1不存在！", "运行出现错误", MB_OK);
		return;
	}
	else if (!FileExist(pThis->m_cstrFileBLocation))
	{
		::MessageBox(pThis->m_hWnd, "策略文件2不存在！", "运行出现错误", MB_OK);
		return;
	}


	CWinThread *m_pThread;
	m_pThread = AfxBeginThread(ControlerThread, NULL, 0);

/*
	if (pThis->m_iBtnJcFlag == 1)
	{
		::KillTimer(pThis->m_hWnd, 0);
		pThis->m_iBtnJcFlag = 0;
	}
	else
	{
		::SetTimer(pThis->m_hWnd, 0, 30, (TIMERPROC) CVisualPCDDlg::TimerProc);
		::SetTimer(pThis->m_hWnd, 1, 10, (TIMERPROC) CVisualPCDDlg::TimerProc);
		pThis->m_iBtnJcFlag = 1;
	}

	RECT rect;
	pThis->GetWindowRect(&rect);
	rect.left -= 20;
	rect.top -= 20;
	rect.right += 20;
	rect.bottom += 20;*/
/////////////////////////////////////////////////////////////////////////////////////
	
	//pEffect->EnableTransform(TRUE, 0, &rect, 10);
	
	
	//RECT rect = {0, 0, 1, 1};
	//((ISonicWndEffect*) a_pEffect)->EnableTransform(TRUE, 0, &rect, 50);
	
	//((ISonicWndEffect*) a_pEffect)->SetLayeredAttributes(0, 128, 2);

	/*
	RECT rect;
	AfxGetMainWnd()->GetWindowRect(&rect);
	POINT ptFrom;
	ptFrom.x = rect.left;
	ptFrom.y = rect.top;
	POINT ptTo = {0, 0};

	((ISonicWndEffect*) a_pEffect)->SlideShow(0, ptFrom, ptTo, 15, FALSE);*/

	//((ISonicImage*) a_pEffect)->Slide

	//CWnd* cWnd = FindWindow("#32770", "策略冲突检测工具");
	//RECT rect;
	//cWnd->GetWindowRect(&rect);

	//AnimateWindow(((CVisualPCDDlg*) a_pEffect)->m_hWnd, 1000, AW_SLIDE | AW_HIDE);
	
}

void CVisualPCDDlg::OnDisplay(ISonicString* pStr, LPVOID)
{
	pThis->ShowInput(NULL, NULL);
}

void CVisualPCDDlg::FadeOut(ISonicString* pStr, LPVOID a_iBtnMinCloseFlag)
{
	
	if ((int) a_iBtnMinCloseFlag == 0)
	{
		pEffect->ShowGently(0, 0, 70);
		pEffect->Delegate(DELEGATE_EVENT_SHOWGENTLY_OVER, NULL, pThis, CVisualPCDDlg::OnMinimize);
	}
	else if ((int) a_iBtnMinCloseFlag == 1)
	{
		pEffect->MoveGently(0, 0, 70);
		pEffect->ShowGently(0, 0, 70);
		pEffect->SetLayeredAttributes(NULL, 128, 2);
		pEffect->Delegate(DELEGATE_EVENT_SHOWGENTLY_OVER, NULL, pThis, CVisualPCDDlg::OnClose);
	}
	else
	{
		MessageBox("error.");
	}
}

void CVisualPCDDlg::OnMinimize(ISonicString* pStr, LPVOID)
{
	pEffect->ShowGently(1, 1, 0);
	((CVisualPCDDlg*) pThis)->ShowWindow(SW_MINIMIZE);
}

void CVisualPCDDlg::OnClose(ISonicString* pStr, LPVOID)
{
	PostQuitMessage(0);
	return;

	HWND hWindow;
	char pszWindowTitle[] = "RacerPro";
	ULONG nProcessID;
	HANDLE hProcessHandle;

	hWindow = ::FindWindow(NULL, pszWindowTitle);
    ::GetWindowThreadProcessId(hWindow, &nProcessID);
    hProcessHandle = ::OpenProcess( PROCESS_TERMINATE, FALSE, nProcessID);
    ::TerminateProcess(hProcessHandle, 4);
	PostQuitMessage(0);
}

void CVisualPCDDlg::GetTabButtonRect()
{

	/*
	HWND  hStatus=::FindWindow("Shell_TrayWnd",NULL);  
	if  (hStatus==NULL)  
	{  
		//cout<<"Get Shell_TrayWnd error!\n";  
		//return -1;  
	}  
	HWND  hNotify=FindWindowEx(hStatus,NULL,"TrayNotifyWnd",NULL); 
	if  (hNotify==NULL)  
	{  
		//cout<<"Get TrayNotifyWnd error!\n";  
		//return -1;  
	}  
	HWND  hNotify1=FindWindowEx(hStatus,hNotify,"ReBarWindow32",NULL);
	if  (hNotify==NULL)  
	{  
		//cout<<"Get ReBarWindow32 error!\n";  
		//return -1;  
	} 
	hNotify1=FindWindowEx(hNotify1,NULL,"MSTaskSwWClass",NULL);
	
	
	
	HWND  hNotify1_0=FindWindowEx(hNotify1,NULL,"ToolBarWindow32",NULL);
	if  (hNotify1_0==NULL)   
	{  
		//cout<<"Get ToolBarWindow32 error!\n";  
		//return -1;  
		int a = 1;
	}  

	//-------------------以上是得到任务栏句柄
	DWORD  pid = 0;  
	GetWindowThreadProcessId(hNotify1_0,&pid);  
	if  (pid==NULL)  
	{  
		//cout<<"Get pid error!\n";  
		//return -1;  
	}   
	
	HANDLE  hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_ALL_ACCESS,true,pid);  
	if  (hProcess==NULL)  
	{  
		//cout<<"Get hd error!\n";  
		//return -1;  
	}  
	
	int  iNum=::SendMessage(hNotify1_0,TB_BUTTONCOUNT ,NULL,NULL);  //获取任务栏上图标个数
	
	unsigned long n = 0;  
	TBBUTTON  *pButton = new TBBUTTON;  
	CString  strInfo = _T("");  
	wchar_t  name[256] = {0};   
	
	TBBUTTON  BButton; 
	
	for(int i=0; i<iNum; i++)  
	{  
		::SendMessage(hNotify1_0,TB_GETBUTTON,i,(LPARAM)(&BButton));  
		ReadProcessMemory(hProcess,&BButton,pButton,sizeof(TBBUTTON),&n);   
		if  (pButton->iString != 0xffffffff)  
		{   
			try  
			{  
				ReadProcessMemory(hProcess,(void *)pButton->iString,name,255,&n); 
				//printf(":::: %d\n",pButton->iString);
			}  
			catch(...)  
			{  
			}      
			strInfo.Format("%d : %s\n",i+1,CString(name));  
			//cout<<strInfo<<endl;
		}
	} 
	CloseHandle(hProcess);
	delete pButton;
	//return 0;*/

	
	/*
	typedef HWND (WINAPI *PROCGETTASKMANWND)();
	PROCGETTASKMANWND GetTaskmanWindow;
	HMODULE hUser32 = GetModuleHandle("user32");
	GetTaskmanWindow = (PROCGETTASKMANWND) GetProcAddress(hUser32,"GetTaskmanWindow");  
	HWND TaskBarWnd = ::GetParent(GetTaskmanWindow()); 


	for(int j = 0; j < 50; j ++)
	{
		SIZE_T len = 256;//sizeof(RECT);
		TCHAR * ptb = new TCHAR[256];
		SIZE_T size;
		HWND tool = (HWND) TaskBarWnd;
		DWORD proID;
		GetWindowThreadProcessId(tool, &proID);
		HANDLE hPro = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE , NULL, proID);
		PVOID pBun = VirtualAllocEx(hPro, NULL, len, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		UINT buffer = len;
		DWORD si = ::SendMessage(tool, TB_GETBUTTONTEXT , (WPARAM)j, (LPARAM)pBun);
		ReadProcessMemory(hPro, pBun, (LPVOID)ptb, len, &size);
		VirtualFreeEx(hPro, pBun, len, MEM_DECOMMIT);
		delete ptb;
	}*/
}


/*
void CVisualPCDDlg::RenderImage(ISonicPaint * pPaint, LPVOID)
{
	if(pPaint->GetCurrentPaint() == NULL)
	{
		return;
	}
	HDC hdc = pPaint->GetCurrentPaint()->hdc;
	int x = pPaint->GetCurrentPaint()->x;
	int y = pPaint->GetCurrentPaint()->y;
	pStr->TextOut(hdc, 100, 100, m_hWnd);
}*/

void CVisualPCDDlg::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	CDC* pDC = pThis->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	//HDC hDC = pThis->GetDC()->GetSafeHdc();

	switch (nTimerid)
	{
	case PROGRESS_GLOW:
		if (pThis->m_iProgressGlow >238 + 70)
			pThis->m_iProgressGlow = 0;
		else
			pThis->m_iProgressGlow += 2;
		pThis->DrawProgressBarGlow(hDC, pThis->m_iProgressX, pThis->m_iProgressY, pThis->m_iProgressGlow);
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;

	case PROGRESS:
		pThis->m_iProgress = 2.38 * pThis->m_controler->getProgress();
		if (pThis->m_iProgress >= 238)
		{
			pThis->StopProgressBar();
		}
		pThis->InvalidateRect(&(pThis->m_rectProgress), 0);
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;

	case POPUPMENU:
		if (pThis->m_iPopup >= 0 && pThis->m_iIsPopdown == 0)
		{
			pThis->m_iPopout ++;
			pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX, pThis->m_iMenuCutY, 
				pThis->m_iMenuCutX, pThis->m_iMenuCutY, pThis->m_iPopout);
			if (pThis->m_iPopout == 4)
			{
				pThis->m_iIsPopdown = 1;
			}
		}
		else if (pThis->m_iPopup >= 0 && pThis->m_iIsPopdown == 1 && pThis->m_iPopout > 0)
		{
			pThis->m_iPopout --;
			pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX, pThis->m_iMenuCutY, 
				pThis->m_iMenuCutX, pThis->m_iMenuCutY, pThis->m_iPopout);
		}
		else if (pThis->m_iPopup >= 0 && pThis->m_iPopout <= 0)
		{
			pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX, pThis->m_iMenuCutY, 
				pThis->m_iMenuCutX, pThis->m_iMenuCutY, 0);
			::KillTimer(pThis->m_hWnd, POPUPMENU);
			pThis->m_iPopup = 0;
			pThis->m_iPopupA = 1;
			pThis->m_iKeepMenu = 1;
			pThis->m_iIsPopdown = 0;
			pThis->m_iPopout = 0;
			
			//pThis->pImgPum->Delegate(DELEGATE_EVENT_MOUSELEAVE, (void*) 1, NULL, CVisualPCDDlg::ClearPopupMenu);
		}
		else
		{
			pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX + pThis->m_iPopup, pThis->m_iMenuCutY + pThis->m_iPopup, 
				pThis->m_iMenuCutX, pThis->m_iMenuCutY);
			pThis->m_iPopupA += 1;
			pThis->m_iPopup += pThis->m_iPopupA;
		}
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;

	case FADEIN:
		if (pThis->m_iTrans < 255)
		{
			pThis->m_iTrans += 40;
			if (pThis->m_iTrans >= 255)
			{
				pThis->DrawWindowGently(255);
			}
			else
			{
				pThis->DrawWindowGently(pThis->m_iTrans);
			}
		}
		else
		{
			pThis->m_iTrans = 0;
			::KillTimer(pThis->m_hWnd, FADEIN);
		}
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;

	case FADEOUT:
		if (pThis->m_iTrans > 0)
		{
			pThis->m_iTrans -= 40;
			if (pThis->m_iTrans <= 0)
			{
				pThis->DrawWindowGently(0);
			}
			else
			{
				pThis->DrawWindowGently(pThis->m_iTrans);
			}
		}
		else
		{
			//pThis->m_iTrans = 0;
			::KillTimer(pThis->m_hWnd, FADEOUT);
			pThis->CloseWindow();
		}
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;

	case ANTI_TWINKLE:
		pThis->InvalidateRect(&(pThis->m_rctBtnJc));
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;

	case SCALE_FADEIN:
		if (pThis->m_iScaleWindowPhase == 0)
		{
			pThis->m_iScaleDisp += 2;
			if (pThis->m_iScaleDisp >= 10)
			{
				pThis->m_iScaleDisp = 10;
				pThis->m_iScaleWindowPhase = 1;
			}

			pThis->m_iScaleTrans += (int) ((FLOAT)255 / 30);
			pThis->DrawScaleWindowGently(hDC, pThis->m_iScaleTrans, pThis->m_iScaleDisp);
		}
		else if (pThis->m_iScaleWindowPhase == 1)
		{

			int iY = 10 - pThis->m_iScaleDisp;
			int iX = (int) (iY * pThis->m_fWndMainRatio);
			pThis->ClipScaleWindowGently(iX, iY, pThis->m_rctWndMainMax.right - pThis->m_rctWndMainMax.left - iX,
				pThis->m_rctWndMainMax.bottom - pThis->m_rctWndMainMax.top - iY, 10);
			pThis->m_iScaleDisp -= 2;
			if (pThis->m_iScaleDisp <= 0)
			{
				pThis->m_iScaleDisp = 0;
				pThis->m_iScaleTrans = 255;
				::KillTimer(pThis->m_hWnd, SCALE_FADEIN);
				pThis->DrawScaleWindowGently(hDC, pThis->m_iScaleTrans, pThis->m_iScaleDisp);
				//pThis->m_iScaleDisp = -10;
				pThis->m_iScaleTrans = 0;
				pThis->m_iScaleWindowPhase = 0;
			}
			else
			{
				pThis->m_iScaleTrans += (int) ((FLOAT)255 / 30);
				pThis->DrawScaleWindowGently(hDC, pThis->m_iScaleTrans, pThis->m_iScaleDisp);
			}
			
		}
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;
	case UPDATE_EDIT:
		pThis->OnChangeEdit1();
		pThis->OnChangeEdit2();
		pThis->ReleaseDC(pDC);
		//::ReleaseDC(pThis->m_hWnd, hDC);
		break;
	}
}

void CVisualPCDDlg::UpdateShadow(void)
{
	UpdateData();
	m_Shadow.SetSize(0);//m_nSize);
	m_Shadow.SetSharpness(5);//m_nSharpness);
	m_Shadow.SetDarkness(150);//m_nDarkness);
	m_Shadow.SetPosition(5, 5);//m_nPosX, m_nPosY);
	m_Shadow.SetColor(RGB(0, 0, 0));//m_nColorR, m_nColorG, m_nColorB));
}

BOOL CVisualPCDDlg::FolderExist(CString strPath)
{
    WIN32_FIND_DATA wfd;
    BOOL rValue = FALSE;
    HANDLE hFind = FindFirstFile(strPath, &wfd);
    if ((hFind!=INVALID_HANDLE_VALUE) &&
		(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
    {
        rValue = TRUE;
    }
    FindClose(hFind);
    return rValue;
}

BOOL CVisualPCDDlg::FileExist(CString strFileName)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(strFileName, &FindFileData);
	
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	else
	{
		FindClose(hFind);
		return true;
	}
	return false;
}

CString CVisualPCDDlg::initKBDir()
{
	CString cstrDir;
	TCHAR cBuffer[260];
	GetCurrentDirectory(MAX_PATH, cBuffer);
	CString cstrPath(cBuffer);
	if (FolderExist(cstrPath + _T("\\kb")))
	{
		cstrDir = cstrPath;
	}
	else
	{
		int nCount = cstrPath.ReverseFind(_T('\\'));
		cstrPath.Delete(nCount, cstrPath.GetLength() - nCount);
		
		if (FolderExist(cstrPath + _T("\\kb")))
		{
			cstrDir = cstrPath;
		}
		else
		{
			//MyMessageBox_Error(_T("initInputDir Error"), _T("Error"));
			return _T("");
		}
	}
	cstrDir += _T("\\kb\\");
	return cstrDir;
}

void CVisualPCDDlg::InitPointer()
{
	pThis = (CVisualPCDDlg*) AfxGetMainWnd();
	char cBuffer[260];
	GetCurrentDirectory(MAX_PATH, cBuffer);
	CString cstrPath(cBuffer);
	if (FolderExist(cstrPath + "\\res"))
	{
		if (pLocation)
		{
			delete pLocation;
		}
		pLocation = new CString(cstrPath);
	}
	else
	{
		//cstrPath.ReleaseBuffer(10);
		int nCount = cstrPath.ReverseFind('\\');
		cstrPath.Delete(nCount, cstrPath.GetLength() - nCount);//.ReleaseBuffer(30);
		
		if (FolderExist(cstrPath + "\\res"))
		{
			if (pLocation)
			{
				delete pLocation;
			}
			pLocation = new CString(cstrPath);
		}
		else
		{
			MessageBox("FolderExist error.");
			exit(0);
		}
	}

	//pLocation = new CString("F:\\Labs\\MyProjects\\VC6Projects\\VisualPCD\\");
	
	*pLocation = *pLocation + '\\';
	m_pLocation = pLocation;

	m_cstrKBDir = *m_pLocation + "kb\\";
	m_cstrFileALocation = *m_pLocation +"examples\\PolicyFileA-20111115.xml";
	m_cstrFileBLocation = *m_pLocation +"examples\\PolicyFileB-20111115.xml";
	
	m_edit1.SetWindowText(m_cstrFileALocation);
	m_edit2.SetWindowText(m_cstrFileBLocation);
	::PostMessage(m_edit1.m_hWnd, EM_SETSEL, 0, 0);
	::PostMessage(m_edit2.m_hWnd, EM_SETSEL, 0, 0);

	m_cstrLogFileLocation = *m_pLocation + "visualpcd_log.txt";
	m_cstrReportLocation = *m_pLocation + "visualpcd_report.txt";

	//m_controler = new PCDControler();
}

void CVisualPCDDlg::InitWindow()
{
	//////////////////////////////////////////////
	
// 	this->SetWindowText("VisualPCD - 策略冲突检测工具");
// 	pStrTitle = GetSonicUI()->CreateString();
// 	pStrTitle->Format("VisualPCD - 策略冲突检测工具");
	this->SetWindowText("VisualPCD - Policy Conflict Detector");
	pStrTitle = GetSonicUI()->CreateString();
	pStrTitle->Format("VisualPCD - Policy Conflict Detector");


	pImgWndMainWindow = GetSonicUI(	)->CreateImage();
	pImgWndMainWindow->Load(*pLocation + "res\\wnd-main.png");
	//pImgWndMainWindow->SetColorKey(RGB(255, 0, 255));
	pImgWndMainWindowPink = GetSonicUI()->CreateImage();
	pImgWndMainWindowPink->Load(*pLocation + "res\\wnd-main-pink.bmp");
	/////////////////////////////////////////////
	

	pEffect = GetSonicUI()->CreateWndEffect();
	m_pEffect = pEffect;

	pEffect->Attach(GetSafeHwnd(), FALSE);
	//pEffect->SetShapeByImage(pImgWndMainWindow, RGB(255, 0, 255));
	pEffect->EnableWholeDrag(TRUE);

	LoadBitmap(NULL, *pLocation + "res\\wnd-main.bmp");
	SetTransparent(TRUE);
	SetTransColor(RGB(255, 0, 255));
	SetClickAnywhereMove(TRUE);

	m_iWndMainX = 340;//m_cimgWndMain.GetWidth();
	m_iWndMainY = 630;//m_cimgWndMain.GetHeight();
	int cxScreen,cyScreen;
	cxScreen=GetSystemMetrics(SM_CXSCREEN);
	cyScreen=GetSystemMetrics(SM_CYSCREEN);
	MoveWindow((cxScreen - m_iWndMainX) / 2, (cyScreen - m_iWndMainY) / 2,m_iWndMainX, m_iWndMainY, TRUE);
	m_iWndMainY = 625;
	//LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
	//style = style | WS_CLIPCHILDREN ;
	//SetWindowLong(m_hWnd, GWL_STYLE, style);


	//pEffect->ShowGently(0, 0, 60);
	//Sleep(50);
	//pEffect->ShowGently(1, 0, 35);
	::SetTimer(pThis->m_hWnd, UPDATE_EDIT, 500, (TIMERPROC) CVisualPCDDlg::TimerProc);

	
}

void CVisualPCDDlg::InitControl()
{
// 	pStrStatic1 = GetSonicUI()->CreateString();
// 	pStrStatic1->Format("策略文件1路径：");
// 
// 	pStrStatic2 = GetSonicUI()->CreateString();
// 	pStrStatic2->Format("策略文件2路径：");
// 
// 	pStrStatic3 = GetSonicUI()->CreateString();
// 	pStrStatic3->Format("检测所用时间：");
	pStrStatic1 = GetSonicUI()->CreateString();
	pStrStatic1->Format("Path of Policy File 1: ");
	
	pStrStatic2 = GetSonicUI()->CreateString();
	pStrStatic2->Format("Path of Policy File 2: ");
	
	pStrStatic3 = GetSonicUI()->CreateString();
	pStrStatic3->Format("Detected Time: ");


	RECT rect1 = {50, 280, 290, 293};
	m_edit1.MoveWindow(&rect1, FALSE);
	m_edit1.m_rcClient.SetRect(0, 0, rect1.right - rect1.left, rect1.bottom - rect1.top);

	RECT rect2 = {50, 330, 290, 343};
	m_edit2.MoveWindow(&rect2, FALSE);
	m_edit2.m_rcClient.SetRect(0, 0, rect2.right - rect2.left, rect2.bottom - rect2.top);

	RECT rect3 = {230, 560, 285, 573};
	m_edit3.MoveWindow(&rect3, FALSE);
	m_edit3.m_rcClient.SetRect(0, 0, rect3.right - rect3.left, rect3.bottom - rect3.top);
}

void CVisualPCDDlg::InitButton()
{
	
	///////////////////////////////////////////////////////////
	pImgBtnMin = GetSonicUI()->CreateImage();
	pImgBtnMin->Load(*pLocation + "res\\btn-min.bmp");
	pImgBtnMin->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnMinHover = GetSonicUI()->CreateImage();
	pImgBtnMinHover->Load(*pLocation + "res\\btn-min-hover.bmp");
	pImgBtnMinHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnMinClick = GetSonicUI()->CreateImage();
	pImgBtnMinClick->Load(*pLocation + "res\\btn-min-click.bmp");
	pImgBtnMinClick->SetColorKey(RGB(255, 0, 255));
	///////////////////////////////////////////////////////////
	pImgBtnClose = GetSonicUI()->CreateImage();
	pImgBtnClose->Load(*pLocation + "res\\btn-close.bmp");
	pImgBtnClose->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseHover = GetSonicUI()->CreateImage();
	pImgBtnCloseHover->Load(*pLocation + "res\\btn-close-hover.bmp");
	pImgBtnCloseHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseClick = GetSonicUI()->CreateImage();
	pImgBtnCloseClick->Load(*pLocation + "res\\btn-close-click.bmp");
	pImgBtnCloseClick->SetColorKey(RGB(255, 0, 255));
	///////////////////////////////////////////////////////////
	pImgBtnMenu = GetSonicUI()->CreateImage();
	pImgBtnMenu->Load(*pLocation + "res\\btn-menu.bmp");
	pImgBtnMenu->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnMenuHover = GetSonicUI()->CreateImage();
	pImgBtnMenuHover->Load(*pLocation + "res\\btn-menu-hover.bmp");
	pImgBtnMenuHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnMenuClick = GetSonicUI()->CreateImage();
	pImgBtnMenuClick->Load(*pLocation + "res\\btn-menu-click.bmp");
	pImgBtnMenuClick->SetColorKey(RGB(255, 0, 255));
	///////////////////////////////////////////////////////////
	pImgBtnJc = GetSonicUI()->CreateImage();
	pImgBtnJc->Load(*pLocation + "res\\btn-big.bmp");
	pImgBtnJc->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnJcHover = GetSonicUI()->CreateImage();
	pImgBtnJcHover->Load(*pLocation + "res\\btn-big-hover.bmp");
	pImgBtnJcHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnJcClick = GetSonicUI()->CreateImage();
	pImgBtnJcClick->Load(*pLocation + "res\\btn-big-click.bmp");
	pImgBtnJcClick->SetColorKey(RGB(255, 0, 255));

// 	pStrBtnJc = GetSonicUI()->CreateString();
// 	pStrBtnJc->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='策略冲突检测', animation=30/", pImgBtnJc->GetObjectId(), 
// 		pImgBtnJcHover->GetObjectId(), 	pImgBtnJcClick->GetObjectId());
// 	pStrBtnJc->Delegate(DELEGATE_EVENT_CLICK, this, *this, CVisualPCDDlg::OnMove);
// 	pStrBtnJcText = GetSonicUI()->CreateString();
// 	pStrBtnJcText->Format("策略冲突检测");
	pStrBtnJc = GetSonicUI()->CreateString();
	pStrBtnJc->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='Conflict Detect', animation=30/", pImgBtnJc->GetObjectId(), 
		pImgBtnJcHover->GetObjectId(), 	pImgBtnJcClick->GetObjectId());
	pStrBtnJc->Delegate(DELEGATE_EVENT_CLICK, this, *this, CVisualPCDDlg::OnMove);
	pStrBtnJcText = GetSonicUI()->CreateString();
	pStrBtnJcText->Format("Conflict Detect");
	
	m_iBtnJcX = 115;
	m_iBtnJcY = 410;

	m_rctBtnJc.left = m_iBtnJcX;
	m_rctBtnJc.top = m_iBtnJcY;
	m_rctBtnJc.right = m_iBtnJcX + 110;
	m_rctBtnJc.bottom = m_iBtnJcY + 20;
	///////////////////////////////////////////////////////////
	pImgBtnXs = GetSonicUI()->CreateImage();
	pImgBtnXs->Load(*pLocation + "res\\btn-big.bmp");
	pImgBtnXs->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnXsHover = GetSonicUI()->CreateImage();
	pImgBtnXsHover->Load(*pLocation + "res\\btn-big-hover.bmp");
	pImgBtnXsHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnXsClick = GetSonicUI()->CreateImage();
	pImgBtnXsClick->Load(*pLocation + "res\\btn-xs-click.bmp");
	pImgBtnXsClick->SetColorKey(RGB(255, 0, 255));
	
// 	pStrBtnXs = GetSonicUI()->CreateString();
// 	pStrBtnXs->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='显示策略文件', animation=30/", pImgBtnXs->GetObjectId(), 
// 		pImgBtnXsHover->GetObjectId(), 	pImgBtnXsClick->GetObjectId());
// 	pStrBtnXs->Delegate(DELEGATE_EVENT_CLICK, this, *this, CVisualPCDDlg::OnDisplay);
// 	pStrBtnXsText = GetSonicUI()->CreateString();
// 	pStrBtnXsText->Format("显示策略文件");
	pStrBtnXs = GetSonicUI()->CreateString();
	pStrBtnXs->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='Policy Files', animation=30/", pImgBtnXs->GetObjectId(), 
		pImgBtnXsHover->GetObjectId(), 	pImgBtnXsClick->GetObjectId());
	pStrBtnXs->Delegate(DELEGATE_EVENT_CLICK, this, *this, CVisualPCDDlg::OnDisplay);
	pStrBtnXsText = GetSonicUI()->CreateString();
	pStrBtnXsText->Format("Policy Files");
	
	m_iBtnXsX = 50;
	m_iBtnXsY = 370;
	
	m_rctBtnXs.left = m_iBtnXsX;
	m_rctBtnXs.top = m_iBtnXsY;
	m_rctBtnXs.right = m_iBtnXsX + 110;
	m_rctBtnXs.bottom = m_iBtnXsY + 20;
	///////////////////////////////////////////////////////////
	pImgBtnTs = GetSonicUI()->CreateImage();
	pImgBtnTs->Load(*pLocation + "res\\btn-big.bmp");
	pImgBtnTs->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnTsHover = GetSonicUI()->CreateImage();
	pImgBtnTsHover->Load(*pLocation + "res\\btn-big-hover.bmp");
	pImgBtnTsHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnTsClick = GetSonicUI()->CreateImage();
	pImgBtnTsClick->Load(*pLocation + "res\\btn-Ts-click.bmp");
	pImgBtnTsClick->SetColorKey(RGB(255, 0, 255));
	
// 	pStrBtnTs = GetSonicUI()->CreateString();
// 	pStrBtnTs->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='显示策略冲突图示', animation=30/", pImgBtnTs->GetObjectId(), 
// 		pImgBtnTsHover->GetObjectId(), 	pImgBtnTsClick->GetObjectId());
// 	pStrBtnTs->Delegate(DELEGATE_EVENT_CLICK, this, *this, CVisualPCDDlg::ShowGraph);
// 	pStrBtnTsText = GetSonicUI()->CreateString();
// 	pStrBtnTsText->Format("显示策略冲突图示");
	pStrBtnTs = GetSonicUI()->CreateString();
	pStrBtnTs->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='Conflict Graph', animation=30/", pImgBtnTs->GetObjectId(), 
		pImgBtnTsHover->GetObjectId(), 	pImgBtnTsClick->GetObjectId());
	pStrBtnTs->Delegate(DELEGATE_EVENT_CLICK, this, *this, CVisualPCDDlg::ShowGraph);
	pStrBtnTsText = GetSonicUI()->CreateString();
	pStrBtnTsText->Format("Conflict Graph");
	
	m_iBtnTsX = 180;
	m_iBtnTsY = 370;
	
	m_rctBtnTs.left = m_iBtnTsX;
	m_rctBtnTs.top = m_iBtnTsY;
	m_rctBtnTs.right = m_iBtnTsX + 110;
	m_rctBtnTs.bottom = m_iBtnTsY + 20;
	///////////////////////////////////////////////////////////



	//::SetTimer(pThis->m_hWnd, ANTI_TWINKLE, 20, (TIMERPROC) CVisualPCDDlg::TimerProc);
	///////////////////////////////////////////////////////////
	pStrBtnMin = GetSonicUI()->CreateString();
	pStrBtnMin->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='Minimize', animation=30/", pImgBtnMin->GetObjectId(), 
		pImgBtnMinHover->GetObjectId(), 	pImgBtnMinClick->GetObjectId());
	pStrBtnMin->Delegate(DELEGATE_EVENT_CLICK, (void*) 0, *this, CVisualPCDDlg::FadeOut);
	
	pStrBtnClose = GetSonicUI()->CreateString();
	pStrBtnClose->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='Close', animation=30/", pImgBtnClose->GetObjectId(), pImgBtnCloseHover->GetObjectId(), 	pImgBtnCloseClick->GetObjectId());
	pStrBtnClose->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDDlg::FadeOut);
///////////////////////////////////////////////////////////////
	
}

void CVisualPCDDlg::InitProgressBar()
{
	pImgPgbEmpty = GetSonicUI()->CreateImage();
	pImgPgbEmpty->Load(*pLocation + "res\\pgb-empty.bmp");
	pImgPgbEmpty->SetColorKey(RGB(255, 0, 255));

	pImgPgbLeft = GetSonicUI()->CreateImage();
	pImgPgbLeft->Load(*pLocation + "res\\pgb-left.bmp");
	pImgPgbLeft->SetColorKey(RGB(255, 0, 255));

	pImgPgbMiddle = GetSonicUI()->CreateImage();
	pImgPgbMiddle->Load(*pLocation + "res\\pgb-middle.bmp");
	pImgPgbMiddle->SetColorKey(RGB(255, 0, 255));

	pImgPgbRight = GetSonicUI()->CreateImage();
	pImgPgbRight->Load(*pLocation + "res\\pgb-right.bmp");
	pImgPgbRight->SetColorKey(RGB(255, 0, 255));

	pImgPgbGlow = GetSonicUI()->CreateImage();
	pImgPgbGlow->Load(*pLocation + "res\\pgb-glow.bmp");
	pImgPgbGlow->SetColorKey(RGB(255, 0, 255));

	pStrPgbGlow = GetSonicUI()->CreateString();
	pStrPgbGlow->Format("/p=%d/", pImgPgbGlow->GetObjectId());

	m_iProgress = 0;
	m_iProgressGlow = 0;
	m_iProgressX = 50;
	m_iProgressY = 600;

	m_rectProgress.left = m_iProgressX + 1;
	m_rectProgress.top = m_iProgressY + 1;
	m_rectProgress.right = m_iProgressX + 1 + 238;
	m_rectProgress.bottom = m_iProgressY + 1 + 11;
	
}

void CVisualPCDDlg::InitPopupMenu()
{
	pImgPum = GetSonicUI()->CreateImage();
	pImgPum->Load(*pLocation + "res\\menu.bmp");
	pImgPum->SetColorKey(RGB(255, 0, 255));
	
	pImgPumBig[0] = GetSonicUI()->CreateImage();
	pImgPumBig[0]->Load(*pLocation + "res\\menu-big-1.bmp");
	pImgPumBig[0]->SetColorKey(RGB(255, 0, 255));
	
	pImgPumBig[1] = GetSonicUI()->CreateImage();
	pImgPumBig[1]->Load(*pLocation + "res\\menu-big-2.bmp");
	pImgPumBig[1]->SetColorKey(RGB(255, 0, 255));
	
	pImgPumBig[2] = GetSonicUI()->CreateImage();
	pImgPumBig[2]->Load(*pLocation + "res\\menu-big-3.bmp");
	pImgPumBig[2]->SetColorKey(RGB(255, 0, 255));
	
	pImgPumBig[3] = GetSonicUI()->CreateImage();
	pImgPumBig[3]->Load(*pLocation + "res\\menu-big-4.bmp");
	pImgPumBig[3]->SetColorKey(RGB(255, 0, 255));
	
	/*pStrPumText[0] = GetSonicUI()->CreateString();
	pStrPumText[0]->Format("新建");
	pStrPumText[1] = GetSonicUI()->CreateString();
	pStrPumText[1]->Format("打开1");
	pStrPumText[2] = GetSonicUI()->CreateString();
	pStrPumText[2]->Format("打开2");
	pStrPumText[3] = GetSonicUI()->CreateString();
	pStrPumText[3]->Format("打开3");
	pStrPumText[4] = GetSonicUI()->CreateString();
	pStrPumText[4]->Format("关闭");*/
	///////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 5; i ++)
	{
		pImgPumItem[i] = GetSonicUI()->CreateImage();
		pImgPumItem[i]->Load(*pLocation + "res\\menu-item\\menu-item-" + (char) (49 + i) + ".bmp");
		pImgPumItem[i]->SetColorKey(RGB(255, 0, 255));
		
		pImgPumItemHover[i] = GetSonicUI()->CreateImage();
		pImgPumItemHover[i]->Load(*pLocation + "res\\menu-item\\menu-item-hover-" + (char) (49 + i) + ".bmp");
		pImgPumItemHover[i]->SetColorKey(RGB(255, 0, 255));
		
		pImgPumItemClick[i] = GetSonicUI()->CreateImage();
		pImgPumItemClick[i]->Load(*pLocation + "res\\menu-item\\menu-item-click-" + (char) (49 + i) + ".bmp");
		pImgPumItemClick[i]->SetColorKey(RGB(255, 0, 255));
	}
	
	///////////////////////////////////////////////////////////////////////

	for (i = 0; i < 5; i ++)
	{
		pStrPumItem[i] = GetSonicUI()->CreateString();
		pStrPumItem[i]->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='', animation=30/", pImgPumItem[i]->GetObjectId(), 
		pImgPumItemHover[i]->GetObjectId(), pImgPumItemClick[i]->GetObjectId());
	}
	pStrPumItem[0]->Delegate(DELEGATE_EVENT_CLICK, (void*) 0, *this, CVisualPCDDlg::RestoreConfig);
	pStrPumItem[1]->Delegate(DELEGATE_EVENT_CLICK, (void*) 0, *this, CVisualPCDDlg::OpenFileA);
	pStrPumItem[2]->Delegate(DELEGATE_EVENT_CLICK, (void*) 0, *this, CVisualPCDDlg::OpenFileB);
	pStrPumItem[3]->Delegate(DELEGATE_EVENT_CLICK, (void*) 0, *this, CVisualPCDDlg::ShowAbout);
	pStrPumItem[4]->Delegate(DELEGATE_EVENT_CLICK, (void*) 0, *this, CVisualPCDDlg::CloseApp);
	///////////////////////////////////////////////////////////////////////
// 	pStrBtnMenu = GetSonicUI()->CreateString();
// 	pStrBtnMenu->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='菜单', animation=255/", pImgBtnMenu->GetObjectId(), 
// 		pImgBtnMenuHover->GetObjectId(), 	pImgBtnMenuClick->GetObjectId());
// 	pStrBtnMenu->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDDlg::ShowPopupMenu);
// 	
// 	pStrBtnMenuShadow = GetSonicUI()->CreateString();
// 	pStrBtnMenuShadow->Format("/a, p=%d, linkc=0, linkt='菜单', animation=255/", pImgBtnMenuClick->GetObjectId());
// 	pStrBtnMenuShadow->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDDlg::ShowPopupMenu);
	pStrBtnMenu = GetSonicUI()->CreateString();
	pStrBtnMenu->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='Menu', animation=255/", pImgBtnMenu->GetObjectId(), 
		pImgBtnMenuHover->GetObjectId(), 	pImgBtnMenuClick->GetObjectId());
	pStrBtnMenu->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDDlg::ShowPopupMenu);
	
	pStrBtnMenuShadow = GetSonicUI()->CreateString();
	pStrBtnMenuShadow->Format("/a, p=%d, linkc=0, linkt='Menu', animation=255/", pImgBtnMenuClick->GetObjectId());
	pStrBtnMenuShadow->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDDlg::ShowPopupMenu);	
	m_iMenuShadow = 0;
	
	m_iMenuButtonX = 5;
	m_iMenuButtonY = 1;
	m_iMenuCutX = m_iMenuButtonX + 2;
	m_iMenuCutY = m_iMenuButtonY + 21;

	m_rgnMenuButton = CreateRectRgn(m_iMenuButtonX, m_iMenuButtonY, m_iMenuButtonX + 57, m_iMenuButtonY +21);
	m_rgnMenu = CreateRectRgn(m_iMenuCutX, m_iMenuCutY, m_iMenuCutX + 108, m_iMenuCutY + 111);

	m_rctMenuButton.left = m_iMenuButtonX;
	m_rctMenuButton.top = m_iMenuButtonY;
	m_rctMenuButton.right = m_iMenuButtonX + 57;
	m_rctMenuButton.bottom = m_iMenuButtonY + 21;

	m_rctMenu.left = m_iMenuCutX;
	m_rctMenu.top = m_iMenuCutY;
	m_rctMenu.right = m_iMenuCutX + 106 + 20;
	m_rctMenu.bottom = m_iMenuCutY + 111 + 20;

	//{m_iMenuButtonX, m_iMenuButtonY, m_iMenuButtonX + 57, m_iMenuButtonY +21};
	//m_rctMenu = {m_iMenuCutX, m_iMenuCutY, m_iMenuCutX + 106, m_iMenuCutY + 111};	

	pStrBtnMenuText = GetSonicUI()->CreateString();
	pStrBtnMenuText->Format("Menu");
	
}

void CVisualPCDDlg::DrawProgressBar(HDC hDC, int nPosX, int nPosY, int nProgress)
{

	int nConX = nPosX + 1;
	int nConY = nPosY + 1;

	pImgPgbEmpty->Draw(hDC, nPosX, nPosY);
	
	
	HRGN hRgn = CreateRectRgn(nConX, nConY, nConX + 238, nConY + 11);
	SelectClipRgn(hDC, hRgn);

	if (nProgress < 0)
	{
		nProgress = 0;
	}
	else if (nProgress > 238)
	{
		nProgress = 238;
	}
	
	if (nProgress == 0)
	{
	}
	else if (0 < nProgress && nProgress <= 35)
	{
		pImgPgbRight->Draw(hDC, nConX + nProgress - 35, nConY);
	}
	else if (35 < nProgress && nProgress <= 70)
	{
		pImgPgbLeft->Draw(hDC, nConX + nProgress - 70, nConY);
		pImgPgbRight->Draw(hDC, nConX + nProgress - 35, nConY);
	}
	else if (70 < nProgress && nProgress <= 105)
	{
		pImgPgbMiddle->Draw(hDC, nConX, nConY);
		pImgPgbLeft->Draw(hDC, nConX, nConY);
		pImgPgbRight->Draw(hDC, nConX + nProgress - 35, nConY);
	}
	else if (105 < nProgress && nProgress <= 140)
	{
		pImgPgbMiddle->Draw(hDC, nConX + 35, nConY);
		pImgPgbLeft->Draw(hDC, nConX, nConY);
		pImgPgbRight->Draw(hDC, nConX + nProgress - 35, nConY);
	}
	else if (140 < nProgress && nProgress <= 210)
	{
		pImgPgbMiddle->Draw(hDC, nConX + 35, nConY);
		pImgPgbMiddle->Draw(hDC, nConX + nProgress - 105, nConY);
		pImgPgbLeft->Draw(hDC, nConX, nConY);
		pImgPgbRight->Draw(hDC, nConX + nProgress - 35, nConY);
	}
	else if (210 < nProgress && nProgress <= 238)
	{
		pImgPgbMiddle->Draw(hDC, nConX + 35, nConY);
		pImgPgbMiddle->Draw(hDC, nConX + 105, nConY);
		pImgPgbMiddle->Draw(hDC, nConX + nProgress - 105, nConY);
		pImgPgbLeft->Draw(hDC, nConX, nConY);
		pImgPgbRight->Draw(hDC, nConX + nProgress - 35, nConY);
	}
	else
	{
		MessageBox("DrawProgressBar error.");
	}

	SelectClipRgn(hDC, NULL);
	DeleteObject(hRgn);

	//DeleteDC(hDC);
}

void CVisualPCDDlg::DrawProgressBarGlow(HDC hDC, int nPosX, int nPosY, int nProgressGlow)
{

	int nConX = nPosX + 1;
	int nConY = nPosY + 1;

	HRGN hRgn = CreateRectRgn(nConX, nConY, nConX + pThis->m_iProgress, nConY + 11);
	SelectClipRgn(hDC, hRgn);
	//pThis->pAnmPgbGlow->
	pThis->pImgPgbGlow->Draw(hDC, nConX - 70 + nProgressGlow, nConY);
	//pThis->pAnmPgbGlow->MoveGently(nConX, nConY, 50, TRUE);
	SelectClipRgn(hDC, NULL);
	DeleteObject(hRgn);
}

void CVisualPCDDlg::StartProgressBar()
{
	pThis->m_iProgress = 0;
	::SetTimer(pThis->m_hWnd, PROGRESS, 30, (TIMERPROC) CVisualPCDDlg::TimerProc);
	::SetTimer(pThis->m_hWnd, PROGRESS_GLOW, 10, (TIMERPROC) CVisualPCDDlg::TimerProc);
}

void CVisualPCDDlg::StopProgressBar()
{
	//pThis->m_iProgress = 0;
	::KillTimer(pThis->m_hWnd, PROGRESS);
	//::KillTimer(pThis->m_hWnd, 1);

	pThis->ShowResult(NULL, NULL);
}

void CVisualPCDDlg::DrawPopupMenu(HDC hDC, int nStartX, int nStartY, int nCutX, int nCutY)
{
	SelectClipRgn(hDC, pThis->m_rgnMenu);

	if (!pThis->m_iKeepMenu)
	{
		pThis->pImgPum->Draw(hDC, nStartX, nStartY);
		for (int i = 0; i < 5; i ++)
		{
			pThis->pStrPumItem[i]->TextOut(hDC, nStartX + 3,  nStartY + 3 + 21 * i, pThis->m_hWnd);
			pThis->pStrPumItem[i]->Detach();
		}
	}
	else
	{
		for (int i = 0; i < 5; i ++)
		{
			pThis->pStrPumItem[i]->TextOut(hDC, nStartX + 3,  nStartY + 3 + 21 * i, pThis->m_hWnd);
		}
	}

	SelectClipRgn(hDC, NULL);
	//DeleteObject(hDC);
	//DeleteDC(hDC);
	//::ReleaseDC(pThis->m_hWnd, hDC);
}

void CVisualPCDDlg::DrawPopupMenu(HDC hDC, int nStartX, int nStartY, int nCutX, int nCutY, int nBig)
{

	//for (int i = 0; i < 4; i ++)
	//{
	//	pThis->pImgPumBig[i]->Clear();
	//}
	
	if (pThis->m_iIsPopdown)
	{
		RECT rect1 = {nCutX + 106 + 2 * nBig, nCutY, nCutX + 106 + 2 * nBig + 2, nCutY + 111 + 2 * nBig + 2};
		pThis->InvalidateRect(&rect1);

		RECT rect2 = {nCutX, nCutY + 111 + 2 * nBig, nCutX + 106 + 2 * nBig + 2, nCutY + 111 + 2 * nBig + 2};
		pThis->InvalidateRect(&rect2);
	}

	HRGN hRgn = CreateRectRgn(nCutX, nCutY, nCutX + 108 + 2 * nBig, nCutY + 111 + 2 * nBig);
	SelectClipRgn(hDC, hRgn);
	//SelectClipRgn(hDC, NULL);

	if (!m_iKeepMenu)
	{
		if (nBig == 0)
		{
			pThis->pImgPum->Draw(hDC, nStartX, nStartY);
		}
		else if (nBig == 1)
		{
			pThis->pImgPumBig[0]->Draw(hDC, nStartX, nStartY);
		}
		else if (nBig == 2)
		{
			pThis->pImgPumBig[1]->Draw(hDC, nStartX, nStartY);
		}
		else if (nBig == 3)
		{
			pThis->pImgPumBig[2]->Draw(hDC, nStartX, nStartY);
		}
		else if (nBig == 4)
		{
			pThis->pImgPumBig[3]->Draw(hDC, nStartX, nStartY);
		}
	}
	for (int i = 0; i < 5; i ++)
	{
		pThis->pStrPumItem[i]->TextOut(hDC, nStartX + 3,  nStartY + 3 + 21 * i, pThis->m_hWnd);
		if (!pThis->m_iKeepMenu)
			pThis->pStrPumItem[i]->Detach();
	}


	SelectClipRgn(hDC, NULL);
	DeleteObject(hRgn);
	//DeleteObject(hDC);
	//DeleteDC(hDC);
	//::ReleaseDC(pThis->m_hWnd, hDC);
}

void CVisualPCDDlg::DrawPopupMenu(HDC hDC)
{
	if (pThis->m_iPopup >= 0 && pThis->m_iIsPopdown == 0)
	{
		pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX, pThis->m_iMenuCutY, 
			pThis->m_iMenuCutX, pThis->m_iMenuCutY, pThis->m_iPopout + 1);
	}
	else if (pThis->m_iPopup >= 0 && pThis->m_iIsPopdown == 1 && pThis->m_iPopout > 0)
	{
		pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX, pThis->m_iMenuCutY, 
			pThis->m_iMenuCutX, pThis->m_iMenuCutY, pThis->m_iPopout - 1);
	}
	else if (pThis->m_iPopup >= 0 && pThis->m_iPopout <= 0)
	{
		pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX, pThis->m_iMenuCutY, 
			pThis->m_iMenuCutX, pThis->m_iMenuCutY, 0);
	}
	else
	{
		pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX + pThis->m_iPopup, pThis->m_iMenuCutY + pThis->m_iPopup, 
			pThis->m_iMenuCutX, pThis->m_iMenuCutY);
	}
}

void CVisualPCDDlg::ShowPopupMenu(ISonicString* pStr, LPVOID)
{
	if (pThis->m_iKeepMenu == 1)
	{
		pThis->ClearPopupMenu(NULL, NULL);
		return;
	}

	::SetTimer(pThis->m_hWnd, POPUPMENU, 20, (TIMERPROC) CVisualPCDDlg::TimerProc);

	pThis->m_iMenuShadow = 1;

	pThis->m_iPopup = -101;
	pThis->m_iPopupA = 13;
	pThis->m_iKeepMenu = 0;
	pThis->m_iIsPopdown = 0;
	pThis->m_iPopout = 0;
	//pThis->pStrBtnMenu->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='菜单', animation=30/", pThis->pImgBtnMenuClick->GetObjectId(), 
	//	pThis->pImgBtnMenuClick->GetObjectId(), pThis->pImgBtnMenuClick->GetObjectId());
	//pThis->Invalidate();
}

void CVisualPCDDlg::InitAbout()
{
/*pImgAbout = GetSonicUI()->CreateImage();
pImgAbout->Load(*pLocation + "res\\wnd-about.png");
pImgAbout->SetColorKey(RGB(255, 0, 255));

  pStrAbout = GetSonicUI()->CreateString();
  pStrAbout->Format("/a, p=%d, linkc=0/", pImgAbout->GetObjectId());
  pStrAbout->Delegate(DELEGATE_EVENT_CLICK, NULL, NULL, CVisualPCDDlg::CloseAbout);
  
	pStrAboutInfo = GetSonicUI()->CreateString();
	pStrAboutInfo->Format("策略冲突检测工具v1.0 by Veotax");
	
	  pStrAboutClose = GetSonicUI()->CreateString();
	  pStrAboutClose->Format("关闭");
	  
		
	m_iKeepAbout = 0;*/
}

void CVisualPCDDlg::KeepPopupMenu(HDC hDC)
{
	pThis->DrawPopupMenu(hDC, pThis->m_iMenuCutX, pThis->m_iMenuCutY, 
				pThis->m_iMenuCutX, pThis->m_iMenuCutY);
}

void CVisualPCDDlg::ClearPopupMenu(ISonicString* pStr, LPVOID)
{

	pThis->m_iKeepMenu = 0;
	pThis->m_iMenuShadow = 0;
	
	for (int i = 0; i < 5; i ++)
	{
		pThis->pStrPumItem[i]->Detach();
	}

	pThis->InvalidateRect(&(pThis->m_rctMenuButton));
	pThis->InvalidateRect(&(pThis->m_rctMenu));
}

void CVisualPCDDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_iKeepMenu == 1)
	{
		ClearPopupMenu(NULL, NULL);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CVisualPCDDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (m_iKeepMenu == 1)
	{
		ClearPopupMenu(NULL, NULL);
	}
	CDialog::OnRButtonDown(nFlags, point);
}

static UINT AboutThread(LPVOID pParam)
{
	//CVisualPCDAboutDlg* dlg = new CVisualPCDAboutDlg(pThis);
	//dlg->DoModal();
	return 0;
}

CVisualPCDAboutDlg* dlgAbout;


void CVisualPCDDlg::ShowAbout(ISonicString* pStr, LPVOID)
{
	pThis->ClearPopupMenu(NULL, NULL);

	if (dlgAbout != NULL)
		delete dlgAbout;
	dlgAbout = new CVisualPCDAboutDlg(pThis);
	dlgAbout->DoModal();
	//dlgAbout->Create(IDD_ABOUTBOX, pThis);
	//dlgAbout->ShowWindow(SW_SHOW);

	//CWinThread *m_pThread;
	//m_pThread = AfxBeginThread(AboutThread, NULL, 0);


	//DialogBox(AfxGetApp()->m_hInstance, (LPCTSTR)IDD_ABOUTBOX, pThis->m_hWnd, NULL);//(DLGPROC)About);
	//m_dlgAbout = new CVisualPCDAboutDlg();
	//m_dlgAbout->Create(IDD_ABOUT, pThis);

	//pThis->m_iKeepAbout = 1;
	//pThis->ClearPopupMenu(NULL, NULL);

}

static UINT ResultThread(LPVOID pParam)
{
	/*
	if (dlgResult != NULL)
		delete dlgResult;
	dlgResult = new CVisualPCDResultDlg(pThis);
	dlgResult->Create(IDD_RESULT, pThis);
	dlgResult->ShowWindow(SW_SHOW);

	//CVisualPCDResultDlg* dlg = new CVisualPCDResultDlg(pThis);
	//dlg->DoModal();*/
	return 0;
}

CVisualPCDInputDlg* dlgInput;

void CVisualPCDDlg::ShowInput(ISonicString* pStr, LPVOID)
{
	if (dlgInput != NULL)
		delete dlgInput;
	dlgInput = new CVisualPCDInputDlg(pThis);
	dlgInput->Create(IDD_INPUT, pThis);
	dlgInput->ShowWindow(SW_SHOW);
}

CVisualPCDGraphDlg* dlgGraph;

void CVisualPCDDlg::ShowGraph(ISonicString* pStr, LPVOID)
{
	if (dlgGraph != NULL)
		delete dlgGraph;
	dlgGraph = new CVisualPCDGraphDlg(pThis);
	dlgGraph->Create(IDD_GRAPH, pThis);
	dlgGraph->ShowWindow(SW_SHOW);
}

CVisualPCDResultDlg* dlgResult;

void CVisualPCDDlg::ShowResult(ISonicString* pStr, LPVOID)
{
	if (dlgResult != NULL)
		delete dlgResult;
	dlgResult = new CVisualPCDResultDlg(pThis);
	dlgResult->Create(IDD_RESULT, pThis);
	dlgResult->ShowWindow(SW_SHOW);

	//CWinThread *m_pThread;
	//m_pThread = AfxBeginThread(ResultThread, NULL, 0);
	//CRuntimeClass* prt = RUNTIME_CLASS(CVisualPCDDlg);
	//m_pThread = AfxBeginThread(this->GetRuntimeClass(), NULL, 0);
	
	//DialogBox(AfxGetApp()->m_hInstance, (LPCTSTR)IDD_ABOUTBOX, pThis->m_hWnd, NULL);//(DLGPROC)About);
	//m_dlgAbout = new CVisualPCDAboutDlg();
	//m_dlgAbout->Create(IDD_ABOUT, pThis);
	
	//pThis->m_iKeepAbout = 1;
	//pThis->ClearPopupMenu(NULL, NULL);
	
}

BOOL CVisualPCDDlg::startEngine()
{
	HWND hWnd = ::FindWindow(NULL, _T("RacerPro"));
	if (hWnd)
	{
		return 0;
	}
	else
	{
		CString strPath = initKBDir();
		CString strRacerDir =  strPath + _T("RacerPro-1-9-2-beta");
		if (FolderExist(strRacerDir))
		{
			CString strRacerEXE = strRacerDir + _T("\\RacerPro.exe");
			CString strRunAsDateEXE = strPath + _T("RunAsDate.exe");
			CString strParameter = _T("/immediate /movetime 05\\05\\2011 00:00:00 \"") + strRacerEXE + _T("\"");
			ShellExecute(NULL, _T("Open"), strRunAsDateEXE, strParameter, _T(""), SW_SHOWNORMAL);//SW_SHOWNORMAL);SW_HIDE
			//createProcess(strRunAsDateEXE, strParameter);
			//killProcess(_T("RunAsDate"));
			//Sleep(3000);
			return 1;
		}
		else
		{
			//MyMessageBox_Error(_T("startEngine Error"), _T("Error"));
			return -1;
		}
	}
}

void CVisualPCDDlg::RestoreConfig(ISonicString* pStr, LPVOID)
{
	pThis->ClearPopupMenu(NULL, NULL);

	//pThis->m_cstrFileALocation = *m_pLocation +"examples\\PolicyFileA.xml";
	//pThis->m_cstrFileALocation = *m_pLocation +"examples\\PolicyFileB.xml";
	/*
	string strRacerEXE;
	strRacerEXE = "C:\\Program Files\\RacerPro-1-9-2-beta";
	if (pThis->FolderExist(strRacerEXE.c_str()))
	{
		strRacerEXE = "C:\\Program Files\\RacerPro-1-9-2-beta\\RacerPro.exe";
		ShellExecute(NULL, "Open", strRacerEXE.c_str(), NULL, NULL, SW_SHOWNORMAL);
		return;
	}

	strRacerEXE = "D:\\Program Files\\RacerPro-1-9-2-beta";
	if (pThis->FolderExist(strRacerEXE.c_str()))
	{
		strRacerEXE = "D:\\Program Files\\RacerPro-1-9-2-beta\\RacerPro.exe";
		ShellExecute(NULL, "Open", strRacerEXE.c_str(), NULL, NULL, SW_SHOWNORMAL);
		return;
	}

	strRacerEXE = "E:\\Program Files\\RacerPro-1-9-2-beta";
	if (pThis->FolderExist(strRacerEXE.c_str()))
	{
		strRacerEXE = "E:\\Program Files\\RacerPro-1-9-2-beta\\RacerPro.exe";
		ShellExecute(NULL, "Open", strRacerEXE.c_str(), NULL, NULL, SW_SHOWNORMAL);
		return;
	}

	strRacerEXE = "F:\\Program Files\\RacerPro-1-9-2-beta";
	if (pThis->FolderExist(strRacerEXE.c_str()))
	{
		strRacerEXE = "F:\\Program Files\\RacerPro-1-9-2-beta\\RacerPro.exe";
		ShellExecute(NULL, "Open", strRacerEXE.c_str(), NULL, NULL, SW_SHOWNORMAL);
		return;
	}

	strRacerEXE = *(pThis->m_pLocation) + "RacerPro-1-9-2-beta";
	if (pThis->FolderExist(strRacerEXE.c_str()))
	{
		strRacerEXE = *(pThis->m_pLocation) + "RacerPro-1-9-2-beta\\RacerPro.exe";
		ShellExecute(NULL, "Open", strRacerEXE.c_str(), NULL, NULL, SW_SHOWNORMAL);
		return;
	}

	::MessageBox(pThis->m_hWnd, "Open RacerPro error.", "Error", MB_OK);
	return;
	*/
	startEngine();
}

static UINT OpenFileAThread(LPVOID pParam)
{
	CVisualPCDFileDlg* dlg = new CVisualPCDFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		_T("XACML Policy File(*.xml)|*.xml||"), pThis, FILEDIALOG_FILEA);
	dlg->DoModal();
	if (pThis->m_cstrFileALocation != "")
	{
		pThis->m_edit1.SetWindowText(pThis->m_cstrFileALocation);
	}
	::PostMessage(pThis->m_edit1.m_hWnd, EM_SETSEL, 0, 0);
	return 0;
}

static UINT OpenFileBThread(LPVOID pParam)
{
	CVisualPCDFileDlg* dlg = new CVisualPCDFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		_T("XACML Policy File(*.xml)|*.xml||"), pThis, FILEDIALOG_FILEB);
	dlg->DoModal();
	if (pThis->m_cstrFileBLocation != "")
	{
		pThis->m_edit2.SetWindowText(pThis->m_cstrFileBLocation);
	}
	::PostMessage(pThis->m_edit2.m_hWnd, EM_SETSEL, 0, 0);
	return 0;
}

void CVisualPCDDlg::OpenFileA(ISonicString* pStr, LPVOID)
{
	pThis->ClearPopupMenu(NULL, NULL);

	CWinThread *m_pThread;
	m_pThread = AfxBeginThread(OpenFileAThread, NULL);
}

void CVisualPCDDlg::OpenFileB(ISonicString* pStr, LPVOID)
{
	pThis->ClearPopupMenu(NULL, NULL);

	CWinThread *m_pThread;
	m_pThread = AfxBeginThread(OpenFileBThread, NULL);
}

void CVisualPCDDlg::CloseApp(ISonicString* pStr, LPVOID)
{
	pThis->ClearPopupMenu(NULL, NULL);

	FadeOut(NULL, (void*) 1);
}


/*
void CVisualPCDDlg::DrawAbout(HDC hDC, int nPosX, int nPosY)
{
	hDC = ::GetDC(NULL);
	pThis->pStrAbout->TextOut(hDC, nPosX, nPosY, pThis->m_hWnd);
	pThis->pStrAboutInfo->TextOut(hDC, nPosX +20, nPosY + 40, pThis->m_hWnd);
	pThis->pStrAboutClose->TextOut(hDC, nPosX + 20, nPosY + 60, pThis->m_hWnd);
}

void CVisualPCDDlg::CloseAbout(ISonicString* pStr, LPVOID)
{
	pThis->m_iKeepAbout = 0;
	pThis->Invalidate();
}*/


void CVisualPCDDlg::InitWindowGently()
{
	m_iTrans = 0;
	pEffect->SetLayeredAttributes(NULL, 0, 2);
}

void CVisualPCDDlg::ShowWindowGently()
{
	::SetTimer(m_hWnd, FADEIN, 20, (TIMERPROC) CVisualPCDDlg::TimerProc);
}

void CVisualPCDDlg::DrawWindowGently(int nTrans)
{
	pEffect->SetLayeredAttributes(NULL, nTrans, 2);
}

void CVisualPCDDlg::HideWindowGently()
{
	pThis->m_iTrans = 255;
	::SetTimer(pThis->m_hWnd, FADEOUT, 20, (TIMERPROC) CVisualPCDDlg::TimerProc);
}

void CVisualPCDDlg::InitScaleWindowGently()
{
	RGBQUAD rgbq;
	rgbq.rgbBlue = 255;
	rgbq.rgbGreen = 0;
	rgbq.rgbRed = 255;

	int iDeltaX, iDeltaY;
	int iDeltaXMax, iDeltaYMax;

	m_cimgWndMain.Load(*pLocation + "res\\wnd-main-photo.bmp");
	m_cimgWndMain.SetTransIndex(0);
	m_cimgWndMain.AlphaCreate();
	m_cimgWndMain.SetTransColor(rgbq);

	//CxImage cimgTemp;
	//cimgTemp.SetTransIndex(0);
	//cimgTemp.AlphaCreate();
	
	m_iScaleDisp = -10;
	m_iScaleDispV = 1;

	m_iScaleTrans = 0;
	m_iScaleTransV = 255 / 3;

	GetWindowRect(&m_rctWndMain);
	m_rctWndMain.right = m_rctWndMain.left + 340;
	m_rctWndMain.bottom = m_rctWndMain.top + 625;
	
	//m_hTopDC = ::GetDC(NULL);
	//m_fWndMainRatio = ((float) m_iWndMainX) / m_iWndMainY;
	m_fWndMainRatio = 0.5;
	m_iScaleWindowPhase = 0;

	iDeltaXMax = (int) (10 * m_fWndMainRatio);
	iDeltaYMax = 10;
	for (int i = 0; i < 21; i ++)
	{
		//m_cimgWndMainBuffer[i].AlphaCreate();
		//m_cimgWndMainBuffer[i].SetTransIndex(0);
		iDeltaX = (int) ((i - 10) * m_fWndMainRatio);
		iDeltaY = i - 10;
		m_cimgWndMain.Resample2(340, 625,//m_iWndMainX + 2 * iDeltaX, m_iWndMainY + 2 * iDeltaY, 
			CxImage::IM_MITCHELL , CxImage::OM_REPEAT, &m_cimgWndMainBuffer[i], FALSE);
		//cimgTemp.Expand(iDeltaXMax - iDeltaX, iDeltaYMax - iDeltaY, iDeltaXMax - iDeltaX, iDeltaYMax - iDeltaY, 
		//	rgbq, &m_cimgWndMainBuffer[i]);
	}
}



void CVisualPCDDlg::ShowScaleWindowGently()
{
	if (dlgMainWndTrans != NULL)
		delete dlgMainWndTrans;
	dlgMainWndTrans = new CVisualPCDTransDlg(pThis);
	dlgMainWndTrans->Create(IDD_TRANS, pThis);
	


	SetWindowLong(dlgMainWndTrans->GetSafeHwnd(), GWL_EXSTYLE, 
		GetWindowLong(dlgMainWndTrans->GetSafeHwnd(), GWL_EXSTYLE) ^ 0x80000); 
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if (hInst) 
	{
		typedef BOOL (WINAPI* MYFUNC) (HWND, COLORREF, BYTE, DWORD);
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes函数指针
		fun=(MYFUNC) GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (fun)
			fun(dlgMainWndTrans->m_hWnd, RGB(212, 208, 200), 255, 3);
		FreeLibrary(hInst);
	}

	dlgMainWndTrans->ShowWindow(SW_SHOW);

	int iDeltaXMax = (int) (10 * m_fWndMainRatio);
	int iDeltaYMax = 10;

	m_rctWndMainMax.left = m_rctWndMain.left - iDeltaXMax;
	m_rctWndMainMax.top = m_rctWndMain.top - iDeltaYMax;
	m_rctWndMainMax.right = m_rctWndMain.right + iDeltaXMax;
	m_rctWndMainMax.bottom = m_rctWndMain.bottom + iDeltaYMax;
	
	dlgMainWndTrans->MoveWindow(&m_rctWndMainMax, TRUE);

	::SetTimer(m_hWnd, SCALE_FADEIN, 1000, (TIMERPROC) CVisualPCDDlg::TimerProc);
}

void CVisualPCDDlg::ClipScaleWindowGently(int iX1, int iY1, int iX2, int iY2, int iStep)
{
	
	HRGN hrgn1 = CreateRectRgn(iX1, iY1, iX2, iY2);
	HRGN hrgn2 = CreateRectRgn(iX1 + (int) (iStep * m_fWndMainRatio), iY1 + iStep, iX2 - (int) (iStep * m_fWndMainRatio), iY2 - iStep);
	CombineRgn(hrgn1, hrgn1, hrgn2, RGN_DIFF);

	//RECT rect = {0, 0, 1366, 768};
	//::InvalidateRect(pThis->m_hWnd, &rect, TRUE);
	//::RedrawWindow()
	//::UpdateWindow(NULL);

	::InvalidateRgn(dlgMainWndTrans->m_hWnd, hrgn1, TRUE);
	::UpdateWindow(dlgMainWndTrans->m_hWnd);
	DeleteObject(hrgn1);

	DeleteObject(hrgn2);
}

void CVisualPCDDlg::DrawScaleWindowGently(HDC hDC, int nTrans, int nScale)
{
	m_hTopDC = dlgMainWndTrans->GetDC()->GetSafeHdc();
	nScale = 0;
	//m_cimgWndMainBuffer[nScale + 10].AlphaSet(nTrans);
	m_cimgWndMainBuffer[nScale + 10].Draw(m_hTopDC, (10 - nScale) * m_fWndMainRatio, 10 - nScale);
	
	::ReleaseDC(NULL, m_hTopDC);
}

void CVisualPCDDlg::HideScaleWindowGently()
{
	::SetTimer(m_hWnd, SCALE_FADEOUT, 20, (TIMERPROC) CVisualPCDDlg::TimerProc);
}

BOOL CVisualPCDDlg::OnEraseBkgnd(CDC* pDC) 
{
	//return TRUE;
	return CBitmapDialog::OnEraseBkgnd(pDC);
}

void CVisualPCDDlg::OnChangeEdit1() 
{
	m_edit1.GetWindowText(m_cstrFileALocation);
}

void CVisualPCDDlg::OnChangeEdit2() 
{
	m_edit2.GetWindowText(m_cstrFileBLocation);
}
