// VisualPCDGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPCD.h"
#include "VisualPCDDlg.h"
#include "VisualPCDGraphDlg.h"


#include <ximage.h>
#include <ximabmp.h>

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

CVisualPCDDlg* pGraphParentThis;

CVisualPCDGraphDlg* pGraphThis;
ISonicWndEffect* pGraphEffect;
CString* pGraphLocation;

#define FADEIN 0
#define FADEOUT 1

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDGraphDlg dialog


CVisualPCDGraphDlg::CVisualPCDGraphDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CVisualPCDGraphDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVisualPCDGraphDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pGraphParentThis = (CVisualPCDDlg*) pParent;
}


void CVisualPCDGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisualPCDGraphDlg)
	DDX_Control(pDX, IDC_GRAPH, m_picGraph);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVisualPCDGraphDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CVisualPCDGraphDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDGraphDlg message handlers

BOOL CVisualPCDGraphDlg::OnInitDialog() 
{
	CBitmapDialog::OnInitDialog();

	InitPointer();
	InitButton();
	InitWindow();
	InitControl();
	
	InitWindowGently();
	ShowWindowGently();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVisualPCDGraphDlg::InitPointer()
{
	pGraphThis = this;
	pGraphLocation = pGraphParentThis->m_pLocation;
	//pResultParentThis->EnableWindow(TRUE);
}


void CVisualPCDGraphDlg::InitWindow()
{
	
// 	this->SetWindowText("策略冲突图示");
// 	pStrGraphTitle = GetSonicUI()->CreateString();
// 	pStrGraphTitle->Format("策略冲突图示");
// 
// 	pStrStatic1 = GetSonicUI()->CreateString();
// 	pStrStatic1->Format("策略文件1内容：");
// 	pStrStatic2 = GetSonicUI()->CreateString();
// 	pStrStatic2->Format("策略文件2内容：");
	this->SetWindowText("Policy Conflict Graph");
	pStrGraphTitle = GetSonicUI()->CreateString();
	pStrGraphTitle->Format("Policy Conflict Graph");
	
	pStrStatic1 = GetSonicUI()->CreateString();
	pStrStatic1->Format("Content of Policy File 1: ");
	pStrStatic2 = GetSonicUI()->CreateString();
	pStrStatic2->Format("Content of Policy File 2: ");

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
	
	pImgWndGraph = GetSonicUI()->CreateImage();
	pImgWndGraph->Load(*pGraphLocation + "res\\wnd-big-graph.bmp");
	
	//pStrWndResult = GetSonicUI()->CreateString();
	//pStrWndResult->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='', animation=30/", pImgWndResult->GetObjectId(),  
	//	pImgWndResult->GetObjectId(),  pImgWndResult->GetObjectId());
	
	
	pGraphEffect = GetSonicUI()->CreateWndEffect();
	
	//pGraphEffect->Attach(pGraphThis->GetSafeHwnd(), TRUE);
	//pGraphEffect->SetShapeByImage(pImgWndResult, RGB(0, 0, 0));
	
	pGraphEffect->Attach(pGraphThis->GetSafeHwnd(), FALSE);
	//pGraphEffect->SetShapeByImage(pImgWndResult, RGB(255, 0, 255));
	pGraphEffect->EnableWholeDrag(TRUE);
	
	
	LoadBitmap(NULL, *pGraphLocation + "res\\wnd-big-graph.bmp");
	SetTransparent(TRUE);
	SetTransColor(RGB(255, 0, 255));
	
	
	RECT rectParent;
	::GetWindowRect(pGraphParentThis->m_hWnd, &rectParent);
	::MoveWindow(this->m_hWnd, rectParent.left - (900 - 384) / 2, rectParent.top + 100, pImgWndGraph->GetWidth(), pImgWndGraph->GetHeight(), TRUE);
	
	
	
}

LRESULT CALLBACK MyMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

void CVisualPCDGraphDlg::InitControl()
{
	CRect rect(20, 40, 880, 600);
	//m_picGraph.MoveWindow(&rect, TRUE);
	//m_picGraph.GetWindowRect(rect);

	m_hHook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC) MyMouseProc, (HINSTANCE) NULL, GetCurrentThreadId());

	ShowGraph();
}

