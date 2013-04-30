// AdvEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "AdvEditDemo.h"
#include "AdvEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvEdit

CAdvEdit::CAdvEdit()
{
	m_brhNull.CreateStockObject(NULL_BRUSH);
	m_bAllowTrack = TRUE;
	m_bHover = TRUE;
	m_bModByUsr = FALSE;
	m_bIsEmpty = TRUE;

	m_nFontSize = 110;
	m_lpszFaceName = _T("����");

	m_clrOutterShadow = RGB(230, 230, 230);
	m_clrInnerShadow = RGB(244, 244, 244);
	m_clrBorderHover = RGB(150, 150, 150);
	m_clrBorderNormal = RGB(192, 192, 192);
	m_clrBkgnd = RGB(255, 255, 255);
	m_clrText  = RGB(0, 0, 0);

	m_ptBorderCorner = CPoint(5, 5);
	m_strTipStr = _T("");
	m_nHoverStyle = 0;

	m_hCursor = NULL;


}

CAdvEdit::~CAdvEdit()
{
}


BEGIN_MESSAGE_MAP(CAdvEdit, CEdit)
	//{{AFX_MSG_MAP(CAdvEdit)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvEdit message handlers

//////////////////////////////////////////////////////////////////////////
//����ѡ��
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//��������
void CAdvEdit::SetFont()
{
	m_nFontSize = 90;
	m_lpszFaceName = "Simsun";
	
	if(m_font.GetSafeHandle())
		m_font.DeleteObject();
	m_font.CreatePointFont(m_nFontSize, m_lpszFaceName);
	CWnd::SetFont(&m_font, FALSE);
}

void CAdvEdit::SetFont(int nPointSize, LPCTSTR lpszFaceName)
{
	m_nFontSize = nPointSize;
	m_lpszFaceName = lpszFaceName;

	ResizeWnd();
}

//////////////////////////////////////////////////////////////////////////
//������ɫ
void CAdvEdit::SetTextColor(COLORREF clrText)
{
	m_clrText = clrText;
}

void CAdvEdit::SetBkgndColor(COLORREF clrBkgnd)
{
	m_clrBkgnd = clrBkgnd;
}

void CAdvEdit::SetBorderColor(COLORREF clrBorderNormal, COLORREF clrBorderHover)
{
	m_clrBorderHover = clrBorderHover;
	m_clrBorderNormal = clrBorderNormal;
}

void CAdvEdit::SetShadowColor(COLORREF clrInnerShadow, COLORREF clrOutterShadow)
{
	m_clrOutterShadow = clrOutterShadow;
	m_clrInnerShadow = clrInnerShadow;
}

//////////////////////////////////////////////////////////////////////////
//����Բ�Ǳ߿�Բ�Ǵ�С
void CAdvEdit::SetBorderCorner(CPoint ptBorderCorner)
{
	m_ptBorderCorner = ptBorderCorner;
}

//////////////////////////////////////////////////////////////////////////
//�ı����ɫ������ʾ
void CAdvEdit::SetGrayTipString(CString strTipStr)
{
	m_strTipStr = strTipStr;

	SetWindowText(strTipStr);
}

//////////////////////////////////////////////////////////////////////////
//�����ڵõ�����֮����ֵ���ʽ
void CAdvEdit::SetHoverStyle(int nHoverStyle/* = FOCUS_DEFAULT*/, int nHoverFontSize/* = 0*/,
		COLORREF clrHoverBkgnd/* = 0*/, int nHoverBorderThick/* = 0*/)
{
	
	m_nHoverStyle = nHoverStyle;

	if(!nHoverStyle)
		return;

	if(nHoverStyle & FOCUS_ENLARGE)
		m_nHoverFontSize = nHoverFontSize;

	if(nHoverStyle & FOCUS_BKCOLOR)
		m_clrHoverBkgnd = clrHoverBkgnd;

	if(nHoverStyle & FOCUS_BORDERTHICK)
		m_nHoverBorderThick = nHoverBorderThick;
}

//////////////////////////////////////////////////////////////////////////
//���ù��
void CAdvEdit::SetCursor(LPCTSTR lpszCur)
{
	m_hCursor = ::LoadCursorFromFile(lpszCur);
}

void CAdvEdit::SetCursor(UINT nIDCursor)
{
	m_hCursor = ::LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDCursor));
}


/*���¶�ʧ����*/

//DEL BOOL CAdvEdit::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	if(dwStyle & WS_BORDER)
//DEL 		dwStyle |= ~ WS_BORDER;
//DEL 
//DEL 
//DEL 	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//DEL }

//DEL BOOL CAdvEdit::PreCreateWindow(CREATESTRUCT& cs) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	if(cs.style & WS_BORDER)
//DEL 		cs.style |= ~ WS_BORDER;
//DEL 
//DEL 	return CEdit::PreCreateWindow(cs);
//DEL }

