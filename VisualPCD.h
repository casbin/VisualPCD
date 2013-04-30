// VisualPCD.h : main header file for the VisualPCD application
//

#if !defined(AFX_VISUALPCD_H__C2B10333_6397_4582_9CC0_4CCEB3F49BF7__INCLUDED_)
#define AFX_VISUALPCD_H__C2B10333_6397_4582_9CC0_4CCEB3F49BF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVisualPCDApp:
// See VisualPCD.cpp for the implementation of this class
//

class CVisualPCDApp : public CWinApp
{
public:
	CVisualPCDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPCDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVisualPCDApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPCD_H__C2B10333_6397_4582_9CC0_4CCEB3F49BF7__INCLUDED_)