void CVisualPCDGraphDlg::InitButton()
{
	pImgBtnClose = GetSonicUI()->CreateImage();
	pImgBtnClose->Load(*pGraphLocation + "res\\btn-close.bmp");
	pImgBtnClose->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseHover = GetSonicUI()->CreateImage();
	pImgBtnCloseHover->Load(*pGraphLocation + "res\\btn-close-hover.bmp");
	pImgBtnCloseHover->SetColorKey(RGB(255, 0, 255));
	
	pImgBtnCloseClick = GetSonicUI()->CreateImage();
	pImgBtnCloseClick->Load(*pGraphLocation + "res\\btn-close-click.bmp");
	pImgBtnCloseClick->SetColorKey(RGB(255, 0, 255));
	
	pStrBtnClose = GetSonicUI()->CreateString();
	pStrBtnClose->Format("/a, p=%d, ph=%d, pc=%d, linkc=0, linkt='Close', animation=30/", pImgBtnClose->GetObjectId(), pImgBtnCloseHover->GetObjectId(), 	pImgBtnCloseClick->GetObjectId());
	pStrBtnClose->Delegate(DELEGATE_EVENT_CLICK, (void*) 1, *this, CVisualPCDGraphDlg::OnClose);
}


void CVisualPCDGraphDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	HDC hDC = dc.GetSafeHdc();
	pStrGraphTitle->TextOut(dc, 10, 6);
	
	pStrBtnClose->TextOut(dc, 900 - 54, 0, pGraphThis->m_hWnd);

	HDC hDCMem = ::CreateCompatibleDC(hDC);//创建兼容DC
	HBITMAP hBitMap = ::CreateCompatibleBitmap(hDC, m_iGraphX, m_iGraphY);//创建兼容位图
	HBITMAP hOldBitMap = (HBITMAP) SelectObject(hDCMem, hBitMap);//将位图选入DC，并保存返回值
	HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDCMem, hBrushWhite);
	Rectangle(hDCMem, 0, 0, m_iGraphX, m_iGraphY);
	DrawGraph(hDCMem);
	BitBlt(hDC, 30, 40, m_iGraphX, m_iGraphY, hDCMem, 0, 0, SRCCOPY);

	SelectObject(hDCMem, hOldBrush);
	DeleteObject(hBrushWhite);
	SelectObject(hDCMem, hOldBitMap);
	DeleteObject(hBitMap);

	DeleteDC(hDCMem);
	//::ReleaseDC(m_hWnd, hDC);
	

	CBitmapDialog::OnPaint();
	// Do not call CBitmapDialog::OnPaint() for painting messages
}

void CVisualPCDGraphDlg::OnClose(ISonicString* pStr, LPVOID)
{
	pGraphThis->HideWindowGently();
}

void CVisualPCDGraphDlg::CloseWindow()
{
	UnhookWindowsHookEx(pGraphThis->m_hHook);
	::EndDialog(pGraphThis->m_hWnd, 0);
}

void CVisualPCDGraphDlg::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	switch (nTimerid)
	{
	case FADEIN:
		if (pGraphThis->m_iTrans < 255)
		{
			pGraphThis->m_iTrans += 40;
			if (pGraphThis->m_iTrans >= 255)
			{
				pGraphThis->DrawWindowGently(255);
			}
			else
			{
				pGraphThis->DrawWindowGently(pGraphThis->m_iTrans);
			}
		}
		else
		{
			pGraphThis->m_iTrans = 0;
			::KillTimer(pGraphThis->m_hWnd, FADEIN);
		}
		break;
	case FADEOUT:
		if (pGraphThis->m_iTrans > 0)
		{
			pGraphThis->m_iTrans -= 40;
			if (pGraphThis->m_iTrans <= 0)
			{
				pGraphThis->DrawWindowGently(0);
			}
			else
			{
				pGraphThis->DrawWindowGently(pGraphThis->m_iTrans);
			}
		}
		else
		{
			//pGraphThis->m_iTrans = 0;
			::KillTimer(pGraphThis->m_hWnd, FADEOUT);
			pGraphThis->CloseWindow();
		}
		break;
	default:
		break;
	}
}

void CVisualPCDGraphDlg::InitWindowGently()
{
	m_iTrans = 0;
	pGraphEffect->SetLayeredAttributes(NULL, 0, 2);
}

void CVisualPCDGraphDlg::ShowWindowGently()
{
	::SetTimer(m_hWnd, FADEIN, 20, (TIMERPROC) CVisualPCDGraphDlg::TimerProc);
}