//////////////////////////////////////////////////////////////////////////
//ȡ������߶ȣ����أ��������༭���С����Ӧ
void CAdvEdit::ResizeWnd()
{
	//�����ֺš�����
	if(m_font.GetSafeHandle())
		m_font.DeleteObject();
	
	m_font.CreatePointFont(m_nFontSize, m_lpszFaceName);
	CWnd::SetFont(&m_font, FALSE);
	
	//ȡ������߶ȣ����أ��������༭���С����Ӧ
	LOGFONT lf;
	m_font.GetLogFont(&lf);
	TRACE("lf.lfHeight : %d\n", lf.lfHeight);//lf.lfHeight�Ǹ���ֵŶ
	
	GetClientRect(&m_rcClient);
	
	int nBottomPos;
	if(GetStyle() & ES_MULTILINE)
	{
		int nLineH = m_rcClient.top - lf.lfHeight;//��lf.lfHeight��Ч�ڼ������ֵ
		nBottomPos = nLineH * (m_rcClient.Height() / nLineH);
	}
	else
		nBottomPos = m_rcClient.top - lf.lfHeight;
	
	m_rcClient.SetRect(m_rcClient.left, m_rcClient.top, m_rcClient.right, 
		nBottomPos);
	
	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, m_rcClient.Width(), m_rcClient.Height(), 
		SWP_NOMOVE | SWP_NOZORDER);
}


void CAdvEdit::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CEdit::PreSubclassWindow();
	
	SetFont();
	//m_font.CreatePointFont(m_nFontSize, m_lpszFaceName);
	ResizeWnd();

//����һ�����⣬��������������֮������Ƕ������ԣ���SetRect�ƶ��ɱ༭��Χʱ��Ч

/*���±�֤���ǲ����еģ���˵�༭���WS_BORDER����ֻ���ڴ�����ʱ�����*/

//	ModifyStyle(WS_BORDER, 0);	

// 	long style = GetWindowLong(m_hWnd, GWL_STYLE);
// 	style |= ~WS_BORDER;
//  SetWindowLong(m_hWnd, GWL_STYLE, style); 
}

HBRUSH CAdvEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if((m_nHoverStyle & FOCUS_BKCOLOR) && m_bHover)
		pDC->SetBkColor(m_clrHoverBkgnd);
	else
		pDC->SetBkColor(m_clrBkgnd);

	//if(m_bIsEmpty)
	//	pDC->SetTextColor(RGB(0, 0, 0));
	//else
	//	pDC->SetTextColor(m_clrText);
// 
// 	if((GetStyle() & ES_PASSWORD) && !m_bHover)
// 		pDC->DrawText("����������", m_rcClient, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	return m_brhNull;//����OnEraseBkgnd���Ķ������ܹ���ʾ
}

//////////////////////////////////////////////////////////////////////////
//����������Ӱ
BOOL CAdvEdit::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	//if(!m_bHover)
	{
		CBrush brhInnerShadow, brhOutterShadow;
		brhInnerShadow.CreateSolidBrush(m_clrInnerShadow);
		brhOutterShadow.CreateSolidBrush(m_clrOutterShadow);

		CBrush* pOldBrh = pDC->SelectObject(&brhOutterShadow);
		pDC->SelectStockObject(NULL_PEN);
		
		CRect rcShadow = m_rcClient;
		rcShadow.InflateRect(3, 3);
		
	//����Ӱ
		rcShadow.OffsetRect(3, 3);
		pDC->RoundRect(&rcShadow, m_ptBorderCorner);
		
	//����Ӱ
		pDC->SelectObject(&brhInnerShadow);
		rcShadow.OffsetRect(-3, -3);
		pDC->RoundRect(&rcShadow, m_ptBorderCorner);
		
	//�ɱ༭����
		CBrush brhEdit;
		brhEdit.CreateSolidBrush(m_clrBkgnd);
		pDC->SelectObject(&brhEdit);	
		pDC->Rectangle(&m_rcClient);


		pDC->SelectObject(pOldBrh);
	}


//��ԵԲ�ǿ�

	CPen pen;
	if(m_bHover)
	{
		pen.CreatePen(PS_SOLID, (m_nHoverStyle & FOCUS_BORDERTHICK) ? 
			m_nHoverBorderThick : 1, m_clrBorderHover);
	}
	else
		pen.CreatePen(PS_SOLID, 1, m_clrBorderNormal);

	pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);

	CRect rcBorder = m_rcClient;
	rcBorder.InflateRect(3, 3);

	pDC->RoundRect(&rcBorder, m_ptBorderCorner);


	//����־�Ŵ�
	int nTmp = m_nFontSize;
	// 	SetFont(((m_nHoverStyle & FOCUS_ENLARGE) && m_bHover) ? 
	// 		m_nHoverFontSize : m_nFontSize, m_lpszFaceName);
	
	if(m_nHoverStyle & FOCUS_ENLARGE)
	{
		if(m_bHover)
			SetFont(m_nHoverFontSize, m_lpszFaceName);
		else
			SetFont(m_nFontSize, m_lpszFaceName);
	}

	m_nFontSize = nTmp;
	
