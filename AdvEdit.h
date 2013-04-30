/***************************************************************************/
/*                        ������CAdvEdit		                           */
/*				 	   (C)CopyRight www.cguage.com		     			   */
/***************************************************************************/

/////////////////////////////////////////////////////////////////////////////
//���ࣺCEdit
//���ܣ�ʵ����3DԲ�Ǳ༭�򣬿��Զ��������С����ɫ���߿�Բ�Ǵ�С���߿���ɫ�ȣ�����
//�Զ����꣬���ö�����껬��Ч��
//���ߣ�C�ϸ�
//		(Email: tangcraig@gmail.com  QQ: 1019714877 blog: www.cguage.com)
//�汾��V0.9(2010��7��12��15:32:41)

//��Ҫ������
// - ���ù��
// void SetCursor(UINT nIDCursor);
// void SetCursor(LPCTSTR lpszCur);
// - ������껬��Ч��
// void SetHoverStyle(int nHoverStyle = FOCUS_DEFAULT, int nHoverFontSize = 0,
// 				   COLORREF clrHoverBkgnd = 0, int nHoverBorderThick = 0);
// 
// void SetGrayTipString(CString strTipStr);	//��ɫ������ʾ
// void SetBorderCorner(CPoint ptBorderCorner);	//����Բ��Բ��
// void SetTextColor(COLORREF clrText);			//����������ɫ
// void SetBkgndColor(COLORREF clrBkgnd);		//���ñ�����ɫ
// - ���ñ߿���ɫ
// void SetBorderColor(COLORREF clrBorderNormal, COLORREF clrBorderHover);
// - ������Ӱ��ɫ
// void SetShadowColor(COLORREF clrInnerShadow, COLORREF clrOutterShadow);
// - �������弰��С
// 	void SetFont(int nPointSize, LPCTSTR lpszFaceName);

/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ADVEDIT_H__9BC7B9B8_C54A_4B57_B105_A6C5F1745B4B__INCLUDED_)
#define AFX_ADVEDIT_H__9BC7B9B8_C54A_4B57_B105_A6C5F1745B4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdvEdit window
//��껬��ʱ��Ч��
enum
{
	FOCUS_DEFAULT,			//Ĭ��Ч����ֻ�б߿���ɫ�仯
	FOCUS_ENLARGE,			//�ı�����		
	FOCUS_BKCOLOR,			//����ɫ�仯
	FOCUS_BORDERTHICK = 4	//�߿��ȱ仯
};

class CAdvEdit : public CEdit
{
// Construction
public:
	CAdvEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvEdit)
	public:
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetCursor(UINT nIDCursor);
	void SetCursor(LPCTSTR lpszCur);
	void SetHoverStyle(int nHoverStyle = FOCUS_DEFAULT, int nHoverFontSize = 0,
		COLORREF clrHoverBkgnd = 0, int nHoverBorderThick = 0);
	void SetGrayTipString(CString strTipStr);
	void SetBorderCorner(CPoint ptBorderCorner);
	void SetTextColor(COLORREF clrText);
	void SetBkgndColor(COLORREF clrBkgnd);
	void SetBorderColor(COLORREF clrBorderNormal, COLORREF clrBorderHover);
	void SetShadowColor(COLORREF clrInnerShadow, COLORREF clrOutterShadow);
	void SetFont();
	void SetFont(int nPointSize, LPCTSTR lpszFaceName);
	virtual ~CAdvEdit();

	// Generated message map functions
public:
	void ResizeWnd();
	//{{AFX_MSG(CAdvEdit)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	HCURSOR m_hCursor;

	int m_nHoverStyle;
	COLORREF m_nHoverBorderThick;
	CString m_strTipStr;
	CPoint m_ptBorderCorner;
	COLORREF m_clrOutterShadow;
	COLORREF m_clrInnerShadow;
	COLORREF m_clrBorderHover;
	COLORREF m_clrBorderNormal;
	COLORREF m_clrBkgnd;
	COLORREF m_clrHoverBkgnd;
	COLORREF m_clrText;
	LPCTSTR m_lpszFaceName;
	int m_nFontSize;
	int m_nHoverFontSize;
	BOOL m_bIsEmpty;
	BOOL m_bModByUsr;
	BOOL m_bHover;
	BOOL m_bAllowTrack;
	CFont m_font;
	CBrush m_brhNull;
	CRect m_rcClient;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVEDIT_H__9BC7B9B8_C54A_4B57_B105_A6C5F1745B4B__INCLUDED_)