void CVisualPCDGraphDlg::DrawWindowGently(int nTrans)
{
	pGraphEffect->SetLayeredAttributes(NULL, nTrans, 2);
}

void CVisualPCDGraphDlg::HideWindowGently()
{
	pGraphThis->m_iTrans = 255;
	::SetTimer(pGraphThis->m_hWnd, FADEOUT, 20, (TIMERPROC) CVisualPCDGraphDlg::TimerProc);
}

string CVisualPCDGraphDlg::itos(int i)
{
	char cBuffer[10];
	itoa(i, cBuffer, 10);
	string s(cBuffer);
	return s;
}

int CVisualPCDGraphDlg::GetCircleX(int iCentreX, int iCentreY, int iRadius, int iSize, int iNo)
{
	return iCentreX + iRadius * cos(2 * PI * ((double) iNo) / iSize + 1);
}

int CVisualPCDGraphDlg::GetCircleY(int iCentreX, int iCentreY, int iRadius, int iSize, int iNo)
{
	return iCentreY + iRadius * sin(2 * PI * ((double) iNo) / iSize + 1);
}

void CVisualPCDGraphDlg::ShowGraph()
{
	m_iGraphX = 860 - 20;
	m_iGraphY = 560 - 20;
	InitGraph();
}

void CVisualPCDGraphDlg::InitGraph()
{
	if (pGraphParentThis->m_controler == NULL)
		return;
	Enquirer* enq = pGraphParentThis->m_controler->m_enq;

	vector<int> niTargetPoliciesShort;
	niTargetPoliciesShort.insert(m_niTargetPolicies.end(), enq->m_niConflictIndex.begin(), enq->m_niConflictIndex.end());

	int iQuints = enq->m_nplcQuints.size();
	int flag;
	for (int i = 0; i < iQuints; i ++)
	{
		if (enq->m_nplcQuints[i].per <= DENYB)
		{
			flag = 1;
			for (int j = 0; j < niTargetPoliciesShort.size(); j ++)
			{
				if (i == niTargetPoliciesShort[j])
				{
					m_niTargetPolicies.push_back(1);
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				m_niTargetPolicies.push_back(0);
			}
		}
	}
	return;
}

void CVisualPCDGraphDlg::DrawGraph(HDC hDC)
{

	m_strFileALocation = pGraphParentThis->m_cstrFileALocation;
	m_strFileBLocation = pGraphParentThis->m_cstrFileBLocation;
	m_parser = new XMLParser(m_strFileALocation, m_strFileBLocation);

	m_nstrSubjects = m_parser->m_nstrSubjects;
	m_nstrResources = m_parser->m_nstrResources;
	m_iSub = m_nstrSubjects.size();
	m_iRes = m_nstrResources.size();

	m_nplcQuints = m_parser->m_nplcQuints;
	m_iQuints = m_nplcQuints.size();

	HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDC, hBrushWhite);

	m_pArrowSolid.nWidth = 7;
	m_pArrowSolid.fTheta = 0.6f;
	m_pArrowSolid.bFill = TRUE;

	m_pArrowHollow.nWidth = 7;
	m_pArrowHollow.fTheta = 0.6f;
	m_pArrowHollow.bFill = FALSE;

	POINT pt;
	for (int i = 0; i < m_iSub; i ++)
	{
		pt.x = GetCircleX(120, 270, 100, m_iSub, i);
		pt.y = GetCircleY(120, 270, 100, m_iSub, i);
		m_niSubjects.push_back(pt);
	}
	for (i = 0; i < m_iRes; i ++)
	{
		pt.x = GetCircleX(640, 270, 100, m_iRes, i);
		pt.y = GetCircleY(640, 270, 100, m_iRes, i);
		m_niResources.push_back(pt);
	}

	

	HFONT hFont = CreateFont(12, 6, 0, 0, 10, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, "SimSun");
	HFONT hOldFont = (HFONT) SelectObject(hDC, hFont);

	HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPenBlackBold = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN hPenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN hPenBlue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	HPEN hOldPen = (HPEN) SelectObject(hDC, hPenBlack);
	//SetDCPenColor(hDC, RGB(255, 0, 0));

	for (i = 0; i < m_iSub; i ++)
	{
		////////////////////////主体名称////////////////////////
		Ellipse(hDC, m_niSubjects[i].x - 8, m_niSubjects[i].y - 8, m_niSubjects[i].x + m_nstrSubjects[i].length() * 6 + 8, m_niSubjects[i].y + 13 + 8);
		TextOut(hDC, m_niSubjects[i].x, m_niSubjects[i].y, m_nstrSubjects[i].c_str(), m_nstrSubjects[i].length());
	}
	for (i = 0; i < m_iRes; i ++)
	{
		////////////////////////资源名称////////////////////////
		Ellipse(hDC, m_niResources[i].x - 8, m_niResources[i].y - 8, m_niResources[i].x + m_nstrResources[i].length() * 6 + 8, m_niResources[i].y + 13 + 8);
		TextOut(hDC, m_niResources[i].x, m_niResources[i].y, m_nstrResources[i].c_str(), m_nstrResources[i].length());
	}

	SelectObject(hDC, hBrushBlack);
	
	string temp;
	for (i = 0; i < m_iQuints; i ++)
	{
		if (m_nplcQuints[i].per <= DENYB)
		{
			////////////////////////授权策略////////////////////////
// 			temp = "策略";
// 			temp += (itos(m_nplcQuints[i].pol) + "：");
// 			if (m_nplcQuints[i].per == PERMITA)
// 				temp += "允许";
// 			else
// 				temp += "拒绝";
			temp = "Policy ";
			temp += (itos(m_nplcQuints[i].pol) + "：");
			if (m_nplcQuints[i].per == PERMITA)
				temp += "Permit ";
			else
				temp += "Deny ";
			temp += m_nplcQuints[i].act;
			if (i != 0)
			{
				if (m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x == m_niSubjects[m_parser->QuintsToSubjectsNO(i - 1)].x &&
					m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y == m_niSubjects[m_parser->QuintsToSubjectsNO(i - 1)].y &&
					m_niSubjects[m_parser->QuintsToResourcesNO(i)].x == m_niSubjects[m_parser->QuintsToResourcesNO(i - 1)].x &&
					m_niSubjects[m_parser->QuintsToResourcesNO(i)].y == m_niSubjects[m_parser->QuintsToResourcesNO(i - 1)].y)
				{
					TextOut(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x * 0.3 + m_niResources[m_parser->QuintsToResourcesNO(i)].x * 0.7 - 10, 
						m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y * 0.3 + m_niResources[m_parser->QuintsToResourcesNO(i)].y * 0.7 - 6, 
						temp.c_str(), temp.size());
				}
				else
				{
					TextOut(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x * 0.7 + m_niResources[m_parser->QuintsToResourcesNO(i)].x * 0.3 - 10, 
						m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y * 0.7 + m_niResources[m_parser->QuintsToResourcesNO(i)].y * 0.3 - 6, 
						temp.c_str(), temp.size());
				}
			}
			else
			{
				TextOut(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x * 0.7 + m_niResources[m_parser->QuintsToResourcesNO(i)].x * 0.3 - 10, 
					m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y * 0.7 + m_niResources[m_parser->QuintsToResourcesNO(i)].y * 0.3 - 6, 
					temp.c_str(), temp.size());
			}

			if (i == 0)
			{
				SelectObject(hDC, hPenRed);
			}
			else if (m_iTargetPolicy == i)
			{
				SelectObject(hDC, hPenBlue);
			}
			else if (m_niTargetPolicies.size() != 0)
			{
				if (m_niTargetPolicies[i] == 1)
				{
					SelectObject(hDC, hPenBlackBold);
				}
			}
			else
			{
				SelectObject(hDC, hPenBlack);
			}

			::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x + m_nstrSubjects[m_parser->QuintsToSubjectsNO(i)].length() * 6 + 7, 
				m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y + 6, NULL);
			ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(i)].x - 9, m_niResources[m_parser->QuintsToResourcesNO(i)].y + 6, &m_pArrowSolid);
			RECT rect = {m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x + 50 + 20, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y + 6 + 40,
				m_niResources[m_parser->QuintsToResourcesNO(i)].x - 3 + 20, m_niResources[m_parser->QuintsToResourcesNO(i)].y + 6 + 40};
			m_nrctLine.push_back(rect);
			m_nLineDivisor.push_back((int) sqrt((rect.left - rect.right) * (rect.left - rect.right) + (rect.top - rect.bottom) * (rect.top - rect.bottom)));
			m_nLineAddent.push_back(rect.left * rect.bottom - rect.right * rect.top);

			SelectObject(hDC, hPenBlack);

		}
	}

	////////////////////////授权策略0////////////////////////
	//SelectObject(hDC, hPenRed);
	//::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(0)].x + m_nstrSubjects[m_parser->QuintsToSubjectsNO(0)].length() * 6 + 7,
	//	m_niSubjects[m_parser->QuintsToSubjectsNO(0)].y + 6, NULL);
	//ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(0)].x - 9, m_niResources[m_parser->QuintsToResourcesNO(0)].y + 6, &m_pArrowSolid);
	//SelectObject(hDC, hPenBlack);

	for (i = 0; i < m_iQuints; i ++)
	{
		if (m_nplcQuints[i].per == SUB_CONTAIN)
		{
			////////////////////////主体的继承策略////////////////////////
//			temp = "策略";
			temp = "Policy ";
			temp += (itos(m_nplcQuints[i].pol));
			TextOut(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x * 0.6 + m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].x * 0.4 - 5, 
				m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y * 0.6 + m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].y * 0.4, 
				temp.c_str(), temp.size());

			if (i == 0)
			{
				SelectObject(hDC, hPenRed);
			}
			else
			{
				SelectObject(hDC, hPenBlack);
			}
			for (int j = 0; j < m_niSubjectContain.size(); j ++)
			{
				if (m_niSubjectContain[j] == i)
				{
					SelectObject(hDC, hPenBlue);
				}
			}
			

			if (m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y <= m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].y)
			{
				::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x + m_nstrSubjects[m_parser->QuintsToSubjectsNO(i)].length() * 3,
					m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y + 12 + 8, NULL);
				ArrowTo(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].x + m_nstrSubjects[m_parser->QuintsToSubjectsNO2(i)].length() * 3,
					m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].y - 8, &m_pArrowHollow);
			}
			else
			{
				::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x + m_nstrSubjects[m_parser->QuintsToSubjectsNO(i)].length() * 3,
					m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y - 8, NULL);
				ArrowTo(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].x + m_nstrSubjects[m_parser->QuintsToSubjectsNO2(i)].length() * 3,
					m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].y + 12 + 8, &m_pArrowHollow);
			}

			SelectObject(hDC, hPenBlack);

		}
		else if (m_nplcQuints[i].per == RES_CONTAIN)
		{
			////////////////////////资源的继承策略////////////////////////
//			temp = "策略";
			temp = "Policy ";
			temp += (itos(m_nplcQuints[i].pol));
			TextOut(hDC, m_niResources[m_parser->QuintsToResourcesNO2(i)].x * 0.6 + m_niResources[m_parser->QuintsToResourcesNO(i)].x * 0.4 - 5, 
				m_niResources[m_parser->QuintsToResourcesNO2(i)].y * 0.6 + m_niResources[m_parser->QuintsToResourcesNO(i)].y * 0.4, 
				temp.c_str(), temp.size());

			if (i == 0)
			{
				SelectObject(hDC, hPenRed);
			}
			else
			{
				SelectObject(hDC, hPenBlack);
			}
			for (int j = 0; j < m_niResourceContain.size(); j ++)
			{
				if (m_niResourceContain[j] == i)
				{
					SelectObject(hDC, hPenBlue);
				}
			}

			if (m_niResources[m_parser->QuintsToResourcesNO(i)].y >= m_niResources[m_parser->QuintsToResourcesNO2(i)].y)
			{
				::MoveToEx(hDC, m_niResources[m_parser->QuintsToResourcesNO2(i)].x + m_nstrResources[m_parser->QuintsToResourcesNO2(i)].length() * 3,
					m_niResources[m_parser->QuintsToResourcesNO2(i)].y + 12 + 8, NULL);
				ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(i)].x + m_nstrResources[m_parser->QuintsToResourcesNO(i)].length() * 3,
					m_niResources[m_parser->QuintsToResourcesNO(i)].y - 8, &m_pArrowHollow);	
			}
			else
			{
				::MoveToEx(hDC, m_niResources[m_parser->QuintsToResourcesNO2(i)].x + m_nstrResources[m_parser->QuintsToResourcesNO2(i)].length() * 3,
					m_niResources[m_parser->QuintsToResourcesNO2(i)].y - 8, NULL);
				ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(i)].x + m_nstrResources[m_parser->QuintsToResourcesNO(i)].length() * 3,
					m_niResources[m_parser->QuintsToResourcesNO(i)].y + 12 + 8, &m_pArrowHollow);	
			}

			SelectObject(hDC, hPenBlack);
		}
	}

	SelectObject(hDC, hOldPen);
	DeleteObject(hPenBlack);
	DeleteObject(hPenBlackBold);
	DeleteObject(hPenRed);
	DeleteObject(hPenBlue);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrushBlack);
	DeleteObject(hBrushWhite);

	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);

	delete m_parser;
	m_parser = NULL;
}