// 	TRACE("(m_nHoverStyle & FOCUS_ENLARGE):%d, m_bHover : %d \n", 
// 		(m_nHoverStyle & FOCUS_ENLARGE), m_bHover);
	TRACE("m_nHoverFontSize : %d, m_nFontSize : %d \n", m_nHoverFontSize, m_nFontSize);

	return CEdit::OnEraseBkgnd(pDC);
}

/*�������滭�߿�����ܴ���*/

//////////////////////////////////////////////////////////////////////////
//���߿�
//DEL void CAdvEdit::OnPaint() 
//DEL {
//DEL 	CPaintDC dc(this); // device context for painting
//DEL 	
//DEL 	// TODO: Add your message handler code here
//DEL 	CPen pen(PS_SOLID, 1, RGB(192, 192, 192));
//DEL //	CPen pen(PS_SOLID, 1, RGB(150, 150, 150));
//DEL 	CPen* pOldPen = dc.SelectObject(&pen);
//DEL 	dc.SelectStockObject(NULL_BRUSH);
//DEL 
//DEL 	Default();
//DEL 	
//DEL 	CRect rcBorder = m_rcClient;
//DEL //	rcBorder.OffsetRect(5, 5);
//DEL 	rcBorder.InflateRect(3, 3);
//DEL 
//DEL 	dc.RoundRect(&rcBorder, CPoint(5, 5));
//DEL 	dc.SelectObject(pOldPen);
//DEL 
//DEL 	// Do not call CEdit::OnPaint() for painting messages
//DEL }

//����������ʾ
//DEL void CAdvEdit::OnPaint() 
//DEL {
//DEL 	CPaintDC dc(this); // device context for painting
//DEL 	
//DEL 	// TODO: Add your message handler code here
//DEL 	if((GetStyle() & ES_PASSWORD) && !m_bHover && m_bIsEmpty)
//DEL 	{
//DEL 		dc.SetTextColor(RGB(192, 192, 192));
//DEL 		dc.DrawText("����������", m_rcClient, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
//DEL 	}
//DEL 	// Do not call CEdit::OnPaint() for painting messages
//DEL 
//DEL }

void CAdvEdit::OnNcPaint() 
{
	// TODO: Add your message handler code here
	CWindowDC dc(this);
	//Invalidate();
	if((GetStyle() & ES_PASSWORD) && !m_bHover && m_bIsEmpty)
 	{
 		dc.SetTextColor(RGB(192, 192, 192));
 		dc.DrawText("����������", m_rcClient, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
 	}
	// Do not call CEdit::OnNcPaint() for painting messages
}

//////////////////////////////////////////////////////////////////////////
//���е�״̬

void CAdvEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_hCursor)
		::SetCursor(m_hCursor);

	if(m_bAllowTrack)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 1;
		tme.hwndTrack = m_hWnd;

		_TrackMouseEvent(&tme);
		m_bAllowTrack = FALSE;
	}


	CEdit::OnMouseMove(nFlags, point);
}

LRESULT CAdvEdit::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bHover = TRUE;
	//Invalidate();

	return 0;
}

LRESULT CAdvEdit::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	/*
	m_bHover = FALSE;
	Invalidate();
	
	m_bAllowTrack = TRUE;

	CWnd* pWnd =this->GetParent();
	
	CRect rcTmp = m_rcClient;
	rcTmp.OffsetRect(3, 3);
	this->ClientToScreen(&rcTmp);
	pWnd->ScreenToClient(&rcTmp);
	pWnd->InvalidateRect(&rcTmp);

	pWnd->UpdateWindow();

//	pWnd->Invalidate();
//  pWnd->UpdateWindow();
//  pWnd->InvalidateRect(&m_rcClient); */

	m_bHover = TRUE;
	Invalidate();
	return 0;
}



void CAdvEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	// TODO: Add your message handler code here
	//if(m_bIsEmpty)
	//{
	//	m_bModByUsr = FALSE;
	//	SetWindowText("");
	//}

}

void CAdvEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	// TODO: Add your message handler code here
	//if(m_bIsEmpty)
	//{
	//	m_bModByUsr = FALSE;
	//	SetWindowText(m_strTipStr);
	//}
}


//////////////////////////////////////////////////////////////////////////
//����ȷ��������Ϊ�ķ�ʽ��OnChar�ֶ������״̬��
void CAdvEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_bModByUsr = TRUE;//����������ͨ�����루������������SetWindowText��ɵ�TextChange��

	CString strInput;
	GetWindowText(strInput);
	if(strInput.GetLength() < 2)
		Invalidate();

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

//�����ǡ��û����롱Ϊ�յ����
void CAdvEdit::OnChange() 
{
	// TODO: Add your control notification handler code here
	if(m_bModByUsr)//Ϊ���������ϵ���SetWindowText��ɵ�Change
	{
		CString strText;
		GetWindowText(strText);

		m_bIsEmpty = strText.IsEmpty();
	}
}