void CVisualPCDGraphDlg::ChangeGraph(HDC hDC)
{
	string temp;
	HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hPenBlue = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	int bBlue;

	for (int i = 1; i < m_iQuints; i ++)
	{
		if (m_nplcQuints[i].per <= DENYB)
		{
			if (m_iTargetPolicy == i)
			{
				SelectObject(hDC, hPenBlue);
			}

			::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x + 50,
				m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y + 6, NULL);
			ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(i)].x - 3,
				m_niResources[m_parser->QuintsToResourcesNO(i)].y + 6, &m_pArrowSolid);

			if (m_iTargetPolicy == i)
			{
				SelectObject(hDC, hPenBlack);
			}
		}
	}

	SelectObject(hDC, hPenRed);
	::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(0)].x + 50,
		m_niSubjects[m_parser->QuintsToSubjectsNO(0)].y + 6, NULL);
	ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(0)].x - 3,
		m_niResources[m_parser->QuintsToResourcesNO(0)].y + 6, &m_pArrowSolid);
	SelectObject(hDC, hPenBlack);

	for (i = 1; i < m_iQuints; i ++)
	{
		if (m_nplcQuints[i].per == SUB_CONTAIN)
		{
			bBlue = 0;
			for (int j = 0; j < m_niSubjectContain.size(); j ++)
			{
				if (m_niSubjectContain[j] == i)
					bBlue = 1;
			}
			if (bBlue)
			{
				SelectObject(hDC, hPenBlue);
			}

			if (m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y <= m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].y)
			{
				::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x + 25,
					m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y + 12, NULL);
				ArrowTo(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].x + 25,
					m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].y, &m_pArrowHollow);
			}
			else
			{
				::MoveToEx(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO(i)].x + 25,
					m_niSubjects[m_parser->QuintsToSubjectsNO(i)].y, NULL);
				ArrowTo(hDC, m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].x + 25,
					m_niSubjects[m_parser->QuintsToSubjectsNO2(i)].y + 12, &m_pArrowHollow);
			}

			if (bBlue)
			{
				SelectObject(hDC, hPenBlack);
			}
		}
		else if (m_nplcQuints[i].per == RES_CONTAIN)
		{
			bBlue = 0;
			for (int j = 0; j < m_niResourceContain.size(); j ++)
			{
				if (m_niResourceContain[j] == i)
					bBlue = 1;
			}
			if (bBlue)
			{
				SelectObject(hDC, hPenBlue);
			}

			if (m_niResources[m_parser->QuintsToResourcesNO(i)].y >= m_niResources[m_parser->QuintsToResourcesNO2(i)].y)
			{
				::MoveToEx(hDC, m_niResources[m_parser->QuintsToResourcesNO2(i)].x + 25,
					m_niResources[m_parser->QuintsToResourcesNO2(i)].y + 12, NULL);
				ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(i)].x + 25,
					m_niResources[m_parser->QuintsToResourcesNO(i)].y, &m_pArrowHollow);	
			}
			else
			{
				::MoveToEx(hDC, m_niResources[m_parser->QuintsToResourcesNO2(i)].x + 25,
					m_niResources[m_parser->QuintsToResourcesNO2(i)].y, NULL);
				ArrowTo(hDC, m_niResources[m_parser->QuintsToResourcesNO(i)].x + 25,
					m_niResources[m_parser->QuintsToResourcesNO(i)].y + 12, &m_pArrowHollow);	
			}

			if (bBlue)
			{
				SelectObject(hDC, hPenBlack);
			}
		}
	}
}

LRESULT CALLBACK MyMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	if (wParam == WM_LBUTTONDOWN)
	{
		POINT pt;
		RECT rect;
		GetCursorPos(&pt);
		pGraphThis->GetWindowRect(&rect);
		
		pt.x -= rect.left;
		pt.y -= rect.top;

		RECT clipRect = {30, 40, 30 + pGraphThis->m_iGraphX, 40 + pGraphThis->m_iGraphY};

		int temp;
		int pre = 10000;
		vector<RECT>::iterator iter;
		int i = 0;
		int target = -2;
		for (iter = pGraphThis->m_nrctLine.begin(); iter < pGraphThis->m_nrctLine.end(); iter ++)
		{
			temp = abs(((*iter).top - (*iter).bottom) * pt.x + ((*iter).right - (*iter).left) * pt.y + pGraphThis->m_nLineAddent[i]) / pGraphThis->m_nLineDivisor[i];
			if (temp < pre && (pt.x - (*iter).left) * ((*iter).right - pt.x) > 0)
			{
				pre = temp;
				target = i;
			}
			i ++;
		}
		target ++;
		if (target == -1 || pre > 10)
		{
			pGraphThis->m_iTargetPolicy = -1;
			pGraphThis->m_niSubjectContain.clear();
			pGraphThis->m_niResourceContain.clear();
			pGraphThis->InvalidateRect(&clipRect);
			return NULL;
			//CallNextHookEx(pGraphThis->m_hHook, nCode, wParam, lParam);
		}
		else if (pGraphParentThis->m_controler == NULL)
		{
			MessageBox(pGraphThis->m_hWnd, "请首先进行策略冲突检测！", "运行出现错误", MB_OK);
			return NULL;
			//return CallNextHookEx(pGraphThis->m_hHook, nCode, wParam, lParam);
		}
		else if (pGraphParentThis->m_controler->m_strPolicyFileALocation != pGraphThis->m_strFileALocation ||
			pGraphParentThis->m_controler->m_strPolicyFileBLocation != pGraphThis->m_strFileBLocation)
		{
			MessageBox(pGraphThis->m_hWnd, "请重新进行策略冲突检测！", "运行出现错误", MB_OK);
			return NULL;
			//return CallNextHookEx(pGraphThis->m_hHook, nCode, wParam, lParam);
		}

		Enquirer* enq = pGraphParentThis->m_controler->m_enq;
		int iConflictIndex = enq->GetConflictIndex(target);
		if (iConflictIndex == -1)
		{
			pGraphThis->m_iTargetPolicy = -1;
			pGraphThis->m_niSubjectContain.clear();
			pGraphThis->m_niResourceContain.clear();
			pGraphThis->InvalidateRect(&clipRect);
			return CallNextHookEx(pGraphThis->m_hHook, nCode, wParam, lParam);
		}

		pGraphThis->m_iTargetPolicy = target;

		pGraphThis->m_niSubjectContain.clear();
		pGraphThis->m_niSubjectContain.insert(pGraphThis->m_niSubjectContain.end(),
			enq->m_niSubjectContain[iConflictIndex].begin(), enq->m_niSubjectContain[iConflictIndex].end());

		pGraphThis->m_niResourceContain.clear();
		pGraphThis->m_niResourceContain.insert(pGraphThis->m_niResourceContain.end(),
			enq->m_niResourceContain[iConflictIndex].begin(), enq->m_niResourceContain[iConflictIndex].end());

		pGraphThis->InvalidateRect(&clipRect);
		//pGraphThis->ShowGraph();

		//string s = pGraphThis->itos(target);
		//MessageBox(pGraphThis->m_hWnd, s.c_str(), NULL, MB_OK);
	}
	return CallNextHookEx(pGraphThis->m_hHook, nCode, wParam, lParam);

}



BOOL CVisualPCDGraphDlg::OnEraseBkgnd(CDC* pDC) 
{
	HRGN hrgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hrgn);
	HRGN hrgn2 = CreateRectRgn(30, 40, 30 + m_iGraphX, 40 + m_iGraphY);
	CombineRgn(hrgn, hrgn, hrgn2, RGN_DIFF);
	SelectClipRgn(pDC->GetSafeHdc(), hrgn);
	
	int result =  CBitmapDialog::OnEraseBkgnd(pDC);
	SelectClipRgn(pDC->GetSafeHdc(), NULL);
	DeleteObject(hrgn);
	DeleteObject(hrgn2);
	return result;
}
